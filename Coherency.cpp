#include "Coherency.h"
void Coherency::MESI_transition (CacheLine c[4], string request)
{
	const char* req = request.c_str(); 
	char req_op = req[0];
	int req_core = req[1]-'0';	//如果是两位数以上的核数，需要重新考虑
	if ( req_op != 'R' && req_op != 'W') return;
	if ( req_op == 'R')
	{
		switch( c[req_core].ccp_state )
		{
			case '-':
			case 'I':
			{
				int other_I = 0;//判断是否全为INVALID或未分配
				for(int i = 0; i<4 ; i++)
				{
					if( i == req_core )	continue;
					switch ( c[i].ccp_state )
					{
						case '-':
						case 'I':
							other_I++;
							break;

						case 'S':
							//有cache为S，不变
							break;

						case 'E':
							c[i].ccp_state = 'S';  //有cache为E，变S
							break;

						case 'M':
							c[i].ccp_state = 'S';  //有cache为M，变S
							break;
					}
				}
				if( other_I == 3)
					c[req_core].ccp_state = 'E';
				else
					c[req_core].ccp_state = 'S';
				break;
			}
			case 'S':
				break;
			case 'E':
				break;
			case 'M':
				break;
		}
	}
	if ( req_op == 'W')
	{
		switch( c[req_core].ccp_state )
		{
			case '-':
			case 'I':
			{
				for(int i=0; i<4 ; i++)
				{
					if( i == req_core ) continue;
					switch ( c[i].ccp_state )
					{
						case '-':
						case 'I':
							break;

						case 'S':
							c[i].ccp_state = 'I';  //有cache为S，变I
							break;

						case 'E':
							c[i].ccp_state = 'I';  //有cache为E，变I
							break;

						case 'M':
							c[i].ccp_state = 'I';  //有cache为M，变I
							break;
					}
				}
				c[req_core].ccp_state = 'M';
				break;
			}
			case 'S':
			{
				for(int i=0; i<4 ; i++)
				{
					if( i != req_core && c[i].ccp_state == 'S')
						c[i].ccp_state = 'I';
				}
				c[req_core].ccp_state = 'M';
				break;				
			}
			case 'E':
				c[req_core].ccp_state = 'M';
				break;
			case 'M':
				break;
		}
	}
}
/*
int main()
{
	CacheLine *c = new CacheLine[4];
	for (int i=0; i<4; i++)
	{
		c[i].init(i);
	}
	Coherency p;
	p.MESI_transition(c,"W0");
	cout<<c[0].ccp_state<<c[1].ccp_state<<c[2].ccp_state<<c[3].ccp_state;
}
*/