#ifndef XOBJECT_H
#define XOBJECT_H

#include <map>
#include <iostream>
#include <cstring>
using namespace std;


#define SLOT(a) #a
#define SIGNAL(a) #a
#define cpp_slots
#define cpp_signals protected
#define cpp_emit

class XObject;

//元对象系统，搜集信号与槽的名称
struct MetaObject {
	//信号组
	const char * signal;
	//槽组
	const char * slot;
	//激活某个信号，idx为信号索引
	static void active(XObject * sender, int idx);
};

struct Connection {
	XObject * receiver; //信号接收者
	int methon;			//槽函数索引
};

//信号索引与连接对象映射
typedef std::multimap<int, Connection> ConnectionMap;
typedef std::multimap<int, Connection>::iterator ConnectionMapIt;

static int find_string(const char *str, const char* substr)
{
	if (strlen(str) < strlen(substr))
	{
		return -1;
	}
	int idx = 0;
	int len = strlen(substr);
	bool start = true;
	const char * pos = str;
	while (*pos)
	{
		if (start && !strncmp(pos, substr, len) && pos[len] == '\n')
		{
			return idx;
		}
		start = false;
		if (*pos == '/n')
		{
			idx++;
			start = true;
		}
		pos++;
	}
	return -1;
}

class XObject
{
public:
	XObject();
	~XObject();
};



#endif