
#include "./../../../3rd/http_parser/http_parser.h"
#include <wawo/net/protocol/http.hpp>

namespace wawo { namespace net { namespace protocol { namespace http {

	int parse_url(wawo::len_cstr const& url, url_fields& urlfields, bool is_connect ) {	

		http_parser_url u;
		int rt = http_parser_parse_url(url.cstr, url.len, is_connect, &u);
		WAWO_RETURN_V_IF_NOT_MATCH( WAWO_NEGATIVE(rt), rt == 0);

		if (u.field_set& (1 << UF_SCHEMA)) {
			urlfields.schema = url.substr(u.field_data[UF_SCHEMA].off, u.field_data[UF_SCHEMA].len);
		}

		if (u.field_set& (1 << UF_HOST)) {
			urlfields.host = url.substr(u.field_data[UF_HOST].off, u.field_data[UF_HOST].len);
		}

		if (u.field_set&(1 << UF_PATH)) {
			urlfields.path = url.substr(u.field_data[UF_PATH].off, u.field_data[UF_PATH].len);
		}

		if (u.field_set&(1 << UF_QUERY)) {
			urlfields.query = url.substr(u.field_data[UF_QUERY].off, u.field_data[UF_QUERY].len);
		}
		if (u.field_set&(1 << UF_USERINFO)) {
			urlfields.userinfo = url.substr(u.field_data[UF_USERINFO].off, u.field_data[UF_USERINFO].len);
		}
		if (u.field_set&(1 << UF_FRAGMENT)) {
			urlfields.fragment = url.substr(u.field_data[UF_FRAGMENT].off, u.field_data[UF_FRAGMENT].len);
		}

		if (u.field_set&(1 << UF_PORT)) {
			urlfields.port = u.port;
		}
		else {
			urlfields.port = 80;
		}

		return wawo::OK;
	}

	inline static int _on_message_begin(http_parser* p_ ) {
		parser* p = (parser*)p_->data;
		WAWO_ASSERT(p != NULL);
		p->type = (u8_t)p_->type;
		
		if (p->on_message_begin != NULL) return p->on_message_begin( WWRP<parser>(p) );
		return 0;
	}

	inline static int _on_url(http_parser* p_, const char* data, ::size_t len) {
		parser* p = (parser*)p_->data;
		WAWO_ASSERT(p != NULL);

		switch (p_->type) {
		case HTTP_REQUEST:
			{
				p->type = T_REQ;
			}
			break;
		case HTTP_RESPONSE:
			{
				p->type = T_RESP;
			}
			break;
		}


		switch (p_->method) {
		case HTTP_DELETE:
			{
				p->opt = protocol::http::O_DELETE;
			}
			break;
		case HTTP_GET:
			{
				p->opt = protocol::http::O_GET;
			}
			break;

		case HTTP_HEAD:
			{
				p->opt = protocol::http::O_HEAD;
			}
			break;
		case HTTP_POST:
			{
				p->opt = protocol::http::O_POST;
			}
			break;
		case HTTP_PUT:
			{
				p->opt = protocol::http::O_PUT;
			}
			break;
		case HTTP_CONNECT:
			{
				p->opt = protocol::http::O_CONNECT;
			}
			break;
		case HTTP_OPTIONS:
			{
				p->opt = protocol::http::O_OPTIONS;
			}
			break;
		case HTTP_TRACE:
			{
				p->opt = protocol::http::O_TRACE;
			}
			break;
		default:
			{
				WAWO_ASSERT(!"UNKNOWN HTTP METHOD");
			}
			break;
		}

		p->url = wawo::len_cstr(data, len);
		if (p->on_url) return p->on_url(WWRP<parser>(p), data, len);

		return 0;
	}

	inline static int _on_status(http_parser* p_, char const* data, ::size_t len) {
		parser* p = (parser*)p_->data;
		WAWO_ASSERT(p != NULL);

		WAWO_ASSERT(p_->status_code != 0);
		p->status_code = p_->status_code;
		p->ver.major = p_->http_major;
		p->ver.minor = p_->http_minor;

		if (p->on_status) return p->on_status(WWRP<parser>(p), data, len);
		return 0;
	}

