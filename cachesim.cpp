
#include "common.h"
#include "argParser.h"
#include "CacheLine.h"
#include "Coherency.h"
#include "traceReader.h"
#include "traceWriter.h"
int main(int argc,char *argv[])
{
	argParser argparser( argc, argv );
	string traceFile = argparser.getTracefile();
	traceReader tracereader( traceFile );
	tracereader.setInst();
	string* request = tracereader.getInst();
	int instnum = tracereader.getInstnum();

	CacheLine *c = new CacheLine[4];
	for (int i=0; i<4; i++)
	{
		c[i].init(i);
	}
	traceWriter print;
	Coherency protocol;
	cout<<"        P0  "<<"P1  "<<"P2  "<<"P3  \n";
	print.printState( c, "      ");
	for (int i=0; i<instnum; i++)
	{
		protocol.MESI_transition( c, request[i] );
		cout<<i<<"   ";
		print.printState( c, request[i]);
	}
	delete[] c;
	return 0;
}

