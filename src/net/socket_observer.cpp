#include <wawo/net/observer_impl/select.hpp>

#if WAWO_ISGNU
#include <wawo/net/observer_impl/epoll.hpp>
#endif

#ifdef WAWO_ENABLE_WCP
#include <wawo/net/observer_impl/wpoll.hpp>
#endif

#include <wawo/net/socket_observer.hpp>
#include <wawo/net/socket.hpp>

namespace wawo { namespace net {

	void socket_observer::_alloc_impl() {
		WAWO_ASSERT(m_impl == NULL);

		switch (m_polltype) {
		case T_SELECT:
		{
			m_impl = new observer_impl::select();
			WAWO_ALLOC_CHECK(m_impl, sizeof(observer_impl::select));
		}
		break;
#if WAWO_ISGNU
		case T_EPOLL:
		{
			m_impl = new observer_impl::epoll();
			WAWO_ALLOC_CHECK(m_impl, sizeof(observer_impl::epoll));
		}
		break;
#endif

#ifdef WAWO_ENABLE_WCP
		case T_WPOLL:
		{
			m_impl = new observer_impl::wpoll();
			WAWO_ALLOC_CHECK(m_impl, sizeof(observer_impl::wpoll));
		}
		break;
#endif
		default:
			{
				WAWO_THROW("invalid poll type");
			}
		}

	}

	void socket_observer::_dealloc_impl() {
		WAWO_ASSERT(m_impl != NULL);
		WAWO_DELETE(m_impl);
	}

	socket_observer::socket_observer(u8_t const& type ) :
		m_impl(NULL),
		m_ops_mutex(),
		m_ops(),
		m_polltype(type)
	{
	}

	socket_observer::~socket_observer() {
		WAWO_ASSERT( m_impl == NULL );
	}

	void socket_observer::init() {
		WAWO_ASSERT(m_impl == NULL);
		_alloc_impl();
		WAWO_ASSERT( m_impl != NULL );
		m_impl->init();

		WAWO_ASSERT(m_ticker == NULL);
		m_ticker = wawo::make_shared<wawo::thread::fn_ticker>(std::bind(&socket_observer::update, this));
		observer_ticker::instance()->schedule(m_ticker);
	}
	void socket_observer::deinit() {

		WAWO_ASSERT(m_ticker != NULL);
		observer_ticker::instance()->deschedule(m_ticker);

		{
			lock_guard<spin_mutex> oplg( m_ops_mutex );
			while(m_ops.size()) {
				m_ops.pop();
			}
		}

		WAWO_ASSERT( m_impl != NULL );
		m_impl->deinit();

		_dealloc_impl();
		WAWO_ASSERT(m_impl == NULL);
	}

	void socket_observer::update() {
		WAWO_ASSERT( m_impl != NULL );
		_process_ops();
		m_impl->check_ioe();
	}

	void socket_observer::_process_ops() {
		if( m_ops.empty() ) {
			return ;
		}

		WAWO_ASSERT( m_impl != NULL );

		lock_guard<spin_mutex> lg(m_ops_mutex);
		while( !m_ops.empty() ) {
			event_op op = m_ops.front();
			m_ops.pop();

			switch( op.op ) {
			case OP_WATCH:
				{
					m_impl->watch(op.flag, op.fd,op.cookie, op.fn, op.err);
				}
				break;
			case OP_UNWATCH:
				{
					m_impl->unwatch(op.flag, op.fd);
				}
				break;
			}
		}
	}

	void observer::watch(u8_t const& flag, int const& fd, WWRP<ref_base> const& cookie, fn_io_event const& fn, fn_io_event_error const& err)
	{
		m_default->watch(flag, fd, cookie, fn , err );
	}

	void observer::unwatch(u8_t const& flag, int const& fd)
	{
		m_default->unwatch(flag, fd);
	}

#ifdef WAWO_ENABLE_WCP
	void observer::wcp_watch(u8_t const& flag, int const& fd, WWRP<ref_base> const& cookie, fn_io_event const& fn, fn_io_event_error const& err)
	{
		m_wcp->watch(flag, fd, cookie, fn, err);
	}
	void observer::wcp_unwatch(u8_t const& flag, int const& fd)
	{
		m_wcp->unwatch(flag, fd);
	}
#endif

	namespace observer_impl {
		void io_select_task::run() {
			WAWO_ASSERT(ctx != NULL);
			if (ctx->poll_type == T_SELECT) {
				switch (id) {
				case IOE_READ:
				{
					lock_guard<spin_mutex> lg_ctx(ctx->r_mutex);
					WAWO_ASSERT(ctx->r_state == S_READ_POSTED);
					ctx->r_state = S_READING;
					task::run();
					ctx->r_state = S_READ_IDLE;
				}
				break;
				case IOE_WRITE:
				{
					lock_guard<spin_mutex> lg_ctx(ctx->r_mutex);
					WAWO_ASSERT(ctx->w_state == S_WRITE_POSTED);
					ctx->w_state = S_WRITING;
					task::run();
					ctx->w_state = S_WRITE_IDLE;
				}
				break;
				default:
				{
					WAWO_THROW("unknown ioe id");
				}
				break;
				}
			}
			else {
				task::run();
			}
		}
	}
}}