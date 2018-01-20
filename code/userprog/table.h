#ifndef TABLE_H
#define TABLE_H

#include "copyright.h"

class Table
{
public:
	Table(int size);
	int Alloc(void *object);
	void *Get(int index);
	void Release(int index);

	void **objectArray;
	int tSize;
	int numProcesses;
}



#endif
