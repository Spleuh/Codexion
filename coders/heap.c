/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:06:54 by jsam              #+#    #+#             */
/*   Updated: 2026/04/21 19:06:58 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	swap(t_node *a, t_node *b)
{
	t_node	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	heapify_up(t_heap *heap, int i)
{
	int	i_parent;

	while (i > 0)
	{
		i_parent = (i - 1) / 2;
		if (heap->tree[i_parent].ts_req < heap->tree[i].ts_req)
			break ;
		swap(&heap->tree[i_parent], &heap->tree[i]);
		i = i_parent;
	}
}

void	heapify_down(t_heap *heap, int i)
{
	int	left;
	int	right;
	int	smallest;

	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		smallest = i;
		if (left < heap->size
			&& heap->tree[left].ts_req < heap->tree[smallest].ts_req)
			smallest = left;
		if (right < heap->size
			&& heap->tree[right].ts_req < heap->tree[smallest].ts_req)
			smallest = right;
		if (smallest == i)
			break ;
		swap(&heap->tree[i], &heap->tree[smallest]);
		i = smallest;
	}
}

void	heap_insert(t_heap *heap, t_node node)
{
	if (heap->size >= heap->max_size)
		return ;
	heap->tree[heap->size] = node;
	heapify_up(heap, heap->size);
	heap->size++;
}

void	heap_pop(t_heap *heap)
{
	if (heap->size <= 0)
		return ;
	heap->size--;
	heap->tree[0] = heap->tree[heap->size];
	heapify_down(heap, 0);
}
