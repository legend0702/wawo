#ifndef _WAWO_CONSTANTS_H_
#define _WAWO_CONSTANTS_H_

#include <wawo/config/compiler.h>
#include <limits.h>

namespace wawo {

	namespace limit {
		//
		const i16_t INT8_MIN_V = (-127L - 1) ;
		const i16_t INT16_MIN_V = (-32767L - 1) ;
		const i32_t INT32_MIN_V = (-2147483647L - 1) ;
		const i64_t INT64_MIN_V = (-9223372036854775807LL - 1);

		const i8_t  INT8_MAX_V  = 127L ;
		const i16_t INT16_MAX_V = 32767L ;
		const i32_t INT32_MAX_V = 2147483647L ;
		const i64_t INT64_MAX_V = 9223372036854775807LL;

		const u8_t  UINT8_MAX_V  = 0xffUL ;
		const u16_t UINT16_MAX_V = 0xffffUL ;
		const u32_t UINT32_MAX_V = 0xffffffffUL ;
		const u64_t UINT64_MAX_V = 0xffffffffffffffffULL;
	}

	enum ErrorCodes {

		OK = 0 ,

		E_EPERM								= -1, //operation not permitted
		E_ENOENT							= -2, //no such file or directory
		E_ESRCH								= -3, //no such process
		E_EINTR								= -4, //interrupted system call
		E_EIO								= -5, //I/O error
		E_ENXIO								= -6, //no such device or address
		E_E2BIG								= -7, //Arg list too long
		E_ENOEXEC							= -8, //Exec format error
		E_EBADF								= -9, //Bad file number
		E_ECHILD							= -10, //No child processes
		E_EAGAIN							= -11, //Try again
		E_ENOMEM							= -12, //Out of memory
		E_EACCESS							= -13, //Permission denied
		E_EFAULT							= -14, //Bad address
		E_ENOTBLK							= -15, //Block device required
		E_EBUSY								= -16, //Device or resource busy
		E_EEXIST							= -17, //File exists
		E_EEXDEV							= -18, //Cross-device link
		E_ENODEV							= -19, //No such device
		E_ENOTDIR							= -20, //Not a directory
		E_EISDIR							= -21, //Is a directory
		E_EINVAL							= -22, //Invalid argument
		E_ENFILE							= -23, //File table overflow
		E_EMFILE							= -24, //Too many open files
		E_ENOTTY							= -25, //Not a tty device
		E_ETXTBSY							= -26, //Text file busy
		E_EFBIG								= -27, //File too large
		E_ENOSPC							= -28, //No space left on device
		E_ESPIPE							= -29, //Illegal seek
		E_EROFS								= -30, //Read-only file system
		E_EMLINK							= -31, //Too many links
		E_EPIPE								= -32, //broken pipe
		E_EDOM								= -33, //Math argument out of domain
		E_ERANGE							= -34, //Math result not representable
		E_EDEADLK							= -35, //dead lock wolld occur
		E_ENAMETOOLONG						= -36, //file too long
		E_ENOLCK							= -37, //No record locks available
		E_ENOSYS							= -38, //Function not implemented
		E_ENOTEMPTY							= -39, //dierctory not empty
		E_ELOOP								= -40, //too many symbolic links encountered
		E_EWOULDBLOCK						= -41, // same as EAGAIN
		E_ENOMSG							= -42,//No message of desired type
		E_EIDRM								= -43, //identifier removed
		E_ECHRNG							= -44, //channel number out of range
		E_EL2NSYNC							= -45, //level 2 not synchronized
		E_EL3HLT							= -46, //level 3 halted
		E_EL3RST							= -47, //level3 reset
		E_ELNRNG							= -48, //Link number out of range
		E_EUNATCH							= -49, //Protocol driver not attached
		E_ENOCSI							= -50, //No CSI structure available
		E_EL2HLT							= -51, //Level 2 halted
		E_EBADE								= -52, //Invalid exchange
		E_EBADR								= -53, //Invalid request descriptor
		E_EXFULL							= -54, //Exchange full
		E_ENOANO							= -55, //No anode
		E_EBADRQC							= -56, //Invalid request code
		E_EBADSLT							= -57, //Invalid slot
		E_EDEADLOCK							= -58, //Same as EDEADLK
		E_EBFONT							= -59, //Bad font file format
		E_ENOSTR							= -60, //No data available
		E_ENODATA							= -61, //No data available
		E_ETIME								= -62, //Timer expired
		E_ENOSR								= -63, //Out of streams resources
		E_ENONET							= -64, //machine is not on network
		E_ENOPKG							= -65, //Package not installed
		E_EREMOTE							= -66, //Object is remote
		E_ENOLINK							= -67, //Link has been severed
		E_EADV								= -68, //Advertise error
		E_ESRMNT							= -69, //Srmount error
		E_ECOMM								= -70, //Communication error on send
		E_EPROTO							= -71, //Protocol error
		E_EMULTIHOP							= -72, //Multihop attempted
		E_EDOTDOT							= -73, //RFS specific error
		E_EBADMSG							= -74, //Not a data message
		E_OVERFLOW							= -75, //Value too large for defined data type
		E_ENOTUNIQ							= -76, //Name not unique on network
		E_EBADFD							= -77, //File descriptor in bad state
		E_REMCHG							= -78, //Remote address changed
		E_ELIBACC							= -79, //Cannot access a needed shared library
		E_ELIBBAD							= -80, //Accessing a corrupted shared library
		E_ELIBSCN							= -81, //A .lib section in an .out is corrupted
		E_ELIMAX							= -82, //Linking in too many shared libraries
		E_ELIEXEC							= -83, //Cannot exec a shared library directly
		E_ELIILSEQ							= -84, //Illegal byte sequence
		E_ERESTART							= -85, //Interrupted system call should be restarted
		E_ESTRPIPE							= -86, //Streams pipe error
		E_EUSERS							= -87, //Too many users
		E_ENOTSOCK							= -88, //Socket operation on non-socket
		E_EDESTADDRREQ						= -89, //Destination address required

