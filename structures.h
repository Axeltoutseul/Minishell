/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:22:37 by axbaudri          #+#    #+#             */
/*   Updated: 2025/04/01 00:15:57 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include "libft/libft.h"

typedef struct s_redir
{
	char			*op;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_build_ctx
{
	char		**tokens;
	int			i;
	int			j;
	char		**new_tokens;
	t_redir		**redir;
}	t_build_ctx;

typedef struct s_command
{
	char		**args;
	char		*heredoc_delim;
	int			heredoc_fd;
	t_redir		*redirections;
}	t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	int			count;
}	t_pipeline;

typedef struct s_env
{
	char			*name;
	char			*value;
	char			*line;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int		shlvl;
	char	*path;
	char	*home_path;
	char	*pwd;
	char	*old_pwd;
	char	**splitted_path;
	char	**env;
	t_env	*env_lines;
	t_env	*export_lines;
	t_list	*history;
	int		exit_status;
}	t_shell;

typedef struct s_exec_context
{
	t_pipeline	*pipeline;
	char		**env;
	int			cmd_count;
	t_shell		*shell;
}	t_exec_context;

typedef struct s_prompt
{
	char	*cmd_line;
	char	*echo;
	char	**strs;
	int		nb_args;
}	t_prompt;

typedef enum e_state
{
	STATE_DEFAULT,
	STATE_IN_SINGLE,
	STATE_IN_DOUBLE,
	STATE_ESCAPING
}				t_state;

typedef struct s_tokenize_context
{
	int		i;
	int		ti;
	char	**tokens;
	char	*curr;
	t_state	state;
}	t_tokenize_context;

#endif
