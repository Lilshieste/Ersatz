#ifndef _ERSATZ_MOCKED_FUNCTION_4_H
#define _ERSATZ_MOCKED_FUNCTION_4_H

#include <memory>
#include <functional>

#include "ersatz_mocked_function_main.h"
#include "ersatz_mocked_function_info.h"

#include "ersatz_mocked_function_n.h"

__ERSATZ_MOCKED_FUNCTION_DEFINITION__
(
	__ERSATZ_CONCAT__(template <typename R, typename P1, typename P2, typename P3, typename P4>),
	R,
	__ERSATZ_CONCAT__(P1 parameter1, P2 parameter2, P3 parameter3, P4 parameter4),
	__ERSATZ_CONCAT__(P1, P2, P3, P4),
	__ERSATZ_CONCAT__(parameter1, parameter2, parameter3, parameter4)
)

//namespace ersatz
//{
//	template <typename R, typename P1, typename P2, typename P3, typename P4>
//	class MockedFunction<R(P1, P2, P3, P4)>
//	{
//	public:
//		typedef std::function<R(P1, P2, P3, P4)> FunctionType;
//
//		MockedFunction()
//		{
//			WillReturnDefault([](P1 parameter1, P2 parameter2, P3 parameter3, P4 parameter4){ return R(); });
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
//			Expectation(std::string functionName, FunctionType defaultReturnExpression)
//			{
//				m_functionName = functionName;
//				m_defaultReturnExpression = defaultReturnExpression;
//				m_invocationCount = 0;
//				m_expectedCount = 0;
//			}
//
//			~Expectation()
//			{
//				if(m_expectedCount > 0)
//				{
//					if(m_invocationCount < m_expectedCount)
//					{
//						std::cout << std::endl << m_functionName << " not invoked expected number of times\n";
//					}
//					else if(m_invocationCount > m_expectedCount)
//					{
//						std::cout << std::endl << m_functionName << " invoked more times than expected\n";
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
//				FunctionType result = m_defaultReturnExpression;
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
//			std::string m_functionName;
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
//		MockedFunction<R(P1, P2, P3, P4)>& WillReturnDefault(FunctionType defaultReturnExpression)
//		{
//			m_defaultReturnExpression = defaultReturnExpression;
//
//			return *this;
//		}
//
//		Expectation& Expect()
//		{
//			m_expectation = std::unique_ptr<Expectation>(new Expectation(GetFunctionName(), m_defaultReturnExpression));
//
//			return *m_expectation;
//		}
//
//		R Invoke(P1 parameter1, P2 parameter2, P3 parameter3, P4 parameter4) const
//		{
//			if(nullptr != m_expectation)
//			{
//				auto matchResult = m_expectation->Match();
//
//				if(matchResult.WasSuccessful)
//				{
//					return matchResult.ReturnExpression(parameter1, parameter2, parameter3, parameter4);
//				}
//			}
//			
//			return m_defaultReturnExpression(parameter1, parameter2, parameter3, parameter4);
//		}
//
//	private:
//		std::string m_functionName;
//		FunctionType m_defaultReturnExpression;
//		std::unique_ptr<Expectation> m_expectation;
//	};
//}

#define MOCKABLE4(METHOD_NAME, RETURN_TYPE)			MOCKABLE4_MAIN(METHOD_NAME, RETURN_TYPE,		,				)
#define MOCKABLE4_CONST(METHOD_NAME, RETURN_TYPE)	MOCKABLE4_MAIN(METHOD_NAME, RETURN_TYPE, const	,				)
#define MOCKABLE4_T(METHOD_NAME, RETURN_TYPE)		MOCKABLE4_MAIN(METHOD_NAME, RETURN_TYPE,		,	typename	)
#define MOCKABLE4_CONST_T(METHOD_NAME, RETURN_TYPE)	MOCKABLE4_MAIN(METHOD_NAME, RETURN_TYPE, const	,	typename	)

#define MOCKABLE4_MAIN(METHOD_NAME, RETURN_TYPE, CONST_DECL, TYPENAME_DECL)																								\
			MOCKABLE_BASE(METHOD_NAME, RETURN_TYPE)																														\
																																										\
			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::ResultType METHOD_NAME(																				\
																			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter1Type param1,				\
																			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter2Type param2,				\
																			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter3Type param3,				\
																			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::Parameter4Type param4) CONST_DECL	\
			{																																							\
				return __##METHOD_NAME.Invoke(param1, param2, param3, param4);																							\
			}

#endif