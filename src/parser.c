#include "codexion.h"

static int	parse_number(char *str, int *number)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	if (!str[0])
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		if (value > (INT_MAX - (str[i] - '0')) / 10)
			return (1);
		value = value * 10 + (str[i] - '0');
		i++;
	}
	*number = value;
	return (0);
}

static int	validate_numbers(char **argv, t_config *config)
{
	if (parse_number(argv[1], &config->number_of_coders)
		|| parse_number(argv[2], &config->time_to_burnout)
		|| parse_number(argv[3], &config->time_to_compile)
		|| parse_number(argv[4], &config->time_to_debug)
		|| parse_number(argv[5], &config->time_to_refactor)
		|| parse_number(argv[6], &config->number_of_compiles_required)
		|| parse_number(argv[7], &config->dongle_cooldown))
		return (1);
	if (config->number_of_coders < 1
		|| config->number_of_compiles_required < 1)
		return (1);
	return (0);
}

int	parse_args(int argc, char **argv, t_config *config)
{
	if (argc != 9)
	{
		fprintf(stderr, "Error: expected 8 arguments\n");
		return (1);
	}
	if (validate_numbers(argv, config))
	{
		fprintf(stderr, "Error: invalid numeric argument\n");
		return (1);
	}
	if (strcmp(argv[8], "fifo") == 0)
		config->scheduler = FIFO;
	else if (strcmp(argv[8], "edf") == 0)
		config->scheduler = EDF;
	else
	{
		fprintf(stderr, "Error: scheduler must be fifo or edf\n");
		return (1);
	}
	return (0);
}
