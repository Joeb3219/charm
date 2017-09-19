#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

#define HASHMAP_DEFAULT_SIZE 256

// We use a FNV-1a hash, as described https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
unsigned long long hash(char* key){
        unsigned long long value = (unsigned long long) 14695981039346656037ULL;
        unsigned long long fnvPrime = 1099511628211L;
        int i = 0, length = strlen(key);
        for(i = 0; i < length; i ++){
                value = value ^ key[i];
                value = value * fnvPrime;
        }
        return value;
}

Hashmap* generateHashmap(){
	int i;
	Hashmap* map = malloc(sizeof(Hashmap));
	map->capacity = HASHMAP_DEFAULT_SIZE;
	map->data = malloc(sizeof(void*) * HASHMAP_DEFAULT_SIZE);
	map->filled = 0;
	for(i = 0; i < map->capacity; i ++) map->data[i] = NULL;
	return map;
}

void destroyHashmap(Hashmap* map){
	int i = 0;
	for(i = 0; i < map->capacity; i ++){
		if(map->data[i] != NULL) free(map->data[i]);
	}
	free(map->data);
	free(map);
}

void hashmapInsert(Hashmap *map, char* key, void* value){
	int i;
	map->filled ++;
	if(map->filled == map->capacity){
		map->capacity *= 2;
		map->data = realloc(map->data, sizeof(void*) * map->capacity);
		for(i = map->capacity / 2; i < map->capacity; i ++) map->data[i] = NULL;
	}
	map->data[hash(key) % map->capacity] = value;
}

void* hashmapRead(Hashmap *map, char* key){
	return map->data[hash(key) % map->capacity];
}
