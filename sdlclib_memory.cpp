#include "sdlclib.h"
#include "sdlclib_memory.h"
#include "sdlclib_memory_info.h"
#include "sdlclib_dbginfo.h"

void * operator new(size_t iSize)
{
	return SDLcMemAlloc(iSize);
}

void operator delete(void * pMemory)
{
	SDLcMemFree(pMemory);
}

void * operator new[](size_t iSize)
{
	return SDLcMemAlloc(iSize);
}

void operator delete[](void * pMemory)
{
	SDLcMemFree(pMemory);
}

void * SDLcMemAlloc(int iSize)
{
	SDLcAssert(iSize >= 0, "Can't allocate memory");
	if (iSize == 0)
	{
		return 0;
	}
	void * pMemory = malloc(iSize);


	if (TSDLcMemoryInfo::s_bSDLcInternalMem)
	{
		TSDLcDbgInfo::IncrementSDlcAllocations();
	}
	else
	{
		TSDLcDbgInfo::IncrementUserAllocations();
	}

	return pMemory;
}
void SDLcMemFree(void * pMemory)
{
	if (pMemory == nullptr)
	{
		return;
	}

	free(pMemory);

	if (TSDLcMemoryInfo::s_bSDLcInternalMem)
	{
		TSDLcDbgInfo::GetInstance().IncrementSDlcDeallocations();
	}
	else
	{
		TSDLcDbgInfo::GetInstance().IncrementUserDeallocations();
	}
}
