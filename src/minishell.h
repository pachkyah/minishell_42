#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_redir_type {
	RED_IN,      // <
	RED_OUT,     // >
	RED_APPEND,  // >>
	RED_HEREDOC  // <<
} t_redir_type;

typedef struct s_redir {
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
} t_redir;

typedef struct s_cmd {
	char			**args;
	t_redir			redirs;
	int				has_pipe;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_shell {
	char	**env;
	int		last_status;
} t_shell;

#endif