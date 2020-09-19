#include "trie.h"

#include <assert.h>
#include <malloc.h>

/* 128 bit bitfield to store the majority of ascii codes. 
* bit 0 is the value bit. It is set when the word is in the trie*/
struct trie_node
{
    uint64_t bitfield[2];
    void *value;
    struct trie_node **children;
};

static unsigned char get_bit_pos(char symbol);

static unsigned char nbits_set(uint64_t bitfield);

static bool bit_is_set(uint64_t bitfield1, uint64_t bitfield2, unsigned char bit_pos);

static unsigned char get_index(
        uint64_t bitfield1, uint64_t bitfield2, unsigned char bit_pos
        );

Trie *Trie_new(void)
{
    struct trie_node *trie = (struct trie_node *) malloc(sizeof(struct trie_node)); 
    if(trie == NULL)
    {
        return NULL;
    }
    trie->bitfield[0] = trie->bitfield[1] = 0;
    trie->value = 0;
    trie->children = NULL;
    return (Trie *) trie;
}

bool Trie_add(Trie *trie, const char *word, void *value)
{
    assert(trie != NULL && word != NULL); 
    struct trie_node *curr = trie;
    for(const char *c = word; *c != '\0'; c++)
    {
        char bit_pos = get_bit_pos(*c);
        size_t index = 
        if(bit_is_set(curr->bitfield[0], curr->bitfield[1], bit_pos)) 
        {
                   
        } else
        {
            
        }
    }

    return NULL;
}


static unsigned char get_bit_pos(char symbol)
{
    assert(symbol >= '!' && symbol <= '~');
    return symbol - '!' + 1;
}


static unsigned char nbits_set(uint64_t bitfield)
{
    unsigned char cnt = 0;
    while(bitfield != 0)
    {
        cnt += bitfield & 1;
        bitfield <<= 1;
    }
    return cnt;
}

static bool bit_is_set(uint64_t bitfield1, uint64_t bitfield2, unsigned char bit_pos)
{

    if(bit_pos >= 64)
    {
        return (bitfield2 << (bit_pos - 64)) & 1;
    } else 
    {
        return (bitfield1 << bit_pos) & 1; 
    } 
}

static unsigned char get_child_index(
        uint64_t bitfield1, uint64_t bitfield2, unsigned char bit_pos
        )
{
    if(bit_pos >= 64)
    {
        uint64_t bitmask = 0;
        bitmask = ~bitmask << (127 - bit_pos);
        return nbits_set(bitfield1) + nbits_set(bitfield2 & bitmask);
    } else
    {
        return nbits_set(bitfield1);
    }
}

