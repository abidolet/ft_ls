#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_data	data = {0};

	parse(argc, argv, &data);
	run(&data);
	free_all(&data);
	return (data.exit_code);
}