#include <wawo/net/socket_pipeline.hpp>
#include <wawo/net/socket.hpp>

namespace wawo { namespace net {

	socket_pipeline::socket_pipeline(WWRP<socket> const& so)
		:SO(so)
	{
	}

	socket_pipeline::~socket_pipeline()
	{}

	void socket_pipeline::init()
	{
		WWRP<socket_handler_head> h = wawo::make_ref<socket_handler_head>();
		m_head = wawo::make_ref<socket_handler_context>(WWRP<socket_pipeline>(this), h);

		WWRP<socket_handler_tail> t = wawo::make_ref<socket_handler_tail>();
		m_tail = wawo::make_ref<socket_handler_context>(WWRP<socket_pipeline>(this), t);

		m_head->P = NULL;
		m_head->N = m_tail;

		m_tail->P = m_head;
		m_tail->N = NULL;
	}

	void socket_pipeline::deinit()
	{
		SO = NULL;
		WWRP<socket_handler_context> h = m_tail;

		while ( h != NULL ) {
			h->PIPE = NULL;
			h->N = NULL;

			WWRP<socket_handler_context> TMP = h->P;
			h->P = NULL;
			h = TMP;
		}
	}
}}