#include <sys/wait.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <errno.h>
#include <termcap.h>
#include <termios.h>
#include <signal.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/wait.h>

// typedef struct s_env
// {
// 	char	*key;
// 	char	*value;
// 	t_env	*next;
// }	t_env;


typedef struct s_command
{
	char				**command;
	char				*path;
	int					infile_fd;
	int					outfile_fd;
	char				*infile;
	char				*outfile;
	struct s_command	*next;
}				t_command;

typedef struct s_parser
{
	int					exit_status;
	int					nb_pipes;
	struct s_command	*commands;
	// struct s_parser		*next;
    //char				*envp;
    //struct s_env		*envs;
}				t_parser;

typedef enum e_builtin
{
	ECH,
	CD,
	PWD,
	ENV,
	EXPORT,
	UNSET,
	EXIT,
	UNKNOWN
}	t_builtin;

void	ft_echo(t_command *commands, t_parser *parser);
size_t	ft_strlen(const char *s);
