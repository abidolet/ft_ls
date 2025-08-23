#ifndef PARSING_H
# define PARSING_H

# include "ft_ls.h"

# define HELP_MSG \
	"Usage: " EXEC_NAME " [OPTION]... [FILE]...\n" \
	"List information about the FILEs (the current directory by default).\n" \
	"Sort entries alphabetically if none of -ftu is specified.\n" \
	"\nMandatory arguments to long options are mandatory for short options too.\n" \
	"  -a, --all\t\t\tdo not ignore entries starting with .\n" \
	"  -l\t\t\t\tuse a long listing format\n" \
	"  -r, --reverse\t\t\treverse order while sorting\n" \
	"  -R, --recursive\t\tlist subdirectories recursively\n" \
	"  -t\t\t\t\tsort by time, newest first\n" \
	"      --help\t\t\tdisplay this help and exit\n" \
	"\nExit status:\n" \
	" 0  if OK,\n" \
	" 1  if minor problems (e.g., cannot access subdirectory),\n" \
	" 2  if serious trouble (e.g., cannot access command-line argument).\n" \
	"\nReport bugs to <abidolet@student.42lyon.fr>.\n" \

# define TRY_MSG "Try '" EXEC_NAME " --help' for more information.\n"
# define INVALID_OPTION_MSG	EXEC_NAME ": invalid option -- '%c'\n" TRY_MSG
# define UNRECOGNIZED_OPTION_MSG EXEC_NAME ": unrecognized option -- '%s'\n" TRY_MSG
# define AMBIGUOUS_OPTION_MSG EXEC_NAME ": option '--%s' is ambiguous; possibilities:"

#define OPTIONS_TABLE \
	X(ALL, 'a', "all") \
	X(LONG, 'l', "\0") \
	X(REVERSE, 'r', "reverse") \
	X(RECURSIVE, 'R', "recursive") \
	X(TIME, 't', "\0") \
	X(HELP, '\0', "help") \

typedef enum e_option
{
	#define X(name, posix, gnu) name = 1 << __COUNTER__,
		OPTIONS_TABLE
	#undef X
	INVALID = 0
}	e_option;

typedef struct s_option_map_gnu
{
	e_option	option;
	const char	*gnu_form;
	_Bool		selected;
}	t_option_map_gnu;

typedef struct s_option_map_posix
{
	e_option	option;
	char		posix_form;
}	t_option_map_posix;

void	parse_options(char *arg, int *options);

#endif