#ifndef _ERSATZ_MOCKED_FUNCTION_0_H
#define _ERSATZ_MOCKED_FUNCTION_0_H

#include <memory>
#include <functional>

#include "ersatz_mocked_function_main.h"
#include "ersatz_mocked_function_info.h"

#include "ersatz_mocked_function_n.h"

__ERSATZ_MOCKED_FUNCTION_DEFINITION__
(
	template <typename R>,
	R,
	,
	,

)

#define MOCKABLE0(METHOD_NAME, RETURN_TYPE)			MOCKABLE0_MAIN(METHOD_NAME, RETURN_TYPE,		,				)
#define MOCKABLE0_CONST(METHOD_NAME, RETURN_TYPE)	MOCKABLE0_MAIN(METHOD_NAME, RETURN_TYPE, const	,				)
#define MOCKABLE0_T(METHOD_NAME, RETURN_TYPE)		MOCKABLE0_MAIN(METHOD_NAME, RETURN_TYPE,		,	typename	)
#define MOCKABLE0_CONST_T(METHOD_NAME, RETURN_TYPE)	MOCKABLE0_MAIN(METHOD_NAME, RETURN_TYPE, const	,	typename	)

#define MOCKABLE0_MAIN(METHOD_NAME, RETURN_TYPE, CONST_DECL, TYPENAME_DECL)								\
			MOCKABLE_BASE(METHOD_NAME, RETURN_TYPE)														\
																										\
			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::ResultType METHOD_NAME() CONST_DECL	\
			{																							\
				return __##METHOD_NAME.Invoke();														\
			}

#endif