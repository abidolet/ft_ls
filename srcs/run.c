#include "ft_ls.h"

void	list(char *path, t_data *data)
{
	if (access(path, R_OK) == -1)
	{
		ft_dprintf(2, "ft_ls: cannot open directory '%s': Permission denied\n", path);
		data->exit_code = 2;
		return ;
	}

	ft_printf("\n%s:\n", path);
	ft_printf("TODO\n");
}

void	run(t_data *data)
{
	if (ft_lstsize(data->files) > 0)
	{
		data->files = ft_lstsort(data->files, sort_paths);

		t_list	*tmp = data->files;
		while (tmp)
		{
			ft_printf("%s  ", tmp->content);
			tmp = tmp->next;
		}

		ft_lstclear(&data->files, free);
		ft_printf("\n");
	}

	if (ft_lstsize(data->paths) > 0)
	{
		data->paths = ft_lstsort(data->paths, sort_paths);

		t_list	*tmp = data->paths;
		while (tmp)
		{
			list(tmp->content, data);
			tmp = tmp->next;
		}

		ft_lstclear(&data->paths, free);
	}
	else if (ft_lstsize(data->files) > 0)
	{
		list(".", data);
	}
}