/*************************************************
 * Fullmoon - MemoryPool
 * Copyright (c) 2010-2012,2015 Queue Sakura-Shiki
 * Released under the MIT license
 */

#include "MemoryPool.h"

// Max chunk count.
#define POOL_CHUNK_COUNT    98304
// Memory size for each chunks. (Byte)
#define	ALLOCATE_CHUNK_SIZE   256


static void*         beginPoolAddress;
static unsigned int  pool[POOL_CHUNK_COUNT][ALLOCATE_CHUNK_SIZE/8];
static char          isUsed[POOL_CHUNK_COUNT];

static int  currentAllocateCount;
static int  count;

void MemoryPool::initialize() {
	beginPoolAddress     = pool;
	currentAllocateCount = 0;
	ZeroMemory(&isUsed, sizeof(isUsed));
	ZeroMemory(&pool  , sizeof(pool));
	count = 0;
};

void MemoryPool::reset() {	
	currentAllocateCount = 0;
	ZeroMemory(&isUsed, sizeof(char)*POOL_CHUNK_COUNT);
	ZeroMemory(&pool  , sizeof(unsigned char)*POOL_CHUNK_COUNT*ALLOCATE_CHUNK_SIZE);
	count = 0;
};

void* MemoryPool::allocate( int size ) {

	if ( size > ALLOCATE_CHUNK_SIZE ) {
		return NULL;
	}

	int preAllocateCount = currentAllocateCount;
	while( TRUE ) {

		currentAllocateCount++;

		if ( currentAllocateCount >= POOL_CHUNK_COUNT ) {
			currentAllocateCount = 0;
		}
		if ( currentAllocateCount == preAllocateCount ) {
			return NULL;
		} else if ( ! isUsed[currentAllocateCount] ) {
			count++;
			isUsed[currentAllocateCount] = TRUE;
			return pool[currentAllocateCount];
		}
	}
	return NULL;
};

void MemoryPool::free( void* chunk ) {
	unsigned int allocateCount = ((unsigned int)chunk-(unsigned int)beginPoolAddress)/(ALLOCATE_CHUNK_SIZE*sizeof(unsigned char));
	if ( POOL_CHUNK_COUNT <= allocateCount ) {
		return;
	}
	count--;
	isUsed[allocateCount] = FALSE;
};

int MemoryPool::getCount() {
	return count;
};
