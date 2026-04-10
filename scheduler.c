#include "codexion.h"


int	get_id_edf(t_heap *heap)
{
	int	id;
	int	i;
	long	tmp;

	id = -1;
	i = 0;
	while (i < heap->size)
	{
		printf("arr[i] id coder: %d\n", heap->arr[i].coder_id);
		if (id < 0)
		{
			id = heap->arr[i].coder_id;
			tmp = heap->arr[i].deadline;
		}
		else if (tmp < heap->arr[i].deadline)
		{
			id = heap->arr[i].coder_id;
			tmp = heap->arr[i].deadline;
		}
		i++;
	}
	printf("get id edf : %d\n", id);
	return (id);
}

