#include "CacheLine.h"
CacheLine::CacheLine ()
{
	core_id = 0;
	ccp_state = '-';
}
void CacheLine::init( int ID = 0 )
{
	core_id = ID;
	ccp_state = '-';

}
CacheLine::~CacheLine(){}

