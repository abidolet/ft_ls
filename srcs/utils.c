#include "ft_ls.h"

void	free_all(t_data *data)
{
	ft_lstclear(&data->paths, free);
	ft_lstclear(&data->files, free);
}

void	check_mem(const char *file, const int line, const char *func,
	void *mem, void **ptr, t_data *data)
{
	if (!mem)
	{
		ft_dprintf(2, "ft_nm: %s%s:%d: %smalloc assertion failed in %s'%s'\n",
			GRAY, file, line, RED, RESET, func);
		free_all(data);
		exit(2);
	}
	*ptr = mem;
}
