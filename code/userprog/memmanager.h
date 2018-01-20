#ifndef MEMMANAGER_H
#define MEMMANAGER_H

#include "copyright.h"
#include "bitmap.h"


class MemoryManager
{
private:
    BitMap *bitmap;

public:	
	int noOfFrame;
	int noOfFreeFrame;
	typedef struct
        {
            bool isOccupied;
            int processID;
            TranslationEntry *entries;
        } Frame;

    Frame* frames;


	MemoryManager()
	{

	}

        MemoryManager(int noOfFrame)
	{
		//bitmap = new BitMap(numPages);
		this->noOfFrame = noOfFrame;
		noOfFreeFrame = noOfFrame;
		frames = new Frame[noOfFrame];

		for(int i=0;i<noOfFrame;i++)
		{
			frames[i].isOccupied = false;
			frames[i].processID = -100;
			frames[i].entries = NULL;
		}
	}

	

    int AllocPage();
    void FreePage(int physPageNum);
    bool PageIsAllocated(int physPageNum);
	bool IsAnyPageFree();
	int NumFreePages();
	int Alloc(int processNo, TranslationEntry &entry);
	int AllocByForce();
};

#endif
