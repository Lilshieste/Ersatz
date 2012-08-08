#ifndef _ERSATZ_MOCKED_FUNCTION_2_H
#define _ERSATZ_MOCKED_FUNCTION_2_H

#include <memory>
#include <functional>

#include "ersatz_mocked_function_main.h"
#include "ersatz_mocked_function_info.h"

#include "ersatz_mocked_function_n.h"

__ERSATZ_MOCKED_FUNCTION_DEFINITION__
(
	__ERSATZ_CONCAT__(template <typename R, typename P1, typename P2>),
	R,
	__ERSATZ_CONCAT__(P1 parameter1, P2 parameter2),
	__ERSATZ_CONCAT__(P1, P2),
	__ERSATZ_CONCAT__(parameter1, parameter2)
)

#define MOCKABLE2(METHOD_NAME, RETURN_TYPE)			MOCKABLE2_MAIN(METHOD_NAME, RETURN_TYPE,		,				)
#define MOCKABLE2_CONST(METHOD_NAME, RETURN_TYPE)	MOCKABLE2_MAIN(METHOD_NAME, RETURN_TYPE, const	,				)
#define MOCKABLE2_T(METHOD_NAME, RETURN_TYPE)		MOCKABLE2_MAIN(METHOD_NAME, RETURN_TYPE,		,	typename	)
#define MOCKABLE2_CONST_T(METHOD_NAME, RETURN_TYPE)	MOCKABLE2_MAIN(METHOD_NAME, RETURN_TYPE, const	,	typename	)

#define MOCKABLE2_MAIN(METHOD_NAME, RETURN_TYPE, CONST_DECL, TYPENAME_DECL)																								\
			MOCKABLE_BASE(METHOD_NAME, RETURN_TYPE)																														\
																																										\
			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::ResultType METHOD_NAME(																				\
																			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter1Type param1,				\
																			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter2Type param2) CONST_DECL	\
			{																																							\
				return __##METHOD_NAME.Invoke(param1, param2);																											\
			}

#endif