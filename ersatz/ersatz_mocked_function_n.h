#ifndef _ERSATZ_MOCKED_FUNCTION_N_H
#define _ERSATZ_MOCKED_FUNCTION_N_H

#include <memory>
#include <functional>

#include "ersatz_mocked_function_main.h"
#include "ersatz_mocked_function_info.h"

// This macro is used to create class definitions for MockedFunction objects using a specified function signature.
//  Ideally, this macro would never be used - but the lack of support for variadic templates in some compilers
//  (e.g., Visual Studio) forces an approach like this.

#define __ERSATZ_CONCAT__(...) __VA_ARGS__
#define __ERSATZ_MOCKED_FUNCTION_DEFINITION__(TEMPLATE_DEF, RETURN_TYPE, PARAMETER_LIST, PARAMETER_TYPES, PARAMETER_NAMES)		\
																																\
namespace ersatz																												\
{																																\
	TEMPLATE_DEF																												\
	class MockedFunction<RETURN_TYPE(PARAMETER_TYPES)>																			\
	{																															\
	public:																														\
		typedef std::function<RETURN_TYPE(PARAMETER_TYPES)> FunctionType;														\
																																\
		MockedFunction()																										\
		{																														\
			WillReturnDefault([](PARAMETER_LIST){ return RETURN_TYPE(); });														\
		}																														\
																																\
		~MockedFunction()																										\
		{																														\
		}																														\
																																\
		struct ExpectationMatchResult																							\
		{																														\
			ExpectationMatchResult(bool wasSuccessful, FunctionType returnExpression)											\
			{																													\
				WasSuccessful = wasSuccessful;																					\
				ReturnExpression = returnExpression;																			\
			}																													\
																																\
			bool WasSuccessful;																									\
			FunctionType ReturnExpression;																						\
		};																														\
																																\
		class Expectation																										\
		{																														\
		public:																													\
			Expectation(MockedFunction<RETURN_TYPE(PARAMETER_TYPES)>& mockedFunction)											\
				: m_mockedFunction(mockedFunction)																				\
			{																													\
				m_invocationCount = 0;																							\
				m_matchCount = 0;																								\
				m_expectedCount = 1;																							\
				m_matcher = [](PARAMETER_TYPES){ return true; };																\
				m_returnExpression = m_mockedFunction.m_defaultReturnExpression;												\
			}																													\
																																\
			Expectation(MockedFunction<RETURN_TYPE(PARAMETER_TYPES)>& mockedFunction, std::function<bool(PARAMETER_TYPES)> matcher)	\
				: m_mockedFunction(mockedFunction)																				\
			{																													\
				m_invocationCount = 0;																							\
				m_matchCount = 0;																								\
				m_expectedCount = 1;																							\
				m_matcher = matcher;																							\
				m_returnExpression = m_mockedFunction.m_defaultReturnExpression;												\
			}																													\
																																\
			~Expectation()																										\
			{																													\
				if(m_expectedCount > 0)																							\
				{																												\
					if(m_matchCount < m_expectedCount)																			\
					{																											\
						std::cout << std::endl << m_mockedFunction.m_functionMetadata.FunctionName << " not invoked expected number of times\n";	\
					}																											\
					else if(m_matchCount > m_expectedCount)																		\
					{																											\
						std::cout << std::endl << m_mockedFunction.m_functionMetadata.FunctionName << " invoked more times than expected\n";		\
					}																											\
				}																												\
			}																													\
																																\
			void Times(unsigned int count)																						\
			{																													\
				m_expectedCount = count;																						\
			}																													\
																																\
			Expectation& WillReturn(FunctionType returnExpression)																\
			{																													\
				m_returnExpression = returnExpression;																			\
																																\
				return *this;																									\
			}																													\
																																\
			ExpectationMatchResult Match(PARAMETER_LIST)																		\
			{																													\
				auto wasSuccessful = false;																						\
				FunctionType result = m_mockedFunction.m_defaultReturnExpression;												\
																																\
				if(m_matcher(PARAMETER_NAMES))																					\
				{																												\
					wasSuccessful = true;																						\
					m_matchCount++;																								\
					result = m_returnExpression;																				\
				}																												\
																																\
				m_invocationCount++;																							\
																																\
				return ExpectationMatchResult(wasSuccessful, result);															\
			}																													\
																																\
		private:																												\
			MockedFunction<RETURN_TYPE(PARAMETER_TYPES)>& m_mockedFunction;														\
			std::function<bool(PARAMETER_TYPES)> m_matcher;																		\
			unsigned int m_invocationCount;																						\
			unsigned int m_matchCount;																							\
			unsigned int m_expectedCount;																						\
																																\
			FunctionType m_returnExpression;																					\
		};																														\
																																\
		std::string GetFunctionName()																							\
		{																														\
			return m_functionName;																								\
		}																														\
																																\
		void SetFunctionName(std::string functionName)																			\
		{																														\
			m_functionName = functionName;																						\
		}																														\
																																\
		MockedFunctionMetadata& GetFunctionMetadata()																			\
		{																														\
			return m_functionMetadata;																							\
		}																														\
																																\
		void SetFunctionMetadata(MockedFunctionMetadata metadata)																\
		{																														\
			m_functionMetadata = metadata;																						\
		}																														\
																																\
		MockedFunction<RETURN_TYPE(PARAMETER_TYPES)>& WillReturnDefault(FunctionType defaultReturnExpression)					\
		{																														\
			m_defaultReturnExpression = defaultReturnExpression;																\
																																\
			return *this;																										\
		}																														\
																																\
		Expectation& Expect()																									\
		{																														\
			m_expectation = std::unique_ptr<Expectation>(new Expectation(*this));												\
																																\
			return *m_expectation;																								\
		}																														\
																																\
		Expectation& Expect(std::function<bool(PARAMETER_TYPES)> matcher)														\
		{																														\
			m_expectation = std::unique_ptr<Expectation>(new Expectation(*this, matcher));										\
																																\
			return *m_expectation;																								\
		}																														\
																																\
		RETURN_TYPE Invoke(PARAMETER_LIST) const																				\
		{																														\
			if(nullptr != m_expectation)																						\
			{																													\
				auto matchResult = m_expectation->Match(PARAMETER_NAMES);														\
																																\
				if(matchResult.WasSuccessful)																					\
				{																												\
					return matchResult.ReturnExpression(PARAMETER_NAMES);														\
				}																												\
			}																													\
																																\
			return m_defaultReturnExpression(PARAMETER_NAMES);																	\
		}																														\
																																\
	private:																													\
		std::string m_functionName;																								\
		MockedFunctionMetadata m_functionMetadata;																				\
		FunctionType m_defaultReturnExpression;																					\
		std::unique_ptr<Expectation> m_expectation;																				\
	};																															\
}

#endif