	inline static int _on_header_field(http_parser* p_, char const* data, ::size_t len) {
		parser* p = (parser*)p_->data;
		WAWO_ASSERT(p != NULL);
		if (p->on_header_field) return p->on_header_field(WWRP<parser>(p), data, len);
		return 0;
	}

	inline static int _on_header_value(http_parser* p_, char const* data, ::size_t len) {
		parser* p = (parser*)p_->data;
		WAWO_ASSERT(p != NULL);
		if (p->on_header_value) return p->on_header_value(WWRP<parser>(p), data, len);
		return 0;
	}

	inline static int _on_headers_complete(http_parser* p_) {
		parser* p = (parser*)p_->data;
		WAWO_ASSERT(p != NULL);

		p->ver.major = p_->http_major;
		p->ver.minor = p_->http_minor;

		if (p->on_headers_complete) return p->on_headers_complete(WWRP<parser>(p));
		return 0;
	}

	inline static int _on_body(http_parser* p_, char const* data, ::size_t len) {
		parser* p = (parser*)p_->data;
		WAWO_ASSERT(p != NULL);
		if (p->on_body) return p->on_body( WWRP<parser>(p), data, len);
		return 0;
	}

	inline static int _on_message_complete(http_parser* p_ ) {
		parser* p = (parser*)p_->data;
		WAWO_ASSERT(p != NULL);

		if (p->on_message_complete) return p->on_message_complete(WWRP<parser>(p));
		return 0;
	}

	inline static int _on_chunk_header(http_parser* p_) {
		parser* p = (parser*)p_->data;
		WAWO_ASSERT(p != NULL);
		if (p->on_chunk_header) return p->on_chunk_header(WWRP<parser>(p));
		return 0;
	}

	inline static int _on_chunk_complete(http_parser* p_) {
		parser* p = (parser*)p_->data;
		WAWO_ASSERT(p != NULL);
		if (p->on_chunk_complete) return p->on_chunk_complete(WWRP<parser>(p));
		return 0;
	}

	parser::parser():
		_p(NULL),
		on_message_begin(NULL),
		on_url(NULL),
		on_header_field(NULL),
		on_header_value(NULL),
		on_headers_complete(NULL),
		on_body(NULL),
		on_message_complete(NULL),

		on_chunk_header(NULL),
		on_chunk_complete(NULL)
	{
	}

	parser::~parser() {
		deinit();
	}

	void parser::init(parser_type const& type_ = PARSER_REQ ) {
		WAWO_ASSERT(_p == NULL);
		_p = (http_parser*) ::malloc(sizeof(http_parser));
		WAWO_ALLOC_CHECK(_p, sizeof(http_parser));

		if (type_ == PARSER_REQ) {
			http_parser_init(_p, HTTP_REQUEST);
		}
		else {
			http_parser_init(_p, HTTP_RESPONSE);
		}

		_p->data = this;
	}

	void parser::deinit() {
		if (_p != NULL) ::free(_p); _p = NULL;
	}

	//return number of parsed bytes 
	u32_t parser::parse(char const* const data, u32_t const& len, int& ec) {
		WAWO_ASSERT(_p != NULL);

		static http_parser_settings _settings;
		_settings.on_message_begin = _on_message_begin;
		_settings.on_url = _on_url;
		_settings.on_status = _on_status;
		_settings.on_header_field = _on_header_field;
		_settings.on_header_value = _on_header_value;
		_settings.on_headers_complete = _on_headers_complete;
		_settings.on_body = _on_body;
		_settings.on_message_complete = _on_message_complete;

		_settings.on_chunk_header = _on_chunk_header;
		_settings.on_chunk_complete = _on_chunk_complete;

		size_t nparsed = http_parser_execute(_p, &_settings, data, len);

		ec = _p->http_errno;
		return nparsed;
	}

}}}}