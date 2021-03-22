#include <stdio.h>
#include <stdlib.h>
typedef int elem_type;
/*分组链接法处理冲突*/
/*list node*/
typedef struct l_node
{
    elem_type e;
    struct l_node *next;
} * list;

/*hash table*/
typedef struct hash_tb
{
    int size;
    list *the_lists;
} * hash_table;
typedef struct l_node *position;
int hash(elem_type key, int size)
{
    return key % size;
}
/*initialize hashtable*/
hash_table init_table(int size)
{
    hash_table h;
    int i;
    h = (hash_table)malloc(sizeof(struct hash_tb));
    if (!h)
        printf("Out of space\n");
    h->size = size;

    h->the_lists = (list *)malloc(sizeof(list) * h->size);
    if (!h->the_lists)
        printf("Out of space\n");

    for (i = 0; i < h->size; i++)
    {
        h->the_lists[i] = (list)malloc(sizeof(struct l_node)); //header
        if (!h->the_lists)
            printf("Out of space\n");
        else
            h->the_lists[i]->next = NULL;
    }
    return h;
}
position find(elem_type key, hash_table h)
{
    position p;
    list l;
    l = h->the_lists[hash(key, h->size)];
    p = l->next;
    while (p != NULL && p->e != key)
        p = p->next;
    return p;
}
void insert(elem_type key, hash_table h)
{
    position p;
    struct l_node *tmp;
    list l;
    p = find(key, h);
    if (!p)
    {
        tmp = (struct l_node *)malloc(sizeof(struct l_node));
        if (!tmp)
            printf("Out of space\n");
        else
            l = h->the_lists[hash(key, 10)];
        tmp->e = key;
        tmp->next = l->next;
        l->next = tmp;
    }
}

void print_l(hash_table h)
{
    int i;
    for (i = 0; i < h->size; i++)
    {
        printf("%d-->", i);
        position p;
        p = h->the_lists[i]->next;
        while (p)
        {
            printf("%d-->", p->e);
            p = p->next;
        }
        printf("\n");
    }
}
void de(elem_type key, hash_table h)
{
    position p, pre;
    position tmp;
    list l = h->the_lists[hash(key, 10)];
    pre = l;
    p = pre->next;
    while (p && p->e != key)
    {
        pre = pre->next;
        p = pre->next;
    }
    if (p)
    {
        pre->next = p->next;
        free(p);
    }
}

int main()
{
    hash_table test_table = init_table(10);
    for (int i = 0; i < 10; i++)
    {
        insert(i * i, test_table);
    }
    print_l(test_table);
    de(49, test_table);
    print_l(test_table);
    return 0;
}