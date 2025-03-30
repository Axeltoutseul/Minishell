/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:21:15 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/30 15:08:12 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_raw_cmds(char **raw_cmds)
{
	int	count;

	count = 0;
	while (raw_cmds[count])
		count++;
	return (count);
}

char	**remove_redirection_tokens(char **tokens)
{
	int		non_redir_count;
	char	**new_tokens;

	non_redir_count = count_non_redir_tokens(tokens);
	if (non_redir_count == -1)
	{
		ft_printf("bash: syntax error near unexpected token `newline'\n");
		free_2d_array(tokens);
		return (NULL);
	}
	new_tokens = build_tokens_without_redir(tokens, non_redir_count);
	free_2d_array(tokens);
	return (new_tokens);
}

char	**remove_hd_tokens(char **tokens, char **heredoc)
{
	int		new_count;
	char	**new_tokens;

	if (tokens == NULL)
		return (NULL);
	new_count = count_tokens_without_hd(tokens);
	if (new_count == -1)
	{
		ft_printf("bash: syntax error near unexpected token `newline'\n");
		free_2d_array(tokens);
		return (NULL);
	}
	new_tokens = build_tokens_without_hd(tokens, heredoc, new_count);
	free_2d_array(tokens);
	return (new_tokens);
}

static char	**extract_redirections(char **tokens, t_redir **redir)
{
	int		non_redir_count;
	char	**new_tokens;

	non_redir_count = count_non_redir_tokens(tokens);
	if (non_redir_count == -1)
	{
		ft_printf("bash: syntax error near unexpected token `newline'\n");
		free_2d_array(tokens);
		return (NULL);
	}
	new_tokens = build_new_tokens(tokens, redir, non_redir_count);
	free_2d_array(tokens);
	return (new_tokens);
}

t_command	*parse_command(char *raw, char **env)
{
	t_command	*cmd;
	char		*expanded_raw;
	char		**tokens;
	char		*heredoc;

	cmd = malloc(sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	expanded_raw = expand_variables(raw, env);
	tokens = advanced_tokenize_modified(expanded_raw);
	free(expanded_raw);
	heredoc = NULL;
	tokens = prepare_tokens(tokens, &heredoc);
	cmd->heredoc_delim = heredoc;
	cmd->heredoc_fd = -1;
	cmd->redirections = NULL;
	tokens = extract_redirections(tokens, &cmd->redirections);
	if (tokens == NULL)
		return (free(cmd), NULL);
	cmd->args = tokens;
	return (cmd);
}
