# HW2-BR389

2nd Homework Assignment Betsy Hoekstra and Robert McCaull

Files:

	makefile is, of course, the makefile.  
	cachetest.cpp contains main, and the test functions which verify that the implementation of Cache is correct.  
	cache.cpp is the implementation of the Cache class in cache.hh.
	cache.hh was given - it's the header containing the class Cache.  
	evictors.hh is the header containing the two Evictor structs - FIFO_Evictor and LRU_Evictor.  evictors.cpp contains the implementations of the structs.  


Design decisions:

	Impl (the hidden implementation of Cache) is built around an unordered map which stores the user's values, and an Evictor which decides which values to get rid of when there's overflow.  Because we used the built-in unordered_map class in C++, we didn't need to make decisions about how to handle collisions, resize the container when necessary, store items, or look up items quickly - that was all handled for us.  
	Get sets val_size (the Cache::index_type reference) to 0 if the item is not in Cache, because a non-existent item has no size.  
	Set does nothing if the item it's adding is larger than the maximum memory size of the Cache, because there's no way the item could be added, even if all the other items were removed.  
	We made sure that del was the only way to remove an item from the cache, internally or externally, so that we could be sure we were using delete to free the memory associated with each item as it was removed to avoid memory leaks.  
	set and del update update the total memory used by keys as they're called, so that space_used can be easily done in constant time.  
	Whenever get, set, or delete is called, the corresponding method of _evictor is called - even though, for FIFO_Evictor, the method called with get does nothing.  This is because the assignment said to make the interface between the Cache and the Evictor as abstract as possible.  