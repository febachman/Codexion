
#include "codexion.h"

static int	request_before(t_priority_queue *queue,
		t_request *a, t_request *b)
{
	if (queue->scheduler == FIFO)
		return (a->sequence < b->sequence);
	if (a->deadline != b->deadline)
		return (a->deadline < b->deadline);
	return (a->sequence < b->sequence);
}

static void	sift_up(t_priority_queue *queue, int index)
{
	int	parent;
	t_request	temp;

	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (!request_before(queue, &queue->items[index],
				&queue->items[parent]))
			break ;
		temp = queue->items[index];
		queue->items[index] = queue->items[parent];
		queue->items[parent] = temp;
		index = parent;
	}
}

static void	sift_down(t_priority_queue *queue, int index)
{
	int	child;
	t_request	temp;

	while (index * 2 + 1 < queue->size)
	{
		child = index * 2 + 1;
		if (child + 1 < queue->size
			&& request_before(queue, &queue->items[child + 1],
				&queue->items[child]))
			child++;
		if (!request_before(queue, &queue->items[child],
				&queue->items[index]))
			break ;
		temp = queue->items[index];
		queue->items[index] = queue->items[child];
		queue->items[child] = temp;
		index = child;
	}
}

int	queue_push(t_priority_queue *queue, t_request request)
{
	if (queue->size >= queue->capacity)
		return (1);
	request.sequence = queue->next_sequence++;
	queue->items[queue->size] = request;
	sift_up(queue, queue->size);
	queue->size++;
	return (0);
}

int	queue_pop(t_priority_queue *queue, t_request *request)
{
	if (queue->size == 0)
		return (1);
	*request = queue->items[0];
	queue->size--;
	if (queue->size > 0)
	{
		queue->items[0] = queue->items[queue->size];
		sift_down(queue, 0);
	}
	return (0);
}
