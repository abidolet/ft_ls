#include <stdlib.h>

#if LIBFT_AUTHORIZED

# include "libft/ft_printf.h"
# include "libft/str.h"

# define dprintf ft_dprintf
# define strlen ft_strlen
# define strncmp ft_strncmp

#else

# include <stdio.h>
# include <string.h>

#endif

#if BONUS

# include "parsing_bonus.h"

#else

# include "parsing.h"

#endif

static e_option get_option_gnu(const char *option_name)
{
	const size_t	option_size = strlen(option_name);
	e_option		option = INVALID;
	size_t			nb_options = 0;

	t_option_map_gnu option_map[] =
	{
		#define X(name, posix, gnu) {name, gnu, 0},
			OPTIONS_TABLE
		#undef X
	};

	for (size_t i = 0; i < sizeof(option_map) / sizeof(option_map[0]); i++)
	{
		if (strncmp(option_name, option_map[i].gnu_form, option_size) == 0)
		{
			option_map[i].selected = 1;
			option = option_map[i].option;
			nb_options++;
		}
	}

	if (nb_options > 1)
	{
		dprintf(2, AMBIGUOUS_OPTION_MSG, option_name);
		for (size_t i = 0; option_map[i].gnu_form; i++)
		{
			if (option_map[i].selected)
			{
				dprintf(2, " '--%s'", option_map[i].gnu_form);
			}
		}
		dprintf(2, "\n"TRY_MSG);
		exit(2);
	}

	return (option);
}

static e_option get_option_posix(const char option_name)
{
	t_option_map_posix option_map[] =
	{
		#define X(name, posix, gnu) {name, posix},
			OPTIONS_TABLE
		#undef X
	};

	for (size_t i = 0; i < sizeof(option_map) / sizeof(option_map[0]); i++)
	{
		if (option_map[i].posix_form == option_name)
		{
			return (option_map[i].option);
		}
	}

	return (INVALID);
}

void	parse_options(char *arg, int *options)
{
	e_option	option;

	if (*arg != '-')
	{
		while (*arg)
		{
			option = get_option_posix(*arg);
			if (option == INVALID)
			{
				dprintf(2, INVALID_OPTION_MSG, *arg);
				exit(2);
			}
			else if (option == HELP)
			{
				dprintf(1, HELP_MSG);
				exit(0);
			}

			*options |= option;
			arg++;
		}
	}

	#if BONUS
	else if (ft_strchr(arg, '='))
	{
		parse_color(arg, options);
	}
	#endif

	else
	{
		option = get_option_gnu(arg + 1);
		if (option == INVALID)
		{
			dprintf(2, UNRECOGNIZED_OPTION_MSG, arg + 1);
			exit(2);
		}
		else if (option == HELP)
		{
			dprintf(1, HELP_MSG);
			exit(0);
		}

		*options |= option;
	}
}
