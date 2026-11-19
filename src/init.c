#include "codexion.h"

static int	init_shared(t_program *program)
{
	if (pthread_mutex_init(&program->lock, NULL) != 0)
		return (1);
	program->lock_initialized = 1;
	if (pthread_mutex_init(&program->print_lock, NULL) != 0)
		return (1);
	program->print_lock_initialized = 1;
	if (pthread_cond_init(&program->condition, NULL) != 0)
		return (1);
	program->condition_initialized = 1;
	return (0);
}

static int	allocate_data(t_program *program)
{
	int	count;

	count = program->config.number_of_coders;
	program->coders = malloc(sizeof(t_coder) * count);
	program->dongles = malloc(sizeof(t_dongle) * count);
	if (!program->coders || !program->dongles)
		return (1);
	memset(program->coders, 0, sizeof(t_coder) * count);
	memset(program->dongles, 0, sizeof(t_dongle) * count);
	if (init_queue(&program->queue, count,
		program->config.scheduler) != 0)
		return (1);
	program->queue_initialized = 1;
	return (0);
}

static int	init_dongles(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->config.number_of_coders)
	{
		if (pthread_mutex_init(&program->dongles[i].mutex, NULL) != 0)
			return (1);
		program->dongles_initialized++;
		i++;
	}
	return (0);
}

static void	init_coders(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->config.number_of_coders)
	{
		program->coders[i].id = i + 1;
		program->coders[i].left_dongle = i;
		program->coders[i].right_dongle = (i + 1)
			% program->config.number_of_coders;
		program->coders[i].compiles_done = 0;
		program->coders[i].program = program;
		i++;
	}
}

int	init_program(t_program *program)
{
	program->coders = NULL;
	program->dongles = NULL;
	program->active = 0;
	program->finished_count = 0;
	program->dongles_initialized = 0;
	program->lock_initialized = 0;
	program->print_lock_initialized = 0;
	program->condition_initialized = 0;
	program->queue_initialized = 0;
	if (init_shared(program) || allocate_data(program)
		|| init_dongles(program))
	{
		cleanup_program(program);
		return (1);
	}
	init_coders(program);
	program->start_time = get_time_ms();
	program->active = 1;
	return (0);
}
