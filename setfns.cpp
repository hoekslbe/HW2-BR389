// test the functionality of the set function on a cache in a variety
// of cases 
TEST_CASE ("Testing SET functionality") {

	Cache::index_type maxmem = 3;
	Cache set_test_cache(maxmem);

	Cache::key_type key1 = "first_key";
	Cache::val_type val1 = (void*) new int(1);
	Cache::index_type size = sizeof(int);

	Cache::key_type key2 = "second_key";
	Cache::val_type val2 = (void*) new int(2);


	// set get_size to a random int value that will be changed 
	// when a get is run to reflect the size of the value gotten
	Cache::index_type get_size = 1;

	SECTION ("Set a value in an empty cache") {
		
		set_test_cache.set(key1, val1, size);

		Cache::val_type get_result = set_test_cache.get(key1, get_size) 

		// Check that the get method on the key returns a pointer to the expected
		// value associated with that key
		REQUIRE( *((int*) get_result) == *((int*) val1));
	}

	SECTION ("Set a value overwriting a previous val in cache") {
		// Set a value into the cache that can be overwritten
		set_test_cache.set(key1, val1, size);
		Cache::index_type get_size = sizeof(int);

	}

	SECTION ("Set a new value in a cache with a preexisting element") {
		set_test_cache.set(key1, val1, size);
		set_test_cache.set(key2, val2, size);

		REQUIRE( );
	}

	SECTION ("Try to set a value in a full cache") {
		// filling cache
		set_test_cache.set(key1, val1, size);
		set_test_cache.set(key2, val2, size);
		set_test_cache.set(key3, val3, size);
		// setting to full cache
		set_test_cache.set(key4, val4, size);

		REQUIRE( *((int*) set_test_cache.get(key4, get_size) == ));
	}
	delete (*int) val1;
	delete (*int) val2;
	delete (*int) val3;
	delete (*int) val4;

}