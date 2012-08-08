#ifndef _ERSATZ_EXPECTATION_INFO_FORMATTER_H
#define _ERSATZ_EXPECTATION_INFO_FORMATTER_H

#include <string>
#include <sstream>
#include "ExpectationInfo.h"

class ExpectationInfoFormatter
{
public:
	ExpectationInfoFormatter()
	{
	}

	~ExpectationInfoFormatter()
	{
	}

	std::string FormatExpectationInfo(ExpectationInfo info)
	{
		std::stringstream stream;

		if(info.ExpectedCount > 0)
		{
			stream << "Function '" << info.ExpectedFunctionName << "' expected " << info.ExpectedCount
				<< "times, but invoked " << info.MatchedCount << " times." << std::endl;
		}

		return stream.str();
	}
};

#endif