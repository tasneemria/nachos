#include "table.h"
#include "synch.h"

Lock *myTableLock = new Lock("tableLock");

Table::Table(int size)
{
	objectArray = new void*[size+5];
	tSize = size;
	numProcesses = 0;

	int i = 0;
	while(i<size)
	{
		objectArray[i] = NULL;
		i++;
 	}
}

int Table::Alloc(void *object)
{
	myTableLock->Acquire();
	int i = 0;
	while(i<tSize)
	{
		if(objectArray[i] == NULL)
		{
			objectArray[i] = object;
			numProcesses++;
			myTableLock->Release();
			return i;
		}
		i++;
	}
	myTableLock->Release();
	return -1;
}

void *Table::Get(int index)
{
	myTableLock->Acquire();
	
	myTableLock->Release();
	
	return objecArray[index];
}

void Table::Release(int index)
{
	myTableLock->Acquire();
	
	objectArray[index] = NULL;
	numProcesses--;
 
	myTableLock->Release();
}



