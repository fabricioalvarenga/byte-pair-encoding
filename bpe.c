#include <stdio.h>
#include <string.h>

#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"


typedef struct {
    char *key;
    size_t value;
} Freq;

typedef struct {
    Freq *items;
    size_t count;
    size_t capacity;
} Freqs;

/*
 * The comparison function must return an integer less than, equal to,
 * or greater than zero if the first argument is considered to be
 * respectively less than, equal to, or greater than the second.
*/
int compare_freqs(const void *a, const void *b) {
    const Freq *af = a;
    const Freq *bf = b;
    return (int)bf->value - (int)af->value;
}

int main() {
    const char *text = "The original BPE algorithm operates by iteratively replacing the most common contiguous sequences of characters in a target text with unused 'placeholder' bytes. The iteration ends when no sequences can be found, leaving the target text effectively compressed. Decompression can be performed by reversing this process, querying known placeholder terms against their corresponding denoted sequence, using a lookup table. In the original paper, this lookup table is encoded and stored alongside the compressed text.";
    int text_size = strlen(text);

    Freq *freq = NULL;

    for (int i = 0; i < text_size-1; ++i) {
        char *pair = (char *)malloc(3 * sizeof(char));
        if (pair == NULL) return 1; 

        pair[0] = text[i];
        pair[1] = text[i+1];
        pair[2] = '\0';

        ptrdiff_t j = shgeti(freq, pair);
        if (j < 0) shput(freq, pair, 1);
        else freq[j].value += 1;
    }

/*    Freqs sorted_freqs = { 0 };

    for (ptrdiff_t i = 0; i < shlen(freq); ++i) {
        nob_da_append(&sorted_freqs, freq[i]);
    }

    qsort(sorted_freqs.items, sorted_freqs.count, sizeof(*sorted_freqs.items), compare_freqs);
*/

    qsort(freq, shlen(freq), sizeof(Freq), compare_freqs);

    for (ptrdiff_t i = 0; i < shlen(freq); ++i) {
        Freq *f = &freq[i];
        printf("%c%c => %zu\n", f->key[0], f->key[1], f->value);
    }

    shfree(freq);

    return 0;
}
