#include "parsing_bonus.h"
#include "libft.h"
#include <stdio.h>

void	handle_result(int found, e_color color, int *options, const char *option, t_color_map color_map[], size_t map_size)
{
	if (found == 1)
	{
		if (color == AUTO)
		{
			color = (isatty(1) ? YES : NO);
		}

		if (color == YES)
		{
			*options |= COLOR;
		}
		else if (color == NO)
		{
			*options &= ~COLOR;
		}
	}
	else
	{
		ft_dprintf(2, (found > 1 ? AMBIGUOUS_ARGUMENT_MSG : INVALID_ARGUMENT_MSG), option, "--color");

		for (size_t i = 0; i < map_size; i++)
		{
			ft_dprintf(2, "  - ‘%s’", color_map[i].arg1);
			ft_dprintf(2, ", ‘%s’", color_map[i].arg2);
			ft_dprintf(2, ", ‘%s’\n", color_map[i].arg3);
		}
		ft_dprintf(2, TRY_MSG);
		exit(1);
	}
}

void	parse_color(char *arg, int *options)
{
	const char	*argument = "-color=";

	if (ft_strncmp(arg, argument, ft_strlen(argument)) == 0)
	{
		const char	*option = ft_strchr(arg, '=') + 1;
		t_color_map color_map[] =
		{
			#define Y(name, arg1, arg2, arg3) {name, arg1, arg2, arg3},
				COLOR_TABLE
			#undef Y
		};

		size_t	size_option = ft_strlen(option);
		size_t	found = 0;
		e_color	color = NO;

		for (size_t i = 0; i < sizeof(color_map) / sizeof(color_map[0]); i++)
		{
			if (ft_strncmp(color_map[i].arg1, option, size_option) == 0
				|| ft_strncmp(color_map[i].arg2, option, size_option) == 0
				|| ft_strncmp(color_map[i].arg3, option, size_option) == 0)
			{
				color = color_map[i].color;
				found++;
			}
		}

		handle_result(found, color, options, option, color_map,
			sizeof(color_map) / sizeof(color_map[0]));
	}
	else
	{
		ft_dprintf(2, INVALID_OPTION_MSG, *arg);
		exit(2);
	}
}