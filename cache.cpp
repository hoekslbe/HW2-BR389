#include "cache.hh"



// At least there's no pImpl_->pop()


struct Cache::Impl {

		Impl(){
		};
		~Impl(){
		};
		/* look for key in cache, if something exists with key, overwrite it to new value, otherwise 
		if there's space for new key-value pair, add value to the cache with key. 
		if there is no space, evict something from the cache so it can 
		*/
		//do we need to use Cache:: everywhere for the types, or can we define them above?  SHOULD we base them on cache?  
		// Also, can we just use the map from stdl?  why couldn't we?  Yep, change to map
		// map of linked lists
		void set(Cache::key_type key, Cache::val_type val, Cache::index_type size){
			Cache::index_type current_space = space_used();
			while current_space + size > maxmem:
			unsigned found_at = find_item(key);
			if (found_at < cache_map.size()) {
				
			} else {
				
			}
		}

		// retrieve a pointer to the value associated with key in cache,
		// or NULL if not found.
		// sets actual size of the returned value (in bytes) in val_size
		val_type get(Cache::key_type key, Cache::index_type& size){
			unsigned found_at = find_item(key);
			if (found_at < cache_map.size()) {
				size = cache_map[found_at][2];
				return cache_map[found_at][1];
			} else {
				return NULL;
			}

		}

		// delete an object from the cache if it is there 
		void del(Cache::key_type key){
			unsigned found_at = find_item(key);
			if (found_at < cache_map.size()) {
				 cache_map.erase(cache_map.begin() + found_at)
			}
		}
		// compute the total amount of memory used up by all cache values (not keys)
		Cache::index_type space_used(){
			Cache::index_type total_space_used = 0;
			for (unsigned i = 0; i < cache_map.size(); i++) {
				total_space_used += cache_map[i][2];
			}
			return total_space_used;
		}
		unsigned find_item (Cache::key_type key) {
			unsigned i = 0;
			for (; i < cache_map.size(), i++) {
				if (cache_map[i][0] == key) {
					return i;
				}
			} 
			return i; //i is 1 past the end of cache_map
		}
		void evict () {
		
		}
		std::unordered_map<Cache::key_type, 
		std::pair<Cache::val_type, Cache::index_type>>;

};

// construct the cache and consequently the Impl
Cache::Cache(Cache::index_type maxmem, Cache::evictor_type evictor = [](){return 0;},
	hash_func hasher = std::hash<std::string>()) 
	: pImpl_(new Impl(maxmem, evictor, hasher));
{
}; 

Cache::~Cache(){
};

void Cache::set(Cache::key_type key, Cache::val_type val, Cache::index_type size){
	pImpl_->set(key, val);
};

// Call get in Impl
Cache::val_type Cache::get(Cache::key_type key, Cache::index_type& size){
	return pImpl_->get(key, size);
};

void Cache::del(Cache::key_type key){
	pImpl_->del(key);
};

Cache::index_type Cache::space_used(){
	return pImpl_->space_used();
};