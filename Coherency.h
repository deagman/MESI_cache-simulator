#ifndef _COHERENCY_H_
#define _COHERENCY_H_
#include "CacheLine.h"
#include "Common.h"
class Coherency
{
	/*
	enum state_t
	{
		'-',
		'I',
		'S',
		'E',
		'M'
	}
	*/
	public:
		void MESI_transition (CacheLine c[], string request);	
};
#endif
