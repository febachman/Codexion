#include "codexion.h"

long long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000
		+ (long long)time.tv_usec / 1000);
}