		E_EMSGSIZE							= -90, //Message too long
		E_EPROTOTYPE						= -91, //Protocol wrong type for socket
		E_ENOPROTOOPT						= -92, //Protocol not available
		E_EPROTONOSUPPORT					= -93, //Protocol not supported
		E_ESOCKTNOSUPPORT					= -94, //Socket type not supported
		E_EOPNOTSUPP						= -95, //Operation not supported on transport
		E_EPFNOSUPPORT						= -96, //Protocol family not supported
		E_EAFNOSUPPORT						= -97, //Address family not supported by protocol
		E_EADDRINUSE						= -98, //Address already in use
		E_EADDRNOTAVAIL						= -99, //Cannot assign requested address
		E_ENETDOWN							= -100, //Network is down
		E_ENETUNREACH						= -101, //Network is unreachable
		E_ENETRESET							= -102, //Network dropped
		E_ECONNABORTED						= -103, //Software caused connection
		E_ECONNRESET						= -104, //Connection reset by
		E_ENOBUFS							= -105, //No buffer space available
		E_EISCONN							= -106, //Transport endpoint
		E_ENOTCONN							= -107, //Transport endpoint
		E_ESHUTDOWN							= -108, //Cannot send after transport
		E_ETOOMANYREFS						= -109, //Too many references
		E_ETIMEOUT							= -110, //Connection timed
		E_ECONNREFUSED						= -111, //Connection refused
		E_EHOSTDOWN							= -112, //Host is down
		E_EHOSTUNREACH						= -113, //No route to host
		E_EALREADY							= -114, //Operation already
		E_EINPROGRESS						= -115, //Operation now in
		E_ESTALE							= -116, //Stale NFS file handle
		E_EUCLEAN							= -117, //Structure needs cleaning
		E_ENOTNAM							= -118, //Not a XENIX-named
		E_ENAVAIL							= -119, //No XENIX semaphores
		E_EISNAM							= -120, //Is a named type file
		E_EREMOTEIO							= -121, //Remote I/O error
		E_EDQUOT							= -122, //Quota exceeded
		E_ENOMEDIUM							= -123, //No medium found
		E_EMEDIUMTYPE						= -124, //Wrong medium type



