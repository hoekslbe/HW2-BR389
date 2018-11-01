#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <utility>

#include "cache.hh"


// This object handles teardown for our tests.  In each test case, we create an instance, and pass it the pointers
// which will need to be deleted after the test.  When the Cleaner goes out of scope, its destructor deletes all
// the pointers we passed to it.  
// This is to avoid un-freed memory hanging around after a failed REQUIRE in testing.  
struct Cleaner {
	Cleaner(){}
	~Cleaner(){
		while (not items_.empty()) {
			auto to_remove = items_.back();
			operator delete((void*) to_remove.first, to_remove.second);
			items_.pop_back();
		}
	}
	void add (Cache::val_type val, Cache::index_type size) {
		items_.push_back(std::make_pair(val, size));
	}
	std::vector<std::pair<Cache::val_type, Cache::index_type>> items_;
};

TEST_CASE ("Testing GET"){
	Cleaner cleanup;

	Cache::key_type key = "cachekey";
	Cache::val_type val = (void*) new int(3);
	Cache::index_type size = sizeof(int);
	cleanup.add(val, size);

	Cache::val_type val2 = (void*) new double(4.0);
	Cache::index_type size2 = sizeof(double);
	cleanup.add(val2, size2);

	Cache::index_type get_size = 1;

	Cache cache(size + size2 + 1);

	SECTION ("Getting an item present in the cache returns the item") {
		cache.set(key, val, size);
		Cache::val_type out = cache.get(key, get_size);
		REQUIRE(*((int*) out) == *((int*) val));
	}

	SECTION ("Get sets valsize to the size of the returned object") {
		cache.set(key, val, size);
		cache.get(key, get_size);
		REQUIRE(get_size == size);
	}

	SECTION ("Get doesn't have a hard-coded val_size to return") {
		cache.set(key, val2, size2);
		cache.get(key, get_size);
		REQUIRE(get_size == size2);
	}

	SECTION ("Getting an item not in the cache returns nullptr") {
		Cache::val_type out = cache.get(key, get_size);
		REQUIRE(out == nullptr);
	}
}

TEST_CASE ("Testing SPACE_USED") {
	Cleaner cleanup;

	Cache::key_type key = "cachekey";
	Cache::val_type val = (void*) new int(3);
	Cache::index_type size = sizeof(int);
	cleanup.add(val, size);

	Cache cache(size + 1);

	SECTION ("Space used by an empty cache is 0") {
		REQUIRE(cache.space_used() == 0);
	}

	SECTION ("Adding an item increases space used") {
		cache.set(key, val, size);
		REQUIRE(cache.space_used() == size);
	}

	SECTION ("Adding and then removing an item does not change space used") {
		cache.set(key, val, size);
		cache.del(key);
		REQUIRE(cache.space_used() == 0);
	}

}

TEST_CASE ("Testing DEL") {
	Cleaner cleanup;

	Cache::key_type key = "cachekey";
	Cache::val_type val = (void*) new int(3);
	Cache::index_type size = sizeof(int);
	cleanup.add(val, size);

	Cache::index_type get_size = 1;

	Cache cache(size + 1);

	SECTION ("Deleting an item present in the cache removes the item") {
		cache.set(key, val, size);
		cache.del(key);
		Cache::val_type out = cache.get(key, get_size);
		REQUIRE(out == nullptr);
	}

	SECTION ("Deleting an item that isn't in the cache does nothing") {
		cache.set(key, val, size);
		cache.del("nottherightkey");
		Cache::val_type out = cache.get(key, get_size);
		REQUIRE(*((int*) out) == *((int*) val));
	}
}