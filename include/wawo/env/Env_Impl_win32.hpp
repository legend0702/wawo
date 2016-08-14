#ifndef _WAWO_ENV_IMPL_WIN32_HPP_
#define _WAWO_ENV_IMPL_WIN32_HPP_

#include <wawo/core.h>
#include <iphlpapi.h>
#include <wawo/log/LoggerManager.h>

#pragma comment(lib, "IPHlpApi.lib")
namespace wawo { namespace env {

	class Env_Impl {

	public:
		Env_Impl() {
		}

		~Env_Impl() {
		}
		//return the ip count if success, and fill in parameter<ips> with local iplist
		int GetLocalIpList( std::vector<wawo::net::AddrInfo>& addrs ) {

			char _buffer[1024]= {0};
			DWORD _buffer_len = 1024;

			ULONG adapter_address_buffer_size = 1024*32; //20kb

			IP_ADAPTER_ADDRESSES* adapter_address(NULL);
			IP_ADAPTER_ADDRESSES* original_address(NULL);
			IP_ADAPTER_ADDRESSES* adapter(NULL);

			adapter_address = (IP_ADAPTER_ADDRESSES*) malloc(adapter_address_buffer_size);
			original_address = adapter_address; //for free

			WAWO_NULL_POINT_CHECK( adapter_address );
			ULONG flags = GAA_FLAG_SKIP_ANYCAST
				| GAA_FLAG_SKIP_MULTICAST
				| GAA_FLAG_SKIP_DNS_SERVER
				| GAA_FLAG_SKIP_FRIENDLY_NAME
				;

			flags = GAA_FLAG_SKIP_ANYCAST;
			DWORD error = ::GetAdaptersAddresses(AF_UNSPEC,flags,NULL, adapter_address, &adapter_address_buffer_size);

			if( ERROR_SUCCESS != error ) {
				free(original_address);
				original_address = NULL;
				WAWO_WARN("[ENV]::GetAdaptersAddresses() failed, error: %d", error );
				return wawo::GetLastErrno() ;
			}

			while( adapter_address ) {
		
				//WAWO_DEBUG("[ENV]ip adress info, \n%s, %.2x-%.2x-%.2x-%.2x-%.2x-%.2x: \n", 
				//	adapter_address->FriendlyName,
				//	adapter_address->PhysicalAddress[0],adapter_address->PhysicalAddress[1],
				//	adapter_address->PhysicalAddress[2],adapter_address->PhysicalAddress[3],
				//	adapter_address->PhysicalAddress[4],adapter_address->PhysicalAddress[5]
				//);

				PIP_ADAPTER_UNICAST_ADDRESS pUnicast = adapter_address->FirstUnicastAddress;
				IP_ADAPTER_DNS_SERVER_ADDRESS* pDnsServer = adapter_address->FirstDnsServerAddress;

				if( pDnsServer ) {
					sockaddr_in* sa_in = (sockaddr_in*) pDnsServer->Address.lpSockaddr;
					memset(_buffer, 0,_buffer_len);
					//WAWO_DEBUG("[ENV]dns: %s", inet_ntop( AF_INET, &(sa_in->sin_addr), _buffer, _buffer_len ) );
				}

				if(adapter_address->OperStatus == IfOperStatusUp) {
					//WAWO_DEBUG("[ENV]interface up");
				} else {
					WAWO_WARN("[ENV]interface down");
				}

				int i=0;
				for( ; pUnicast != NULL;i++ ) {
					if( pUnicast->Address.lpSockaddr->sa_family == AF_INET ) {
						sockaddr_in* sa_in = (sockaddr_in*)(pUnicast->Address.lpSockaddr) ;
						memset(_buffer, 0,_buffer_len);
						::inet_ntop(AF_INET, &(sa_in->sin_addr), _buffer, _buffer_len) ;
						
						wawo::net::AddrInfo info ;

						info.family= wawo::net::F_AF_INET;
						info.ip = Len_CStr( _buffer, wawo::strlen(_buffer) );

						addrs.push_back( info );

					} else if( pUnicast->Address.lpSockaddr->sa_family == AF_INET6 ) {
						sockaddr_in6* sa_in = (sockaddr_in6*)(pUnicast->Address.lpSockaddr) ;
						memset(_buffer, 0,_buffer_len);
						inet_ntop(AF_INET6, &(sa_in->sin6_addr), _buffer, _buffer_len) ;

						wawo::net::AddrInfo info;

						if( strlen(_buffer) == 128 ) {
							info.family = wawo::net::F_AF_INET6;
							info.ip = Len_CStr( _buffer, wawo::strlen(_buffer) );
							addrs.push_back( info );
						}
					} else {
						WAWO_THROW_EXCEPTION("invalid AF familay");
					}

					pUnicast = pUnicast->Next;
				}
				adapter_address = adapter_address->Next;
			}

			free(original_address);
			return wawo::OK ;
		}

		//refer to https://msdn.microsoft.com/en-us/library/windows/desktop/ms724295(v=vs.85).aspx
		int GetLocalComputerName(Len_CStr& name) {

			TCHAR infoBuf[128];
			DWORD bufSize = 128;

			BOOL rt = GetComputerName(infoBuf, &bufSize );
			WAWO_RETURN_V_IF_NOT_MATCH( WAWO_NEGATIVE(rt), rt != wawo::OK );

			char mbBuf[512] = {0};
			int size = std::wcstombs(mbBuf, infoBuf, 512 );
			if (size == -1) {
				return wawo::GetLastErrno();
			}

			name = Len_CStr(mbBuf, size);
			return wawo::OK;
		}
	};
}}
#endif