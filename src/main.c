
#include "codexion.h"

int	main(int argc, char **argv)
{
	t_program	program;

	memset(&program, 0, sizeof(program));
	if (parse_args(argc, argv, &program.config) != 0)
		return (1);
	if (init_program(&program) != 0)
		return (1);
	if (run_simulation(&program) != 0)
	{
		cleanup_program(&program);
		return (1);
	}
	cleanup_program(&program);
	return (0);
}
