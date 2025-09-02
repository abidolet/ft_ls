#include "ft_ls.h"
#include "parsing.h"
#include <dirent.h>
#include <stdbool.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>

int	count_digits(int n)
{
	return (n < 10 ? 1 : 1 + count_digits(n / 10));
}

void print_file_type(mode_t mode)
{
	switch (mode & S_IFMT)
	{
		case S_IFREG:	ft_printf("-"); break;
		case S_IFDIR:	ft_printf("d"); break;
		case S_IFLNK:	ft_printf("l"); break;
		case S_IFCHR:	ft_printf("c"); break;
		case S_IFBLK:	ft_printf("b"); break;
		case S_IFIFO:	ft_printf("p"); break;
		case S_IFSOCK:	ft_printf("s"); break;
		default:		ft_printf("?");
	}
}

void print_permissions(mode_t mode)
{
	ft_printf("%c", (mode & S_IRUSR) ? 'r' : '-');
	ft_printf("%c", (mode & S_IWUSR) ? 'w' : '-');
	ft_printf("%c", (mode & S_IXUSR) ? 'x' : '-');
	ft_printf("%c", (mode & S_IRGRP) ? 'r' : '-');
	ft_printf("%c", (mode & S_IWGRP) ? 'w' : '-');
	ft_printf("%c", (mode & S_IXGRP) ? 'x' : '-');
	ft_printf("%c", (mode & S_IROTH) ? 'r' : '-');
	ft_printf("%c", (mode & S_IWOTH) ? 'w' : '-');
	ft_printf("%c", (mode & S_IXOTH) ? 'x' : '-');
}

void print_owner_group(struct stat *st)
{
	struct passwd	*pw = getpwuid(st->st_uid);
	struct group	*gr = getgrgid(st->st_gid);
	
	if (pw)
	{
		ft_printf("%s ", pw->pw_name);
	}
	else
	{
		ft_printf("%d ", st->st_uid);
	}

	if (gr)
	{
		ft_printf("%s", gr->gr_name);
	}
	else
	{
		ft_printf("%d", st->st_gid);
	}
}

void print_file_size(struct stat *st)
{
	ft_printf("%d", st->st_size);
}

void print_modification_time(struct stat *st)
{
	time_t now = time(NULL);
	time_t mtime = st->st_mtime;
	char time_buf[20];
	struct tm *tm_info;

	if (now - mtime > 15778476)
	{
		tm_info = localtime(&mtime);
		strftime(time_buf, sizeof(time_buf), "%b %e  %Y", tm_info);
	}
	else
	{
		tm_info = localtime(&mtime);
		strftime(time_buf, sizeof(time_buf), "%b %e %H:%M", tm_info);
	}

	ft_printf("%s", time_buf);
}

long	calculate_total_blocks(t_list *files)
{
	long	total = 0;
	t_list	*current = files;

	while (current)
	{
		t_info *info = current->content;
		total += info->st.st_blocks;
		current = current->next;
	}

	return (total / 2);
}

void	print_long_format(struct stat st, int padding_links, int padding_size)
{
	print_file_type(st.st_mode);
	print_permissions(st.st_mode);
	while (padding_links-- >= count_digits(st.st_nlink))
	ft_printf(" ");
	ft_printf("%d ", st.st_nlink);
	print_owner_group(&st);
	while (padding_size-- >= count_digits(st.st_size))
		ft_printf(" ");
	print_file_size(&st);
	ft_printf(" ");
	print_modification_time(&st);
	ft_printf(" ");
}

void	sort(int options, t_list **files)
{
	if (options & TIME)
	{
		if (options & REVERSE)
		{
			*files = ft_lstsort(*files, sort_paths_time_reverse);
		}
		else
		{
			*files = ft_lstsort(*files, sort_paths_time);
		}
	}
	else
	{
		if (options & REVERSE)
		{
			*files = ft_lstsort(*files, sort_paths_reverse);
		}
		else
		{
			*files = ft_lstsort(*files, sort_paths);
		}
	}
}

