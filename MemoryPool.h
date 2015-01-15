/*************************************************
 * Fullmoon - MemoryPool
 * Copyright (c) 2010-2012,2015 Queue Sakura-Shiki
 * Released under the MIT license
 */

// Constructor using memory pool.
class ManagedObject {
public:
	static void* operator new(size_t size) {
	    return MemoryPool::allocate(size);
	}
	static void operator delete(void* pv) {
	    MemoryPool::free(pv);
	}
};

// Allocate memory from memory pool.
template <class V > V* MALLOC() {
	V* v = (V*)MemoryPool::allocate(sizeof(V));
	V impl;
	CopyMemory( v, &impl, sizeof(unsigned int) ); 
	return v;
}
#define FREE(v)   (MemoryPool::free(v))

// interface to implements.
class MemoryPool
{
public:

	static void initialize();
	static void reset();
	static void* allocate( int size );
	static void free( void* chunk );
	static unsigned int getCount();

private:
	MemoryPool(void){};
	~MemoryPool(void){};

};

