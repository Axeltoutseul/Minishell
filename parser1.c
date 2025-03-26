/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:21:15 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/26 15:35:23 by quenalla         ###   ########.fr       */
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

static int	count_non_redirection_tokens(char **tokens)
{
	int		index;
	int		count;

	index = 0;
	count = 0;
	while (tokens[index])
	{
		if (ft_strcmp(tokens[index], ">") == 0
			|| ft_strcmp(tokens[index], ">>") == 0
			|| ft_strcmp(tokens[index], "<") == 0)
		{
			if (!tokens[index + 1])
				return (-1);
			index = index + 2;
		}
		else
		{
			count = count + 1;
			index = index + 1;
		}
	}
	return (count);
}

static char	**dup_non_redirection_tokens(char **tokens, int count)
{
	int		index;
	int		pos;
	char	**new_tokens;

	index = 0;
	pos = 0;
	new_tokens = malloc(sizeof(char *) * (count + 1));
	if (new_tokens == NULL)
		return (NULL);
	while (tokens[index])
	{
		if (ft_strcmp(tokens[index], ">") == 0
			|| ft_strcmp(tokens[index], ">>") == 0
			|| ft_strcmp(tokens[index], "<") == 0)
			index = index + 2;
		else
		{
			new_tokens[pos] = ft_strdup(tokens[index]);
			pos = pos + 1;
			index = index + 1;
		}
	}
	new_tokens[pos] = NULL;
	return (new_tokens);
}

char	**remove_redirection_tokens(char **tokens)
{
	int		non_redir_count;
	char	**new_tokens;

	non_redir_count = count_non_redirection_tokens(tokens);
	if (non_redir_count == -1)
	{
		ft_printf("bash: syntax error near unexpected token `newline'\n");
		free_2d_array(tokens);
		return (NULL);
	}
	new_tokens = dup_non_redirection_tokens(tokens, non_redir_count);
	free_2d_array(tokens);
	return (new_tokens);
}

t_command	*parse_command(char *raw)
{
	t_command	*cmd;
	char		**tokens;
	char		*heredoc;
	char		*expanded_raw;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	expanded_raw = expand_variables(raw);
	tokens = advanced_tokenize_modified(expanded_raw);
	free(expanded_raw);
	heredoc = NULL;
	tokens = remove_hd_tokens(tokens, &heredoc);
	cmd->heredoc_delim = heredoc;
	cmd->heredoc_fd = -1;
	cmd->redirections = NULL;
	tokens = extract_redirections(tokens, &cmd->redirections);
	if (!tokens)
	{
		free(cmd);
		return (NULL);
	}
	cmd->args = tokens;
	return (cmd);
}
