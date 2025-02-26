/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:55 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/26 20:23:18 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_ARGS 64
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <linux/limits.h>
# include <signal.h>
# include <sys/wait.h>
# include "env.h"
# include "prompt.h"
# include "libft/libft.h"

typedef struct s_command
{
	char	**args;
	char	*heredoc_delim;
}	t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	int			count;
}	t_pipeline;

typedef struct s_exec_context
{
	t_pipeline	*pipeline;
	char		**env;
	int			cmd_count;
}	t_exec_context;

typedef struct s_shell
{
	int		shlvl;
	char	*path;
	char	*pwd;
	char	*old_pwd;
	char	**splitted_path;
	char	**env;
	t_env	*env_lines;
	t_env	*export_lines;
}	t_shell;

typedef enum e_state
{
	STATE_DEFAULT,
	STATE_IN_SINGLE,
	STATE_IN_DOUBLE,
	STATE_ESCAPING
}				t_state;

int			handle_heredoc(const char *delimiter);
t_pipeline	*parse_input(const char *line);
void		free_pipeline(t_pipeline *pipeline);
void		execute_pipeline(t_pipeline *pipeline, char **env);
int			adv_handle_redirect(const char *target, const char *op, int std_fd);
int			handle_redirection_char(const char *file, const char *op);
int			redirect_file(const char *target, int std_fd, int flags, int mode);
int			handle_heredoc(const char *delimiter);
void		setup_signal(void);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
char		**advanced_tokenize(const char *line);
void		execute_command(char *cmd, int in_fd, int out_fd);
void		execute_pipes(char *input);

void		add_lines(t_shell *shell, t_prompt *prompt);
int			calculate_size_for_replace(const char *str, char *a, char *b);
int			calculate_total_size(int size, char **strs, char *sep);
void		check_error(char *name, char *arg);
int			check_path_validity(char *cmd);
int			count_occurs(const char *cmd_line, int to_find);
int			count_occurs2(const char *str, char *to_find);
int			count_quotes(const char *cmd_line);
int			count_strings(char **strs);
int			count_words(const char *str);
void		display_history(void);
void		exec_cd(t_shell *shell, t_prompt *prompt);
char		*exec_echo(char *cmd_line, char **strs);
void		exec_export(t_shell *shell, t_prompt *prompt);
void		exec_unset(t_shell *shell, t_prompt *prompt);
int			existing_command(char **paths, char *cmd);
void		execute_builtin(t_shell *shell, t_prompt *prompt);
char		*find_path_line(char **envp);
char		*find_third_word(const char *cmd_line);
char		*first_word(char *str);
void		free_2d_array(char **strs);
void		free_terminal(t_shell *shell);
char		*ft_strcpy(char *dest, const char *src);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin2(int size, char **strs, char *sep);
char		*ft_strndup(const char *src, size_t n);
void		ft_swap(char **s1, char **s2);
void		handle_pipe(char *cmd1[], char *cmd2[]);
int			handle_redirection(const char *file, int io_flag);
t_shell		*init_shell(char **envp);
char		*join_strings(char **strs);
char		*replace(const char *str, char *a, char *b);
void		update_paths(t_shell *shell, t_env **env);
void		verif_history(const char *input);

#endif
