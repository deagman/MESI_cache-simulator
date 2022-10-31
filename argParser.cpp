#include "argParser.h"
argParser::argParser(int argc, char* argv[])
{
	char opt;
	//使用getopt()函数读取选项参数,optarg为选项参数
	while( ( opt = getopt(argc,argv,"ht:") ) != -1)
	{
		switch (opt)
		{
		case 'h':
			printHelp();  //打印帮助信息
			break;
		case 't':
			traceFilename = optarg;
			break;
		default :
			break;
		}
	}
}
argParser::~argParser(){}
void argParser::printHelp()
{
	cout<<"Usage:"<< "./my.exe [-h] -t <file>\n";
	cout<<"Options:\n";
	cout<<"-h         Print this help message.\n";
	/*
	cout<<"-p         Cache Coherency Protocol option.\n";
	cout<<"-n         Number of cores.\n";
	*/
	cout<<"-t         Trace file.\n";
	cout<<"Examples:\n";
	cout<<"./my.exe -t mytrace.txt\n";
}
string argParser::getTracefile()
{
	return traceFilename;
}