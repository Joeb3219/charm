#ifndef HASHMAP_H_
#define HASHMAP_H_

	struct Hashmap{
		int capacity;
		int filled;
		void** data;
	};

	typedef struct Hashmap Hashmap;

	unsigned long long hash(char* key);
	Hashmap* generateHashmap();
	void hashmapInsert(Hashmap *map, char* key, void* value);
	void* hashmapRead(Hashmap* map, char* key);
	void destroyHashmap(Hashmap* map);

#endif
