/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:55 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/25 18:08:14 by axbaudri         ###   ########.fr       */
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
# include "structures.h"
# include "libft/libft.h"

// Token
char		**advanced_tokenize_modified(const char *line);
int			count_raw_cmds(char **raw_cmds);
void		process_default(char c, t_state *state, char **curr);
void		process_in_single(char c, t_state *state, char **curr);
void		process_in_double(char c, t_state *state, char **curr);
void		process_escaping(char c, t_state *state, char **curr);
char		**remove_hd_tokens(char **tokens, char **heredoc);
char		*get_command_path(char *cmd, t_shell *shell);
char		**split_pipeline(const char *line);
char		*preprocess_line(const char *line);
char		**build_new_tokens(char **tokens, t_redirection **redir, int size);
int			count_non_redir_tokens(char **tokens);
// Redirection
int			handle_heredoc(const char *delimiter);
void		free_pipeline(t_pipeline *pipeline);
void		execute_pipeline(t_shell *shell, t_pipeline *pipeline, char **env);
int			adv_handle_redirect(const char *target, const char *op, int std_fd);
void		handle_pipe(char *cmd1[], char *cmd2[]);
int			handle_redirection(const char *file, int io_flag);
int			handle_redirection_char(const char *file, const char *op);
int			redirect_file(const char *target, int std_fd, int flags, int mode);
void		setup_signal(void);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
char		*expand_variables(const char *input);
int			apply_redirections(char **token);
int			apply_command_redirections(t_command *cmd);
int			handle_heredoc_parent_pipe(const char *delimiter);

// Outils de strings
int			calculate_total_size(int size, char **strs, char *sep);
void		check_error(char *name, char *arg);
int			count_occurs(const char *cmd_line, int to_find);
int			count_quotes(const char *cmd_line);
int			count_strings(char **strs);
int			count_words(const char *str);
char		*ft_strcpy(char *dest, const char *src);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin2(int size, char **strs, char *sep);
char		*ft_strndup(const char *src, size_t n);
void		ft_swap(char **s1, char **s2);
int			is_space(int c);
void		sort_strings(char **envp, int size);
// Gestion de la structure principale
void		free_2d_array(char **strs);
void		free_terminal(t_shell *shell);
t_shell		*init_shell(char **envp);
// Gestion de l'environnement
void		add_env_line(t_env **env, t_env *new);
void		add_lines(t_shell *shell, t_prompt *prompt);
void		copy_env(t_env **env, char **envp);
void		copy_export(t_env **export, char **envp);
int			env_size(t_env *env);
void		exec_cd(t_shell *shell, t_prompt *prompt);
void		exec_export(t_shell *shell, t_prompt *prompt);
void		exec_unset(t_shell *shell, t_prompt *prompt);
void		free_env_lines(t_env *env);
void		free_new_and_temp(t_env *new, t_env *temp);
char		**get_lines_export(char **envp);
char		**get_lines(char **envp);
char		*get_path_value(char **envp, char *name);
int			get_shell_level(char **envp);
int			is_in_list(t_env *env, char *var_name);
t_env		*new_line(char *env_line);
void		remove_line(t_env **lst, char *arg);
char		**split_path(char **envp);
void		update_line(char *arg, t_env **env);
void		update_paths(t_shell *shell, t_env **env);
void		write_env(t_prompt *prompt, t_env *env);
void		write_export(t_env *env);
void		exec_echo_builtin(t_command *cmd);
// Parsing du prompt
char		**advanced_tokenize(const char *line);
int			check_path_validity(char *cmd);
int			closed_quotes(char *cmd_line);
void		display_history(t_shell *shell);
void		exec_echo(t_prompt *prompt);
void		execute_builtin(t_shell *shell, t_prompt *prompt);
int			existing_command(char **paths, char *cmd);
void		free_prompt(t_prompt *prompt);
t_prompt	*init_prompt(const char *buffer);
t_command	*parse_command(char *raw);
t_pipeline	*parse_input(const char *line);
int			valid_arg(char *name, char *arg);
int			valid_name(char *name);
int			valid_value(char *s);
void		verif_history(t_shell *shell, const char *input);
int			is_builtin(const char *cmd);

#endif
