#ifndef _ERSATZ_EXPECTATION_INFO_H
#define _ERSATZ_EXPECTATION_INFO_H

#include <string>

struct ExpectationInfo
{
	ExpectationInfo()
	{
		ExpectedFunctionName = "";
		MatchedCount = 0;
		ExpectedCount = 0;
	}

	std::string ExpectedFunctionName;
	unsigned int MatchedCount;
	unsigned int ExpectedCount;
};

#endif