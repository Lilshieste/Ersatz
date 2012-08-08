#ifndef _ERSATZ_MOCKED_FUNCTION_N_H
#define _ERSATZ_MOCKED_FUNCTION_N_H

#include <memory>
#include <functional>
#include <ostream>

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
			WillDoByDefault([](PARAMETER_LIST){ return RETURN_TYPE(); });														\
		}																														\
																																\
		~MockedFunction()																										\
		{																														\
		}																														\
																																\
		struct ExpectationMatchResult																							\
		{																														\
			ExpectationMatchResult(bool wasSuccessful, FunctionType action)											\
			{																													\
				WasSuccessful = wasSuccessful;																					\
				Action = action;																			\
			}																													\
																																\
			bool WasSuccessful;																									\
			FunctionType Action;																						\
		};																														\
																																\
		class Expectation																										\
		{																														\
		public:																													\
			Expectation(MockedFunction<RETURN_TYPE(PARAMETER_TYPES)>& mockedFunction)											\
				: m_mockedFunction(mockedFunction)																				\
			{																													\
				Initialize(m_mockedFunction, [](PARAMETER_TYPES){ return true; });												\
			}																													\
																																\
			Expectation(MockedFunction<RETURN_TYPE(PARAMETER_TYPES)>& mockedFunction, std::function<bool(PARAMETER_TYPES)> matcher)	\
				: m_mockedFunction(mockedFunction)																				\
			{																													\
				Initialize(m_mockedFunction, matcher);																			\
			}																													\
																																\
			~Expectation()																										\
			{																													\
				if(!m_matchingInvocationCountVerifier(m_matchingInvocationCount))																		\
				{																												\
					std::cout << std::endl << m_mockedFunction.m_functionMetadata.FunctionName << " not invoked expedted number of times." << std::endl;\
				}																												\
			}																													\
																																\
			void Times(unsigned int count)																						\
			{																													\
				Times([count](unsigned int matchingInvocationCount){ return matchingInvocationCount == count; });				\
			}																													\
																																\
			void Times(std::function<bool(unsigned int)> matchingInvocationCountVerifier)										\
			{																													\
				m_matchingInvocationCountVerifier = matchingInvocationCountVerifier;											\
			}																													\
																																\
			Expectation& WillDo(FunctionType action)																			\
			{																													\
				m_action = action;																								\
																																\
				return *this;																									\
			}																													\
																																\
			ExpectationMatchResult Match(PARAMETER_LIST)																		\
			{																													\
				auto wasSuccessful = false;																						\
				FunctionType action = m_mockedFunction.m_defaultAction;												\
																																\
				if(m_matcher(PARAMETER_NAMES))																					\
				{																												\
					wasSuccessful = true;																						\
					m_matchingInvocationCount++;																				\
					action = m_action;																							\
				}																												\
																																\
				m_invocationCount++;																							\
																																\
				return ExpectationMatchResult(wasSuccessful, action);															\
			}																													\
																																\
		private:																												\
			MockedFunction<RETURN_TYPE(PARAMETER_TYPES)>& m_mockedFunction;														\
			std::function<bool(PARAMETER_TYPES)> m_matcher;																		\
			std::function<bool(unsigned int)> m_matchingInvocationCountVerifier;												\
			unsigned int m_invocationCount;																						\
			unsigned int m_matchingInvocationCount;																				\
																																\
			FunctionType m_action;																								\
																																\
			void Initialize(MockedFunction<RETURN_TYPE(PARAMETER_TYPES)>& mockedFunction, std::function<bool(PARAMETER_TYPES)> matcher)	\
			{																													\
				m_invocationCount = 0;																							\
				m_matchingInvocationCount = 0;																					\
				m_matcher = matcher;																							\
				m_action = m_mockedFunction.m_defaultAction;																	\
				Times(1);																										\
			}																													\
																																\
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
		MockedFunction<RETURN_TYPE(PARAMETER_TYPES)>& WillDoByDefault(FunctionType defaultAction)					\
		{																														\
			m_defaultAction = defaultAction;																\
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
					return matchResult.Action(PARAMETER_NAMES);														\
				}																												\
			}																													\
																																\
			return m_defaultAction(PARAMETER_NAMES);																	\
		}																														\
																																\
	private:																													\
		std::string m_functionName;																								\
		MockedFunctionMetadata m_functionMetadata;																				\
		FunctionType m_defaultAction;																					\
		std::unique_ptr<Expectation> m_expectation;																				\
	};																															\
}

#endif