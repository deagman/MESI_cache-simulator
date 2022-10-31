#ifndef _TRACEREADER_H_
#define _TRACEREADER_H_
#include "Common.h"
#include <fstream>
#include <sstream>
class traceReader
{
	private:
		string traceFile;
		ifstream trace;
		string request[100];	//存储指令流的数组
		int instnum;		//统计一共多少行指令
	public:
		traceReader();
		traceReader( string );
		~traceReader();
		void setInst();
		string* getInst();
		int getInstnum();

};
#endif