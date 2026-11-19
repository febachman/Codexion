#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_config
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	t_scheduler		scheduler;
}	t_config;

typedef struct s_request
{
	int				coder_id;
	long long		request_time;
	long long		deadline;
	unsigned long	sequence;
}	t_request;

typedef struct s_priority_queue
{
	t_request		*items;
	int				size;
	int				capacity;
	unsigned long	next_sequence;
	t_scheduler		scheduler;
}	t_priority_queue;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	long long		available_at;
}	t_dongle;

typedef struct s_program	t_program;

typedef struct s_coder
{
	int				id;
	int				left_dongle;
	int				right_dongle;
	int				compiles_done;
	long long		last_compile_start;
	pthread_t		thread;
	t_program		*program;
}	t_coder;

struct s_program
{
	t_config			config;
	long long			start_time;
	int					active;
	int					finished_count;
	t_coder				*coders;
	t_dongle			*dongles;
	t_priority_queue	queue;
	pthread_mutex_t		lock;
	pthread_mutex_t		print_lock;
	pthread_cond_t		condition;
	int					dongles_initialized;
	int					lock_initialized;
	int					print_lock_initialized;
	int					condition_initialized;
	int					queue_initialized;
	pthread_t			monitor;
};

int		parse_args(int argc, char **argv, t_config *config);

int		init_program(t_program *program);
int		run_simulation(t_program *program);
void	cleanup_program(t_program *program);

void	*coder_routine(void *arg);
void	*monitor_routine(void *arg);

int		init_queue(t_priority_queue *queue, int capacity,
			t_scheduler scheduler);
void	destroy_queue(t_priority_queue *queue);
int		queue_push(t_priority_queue *queue, t_request request);
int		queue_pop(t_priority_queue *queue, t_request *request);

long long	get_time_ms(void);
void	print_status(t_program *program, int coder_id, char *message);

#endif
