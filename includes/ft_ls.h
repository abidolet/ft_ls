#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <sys/stat.h>

typedef struct s_info
{
	char		*name;
	struct stat	st;
}	t_info;

typedef struct s_data
{
	t_list	*paths;
	t_list	*files;
	int		options;
	char	*path;
	int		exit_code;
	int		padding_links;
	int		padding_size;
}	t_data;

# define INFO __FILE__, __LINE__, __func__

// parse.c
void	parse(int argc, char **argv, t_data *data);

// run.c
void	run(t_data *data);

// sort.c
void	sort(int options, t_list **files);

// utils.c
void	free_all(t_data *data);
void	check_mem(const char *file, const int line, const char *func,
	void *mem, void **ptr, t_data *data);

#endif