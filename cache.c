#include <string.h>

#include "cache.h"
#include "stats.h"


void cache_init() {
	int i = 0;
	for (i = 0; i < CACHE_SIZE; i++) {
		cache[i].path[0] = 0;
		cache[i].root = -1;
	}

	cache_pos = 0;
}

int cache_lookup(const char *path) {
	int i = 0;
	for (i = 0; i < CACHE_SIZE; i++) {
		int pos = cache_pos - i;
		if (pos < 0) pos += CACHE_SIZE;

		if (strcmp(cache[pos].path, path) == 0) {
			if (stats_enabled) stats_cache_hits++;
			return cache[pos].root;
		}
	}

	if (stats_enabled) stats_cache_misses++;

	return -1;
}

void cache_invalidate(const char *path) {
	int i = 0;
	for (i = 0; i < CACHE_SIZE; i++) {
		int pos = cache_pos - i;
		if (pos < 0) pos += CACHE_SIZE;

		if (strcmp(cache[pos].path, path) == 0) {
			cache[pos].path[0] = 0;
			cache[pos].root = -1;
		}
	}
}

void cache_save(const char *path, int root) {
	cache_pos++;
	cache_pos %= CACHE_SIZE;

	strcpy(cache[cache_pos].path, path);
	cache[cache_pos].root = root;
}
