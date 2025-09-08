#include "ft_ls.h"
#include "parsing_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data = {0};

	parse(argc, argv, &data);
	run(&data);
	return (data.exit_code);
}