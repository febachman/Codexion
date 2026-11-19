#include "codexion.h"

void	print_status(t_program *program, int coder_id, char *message)
{
	long long	timestamp;

	pthread_mutex_lock(&program->print_lock);
	timestamp = get_time_ms() - program->start_time;
	printf("%lld %d %s\n", timestamp, coder_id, message);
	pthread_mutex_unlock(&program->print_lock);
}
