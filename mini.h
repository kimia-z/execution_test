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

int		ft_execute(t_parser *parser);

void	ft_echo(t_command *commands, t_parser *parser);
void	ft_pwd(t_command *commands, t_parser *parser);
void	ft_exit(t_command *commands, t_parser *parser);

void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);
int		ft_isspace(int c);


void	test_echo(void);
void	test_pwd(void);
void	test_exit(void);
