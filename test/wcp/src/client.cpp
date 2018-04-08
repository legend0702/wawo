
#include <wawo.h>
#include "shared.hpp"

class client_req_handler:
	public wawo::net::channel_inbound_handler_abstract,
	public wawo::net::channel_activity_handler_abstract
{
	int transfer_state;
	wawo::byte_t* file_content;
	WWSP<wawo::packet> received_packet;
	wawo::u32_t filelen;

	WWSP<wawo::packet> tmp;

public:
	client_req_handler():
		file_content(0)
	{}
	~client_req_handler() {
		::free(file_content);
	}

	void connected(WWRP<wawo::net::channel_handler_context> const& ctx) {

		#if TEST_FILE<8
			FILE* fp = fopen("../FILE_7", "rb");
		#elif TEST_FILE<63
		FILE* fp = fopen("../FILE_63", "rb");
		#else
		FILE* fp = fopen("../FILE", "rb");
		#endif

		WAWO_ASSERT(fp != NULL);
		//long begin = ftell(fp);
		int seekrt = fseek(fp, 0L, SEEK_END);
		long end = ftell(fp);
		int seekbeg = fseek(fp, 0L, SEEK_SET);
		(void)seekrt;
		(void)seekbeg;

		wawo::u32_t flen = end;
		file_content = new wawo::byte_t[flen];
		::size_t rbytes = fread((char*)file_content, 1, flen, fp);
		int fclosert = fclose(fp);

		received_packet = wawo::make_shared < wawo::packet>(flen);
		transfer_state = wcp_test::C_REQUEST;
		tmp = wawo::make_shared < wawo::packet>(flen);

		WWSP<wawo::packet> outp = wawo::make_shared<wawo::packet>();
		outp->write<wawo::u8_t>(wcp_test::C_TRANSFER_FILE);

		int sndrt = ctx->write(outp);
		WAWO_ASSERT(sndrt == wawo::OK);
		transfer_state = wcp_test::C_RECEIVE_HEADER;
	}

	void read(WWRP<wawo::net::channel_handler_context> const& ctx, WWSP<wawo::packet> const& income) {

		if (tmp->len()) {
			income->write_left(tmp->begin(), tmp->len() );
			tmp->reset();
		}

_CHECK:
		switch (transfer_state) {
		case wcp_test::C_REQUEST:
			{
				WWSP<wawo::packet> outp = wawo::make_shared<wawo::packet>();
				outp->write<wawo::u8_t>(wcp_test::C_TRANSFER_FILE);

				int sndrt = ctx->write(outp);
				WAWO_ASSERT(sndrt == wawo::OK);
				transfer_state = wcp_test::C_RECEIVE_HEADER;
				goto _CHECK;
			}
			break;

		case wcp_test::C_RECEIVE_HEADER:
			{
				if (income->len() >= (sizeof(wawo::u8_t) + sizeof(wawo::u32_t))) {
					wawo::u8_t cmd = income->read<wawo::u8_t>();
					WAWO_ASSERT(cmd == wcp_test::C_TRANSFER_FILE_HEADER);

					filelen = income->read<wawo::u32_t>();
					transfer_state = wcp_test::C_RECEIVE_CONTENT;
					goto _CHECK;
				}
				tmp = income;
			}
			break;
		case wcp_test::C_RECEIVE_CONTENT:
			{
				if (income->len() >= filelen) {
					received_packet->write(income->begin(), filelen);
					income->skip(filelen);
					transfer_state = wcp_test::C_RECEIVE_DONE;
					goto _CHECK;
				}
				tmp = income;
			}
			break;
		case wcp_test::C_RECEIVE_DONE:
			{
				if (wawo::strncmp((char*)file_content, (char*)received_packet->begin(), filelen) != 0) {
					WAWO_ASSERT("file transfer failed");
				}

#if FAST_TRANSFER
				transfer_state = wcp_test::C_RECEIVE_HEADER;
#else
				transfer_state = wcp_test::C_REQUEST;
#endif
				received_packet->reset();

				goto _CHECK;
			}
			break;
		}
	}

};


int main(int argc, char** argv) {

	wawo::app _app;

	wawo::net::socketaddr raddr;
	raddr.so_family = wawo::net::F_AF_INET;

	if (argc == 2) {
		raddr.so_type = wawo::net::T_STREAM;
		raddr.so_protocol = wawo::net::P_TCP;
	} else {
		raddr.so_type = wawo::net::T_DGRAM;
		raddr.so_protocol = wawo::net::P_WCP;
	}

	raddr.so_address = wawo::net::address("127.0.0.1", 32310);

	WWRP<wawo::net::socket> so = wawo::make_ref<wawo::net::socket>(sbc, raddr.so_family, raddr.so_type, raddr.so_protocol);

	int openrt = so->open();
	WAWO_RETURN_V_IF_NOT_MATCH(openrt, openrt == wawo::OK);

	WWRP < wawo::net::channel_handler_abstract > h = wawo::make_ref<client_req_handler>();
	so->pipeline()->add_last(h);

	int rt = so->async_connect(raddr.so_address);
	WAWO_RETURN_V_IF_NOT_MATCH(rt, rt == wawo::OK);

	_app.run_for();
	return wawo::OK;
}