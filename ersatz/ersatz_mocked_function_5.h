#ifndef _ERSATZ_MOCKED_FUNCTION_5_H
#define _ERSATZ_MOCKED_FUNCTION_5_H

#include <memory>
#include <functional>

#include "ersatz_mocked_function_main.h"
#include "ersatz_mocked_function_info.h"

#include "ersatz_mocked_function_n.h"

__ERSATZ_MOCKED_FUNCTION_DEFINITION__
(
	__ERSATZ_CONCAT__(template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>),
	R,
	__ERSATZ_CONCAT__(P1 parameter1, P2 parameter2, P3 parameter3, P4 parameter4, P5 parameter5),
	__ERSATZ_CONCAT__(P1, P2, P3, P4, P5),
	__ERSATZ_CONCAT__(parameter1, parameter2, parameter3, parameter4, parameter5)
)

#define MOCKABLE5(METHOD_NAME, RETURN_TYPE)			MOCKABLE5_MAIN(METHOD_NAME, RETURN_TYPE,		,				)
#define MOCKABLE5_CONST(METHOD_NAME, RETURN_TYPE)	MOCKABLE5_MAIN(METHOD_NAME, RETURN_TYPE, const	,				)
#define MOCKABLE5_T(METHOD_NAME, RETURN_TYPE)		MOCKABLE5_MAIN(METHOD_NAME, RETURN_TYPE,		,	typename	)
#define MOCKABLE5_CONST_T(METHOD_NAME, RETURN_TYPE)	MOCKABLE5_MAIN(METHOD_NAME, RETURN_TYPE, const	,	typename	)

#define MOCKABLE5_MAIN(METHOD_NAME, RETURN_TYPE, CONST_DECL, TYPENAME_DECL)																								\
			MOCKABLE_BASE(METHOD_NAME, RETURN_TYPE)																														\
																																										\
			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::ResultType METHOD_NAME(																				\
																			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter1Type param1,				\
																			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter2Type param2,				\
																			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter3Type param3,				\
																			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter4Type param4,				\
																			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter5Type param5) CONST_DECL	\
			{																																							\
				return __##METHOD_NAME.Invoke(param1, param2, param3, param4, param5);																					\
			}

#endif