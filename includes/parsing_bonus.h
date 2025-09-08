#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# define TRY_MSG "Try '" EXEC_NAME " --help' for more information.\n"
# define INVALID_OPTION_MSG	EXEC_NAME ": invalid option -- '%c'\n" TRY_MSG
# define UNRECOGNIZED_OPTION_MSG EXEC_NAME ": unrecognized option -- '%s'\n" TRY_MSG
# define AMBIGUOUS_OPTION_MSG EXEC_NAME ": option '--%s' is ambiguous; possibilities:"
# define AMBIGUOUS_ARGUMENT_MSG EXEC_NAME ": ambiguous argument '%s' for '%s'\n" "Valid arguments are:\n"
# define INVALID_ARGUMENT_MSG EXEC_NAME ": invalid argument '%s' for '%s'\n" "Valid arguments are:\n"

# define HELP_MSG \
	"Usage: " EXEC_NAME " [OPTION]... [FILE]...\n" \
	"List information about the FILEs (the current directory by default).\n" \
	"Sort entries alphabetically if none of -ftu is specified.\n" \
	"\n  -a, --all\t\t\tdo not ignore entries starting with .\n" \
	"      --color[=WHEN]\t\tcolor the output WHEN; more info below\n" \
	"  -d, --directory\t\tlist directories themselves, not their contents\n" \
	"  -f\t\t\t\tlist all entries in directory order\n" \
	"  -g\t\t\t\tlike -l, but do not list owner\n" \
	"  -l\t\t\t\tuse a long listing format\n" \
	"  -r, --reverse\t\t\treverse order while sorting\n" \
	"  -R, --recursive\t\tlist subdirectories recursively\n" \
	"  -t\t\t\t\tsort by time, newest first\n" \
	"  -u\t\t\t\twith -lt: sort by, and show, access time;\n" \
	"  \t\t\t\twith -l: show access time and sort by name;\n" \
	"  \t\t\t\totherwise: sort by access time, newest first\n\n" \
	"      --help\t\tdisplay this help and exit\n" \
	"\nThe WHEN argument defaults to 'always' and can also be 'auto' or 'never'.\n" \
	"\nUsing color to distinguish file types is disabled both by default and\n" \
	"with --color=never.  With --color=auto, ls emits color codes only when\n" \
	"standard output is connected to a terminal.  The LS_COLORS environment\n" \
	"variable can change the settings.  Use the dircolors(1) command to set it.\n" \
	"\nExit status:\n" \
	" 0  if OK,\n" \
	" 1  if minor problems (e.g., cannot access subdirectory),\n" \
	" 2  if serious trouble (e.g., cannot access command-line argument).\n" \
	"\nReport bugs to <abidolet@student.42lyon.fr>.\n" \

# define OPTIONS_TABLE \
	X(LONG, 'l', "\0") \
	X(RECURSIVE, 'R', "recursive") \
	X(ALL, 'a', "all") \
	X(REVERSE, 'r', "reverse") \
	X(TIME, 't', "\0") \
	X(HELP, '\0', "help") \
	X(UTIME, 'u', "\0") \
	X(NO_SORT, 'f', "\0") \
	X(GLONG, 'g', "\0") \
	X(DIRECTORY, 'd', "directory") \
	X(COLOR, '\0', "color") \

typedef enum e_option
{
	#define X(name, ...) name = 1 << __COUNTER__,
		OPTIONS_TABLE
	#undef X
	INVALID = 0
}	e_option;

typedef struct s_option_map_posix
{
	e_option	option;
	char		posix_form;
}	t_option_map_posix;

typedef struct s_option_map_gnu
{
	e_option	option;
	const char	*gnu_form;
	_Bool		selected;
}	t_option_map_gnu;

# define COLOR_TABLE \
	Y(YES, "always", "yes", "force") \
	Y(NO, "never", "no", "none") \
	Y(AUTO, "auto", "tty", "if-tty") \

typedef enum e_color
{
	#define Y(name, ...) name = 1 << __COUNTER__,
		COLOR_TABLE
	#undef Y
}	e_color;

typedef struct s_color_map
{
	e_color	color;
	const char	*arg1;
	const char	*arg2;
	const char	*arg3;
}	t_color_map;

void	parse_options(char *arg, int *options);
void	parse_color(char *arg, int *options);

#endif