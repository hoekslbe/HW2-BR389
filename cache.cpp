#include "cache.hh"


class C_imPl {

	public:

		C_imPl(){
		};
		~C_imPl(){
		};
		/* look for key in cache, if something exists with key, overwrite it to new value, otherwise 
		if there's space for new key-value pair, add value to the cache with key. 
		if there is no space, evict something from the cache so it can 
		*/
		void set(){

		}

		// retrieve a pointer to the value associated with key in cache,
		// or NULL if not found.
		// sets actual size of the returned value (in bytes) in val_size
		val_type get(){

		}

		// delete an object from the cache if it is there 
		void del(){

		}
		// compute the total amount of memory used up by all cache values (not keys)
		index_type space_used(){

		}
	private:
		std::vector<std::tuple<key_type key, val_type val, index_type size>> cache_map; 

};

// construct the cache and consequently the cimpl
Cache::Cache(index_type maxmem, evictor_type evictor = [](){return 0;},
	hash_func hasher = std::hash<std::string>()) {
	pImpl_ = new C_imPl();
}; 

Cache::~Cache(){
	delete pImpl_;
};

void Cache::set(key_type key, val_type val, index_type size){
	pImpl_->set(key, val, size);
};

// Call get in C_imPl
val_type Cache::get(key_type key, index_type& size){
	return pImpl_->get(key, size);
};

void Cache::del(key_type key){
	pImpl_->del(key);
};

index_type Cache::space_used(){
	return pImpl_->space_used();
};