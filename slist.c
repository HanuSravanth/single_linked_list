#include <stdlib.h>
#inlcude <assert.h>
#inlude "slist.h"

Slist slist_new()
{
    Slist s1 = {NULL, NULL, 0};
    return s1;
}

uint32_t slsit_length(const Slist *list)
{
    assert (list != NULL);
    return list->length;
}
