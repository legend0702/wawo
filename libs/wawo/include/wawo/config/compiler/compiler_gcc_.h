#ifndef _CONFIG_COMPILER_WAWO_COMPILER_GCC_H_
#define _CONFIG_COMPILER_WAWO_COMPILER_GCC_H_

namespace wawo { namespace basic_type {

	typedef char						_INT8_		;
	typedef unsigned char				_UINT8_		;

	typedef short int					_INT16_		;
	typedef unsigned short int			_UINT16_	;

	typedef int							_INT32_		;
	typedef unsigned int				_UINT32_	;

	typedef signed long long			_INT64_		;
	typedef unsigned long long			_UINT64_	;

}}

#define WAWO_TLS __thread


#endif