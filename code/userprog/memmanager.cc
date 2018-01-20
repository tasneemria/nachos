#include "copyright.h"
#include "memmanager.h"
#include "synch.h"

Lock *myLock = new Lock("myLock");

extern Table*  processTable;

int MemoryManager::AllocPage()
{
	int alocpage;
	myLock->Acquire();
	alocpage = bitmap->Find();
	myLock->Release();
	return alocpage;
}

bool MemoryManager::PageIsAllocated(int physPageNum)
{
	bool pageAllocation;
	myLock->Acquire();
	pageAllocation = bitmap->Test(physPageNum);	
	myLock->Release();
	return pageAllocation;
}

void MemoryManager::FreePage(int physPageNum)
{
	myLock->Acquire();
	bitmap->Clear(physPageNum);
	myLock->Release();
	return;
}

bool MemoryManager::IsAnyPageFree()
{
	myLock->Acquire();
	bool ret;
	if(bitMap->NumClear() == 0)
		ret = false;
	else
		ret = true;
	myLock->Release();
	return ret;
}

int MemoryManager::NumFreePages()
{
	myLock->Acquire();
	int ret = bitMap->NumClear();
	myLock->Release();
	return ret;
}

int MemoryManager::Alloc(int processNo, TranslationEntry &entry)
{
	myLock->Acquire();
	
	int toEntry;
	for(int i=0;i<noOfFrame;i++)
	{
		if(!frames[i].isOccupied)
		{
			toEntry = i;
			noOfFreeFrame--;
			break;
		}
	}
	frames[toEntry].isOccupied = true;
	frames[toEntry].processID = processNo;
	frames[toEntry].entries = entry;	
	
	myLock->Release();
}

int MemoryManager::AllocByForce()
{
	int randomPage;
	randomPage = rand()%noOfFrame;
	return randomPage;
	
}
