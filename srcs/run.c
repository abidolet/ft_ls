#include "ft_ls.h"
#include "parsing_bonus.h"
#include <dirent.h>
#include <stdbool.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1

char	*get_color(const char *path)
{
	static char	res[16];
	char	*ls_colors = DEFAULT_LS_COLORS;

	struct stat	st;
	if (lstat(path, &st) == -1)
	{
		return ("");
	}

	while (ls_colors)
	{
		if ((ft_strncmp(ls_colors, "di=", 3) == 0 && S_ISDIR(st.st_mode))
			|| (ft_strncmp(ls_colors, "ln=", 3) == 0 && S_ISLNK(st.st_mode))
			|| (ft_strncmp(ls_colors, "ex=", 3) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
			|| (ft_strncmp(ls_colors, "ow=", 3) == 0 && S_ISDIR(st.st_mode) && (st.st_mode & S_IWOTH) && !(st.st_mode & S_ISVTX)))
		{
			const char *start = ls_colors + 3;
			const char *end = ft_strchr(start, ':');
			size_t len = end ? (size_t)(end - start) : strlen(start);
			if (len > sizeof(res) - 6)
				len = sizeof(res) - 6;
			strcpy(res, "\033[");
			strncat(res, start, len);
			strcat(res, "m");
			return (res);
		}

		if (ft_strchr(ls_colors, ':') == NULL)
		{
			break ;
		}
		ls_colors = ft_strchr(ls_colors, ':') + 1;
	}

	return ("");
}

# define PRINT(options, path, fmt, ...) \
	((options & COLOR) \
		? ft_printf("%s" fmt "%s", get_color(path), __VA_ARGS__, RESET) \
		: ft_printf(fmt, __VA_ARGS__))
#else

# define PRINT(options, path, ...) ft_printf(__VA_ARGS__)

#endif

void	print_link(int options, const char *path, const char *name)
{
	(void)options;
	char	link_target[PATH_MAX];
	ssize_t	len = readlink(path, link_target, sizeof(link_target) - 1);

	if (len != -1)
	{
		link_target[len] = '\0';
		PRINT(options, path, "%s -> %s\n", name, link_target);
	}
}

int	count_digits(int n)
{
	return (n < 10 ? 1 : 1 + count_digits(n / 10));
}

void print_file_type(mode_t mode)
{
	switch (mode & S_IFMT)
	{
		case S_IFREG:	ft_printf("-"); break ;
		case S_IFDIR:	ft_printf("d"); break ;
		case S_IFLNK:	ft_printf("l"); break ;
		case S_IFCHR:	ft_printf("c"); break ;
		case S_IFBLK:	ft_printf("b"); break ;
		case S_IFIFO:	ft_printf("p"); break ;
		case S_IFSOCK:	ft_printf("s"); break ;
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

void print_owner_group(struct stat *st, int options)
{
	if (!(options & GLONG))
	{
		struct passwd	*pw = getpwuid(st->st_uid);
		if (pw)
		{
			ft_printf("%s ", pw->pw_name);
		}
		else
		{
			ft_printf("%d ", st->st_uid);
		}
	}

	struct group	*gr = getgrgid(st->st_gid);
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

void print_modification_time(struct stat *st, int options)
{
	time_t	mtime;
	if (options & UTIME)
	{
		mtime = st->st_atime;
	}
	else
	{
		mtime = st->st_mtime;
	}

	time_t		now = time(NULL);
	char		time_buf[20];
	struct tm	*tm_info;

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

	while (files)
	{
		t_info *info = files->content;
		total += info->st.st_blocks;
		files = files->next;
	}

	return (total / 2);
}

void	print_long_format(struct stat st, int padding_links, int padding_size, int options)
{
	print_file_type(st.st_mode);
	print_permissions(st.st_mode);
	while (padding_links-- >= count_digits(st.st_nlink))
	ft_printf(" ");
	ft_printf("%d ", st.st_nlink);
	print_owner_group(&st, options);
	while (padding_size-- >= count_digits(st.st_size))
		ft_printf(" ");
	print_file_size(&st);
	ft_printf(" ");
	print_modification_time(&st, options);
	ft_printf(" ");
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
		if (lstat(full_path, &tmp->st) == -1)
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
	int		size;
	data->padding_links = 0;
	data->padding_size = 0;

	while (to_list)
	{
		size = count_digits(((t_info *)to_list->content)->st.st_nlink);
		if (size > data->padding_links)
		{
			data->padding_links = size;
		}

		size = count_digits(((t_info *)to_list->content)->st.st_size);
		if (size > data->padding_size)
		{
			data->padding_size = size;
		}

		to_list = to_list->next;
	}
}

void	print(t_data *data, t_list *to_list, const char *path)
{
	if (data->options & LONG || data->options & GLONG)
	{
		ft_printf("total %d\n", calculate_total_blocks(to_list));
		calculate_padding(data, to_list);
	}

	while (to_list)
	{
		t_info	*info = to_list->content;

		if (data->options & LONG || data->options & GLONG)
		{
			print_long_format(info->st, data->padding_links, data->padding_size, data->options);
		}

		char	full_path[PATH_MAX];
		snprintf(full_path, sizeof(full_path), "%s/%s", path, info->name);

		if ((data->options & LONG || data->options & GLONG)
			&& S_ISLNK(info->st.st_mode))
		{
			print_link(data->options, full_path, info->name);
		}
		else
		{
			PRINT(data->options, full_path, "%s\n", info->name);
		}

		to_list = to_list->next;
	}
}

void	print_header(t_data *data, const char *path)
{
	static bool	first_call = true;

	if (ft_lstsize(data->paths) > 1 || data->exit_code != 0 || data->options & RECURSIVE)
	{
		if (!first_call)
		{
			ft_printf("\n");
		}
		ft_printf("%s:\n", path);
	}

	first_call = false;
}

void	list(const char	*path, t_data *data);

void	handle_recursive(t_data *data, t_list *to_list, const char *path)
{
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
	print(data, to_list, path);
	if (data->options & RECURSIVE)
	{
		handle_recursive(data, to_list, path);
	}
	closedir(dir);
	ft_lstclear(&to_list, free);
}

void	print_line(void *info_ptr, t_data *data)
{
	t_info *info = (t_info *)info_ptr;

	if (data->options & LONG || data->options & GLONG)
	{
		print_long_format(info->st, data->padding_links, data->padding_size, data->options);
	}
	ft_printf("%s\n", info->name);
}

void	list_files(t_data *data)
{
	if (ft_lstsize(data->files) > 0)
	{
		sort(data->options, &data->files);
		calculate_padding(data, data->files);

		t_list *tmp = data->files;
		while (tmp)
		{
			print_line(tmp->content, data);
			tmp = tmp->next;
		}

		ft_lstclear(&data->files, free);

		if (ft_lstsize(data->paths) > 0)
		{
			ft_printf("\n");
		}
	}
}

void	run(t_data *data)
{
	if (data->options & DIRECTORY)
	{
		data->files = ft_lstmerge(data->files, data->paths);
		data->paths = NULL;
	}

	list_files(data);

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
}
