#ifndef _TRACEWRITER_H_
#define _TRACEWRITER_H_
#include "common.h"
#include "CacheLine.h"
class traceWriter
{
	public:
		void printState( CacheLine [], string );
};
#endif