		// 1---19999, reserved for system call error code (windows)
		E_WSAEINTR						= -10004,// A blocking operation was interrupted by a call to WSACancelBlockingCall.
		E_WSAEBADF						= -10009,// The file handle supplied is not valid.
		E_WSAEMFILE						= -10024,// Too many open sockets.
		E_WSAEWOULDBLOCK				= -10035,// A non-blocking socket operation could not be completed immediately.
		E_WSAEINPROGRESS				= -10036,// A blocking operation is currently executing.
		E_WSAEALREADY					= -10037,// An operation was attempted on a non-blocking socket that already had an operation in progress.
		E_WSAENOTSOCK					= -10038,// An operation was attempted on something that is not a socket.
		E_WSAEMSGSIZE					= -10040,// A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram into was smaller than the datagram itself.
		E_WSAEOPNOTSUPP					= -10045, //The attempted operation is not supported for the type of object referenced.
		E_WSAEADDRINUSE					= -10048, // Only one usage of each socket address (protocol/network address/port) is normally permitted.
		E_WSAEADDRNOTAVAIL				= -10049,// The requested address is not valid in its context.
		E_WSAENETDOWN					= -10050,//A socket operation encountered a dead network.
		E_WSAENETUNREACH				= -10051, // A socket operation was attempted to an unreachable network.
		E_WSAENETRESET					= -10052,// The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress.
		E_WSAECONNABORTED				= -10053,// An established connection was aborted by the software in your host machine.
		E_WSAECONNRESET					= -10054,// An existing connection was forcibly closed by the remote host.
		E_WSAENOBUFS					= -10055,// An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.
		E_WSAEISCONN					= -10056, // A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using a sendto call) no address was supplied.
		E_WSAENOTCONN					= -10057,// A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using a sendto call) no address was supplied.
		E_WSAESHUTDOWN					= -10058, //A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call
		E_WSAETOOMANYREFS				= -10059, //Too many references to some kernel object.
		E_WSAETIMEDOUT					= -10060, //A connection attempt failed because the connected party did not properly respond after a period of time, or established connection failed because connected host has failed to respond.
		E_WSAECONNREFUSED				= -10061, //No connection could be made because the target machine actively refused it.
		E_WSAELOOP						= -10062, //Cannot translate name
		E_WSAEHOSTDOWN					= -10064,// A socket operation failed because the destination host was down
		E_WSAEHOSTUNREACH				= -10065,// A socket operation was attempted to an unreachable host.
		E_WSAEPROCLIM					= -10067,// A Windows Sockets implementation may have a limit on the number of applications that may use it simultaneously.
		E_WSAEUSERS						= -10068,
		E_WSAEDQUOT						= -10069,

		E_WSASYSNOTREADY				= -10091,
		E_WSANOTINITIALISED				= -10093,

		E_WSAEPROVIDERFAILEDINIT		= -10106,
		E_WSASYSCALLFAILURE				= -10107,
		E_WSASERVICE_NOT_FOUND			= -10108,
		E_WSATYPE_NOT_FOUND				= -10109,
		E_WSA_E_NO_MORE					= -10110,
		E_WSA_E_CANCELLED				= -10111,
		E_WSAEREFUSED					= -10112,
		E_WSAHOST_NOT_FOUND				= -11001,
		E_WSATRY_AGAIN					= -11002,
		E_WSANO_RECOVERY				= -11003,
		E_WSANO_DATA					= -11004,
		E_WSA_QOS_RECEIVERS				= -11005,
		E_WSA_QOS_SENDERS				= -11006,

		//internal error
		E_OPERATION_NOT_SUPPORTED	= -20001,
		E_INVALID_OPERATION			= -20002,
		E_INVALID_STATE				= -20003,
		E_NO_TASK_RUNNER_AVAILABLE	= -20004,
		E_INIT_LOG_FILE_FAILED		= -20006,
		E_MALLOC_FAILED				= -20007,
		E_MEMORY_ACCESS_ERROR		= -20008,
		E_MEMORY_ALLOC_FAILED		= -20009,
		E_MEMORY_NEW_FAILED			= -20010,
		E_TRY_AGAIN					= -20011,
		E_UNKNOWN					= -20012,
		E_INVALID_IP_ADDR			= -20013,
		E_INVALID_DATA				= -20014,
		E_DECRYPT_FAILED			= -20015,
		E_ENCRYPT_FAILED			= -20016,

		E_TASK_INVALID_OPERATION							= -21001,
		E_TASK_THREAD_STATE_ERROR							= -21002,
		E_TASK_ASSIGN_TASK_RUNNER_NOT_IN_WAITING_STATE		= -21003,
		E_TASK_ASSIGN_TASK_SIGNAL_FAILED					= -21004,
		E_TASK_RUNNER_BUSY									= -21005,
		E_TASK_RUNNER_INVALID_STATE							= -21006,
		E_TASK_MANAGER_INVALID_STATE						= -21007,
		E_TASK_RUNNER_POOL_INVALID_STATE					= -21008,

