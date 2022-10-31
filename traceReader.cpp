#include "traceReader.h"
traceReader::traceReader()
{
	traceFile = "";
	instnum = 0;
}
traceReader::traceReader( string file )
{
	traceFile = file;
	instnum = 0;
}
traceReader::~traceReader()
{
	if ( trace.is_open() ) trace.close();
}
void traceReader::setInst()
{
	trace.open( traceFile, ios::in );
	if ( !trace.is_open() )
	{
		cout<<"Can not open the file: "<< traceFile <<endl;
		return;
	}
	string traceLine;	//读取trace的每一行
	string field;	//读取每一行的各个参数
	int fieldID;
	int cycle;
	string req;
	/*
	trace格式为
	0 R0
	1 W1
	表示第一个指令周期里对CPU0读，第二个指令周期表示对CPU1写
	*/
	while( getline (trace, traceLine) )
	{
		istringstream lineStream (traceLine);
		fieldID = 0;
		//不同参数之间以空格分开
		while( getline (lineStream, field, ' ') )
		{
			if(fieldID == 0)
			{
				cycle = atoi(field.c_str());
			}
			if(fieldID == 1)
			{
				req = field;
			}
			fieldID++;
		}
		request[cycle] = req;
		instnum++;
	}

}
string* traceReader::getInst()
{
	return request;
}
int traceReader::getInstnum()
{
	return instnum;
}
/*
int main()
{
	traceReader r("mytest");
	r.setInst();
	string* request = r.getInst();
	int num = r.getInstnum();
	cout<<num<<request[0]<<request[1]<<request[2];
}
*/

