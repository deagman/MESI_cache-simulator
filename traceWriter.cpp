#include "traceWriter.h"
void traceWriter::printState( CacheLine c[4], string request )
{
	cout<< request <<"  ";
	for(int i=0; i<4; i++)
	{
		cout<< c[i].ccp_state <<"   ";
	}
	cout<<endl;
}
/*
int main()
{
	CacheLine *c = new CacheLine[4];
	for (int i=0; i<4; i++)
	{
		c[i].init(i);
	}
	traceWriter t;
	t.printState(c,"NO");

}
*/