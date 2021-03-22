#include <stdio.h>
#include <stdlib.h>

typedef int elem_type;
typedef unsigned int position;
enum status
{
    legitimate,
    empty,
    deleted
};
typedef struct hash_entry
{
    elem_type e;
    enum status info;
} cell;

/*hash table*/
typedef struct hash_tb
{
    int size;
    cell *the_cells;
} * hash_table;

/*initialize table*/
hash_table init_table(int size)
{
    hash_table h;
    int i;

    h = (hash_table)malloc(sizeof(struct hash_tb));
    if (!h)
        printf("Out of space\n");
    h->size = size;
    h->the_cells = (cell *)malloc(sizeof(struct hash_entry) * h->size);
    if (!h->the_cells)
        printf("Out of space\n");
    for (i = 0; i < h->size; i++)
        h->the_cells[i].info = empty;
    return h;
}
int hash(elem_type e, int size)
{
    return e % size;
}

position find(elem_type key, hash_table h)
{
    position current_pos;
    int collision_num = 0;
    current_pos = hash(key, h->size);
    while (h->the_cells[current_pos].info != empty && h->the_cells[current_pos].e != key)
    {
        /*平方探测*/
        current_pos += 2 * ++collision_num - 1;
        if (current_pos >= h->size)
            current_pos -= h->size;
    }
    return current_pos;
}

void insert(elem_type key, hash_table h)
{
    position pos;
    pos = find(key, h);
    if (h->the_cells[pos].info != legitimate)
    {
        h->the_cells[pos].info = legitimate;
        h->the_cells[pos].e = key;
    }
}

void print_table(hash_table h)
{
    for (int i = 0; i < h->size; i++)
        printf("%d  ", h->the_cells[i].e);
    printf("\n");
}

int main()
{
    int l[5] = {89, 19, 49, 59, 69};
    hash_table test_table;
    test_table = init_table(10);
    for (int i = 0; i < 5; i++)
        insert(l[i], test_table);
    print_table((test_table));
}

/*再散列*/
