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

//namespace ersatz
//{
//	template <typename R>
//	class MockedFunction<R()>
//	{
//	public:
//		typedef std::function<R()> FunctionType;
//
//		MockedFunction()
//		{
//			WillReturnDefault([](){ return R(); });
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
//				m_expectedCount = 1;
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
//		MockedFunction<R()>& WillReturnDefault(FunctionType defaultReturnExpression)
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
//		R Invoke() const
//		{
//			if(nullptr != m_expectation)
//			{
//				auto matchResult = m_expectation->Match();
//
//				if(matchResult.WasSuccessful)
//				{
//					return matchResult.ReturnExpression();
//				}
//			}
//			
//			return m_defaultReturnExpression();
//		}
//
//	private:
//		std::string m_functionName;
//		FunctionType m_defaultReturnExpression;
//		std::unique_ptr<Expectation> m_expectation;
//	};
//}



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