#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

typedef struct s_data
{
	t_list	*paths;
	t_list	*files;
	int		options;
	int		exit_code;
}	t_data;

# define INFO __FILE__, __LINE__, __func__

// utils.c
void	free_all(t_data *data);
void	check_mem(const char *file, const int line, const char *func,
	void *mem, void **ptr, t_data *data);
int		sort_paths(void *s1, void *s2);

// parse.c
void	parse(int argc, char **argv, t_data *data);

// run.c
void	run(t_data *data);

#endif