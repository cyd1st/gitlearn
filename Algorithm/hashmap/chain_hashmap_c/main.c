#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HASH_KEY_LEN 30

typedef struct HashNode {
    char key[MAX_HASH_KEY_LEN + 1];
    int value;
    struct HashNode *next;
} HashNode;

typedef struct HashMap {
    int size;
    HashNode **table;
} HashMap;

// create hashmap
HashMap *CreateHashMap(int size) {
    HashMap *hashmap = (HashMap *)malloc(sizeof(HashMap));
    hashmap->size = size;
    hashmap->table = (HashNode **)calloc(size, sizeof(HashMap *));
    if (hashmap->table == NULL) {
        printf("Failed to malloc, size: %lu\n", size * sizeof(HashMap *));
        return NULL;
    }
    return hashmap;
}

// hash
int hash(HashMap *map, const char *key, int keyLen) {
    if (keyLen <= 0 || keyLen > MAX_HASH_KEY_LEN) {
        printf("[%s] keyLen is invalid, keyLen: %d\n", __FUNCTION__, keyLen);
        return -1;
    }

    int sum = 0;
    for (int i = 0; i < keyLen; i++) {
        sum += key[i];
    }
    return sum % map->size;
}

// get value
int HashGetValue(HashMap *map, const char *key, int keyLen) {
    int hashIndex = hash(map, key, keyLen);
    if (hashIndex < 0) {
        return -1;
    }

    HashNode *node = map->table[hashIndex];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }

    return -1;
}

// get hash node
HashNode *HashGetNode(HashMap *map, char *key, int keyLen) {
    int hashIndex = hash(map, key, keyLen);
    if (hashIndex < 0) {
        return NULL;
    }

    HashNode *node = map->table[hashIndex];
    if (node == NULL) {
        return NULL;
    }

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node;
        }
        node = node->next;
    }

    return NULL;
}

// hash insert
int HashInsert(HashMap *map, const char *key, int keyLen, int value) {
    if (map == NULL || keyLen <= 0 || keyLen > MAX_HASH_KEY_LEN) {
        printf("[%s\n] input value error.", __FUNCTION__);
        printf("map = %p, keyLen = %d\n", map, keyLen);
        return -1;
    }

    int hashIndex = hash(map, key, keyLen);
    if (hashIndex < 0) {
        return -1;
    }

    HashNode *node = (HashNode *)malloc(sizeof(HashNode));
    char *ret = strcpy(node->key, key);
    if (ret == 0) {
        printf("[%d] strcpy failed, ret = %s.\n", __LINE__, ret);
        return -1;
    }
    node->value = value;
    node->next = NULL;

    HashNode *cur = map->table[hashIndex];
    if (cur == NULL) {
        map->table[hashIndex] = node;
        return 0;
    }

    while (cur->next != NULL) {
        if (strcmp(cur->key, key) == 0) {
            cur->value = value;
            return 0;
        }
        cur = cur->next;
    }

    cur->next = node;
    return 0;
}

// hash delete key
int HashDeleteKey(HashMap *map, char *key, int keyLen) {
    int hashIndex = hash(map, key, keyLen);
    if (hashIndex < 0) {
        return -1;
    }

    HashNode *node = map->table[hashIndex];
    if (node == NULL) {
        // key not found
        return -1;
    }

    if (strcmp(node->key, key) == 0) {
        free(node);
        map->table[hashIndex] = NULL;
        return 0;
    }

    HashNode *prev = node;
    HashNode *cur = node->next;
    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0) {
            prev->next = cur->next;
            free(cur);
            return 0;
        }
        prev = cur;
        cur = cur->next;
    }

    // key not found
    return -1;
}

// destroy map
int DestroyHashMap(HashMap *map) {
    if (map == NULL) {
        // key not found
        return -1;
    }

    for (int i = 0; i < map->size; i++) {
        HashNode *node = map->table[i];
        if (node == NULL) {
            continue;
        }
        while (node != NULL) {
            HashNode *cur = node;
            node = node->next;
            free(cur);
        }
        return 0;
    }

    free(map->table);
    free(map);
    return 0;
}

int main() {
    HashMap* map = CreateHashMap(10);

    const char a[] = "apple";
    const char b[] = "banana";
    const char o[] = "orange";
    const char w[] = "watermelon";

    HashInsert(map, a, strlen(a), 563);
    HashInsert(map, b, strlen(b), 24367);
    HashInsert(map, o, strlen(o), 456);

    printf("Value of 'apple': %d\n", HashGetValue(map, a, strlen(a)));
    printf("Value of 'banana': %d\n", HashGetValue(map, b, strlen(b)));
    printf("Value of 'orange': %d\n", HashGetValue(map, o, strlen(o)));
    printf("Value of 'watermelon': %d\n", HashGetValue(map, w, strlen(w)));
    DestroyHashMap(map);

    return 0;
}