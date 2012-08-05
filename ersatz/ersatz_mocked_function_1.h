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

//namespace ersatz
//{
//	template <typename R, typename P1>
//	class MockedFunction<R(P1)>
//	{
//	public:
//		typedef std::function<R(P1)> FunctionType;
//
//		MockedFunction()
//		{
//			WillReturnDefault([](P1 parameter1){ return R(); });
//		}
//
//		~MockedFunction()
//		{
//		}
//
//		//////////////
//		//	
//		struct ExpectationMatchResult
//		{
//			ExpectationMatchResult(bool wasSuccessful, FunctionType returnExpression)
//			{
//				WasSuccessful = wasSuccessful;
//				ReturnExpression = returnExpression;
//			}
//
//			bool WasSuccessful;
//			FunctionType ReturnExpression;
//		};
//
//		class Expectation
//		{
//		public:
//			Expectation(MockedFunction<R(P1)>& mockedFunction)
//				: m_mockedFunction(mockedFunction)
//			{
//				m_invocationCount = 0;
//				m_expectedCount = 1;
//			}
//
//			~Expectation()
//			{
//				if(m_expectedCount > 0)
//				{
//					if(m_invocationCount < m_expectedCount)
//					{
//						std::cout << std::endl << m_mockedFunction.m_functionName << " not invoked expected number of times\n";
//					}
//					else if(m_invocationCount > m_expectedCount)
//					{
//						std::cout << std::endl << m_mockedFunction.m_functionName << " invoked more times than expected\n";
//					}
//				}
//			}
//
//			void Times(unsigned int count)
//			{
//				m_expectedCount = count;
//			}
//
//			Expectation& WillReturn(FunctionType returnExpression)
//			{
//				m_returnExpression = returnExpression;
//
//				return *this;
//			}
//
//			ExpectationMatchResult Match()
//			{
//				auto wasSuccessful = false;
//				FunctionType result = m_mockedFunction.m_defaultReturnExpression;
//
//				if(m_invocationCount < m_expectedCount)
//				{
//					wasSuccessful = true;
//					result = m_returnExpression;
//				}
//
//				m_invocationCount++;
//
//				return ExpectationMatchResult(wasSuccessful, result);
//			}
//
//		private:
//			MockedFunction<R(P1)>& m_mockedFunction;
//			//std::string m_functionName;
//			unsigned int m_invocationCount;
//			unsigned int m_expectedCount;
//
//			FunctionType m_returnExpression;
//			FunctionType m_defaultReturnExpression;
//		};
//		//////////////
//
//		std::string GetFunctionName()
//		{
//			return m_functionName;
//		}
//
//		void SetFunctionName(std::string functionName)
//		{
//			m_functionName = functionName;
//		}
//
//		MockedFunction<R(P1)>& WillReturnDefault(FunctionType defaultReturnExpression)
//		{
//			m_defaultReturnExpression = defaultReturnExpression;
//
//			return *this;
//		}
//
//		Expectation& Expect()
//		{
//			m_expectation = std::unique_ptr<Expectation>(new Expectation(*this));
//
//			return *m_expectation;
//		}
//
//		R Invoke(P1 parameter1) const
//		{
//			if(nullptr != m_expectation)
//			{
//				auto matchResult = m_expectation->Match();
//
//				if(matchResult.WasSuccessful)
//				{
//					return matchResult.ReturnExpression(parameter1);
//				}
//			}
//			
//			return m_defaultReturnExpression(parameter1);
//		}
//
//	private:
//		std::string m_functionName;
//		FunctionType m_defaultReturnExpression;
//		std::unique_ptr<Expectation> m_expectation;
//	};
//}

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