#include "ft_ls.h"
#include <string.h>

int	sort_paths_time_reverse(void *s1, void *s2)
{
	return (sort_paths_time(s2, s1));
}

int	sort_paths_time(void *s1, void *s2)
{
	t_info	*p1 = s1;
	t_info	*p2 = s2;

	if (p1->st.st_mtim.tv_sec != p2->st.st_mtim.tv_sec)
	{
		return (p2->st.st_mtim.tv_sec - p1->st.st_mtim.tv_sec);
	}
	else if (p1->st.st_mtim.tv_nsec != p2->st.st_mtim.tv_nsec)
	{
		return (p2->st.st_mtim.tv_nsec - p1->st.st_mtim.tv_nsec);
	}
	return (sort_paths(s1, s2));
}

int	sort_paths_reverse(void *s1, void *s2)
{
	return (sort_paths(s2, s1));
}

int	sort_paths(void *s1, void *s2)
{
	return (ft_strcmp(((t_info *)s1)->name, ((t_info *)s2)->name));
}

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
