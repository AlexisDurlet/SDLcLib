#pragma once

void * operator new(size_t iSize);

void operator delete(void * pMemory);

void * operator new[](size_t iSize);

void operator delete[](void * pMemory);

void * SDLcMemAlloc(const int iSize);
void SDLcMemFree(void * pMemory);

