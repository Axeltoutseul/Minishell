/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:21:15 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/27 09:58:15 by qacjl            ###   ########.fr       */
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
	int		i;
	int		new_count;
	char	**new_tokens;

	i = 0;
	new_count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0)
		{
			if (!tokens[i + 1])
			{
				ft_printf("bash:syntax error near unexpected token `newline'\n");
				free_2d_array(tokens);
				return (NULL);
			}
			i += 2;
		}
		else
		{
			new_count++;
			i++;
		}
	}
	new_tokens = malloc(sizeof(char *) * (new_count + 1));
	if (!new_tokens)
		return (NULL);
	i = 0;
	new_count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0)
			i += 2;
		else
			new_tokens[new_count++] = ft_strdup(tokens[i++]);
	}
	new_tokens[new_count] = NULL;
	free_2d_array(tokens);
	return (new_tokens);
}

char	**remove_hd_tokens(char **tokens, char **heredoc)
{
	int		i;
	int		new_count;
	char	**new_tokens;

	if (tokens == NULL)
		return (NULL);
	i = 0;
	new_count = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strcmp(tokens[i], "<<") == 0)
		{
			if (tokens[i + 1] == NULL)
			{
				ft_printf("bash: syntax error near unexpected token `newline'\n");
				free_2d_array(tokens);
				return (NULL);
			}
			i = i + 2;
		}
		else
		{
			new_count++;
			i++;
		}
	}
	new_tokens = malloc(sizeof(char *) * (new_count + 1));
	if (new_tokens == NULL)
		return (NULL);
	i = 0;
	new_count = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strcmp(tokens[i], "<<") == 0)
		{
			if (tokens[i + 1] == NULL)
			{
				ft_printf("bash: unexpected error: missing heredoc delimiter\n");
				free_2d_array(tokens);
				free(new_tokens);
				return (NULL);
			}
			*heredoc = ft_strdup(tokens[i + 1]);
			i = i + 2;
		}
		else
		{
			new_tokens[new_count] = ft_strdup(tokens[i]);
			new_count++;
			i++;
		}
	}
	new_tokens[new_count] = NULL;
	free_2d_array(tokens);
	return (new_tokens);
}

static char	**extract_redirections(char **tokens, t_redirection **redir)
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

t_command	*parse_command(char *raw)
{
	t_command	*cmd;
	char		**tokens;
	char		*heredoc;
	char		*expanded_raw;

	cmd = malloc(sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	expanded_raw = expand_variables(raw);
	tokens = advanced_tokenize_modified(expanded_raw);
	free(expanded_raw);
	heredoc = NULL;
	tokens = remove_hd_tokens(tokens, &heredoc);
	if (tokens == NULL)
	{
		free(cmd);
		return (NULL);
	}
	cmd->heredoc_delim = heredoc;
	cmd->heredoc_fd = -1;
	cmd->redirections = NULL;
	tokens = extract_redirections(tokens, &cmd->redirections);
	if (tokens == NULL)
	{
		free(cmd);
		return (NULL);
	}
	cmd->args = tokens;
	return (cmd);
}
