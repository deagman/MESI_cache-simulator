#ifndef _ARGPARSER_H_
#define _ARGPARSER_H_
#include "common.h"
#include <getopt.h>
class argParser
{
	private:
	string traceFilename;	//输入文件名
	public:
	argParser(int argc, char* argv[]);
	~argParser();
	void printHelp();
	string getTracefile();
};
#endif
