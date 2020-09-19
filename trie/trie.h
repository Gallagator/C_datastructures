#ifndef TRIE_H
#define TRIE_H 

#include <stdint.h>
#include <stdbool.h>


typedef void Trie;

Trie *Trie_new(void);

bool Trie_add(Trie *trie, const char *word, void *value);

#endif
