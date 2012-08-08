#ifndef __ERSATZ_MOCKED_FUNCTION_MAIN_H
#define __ERSATZ_MOCKED_FUNCTION_MAIN_H

#include "ersatz_mocked_function_metadata.h"

namespace ersatz
{
	template <typename T>
	class MockedFunction;
}

#define MOCKABLE_BASE(METHOD_NAME, RETURN_TYPE)															\
		private:																						\
			ersatz::MockedFunction<RETURN_TYPE> __##METHOD_NAME;										\
			std::string __##METHOD_NAME##_name;															\
																										\
		public:																							\
			ersatz::MockedFunction<RETURN_TYPE>& Setup_##METHOD_NAME()									\
			{																							\
				__##METHOD_NAME.GetFunctionMetadata().FunctionName = #METHOD_NAME;						\
				return __##METHOD_NAME;																	\
			}																							\
																										\
			ersatz::MockedFunction<RETURN_TYPE>& Setup_##METHOD_NAME(std::string file, int lineNumber)	\
			{																							\
				auto metadata = MockedFunctionMetadata(#METHOD_NAME, file, lineNumber);					\
				__##METHOD_NAME.SetFunctionMetadata(metadata);											\
				return __##METHOD_NAME;																	\
			}

#define MOCK_SETUP(MOCK_INSTANCE, MOCKABLE_METHOD_NAME)				\
	MOCK_INSTANCE.Setup_##MOCKABLE_METHOD_NAME(__FILE__, __LINE__)

#endif