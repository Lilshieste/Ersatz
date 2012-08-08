// TODO: Actually develop this using gcc, or something else other than VS, to verify functionality

#ifndef _ERSATZ_MOCKED_FUNCTION_VARIADIC_H
#define _ERSATZ_MOCKED_FUNCTION_VARIADIC_H

#include <memory>
#include <functional>

#include "ersatz_mocked_function_main.h"
#include "ersatz_mocked_function_info.h"

namespace ersatz
{
	template <typename R, typename... Parameters>
	class MockedFunction<R(Parameters...)>
	{
	public:
		typedef std::function<R(Parameters...)> FunctionType;

		MockedFunction()
		{
			WillReturnDefault([](Parameters...){ return R(); });
		}

		~MockedFunction()
		{
		}

		//////////////
		//	
		struct ExpectationMatchResult
		{
			ExpectationMatchResult(bool wasSuccessful, FunctionType returnExpression)
			{
				WasSuccessful = wasSuccessful;
				ReturnExpression = returnExpression;
			}

			bool WasSuccessful;
			FunctionType ReturnExpression;
		};

		class Expectation
		{
		public:
			Expectation(std::string functionName, FunctionType defaultReturnExpression)
			{
				m_functionName = functionName;
				m_matcher = [](Parameters...){ return true; };
				m_defaultReturnExpression = defaultReturnExpression;
				m_invocationCount = 0;
				m_expectedCount = 0;
			}

			~Expectation()
			{
				if(m_expectedCount > 0)
				{
					if(m_invocationCount < m_expectedCount)
					{
						std::cout << std::endl << m_functionName << " not invoked expected number of times\n";
					}
					else if(m_invocationCount > m_expectedCount)
					{
						std::cout << std::endl << m_functionName << " invoked more times than expected\n";
					}
				}
			}

			void Times(unsigned int count)
			{
				m_expectedCount = count;
			}

			Expectation& WillReturn(FunctionType returnExpression)
			{
				m_returnExpression = returnExpression;

				return *this;
			}

			Expectation& WithMatcher(std::function<bool(Parameters...)> matcher)
			{
				m_matcher = matcher;

				return *this;
			}

			ExpectationMatchResult Match()
			{
				auto wasSuccessful = false;
				FunctionType result = m_defaultReturnExpression;

				if(m_invocationCount < m_expectedCount)
				{
					wasSuccessful = true;
					result = m_returnExpression;
				}

				m_invocationCount++;

				return ExpectationMatchResult(wasSuccessful, result);
			}

		private:
			std::string m_functionName;
			std::function<bool(Parameters...)> m_matcher;
			unsigned int m_invocationCount;
			unsigned int m_expectedCount;

			FunctionType m_returnExpression;
			FunctionType m_defaultReturnExpression;
		};
		//////////////

		std::string GetFunctionName()
		{
			return m_functionName;
		}

		void SetFunctionName(std::string functionName)
		{
			m_functionName = functionName;
		}

		void SetFunctionMetadata(std::string functionName)
		{
			m_functionName = functionName;
		}

		MockedFunction<R(Parameters...)>& WillReturnDefault(FunctionType defaultReturnExpression)
		{
			m_defaultReturnExpression = defaultReturnExpression;

			return *this;
		}

		Expectation& Expect()
		{
			m_expectation = std::unique_ptr<Expectation>(new Expectation(GetFunctionName(), m_defaultReturnExpression));

			return *m_expectation;
		}

		R Invoke(Parameters... params) const
		{
			if(nullptr != m_expectation)
			{
				auto matchResult = m_expectation->Match();

				if(matchResult.WasSuccessful)
				{
					return matchResult.ReturnExpression(std::forward<ersatz::MockedFunctionInfo<RETURN_TYPE>::ParameterTypes>(params)...);
				}
			}
			
			return m_defaultReturnExpression(std::forward<ersatz::MockedFunctionInfo<RETURN_TYPE>::ParameterTypes>(params)...);
		}

	private:
		std::string m_functionName;
		FunctionType m_defaultReturnExpression;
		std::unique_ptr<Expectation> m_expectation;
	};
}

#define MOCKABLE(METHOD_NAME, RETURN_TYPE)			MOCKABLE_MAIN(METHOD_NAME, RETURN_TYPE,			,				)
#define MOCKABLE_CONST(METHOD_NAME, RETURN_TYPE)	MOCKABLE_MAIN(METHOD_NAME, RETURN_TYPE, const	,				)
#define MOCKABLE_T(METHOD_NAME, RETURN_TYPE)		MOCKABLE_MAIN(METHOD_NAME, RETURN_TYPE,			,	typename	)
#define MOCKABLE_CONST_T(METHOD_NAME, RETURN_TYPE)	MOCKABLE_MAIN(METHOD_NAME, RETURN_TYPE, const	,	typename	)

#define MOCKABLE_MAIN(METHOD_NAME, RETURN_TYPE, CONST_DECL, TYPENAME_DECL)																								\
			MOCKABLE_BASE(METHOD_NAME, RETURN_TYPE)																														\
																																										\
			TYPENAME_DECL ersatz::MockedFunctionInfo<RETURN_TYPE>::ResultType METHOD_NAME(ersatz::MockedFunctionInfo<RETURN_TYPE>::ParameterTypes params)	CONST_DECL	\
			{																																							\
				return __##METHOD_NAME.Invoke(std::forward<ersatz::MockedFunctionInfo<RETURN_TYPE>::ParameterTypes>(params)...);										\
			}

#endif