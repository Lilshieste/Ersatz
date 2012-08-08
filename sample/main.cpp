#include <iostream>
#include <string>

#include "ersatz.h"

using namespace std;

template <typename T>
class IBlah
{
public:
	virtual int DoStuffAndReturn() = 0;
	
	virtual void DoStuff() const = 0;

	virtual int OtherStuff(int number) = 0;

	virtual void DoStuff2(int number, std::string name) = 0;
	virtual int DoStuff3(int number, std::string name, int num2) = 0;
	virtual int DoStuff4(int num1, int num2, int num3, int num4) = 0;
	virtual int DoStuff5(int num1, int num2, int num3, int num4, int num5) = 0;

	virtual T GenericStuff(T item) const = 0;
};

template <typename T>
class FakeBlah : public IBlah<T>
{
public:
	MOCKABLE0(DoStuffAndReturn, int());
	
	MOCKABLE0_CONST(DoStuff, void());

	MOCKABLE1(OtherStuff, int(int number));

	MOCKABLE2(DoStuff2, void(int number, std::string name));
	MOCKABLE3(DoStuff3, int(int number, std::string name, int num2));
	MOCKABLE4(DoStuff4, int(int num1, int num2, int num3, int num4));
	MOCKABLE5(DoStuff5, int(int num1, int num2, int num3, int num4, int num5));

	MOCKABLE1_CONST_T(GenericStuff, T(T item));
};

int main()
{
	auto testBlah = FakeBlah<float>();

	MOCK_SETUP(testBlah, OtherStuff)
		.Expect([](int num){ return num < 42; })
		.Times([](int invocationCount){ return invocationCount > 2; });

	testBlah.OtherStuff(41);
	testBlah.OtherStuff(40);
	testBlah.OtherStuff(40);

	cout << "Press Enter to exit";

	string input;
	getline(cin, input);
}