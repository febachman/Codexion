
#include "codexion.h"

int	init_queue(t_priority_queue *queue, int capacity,
		t_scheduler scheduler)
{
	queue->items = malloc(sizeof(t_request) * capacity);
	if (!queue->items)
		return (1);
	queue->size = 0;
	queue->capacity = capacity;
	queue->next_sequence = 0;
	queue->scheduler = scheduler;
	return (0);
}

void	destroy_queue(t_priority_queue *queue)
{
	free(queue->items);
	queue->items = NULL;
	queue->size = 0;
	queue->capacity = 0;
}