void	get_files(t_data *data, t_list **to_list, DIR *dir, const char *path)
{
	struct dirent	*entry;
	t_list			*new_node;
	t_info			*tmp;

	while ((entry = readdir(dir)) != NULL)
	{
		if (!(data->options & ALL) && entry->d_name[0] == '.')
		{
			continue ;
		}

		char	full_path[PATH_MAX];
		snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
		check_mem(INFO, ft_calloc(1, sizeof(t_info)), (void **)&tmp, data);
		tmp->name = entry->d_name;
		if (stat(full_path, &tmp->st) == -1)
		{
			free(tmp);
			continue ;
		}
		check_mem(INFO, ft_lstnew(tmp), (void **)&new_node, data);
		ft_lstadd_back(to_list, new_node);
	}
	sort(data->options, to_list);
}

void	calculate_padding(t_data *data, t_list *to_list)
{
	int	size;
	t_list	*tmp = to_list;
	data->padding_links = 0;
	data->padding_size = 0;

	while (tmp)
	{
		size = count_digits(((t_info *)tmp->content)->st.st_nlink);
		if (size > data->padding_links)
		{
			data->padding_links = size;
		}

		size = count_digits(((t_info *)tmp->content)->st.st_size);
		if (size > data->padding_size)
		{
			data->padding_size = size;
		}

		tmp = tmp->next;
	}
}

void	print(t_data *data, t_list *to_list)
{
	if (data->options & LONG)
	{
		ft_printf("total %d\n", calculate_total_blocks(to_list));
		calculate_padding(data, to_list);
	}

	t_list	*tmp = to_list;
	while (tmp)
	{
		t_info	*info = tmp->content;

		if (data->options & LONG)
		{
			print_long_format(info->st, data->padding_links, data->padding_size);
		}
		ft_printf("%s\n", info->name);

		tmp = tmp->next;
	}
}

void	print_header(t_data *data, const char *path)
{
	static bool	first_call = true;

	if (ft_lstsize(data->paths) > 1 || data->options & RECURSIVE)
	{
		if (!first_call)
		{
			ft_printf("\n");
		}
		ft_printf("%s:\n", path);
	}

	first_call = false;
}

void	do_nothing(void *ptr)
{
	(void)ptr;
}

void	list(const char	*path, t_data *data)
{
	DIR *dir = opendir(path);
	if (dir == NULL)
	{
		ft_dprintf(2, "ft_ls: cannot open directory '%s': Permission denied\n", path);
		data->exit_code = (data->options & RECURSIVE ? 1 : 2);
		return ;
	}

	t_list	*to_list = NULL;
	print_header(data, path);
	get_files(data, &to_list, dir, path);
	print(data, to_list);

	if (data->options & RECURSIVE)
	{
		t_list	*tmp = to_list;
		while (tmp)
		{
			t_info	*info = tmp->content;

			if (ft_strcmp(info->name, ".") && ft_strcmp(info->name, ".."))
			{
				char	full_path[PATH_MAX];
				snprintf(full_path, sizeof(full_path), "%s/%s", path, info->name);
				struct stat	path_stat;
				if (stat(full_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
				{
					list(full_path, data);
				}
			}

			tmp = tmp->next;
		}
	}

	closedir(dir);
	ft_lstclear(&to_list, free);
}

void	run(t_data *data)
{
	size_t	size = ft_lstsize(data->files);
	if (size > 0)
	{
		sort(data->options, &data->files);

		t_list	*tmp = data->files;
		int	padding_links = 0;
		int	padding_size = 0;
		while (tmp)
		{
			int	size = count_digits(((t_info *)tmp->content)->st.st_nlink);
			if (size > padding_links)
			{
				padding_links = size;
			}
			size = count_digits(((t_info *)tmp->content)->st.st_size);
			if (size > padding_size)
			{
				padding_size = size;
			}
			tmp = tmp->next;
		}

		tmp = data->files;
		while (tmp)
		{
			t_info	*info = tmp->content;

			if (data->options & LONG)
			{
				print_long_format(info->st, padding_links, padding_size);
			}

			ft_printf("%s\n", info->name);
			tmp = tmp->next;
		}

		ft_lstclear(&data->files, free);
		data->files = NULL;
		ft_printf("\n");
	}

	if (ft_lstsize(data->paths) > 0)
	{
		sort(data->options, &data->paths);

		t_list	*tmp = data->paths;
		while (tmp)
		{
			t_info	*info = tmp->content;
			list(info->name, data);
			tmp = tmp->next;
		}
		ft_lstclear(&data->paths, free);
	}
	else if (data->exit_code == 0)
	{
		list(".", data);
	}
	else
	{
		data->exit_code = 2;
	}
}