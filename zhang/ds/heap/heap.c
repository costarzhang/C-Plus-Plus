#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef int elem_type;
typedef struct heap
{
    int capacity;
    int size;
    elem_type *elements;
} * priority_queue; //优先级队列

priority_queue init(int max_elements)
{
    priority_queue queue;
    queue = (priority_queue)malloc(sizeof(struct heap));
    if (!queue)
    {
        printf("Out of space\n");
        return NULL;
    }
    queue->elements = (elem_type *)malloc(sizeof(elem_type) * max_elements);
    if (!queue->elements)
    {
        printf("Out of space\n");
        return NULL;
    }
    queue->capacity = max_elements;
    queue->size = 0; //queue is empty
}

void insert(elem_type x, priority_queue queue)
{
    int i;
    queue->elements[0] = x; //tag
    if (queue->capacity == queue->size)
    {
        printf("Priority queue is full\n");
        return;
    }
    for (i = ++queue->size; queue->elements[i / 2] > x; i /= 2) //向上调整
        queue->elements[i] = queue->elements[i / 2];
    queue->elements[i] = x;
}

elem_type delete_min(priority_queue queue)
{
    int i, child;
    if (queue->size == 0)
    {
        printf("Priority is empty\n");
        exit(0);
    }
    queue->elements[0] = queue->elements[1];
    elem_type last_elem = queue->elements[queue->size--];
    for (i = 1; 2 * i <= queue->size; i = child)
    {
        child = 2 * i; //当前结点的左孩子
        /*找到结点i的最小孩子结点*/
        if (child != queue->size && queue->elements[child + 1] < queue->elements[child])
            child++;
        if (last_elem > queue->elements[child])
            queue->elements[i] = queue->elements[child];
        else
            break;
    }
    queue->elements[i] = last_elem;
    return queue->elements[0];
}

void up(priority_queue queue, int curr_pos)
{
    if (curr_pos < 0 || curr_pos > queue->size)
        return;
    int i;

    queue->elements[0] = queue->elements[curr_pos]; //tag

    for (i = curr_pos; queue->elements[i / 2] > queue->elements[0]; i /= 2)
        queue->elements[i] = queue->elements[i / 2];
    queue->elements[i] = queue->elements[0];
}

void down(priority_queue queue, int curr_pos)
{
    if (curr_pos < 0 || curr_pos > queue->size)
        return;
    queue->elements[0] = queue->elements[curr_pos];
    int i, child;
    for (i = curr_pos; i * 2 <= queue->size; i = child)
    {
        child = i * 2;
        if (child != queue->size && queue->elements[child + 1] < queue->elements[child])
            child++;
        if (queue->elements[0] < queue->elements[child])
            return;
        else
            queue->elements[i] = queue->elements[child];
    }
    queue->elements[i] = queue->elements[0];
}

void decrease_key(int pos, unsigned int delta, priority_queue queue)
{
    if (pos < 1 || pos > queue->size)
        return;
    queue->elements[pos] -= delta;
    up(queue, pos);
}

void increase_key(int pos, unsigned int delta, priority_queue queue)
{
    if (pos < 1 || pos > queue->size)
        return;
    queue->elements[pos] += delta;
    down(queue, pos);
}

elem_type delete_key(int pos, priority_queue queue)
{
    elem_type tmp = queue->elements[pos];
    decrease_key(pos, INT_MAX, queue);
    delete_min(queue);
    return tmp;
}

priority_queue buid_heap(elem_type *list, int size, int max_elements)
{
    priority_queue queue;
    int i;
    queue = init(max_elements);
    for (i = 0; i < size; i++)
        insert(list[i], queue);
    return queue;
}
void print_heap(priority_queue queue)
{
    for (int i = 1; i <= queue->size; i++)
        printf("%d  ", queue->elements[i]);
    printf("\n");
}
int main()
{
    elem_type list[15] = {150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130};
    priority_queue test_queue = buid_heap(list, 15, 16);
    insert(55, test_queue);
    delete_key(1, test_queue);
    print_heap(test_queue);
    delete_min(test_queue);
    print_heap(test_queue);
}