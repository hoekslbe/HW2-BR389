#include "cache.hh"

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
		// 
		void set(Cache::key_type key, Cache::val_type val, Cache::index_type size){
			auto found_at = cache_map.find(key);
			if (found_at != cache_map.end()) {
				// evict the element at found at's position 
			}
			// while (space_used + size > maxmem) evict things from 
			// the cache until there is enough space for the element
			// we want to add 

			// cache_map[key] = std::pair<val, size> 
			// increment space_used somehow 
			while (current_space + size > maxmem) {
				unsigned found_at = find_item(key);
			}
			
			if (found_at < cache_map.size()) {
				
			} else {
				
			}
		}

		// retrieve a pointer to the value associated with key in cache,
		// or NULL if not found.
		// sets actual size of the returned value (in bytes) in val_size
		val_type get(Cache::key_type key, Cache::index_type& size){
			// return an iterator set to the key element if it exists
			// and set to the end of the cache_map if it does not
			auto found_at = cache_map.find(key);
			if (found_at != cache_map.end()) {
				// set size reference to the size of the map element
				size = found_at->second->second;
				// return value for key at iterator from val, size pair
				return found_at->second->first;

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

		// unsigned find_item (Cache::key_type key) {
		// 	unsigned i = 0;
		// 	for (; i < cache_map.size(), i++) {
		// 		if (cache_map[i][0] == key) {
		// 			return i;
		// 		}
		// 	} 
		// 	return i; //i is 1 past the end of cache_map
		// }
		void evict () {
		
		}

		// evict something specific using the iterator to its position given by find() in the map
		void evict_at (std::iterator<string, void*>) {


		}
		//std::unordered_map< Cache::key_type, std::pair < Cache::val_type, Cache::index_type > > cache_map;
		std::unordered_map<std::string, void*> cache_map;


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