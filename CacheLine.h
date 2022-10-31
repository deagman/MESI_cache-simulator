#ifndef _CACHELINE_H_
#define _CACHELINE_H_
class CacheLine
{
	public:
	//这里的核号和状态都是公开的
	int core_id;
	char ccp_state;  //缓存行的一致状态,显式使用
	/*
	uint8_t *c_data = new uint8_t[cacheline_size];
	还可以添加有效位、地址、数据等成员数据……
	*/
	CacheLine ();
	~CacheLine();
	void init ( int );
};
#endif