		E_SOCKET_IO_SELECT_REACH_LIMIT						= -30001,
		E_SOCKET_IO_SELECT_EVENT_REGISTER_EXISTS			= -30002,
		E_SOCKET_IO_EVENT_UNREGISTER_TARGET_NOT_EXISTS		= -30003,
		E_SOCKET_IO_NOT_NONBLOCKING_SOCKET					= -30005,
		E_SOCKET_IO_INVALID_FALG							= -30006,
		E_SOCKET_REMOTE_GRACE_CLOSE							= -30007,
		E_SOCKET_SEND_BUFFER_FULL							= -30011,
		E_SOCKET_RECV_BUFFER_FULL							= -30012,
		E_SOCKET_SEND_IO_BLOCK								= -30013,
		E_SOCKET_SEND_IO_BLOCK_EXPIRED						= -30015,

		E_SOCKET_RECV_IO_BLOCK								= -30016,
		E_SOCKET_SET_NON_BLOCKING_FAILED					= -30017,
		E_SOCKET_SET_SND_BUFFER_FAILED						= -30018,
		E_SOCKET_SET_RCV_BUFFER_FAILED						= -30019,
		E_SOCKET_INVALID_FAMILY								= -30021,
		E_SOCKET_INVALID_TYPE								= -30022,
		E_SOCKET_INVALID_FD									= -30023,
		E_SOCKET_INVALID_STATE								= -30024,
		E_SOCKET_FORCE_CLOSE								= -30025,

		E_SOCKET_CONNECTING_CANCEL							= -30026,
		E_SOCKET_CONNECTING									= -30027,
		E_SOCKET_NOT_CONNECTED								= -30029,
		E_SOCKET_SEND_BUFFER_NOT_ENOUGH						= -30032,
		E_SOCKET_INVALID_OPERATION							= -30033,
		E_SOCKET_RECEIVED_RST								= -30034,

		E_SOCKET_ASYNC_FLUSH_TIMER_EXPIRED					= -30035,
		E_SOCKET_SEND_BUFFER_EMPTY							= -30037,

		E_SOCKET_SEND_PACKET_EMPTY							= -30040,
		E_SOCKET_ALREADY_CLOSED								= -30041,
		E_SOCKET_PROXY_EXIT									= -30042,
		E_SOCKET_PROXY_INVALID_STATE						= -30043,
		E_SOCKET_UNKNOW_ERROR								= -30045,

		E_SOCKET_RD_SHUTDOWN_ALREADY						= -30046,
		E_SOCKET_WR_SHUTDOWN_ALREADY						= -30047,

		E_SOCKET_PUMP_TRY_AGAIN								= -30048,

		E_TLP_HANDSHAKE_DONE								= -30049,
		E_TLP_INVALID_PACKET								= -30050,
		E_TLP_UNKNOWN_CIPHER								= -30051,
		E_TLP_HANDSHAKE_MESSAGE_CHECK_FAILED				= -30052,
		E_TLP_INVALID_STATE									= -30053,
		E_TLP_HLEN_LEN_READ_FAILED							= -30054,
		E_TLP_TRY_AGAIN										= -30055,

		E_NET_SERVICE_ID_NOT_AVAILABLE						= -40001,
		E_NET_SERVICE_ID_NOT_CONNECTED						= -40002,
		E_NET_SERVICE_ALREADY_CONNECTED						= -40003,
		E_NET_SERVICE_HOST_NOT_FOUND						= -40004,
		E_NET_SERVICE_NOT_CONNECTED							= -40005,
		E_NET_SERVICE_INFO_NOT_FOUND						= -40006,
		//task error

		E_NET_MESSAGE_EXCEED_LENGTH							= -41001,

		E_PEER_NO_SOCKET_ATTACHED							= -42001,
		E_PEER_MESSAGE_ENCODE_FAILED						= -42002,
		E_PEER_INVALID_REQUEST								= -42003,
		E_PEER_PROXY_EXIT									= -42004,
		E_PEER_PROXY_INVALID_STATE							= -42005,



		E_HTTP_REQUEST_MISSING_OPTION						= -43001,
		E_HTTP_MESSAGE_INVALID_TYPE							= -43002,
		E_HTTP_REQUEST_NOT_DONE								= -43003,
		E_HTTP_MISSING_HOST									= -43004,

	};

	typedef i32_t CodeT;

} //endif wawo ns

#endif //END OF WAWO_ERROR_HEADER