#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_empty_list()
{
    Slist s1 = slist_new();
    Slist *list = &s1;
    assert(slist_length(list) == 0);
}

int main()
{
    //printf("Hello world!\n");
    test_empty_list();
    return 0;
}
