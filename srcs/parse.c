#include "ft_ls.h"
#include "parsing_bonus.h"

static void	parse_args(char *arg, t_data *data)
{
	struct stat	st;
	t_list		*new_node = NULL;
	t_info		*info;

	if (lstat(arg, &st) == -1)
	{
		ft_dprintf(2, "ft_ls: cannot access '%s': No such file or directory\n", arg);
		data->exit_code = 2;
	}
	else if (S_ISREG(st.st_mode))
	{
		check_mem(INFO, ft_calloc(1, sizeof(t_info)), (void **)&info, data);
		info->name = arg;
		info->st = st;
		check_mem(INFO, ft_lstnew(info), (void **)&new_node, data);
		ft_lstadd_back(&data->files, new_node);
	}
	else if (S_ISDIR(st.st_mode))
	{
		check_mem(INFO, ft_calloc(1, sizeof(t_info)), (void **)&info, data);
		info->name = arg;
		info->st = st;
		check_mem(INFO, ft_lstnew(info), (void **)&new_node, data);
		ft_lstadd_back(&data->paths, new_node);
	}
	else
	{
		ft_dprintf(2, "ft_ls: cannot access '%s': No such file or directory\n", arg);
	}
}

void	parse(int argc, char **argv, t_data *data)
{
	for (int i = 1; i < argc; i++)
	{
		if (*argv[i] != '-' || !*(argv[i] + 1))
		{
			parse_args(argv[i], data);
		}
		else
		{
			parse_options(argv[i] + 1, &data->options);
		}
	}

	if (data->paths == NULL && data->files == NULL
		&& data->exit_code == 0)
	{
		parse_args(".", data);
	}

	if (data->options & NO_SORT)
	{
		data->options &= ~TIME;
		data->options &= ~UTIME;
		data->options &= ~LONG;
		data->options &= ~GLONG;
		data->options |= ALL;
	}
}
