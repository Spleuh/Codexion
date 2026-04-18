#include "codexion.h"


void    swap(t_node *a, t_node *b)
{
    t_node tmp = *a;
    *a = *b;
    *b = tmp;
}

void    heapify_up(t_heap *heap, int i)
{
    int i_parent;
    while (i > 0)
    {
        i_parent = (i - 1) / 2;

        if (heap->tree[i_parent].ts_req < heap->tree[i].ts_req)
            break;
        swap(&heap->tree[i_parent], &h->tree[i]);
        i = i_parent;
    }
}

void    heapify_down(t_heap *heap, int i)
{
    int left;
    int right;
    int smallest;

    while (1)
    {
        left = 2 * i + 1;
        right = 2 * i + 2;
        smallest = i;
        if (left < heap->size &&
            heap->tree[left].ts_req < heap->tree[smallest].ts_req)
            smallest = left;
        if (right < h->size &&
            h->tree[right].ts_req < h->tree[smallest].ts_req)
            smallest = right;
        if (smallest == i)
            break;
        swap(&heap->tree[i], &heap->tree[smallest]);
        i = smallest;
    }
}

void    heap_insert(t_heap *heap, t_node node)
{
    if (heap->size >= heap->max_size)
        return;
    heap->tree[heap->size] = node;
    heapify_up(heap, h->size);
    h->size++;
}

void    heap_pop(t_heap *heap)
{
    t_node top;

    if (heap->size <= 0)
        return ;
    top = heap->tree[0];
    heap->size--;
    heap->tree[0] = h->tree[h->size];
    heapify_down(heap, 0);
    return top;
}


// typedef struct s_node {
//     int id_coder;
//     long ts_req;   // priorité (plus petit = plus prioritaire)
// } t_node;

// typedef struct s_heap {
//     t_node *tree;
//     int size;
//     int max_size;
// } t_heap;

// t_heap heap;

// heap.tree = malloc(sizeof(t_node) * 100);
// heap.size = 0;
// heap.max_size = 100;

// heap_insert(&heap, (t_node){1, 50});
// heap_insert(&heap, (t_node){2, 10});
// heap_insert(&heap, (t_node){3, 30});

// t_node n = heap_pop(&heap);
// // n.ts_req == 10 (priorité max)