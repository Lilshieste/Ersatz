#ifndef _ERSATZ_MOCKED_FUNCTION_1_H
#define _ERSATZ_MOCKED_FUNCTION_1_H

#include <memory>
#include <functional>

#include "ersatz_mocked_function_main.h"
#include "ersatz_mocked_function_info.h"

#include "ersatz_mocked_function_n.h"

__ERSATZ_MOCKED_FUNCTION_DEFINITION__
(
	__ERSATZ_CONCAT__(template <typename R, typename P1>),
	R,
	P1 parameter1,
	P1,
	parameter1
)

#define MOCKABLE1(METHOD_NAME, RETURN_TYPE)			MOCKABLE1_MAIN(METHOD_NAME, RETURN_TYPE,		,				)
#define MOCKABLE1_CONST(METHOD_NAME, RETURN_TYPE)	MOCKABLE1_MAIN(METHOD_NAME, RETURN_TYPE, const	,				)
#define MOCKABLE1_T(METHOD_NAME, RETURN_TYPE)		MOCKABLE1_MAIN(METHOD_NAME, RETURN_TYPE,		,	typename	)
#define MOCKABLE1_CONST_T(METHOD_NAME, RETURN_TYPE)	MOCKABLE1_MAIN(METHOD_NAME, RETURN_TYPE, const	,	typename	)

#define MOCKABLE1_MAIN(METHOD_NAME, RETURN_TYPE, CONST_DECL, TYPENAME_DECL)																											\
			MOCKABLE_BASE(METHOD_NAME, RETURN_TYPE)																																	\
																																													\
			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::ResultType METHOD_NAME(TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter1Type param1) CONST_DECL	\
			{																																										\
				return __##METHOD_NAME.Invoke(std::forward<ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter1Type>(param1));														\
			}

#endif