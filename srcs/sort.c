#include "ft_ls.h"
#include "parsing_bonus.h"

int	sort_paths(void *s1, void *s2)
{
	return (ft_strcmp(((t_info *)s1)->name, ((t_info *)s2)->name));
}

int	sort_paths_mtim(void *s1, void *s2)
{
	const struct timespec *st1 = &((t_info *)s1)->st.st_mtim;
	const struct timespec *st2 = &((t_info *)s2)->st.st_mtim;

	if (st1->tv_sec != st2->tv_sec)
	{
		return (st2->tv_sec - st1->tv_sec);
	}
	else if (st1->tv_nsec != st2->tv_nsec)
	{
		return (st2->tv_nsec - st1->tv_nsec);
	}
	return (sort_paths(s1, s2));
}

int	sort_paths_atim(void *s1, void *s2)
{
	const struct timespec *st1 = &((t_info *)s1)->st.st_atim;
	const struct timespec *st2 = &((t_info *)s2)->st.st_atim;

	if (st1->tv_sec != st2->tv_sec)
	{
		return (st2->tv_sec - st1->tv_sec);
	}
	else if (st1->tv_nsec != st2->tv_nsec)
	{
		return (st2->tv_nsec - st1->tv_nsec);
	}
	return (sort_paths(s1, s2));
}
 
void	sort(int options, t_list **files)
{
	if (options & NO_SORT)
	{
		return ;
	}

    if (options & UTIME)
    {
		if ((options & LONG || options & GLONG) && !(options & TIME))
		{
			*files = ft_lstsort(*files, sort_paths);
		}
		else
		{
			*files = ft_lstsort(*files, sort_paths_atim);
		}
    }
	else if (options & TIME)
	{
		*files = ft_lstsort(*files, sort_paths_mtim);
	}
	else
	{
		*files = ft_lstsort(*files, sort_paths);
	}

	if (options & REVERSE)
	{
		ft_lstreverse(files);
	}
}
