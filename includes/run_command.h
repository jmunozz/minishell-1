#ifndef RUN_COMMAND
# define RUN_COMMAND

# include "minishell.h"
# define OP 1
# define PIPE 2
# define HEREDOC 3
# define SSHELL 4
# define PROS 100
# define SENT 101
# define JOB 102
# define BDATA ((char*)begin->data)
# define SNDATA ((char*)src->next->data)
# define BOTHER_FD ((t_pipe*)begin->next->data)->others_fd

typedef struct	s_pipe
{
	int			fixed_pip[2];
	char		**others_fd;
}				t_pipe;

/*
**exec.c
*/
void			ft_execve(char **argv, char **env, t_config *config);
void			ft_launch_process(t_list *begin, t_config *config);
void			ft_kill_father(t_config *config);
/*
**files.c
*/
int				ft_access_dir(char const *path);
int				ft_access_exec(char *path, char **argv, t_config *config);
/*
**lexer.c
*/
t_list			*ft_lexer(char *cmd);
char			*ft_envvarinsert(char *cmd, size_t *i, t_config *config);
t_list			*ft_built_couple(char *cmd, size_t *i);
t_list			*ft_av_handle(char *cmd, size_t i);
int				ft_dodge_quote(char *cmd, size_t i);
t_list			*ft_quote_handle(t_list *next, t_config *config);
char			*ft_match_op(char *cmd, size_t *i);
int				ft_next_op(char *cmd, size_t i);
void			ft_lexer_sshell_off(char *cmd, size_t i);
t_list			*ft_lexer_sshell_on(char *cmd, size_t *i, t_list *next);
/*
**parser.c
*/
char			*ft_save_cmd(char *cmd);
int				ft_node_descriptors(t_list *begin, t_list **rhead,
				t_config *config, int **r_pipe);
int				ft_build_pipe(t_list *begin, t_config *config, int **r_pipe);
void			ft_parse(t_list *begin, t_config *config);
 t_list			*ft_run_sentence(t_list *begin, t_config *config, int *r_pipe);
int				ft_redirectpipe(char *file, int *pip, char *tmp);
/*
**parser_multiple_fd.c
*/
void			ft_handle_multiplefd(char **others_fd);
/*
**wait.c
*/
void			ft_wait_sentence(t_list *job, char *sentence, t_config *config);
/*
**heredoc.c
*/
int				ft_herringbone(t_list *begin, t_config *config);
#endif
