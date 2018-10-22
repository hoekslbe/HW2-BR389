#include "evictors.hh" //Contains cache.hh
#include <cassert>
#include <iostream>

// Tests the get, set, delete, and space_used functions of a cache when overflow does not occur.   
// Behavior does not depend on the replacement policy used, because no items are evicted.  
void basic_nonoverflow_test() {
	Cache::key_type key1 = "cachekey1";
	Cache::val_type val1 = (void*) new int(3);
	Cache::index_type size1 = sizeof(int);

	Cache::key_type key2 = "cachekey2";
	Cache::val_type val2 = (void*) new double(4.0);
	Cache::index_type size2 = sizeof(double);

	Cache::index_type get_size = 1;

	Cache cache(size1 + size2 + 1);

	assert(cache.space_used() == 0);
	assert(cache.get(key1, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.get(key2, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.space_used() == 0);

	cache.del(key1);
	assert(cache.space_used() == 0);
	assert(cache.get(key1, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.get(key2, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.space_used() == 0);

	cache.del(key2);
	assert(cache.space_used() == 0);
	assert(cache.get(key1, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.get(key2, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.space_used() == 0);

	cache.set(key1, val1, size1);
	assert(cache.space_used() == size1);
	assert(*((int*) cache.get(key1, get_size)) == *((int*)val1));
	assert(get_size == size1);
	assert(cache.get(key2, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.space_used() == size1);

	cache.set(key1, val1, size1);
	assert(cache.space_used() == size1);
	assert(*((int*) cache.get(key1, get_size)) == *((int*)val1));
	assert(get_size == size1);
	assert(cache.get(key2, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.space_used() == size1);

	cache.set(key2, val2, size2);
	assert(cache.space_used() == size1 + size2);
	assert(*((int*) cache.get(key1, get_size)) == *((int*)val1));
	assert(get_size == size1);
	assert(*((double*) cache.get(key2, get_size)) == *((double*)val2));
	assert(get_size == size2);
	assert(cache.space_used() == size1 + size2);

	cache.set(key2, val2, size2);
	assert(cache.space_used() == size1 + size2);
	assert(*((int*) cache.get(key1, get_size)) == *((int*)val1));
	assert(get_size == size1);
	assert(*((double*) cache.get(key2, get_size)) == *((double*)val2));
	assert(get_size == size2);
	assert(cache.space_used() == size1 + size2);

	cache.del(key1);
	assert(cache.space_used() == size2);
	assert(cache.get(key1, get_size) == nullptr);
	assert(get_size == 0);
	assert(*((double*) cache.get(key2, get_size)) == *((double*)val2));
	assert(get_size == size2);
	assert(cache.space_used() == size2);

	cache.del(key1);
	assert(cache.space_used() == size2);
	assert(cache.get(key1, get_size) == nullptr);
	assert(get_size == 0);
	assert(*((double*) cache.get(key2, get_size)) == *((double*)val2));
	assert(get_size == size2);
	assert(cache.space_used() == size2);

	cache.del(key2);
	assert(cache.space_used() == 0);
	assert(cache.get(key1, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.get(key2, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.space_used() == 0);

	cache.del(key2);
	assert(cache.space_used() == 0);
	assert(cache.get(key1, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.get(key2, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.space_used() == 0);

	cache.set(key2, val2, size1 + size2 + 100);
	assert(cache.space_used() == 0);
	assert(cache.get(key1, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.get(key2, get_size) == nullptr);
	assert(get_size == 0);
	assert(cache.space_used() == 0);

	delete (int*) val1;
	delete (double*) val2;

	std::cout << "Passed the basic tests\n";
}

// Tests the functionality of a cache when overflow occurs while using a FIFO evictor.
void FIFO_overflow_test() {
	
	Cache::key_type key1 = "key1";
	Cache::val_type val1 = (void*) new int(1);
	Cache::index_type size1 = sizeof (int);

	Cache::key_type key2 = "key2";
	Cache::val_type val2 = (void*) new int(2);
	Cache::index_type size2 = sizeof (int);

	Cache::key_type key3 = "key3";
	Cache::val_type val3 = (void*) new int(3);
	Cache::index_type size3 = sizeof (int);

	Cache::key_type key4 = "key4";
	Cache::val_type val4 = (void*) new int(4);
	Cache::index_type size4 = sizeof (int);

	Cache::index_type get_size = 1;

	Cache cache(size1 + size2 + size3);

	cache.set(key1, val1, size1);
	cache.set(key2, val2, size2);
	cache.set(key3, val3, size3);

	assert (cache.space_used() == size1 + size2 + size3);
	assert (*((int*) cache.get(key1, get_size)) == *((int*)val1));
	assert(get_size == size1);
	assert (*((int*) cache.get(key2, get_size)) == *((int*)val2));
	assert(get_size == size2);
	assert (*((int*) cache.get(key3, get_size)) == *((int*)val3));
	assert(get_size == size3);

	cache.set(key4, val4, size4);

	assert(cache.space_used() == size2 + size3 + size4);
	assert (cache.get(key1, get_size) == nullptr);
	assert(get_size == 0);
	assert (*((int*) cache.get(key2, get_size)) == *((int*)val2));
	assert(get_size == size2);
	assert (*((int*) cache.get(key3, get_size)) == *((int*)val3));
	assert(get_size == size3);
	assert (*((int*) cache.get(key4, get_size)) == *((int*)val4));
	assert(get_size == size4);

	cache.set(key1, val1, size1);

	assert(cache.space_used() == size3 + size4 + size1);
	assert (*((int*) cache.get(key1, get_size)) == *((int*)val1));
	assert(get_size == size1);
	assert (cache.get(key2, get_size) == nullptr);
	assert(get_size == 0);
	assert (*((int*) cache.get(key3, get_size)) == *((int*)val3));
	assert(get_size == size3);
	assert (*((int*) cache.get(key4, get_size)) == *((int*)val4));
	assert(get_size == size4);

	delete (int*) val1;
	delete (int*) val2;
	delete (int*) val3;
	delete (int*) val4;

	std::cout << "Passed the FIFO tests\n";
}

// Tests the functionality of a cache when overflow occurs while using an LRU evictor.
void LRU_overflow_test() {
	
	Cache::key_type key1 = "key1";
	Cache::val_type val1 = (void*) new int(1);
	Cache::index_type size1 = sizeof (int);

	Cache::key_type key2 = "key2";
	Cache::val_type val2 = (void*) new int(2);
	Cache::index_type size2 = sizeof (int);

	Cache::key_type key3 = "key3";
	Cache::val_type val3 = (void*) new int(3);
	Cache::index_type size3 = sizeof (int);

	Cache::key_type key4 = "key4";
	Cache::val_type val4 = (void*) new int(4);
	Cache::index_type size4 = sizeof (int);

	Cache::index_type get_size = 1;

	Cache cache(size1 + size2 + size3);

	cache.set(key1, val1, size1);
	cache.set(key2, val2, size2);
	cache.set(key3, val3, size3);

	assert (cache.space_used() == size1 + size2 + size3);
	assert (*((int*) cache.get(key3, get_size)) == *((int*)val3));
	assert(get_size == size3);
	assert (*((int*) cache.get(key2, get_size)) == *((int*)val2));
	assert(get_size == size2);
	assert (*((int*) cache.get(key1, get_size)) == *((int*)val1));
	assert(get_size == size1);

	cache.set(key4, val4, size4);

	assert(cache.space_used() == size1 + size2 + size4);
	assert (*((int*) cache.get(key1, get_size)) == *((int*) val1));
	assert(get_size == size1);
	assert (*((int*) cache.get(key2, get_size)) == *((int*)val2));
	assert(get_size == size2);
	assert (cache.get(key3, get_size) == nullptr);
	assert(get_size == 0);
	assert (*((int*) cache.get(key4, get_size)) == *((int*)val4));
	assert(get_size == size4);

	cache.set(key3, val3, size3);

	assert(cache.space_used() == size3 + size4 + size1);
	assert (cache.get(key1, get_size) == nullptr);
	assert(get_size == 0);
	assert (*((int*) cache.get(key2, get_size)) == *((int*)val2));
	assert(get_size == size2);
	assert (*((int*) cache.get(key3, get_size)) == *((int*)val3));
	assert(get_size == size3);
	assert (*((int*) cache.get(key4, get_size)) == *((int*)val4));
	assert(get_size == size4);

	delete (int*) val1;
	delete (int*) val2;
	delete (int*) val3;
	delete (int*) val4;

	std::cout << "Passed the LRU tests\n";
}

// Runs tests to verify cache functionality.  One of FIFO_overflow_test or LRU_overflow_test should
// be commented out, so that FIFO_overflow_test runs when the cache is using a FIFO replacement policy,
// and LRU_overflow_test runs when the cache is using an LRU replacement policy.  
int main () {
	basic_nonoverflow_test();
	//FIFO_overflow_test();
	LRU_overflow_test();
	std::cout << "Passed all the tests\n";
	return 1;
}