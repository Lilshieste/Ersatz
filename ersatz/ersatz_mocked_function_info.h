#ifndef __ERSATZ_MOCKED_FUNCTION_INFO_H
#define __ERSATZ_MOCKED_FUNCTION_INFO_H

#include <functional>

namespace ersatz
{
	template <typename T>
	class MockedFunctionInfo;

#ifdef ERSATZ_USE_VARIADIC_TEMPLATES
	template <typename R, typename... Params>
	class MockedFunctionInfo<R(Params...)>
	{
	public:
		typedef R							ResultType;
		typedef std::function<R(Params)>	FunctionType;
		typedef Params...					ParameterTypes;
	};
#endif

	template <typename R>
	class MockedFunctionInfo<R()>
	{
	public:
		typedef R					ResultType;
		typedef std::function<R()>	FunctionType;
	};

	template <typename R, typename P1>
	class MockedFunctionInfo<R(P1)> : public MockedFunctionInfo<R()>
	{
	public:
		typedef P1						Parameter1Type;
		typedef std::function<R(P1)>	FunctionType;
	};

	template <typename R, typename P1, typename P2>
	class MockedFunctionInfo<R(P1, P2)> : public MockedFunctionInfo<R(P1)>
	{
	public:
		typedef P2 Parameter2Type;
		typedef std::function<R(P1, P2)>	FunctionType;
	};

	template <typename R, typename P1, typename P2, typename P3>
	class MockedFunctionInfo<R(P1, P2, P3)> : public MockedFunctionInfo<R(P1, P2)>
	{
	public:
		typedef P3 Parameter3Type;
		typedef std::function<R(P1, P2, P3)>	FunctionType;
	};

	template <typename R, typename P1, typename P2, typename P3, typename P4>
	class MockedFunctionInfo<R(P1, P2, P3, P4)> : public MockedFunctionInfo<R(P1, P2, P3)>
	{
	public:
		typedef P4 Parameter4Type;
		typedef std::function<R(P1, P2, P3, P4)>	FunctionType;
	};

	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	class MockedFunctionInfo<R(P1, P2, P3, P4, P5)> : public MockedFunctionInfo<R(P1, P2, P3, P4)>
	{
	public:
		typedef P5 Parameter5Type;
		typedef std::function<R(P1, P2, P3, P4, P5)>	FunctionType;
	};
}

#endif