#ifndef _ERSATZ_MOCKED_FUNCTION_METADATA_H
#define _ERSATZ_MOCKED_FUNCTION_METADATA_H

struct MockedFunctionMetadata
{
	MockedFunctionMetadata()
	{
		Initialize("", "", 0);
	}

	MockedFunctionMetadata(std::string functionName, std::string fileName, unsigned int lineNumber)
	{
		Initialize(functionName, fileName, lineNumber);
	}

	std::string FunctionName;
	std::string FileName;
	unsigned int LineNumber;

private:
	void Initialize(std::string functionName, std::string fileName, unsigned int lineNumber)
	{
		FunctionName	= functionName;
		FileName		= fileName;
		LineNumber		= lineNumber;
	}
};

#endif