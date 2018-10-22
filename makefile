all: cachetest

cachetest: cachetest.o cache.o evictors.o
	g++ -o cachetest cachetest.o cache.o evictors.o -Wall -Werror -Wextra -pedantic

cachetest.o: cachetest.cpp
	g++ -c cachetest.cpp -Wall -Werror -Wextra -pedantic

cache.o: cache.cpp evictors.o
	g++ -c cache.cpp -Wall -Werror -Wextra -pedantic

evictors.o: evictors.cpp
	g++ -c evictors.cpp -Wall -Werror -Wextra -pedantic

clean: 
	rm -f *.o