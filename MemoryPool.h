/*************************************************
 * Fullmoon - MemoryPool
 * Copyright (c) 2010-2012,2015 Queue Sakura-Shiki
 * Released under the MIT license
 */

// Allocate memory for class object from memory pool.
class ManagedObject {
public:
	static void* operator new(size_t size) {
	    return MemoryPool::allocate(size);
	}
	static void operator delete(void* pv) {
	    MemoryPool::free(pv);
	}
};

// HACK : Allocate memory for class object from memory pool.
//        But the constructor is not called.
//        Just copying the vitual method table's pointer address.
// use-case -> using memory by best effort.
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

	// init memory pool state.
	static void initialize();
	
	// reset memory pool. All memories are droped.
	// WARN : The object's destructor can not be called. Do it yourself.
	static void reset();
	
	// allcate memory.
	static void* allocate( int size );
	
	// drop memory.
	static void free( void* chunk );
	
	// show used memory chunk count.
	static unsigned int getCount();

private:
	MemoryPool(void){};
	~MemoryPool(void){};

};

