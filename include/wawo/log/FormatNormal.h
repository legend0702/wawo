#ifndef _WAWO_FORMAT_NORMAL_H_
#define _WAWO_FORMAT_NORMAL_H_

#include <wawo/core.h>
#include <wawo/log/FormatInterface.h>

namespace wawo { namespace log {
	class FormatNormal: public FormatInterface {
	public:
		int Format( char* const buffer, u32_t const& size, char const* const format , va_list valist );
	};

}}

#endif