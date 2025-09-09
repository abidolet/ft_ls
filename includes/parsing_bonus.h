#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# define DEFAULT_LS_COLORS "rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:"

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
