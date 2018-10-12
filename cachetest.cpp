#include "cache.hh"

// tests the set functionality of cache by creating 
void set_test(Cache any_cache, key_type key, val_type val, index_type size) {
	
	any_cache.set(key, val, size);
	assert(any_cache)
}
void get_test(Cache any_cache) {

}
void overflow_test(Cache any_cache, index_type maxmem) {
	index_type spaces_used = Cache1.space_used();
	// fill Cache with garbage until it is intentionally overfilled
	val_type size = 8;
	while(spaces_used < maxmem) {
		Cache1.set("fillerup", 1, 8);
		spaces_used +=1;
	}
	Cache1.set("lastfill", 1, 8);
	
	val_type overflow_get_result = Cache1.get("lastfill", &size)
	// at this point, the cache should have overflowed 
	//assert(overflow_get_result = )


}

int main {
	Cache::index_type maxmem = 10;
	uint32_t* someint = new 1; 
	auto valptr = unique_ptr(someint);
	key_type key = "anykey"
	val_type val = (void*) valptr;
	hash_func = 
	Cache1 = Cache::Cache(maxmem, evictor, hasher);
	overflow_test(Cache1, maxmem);



}