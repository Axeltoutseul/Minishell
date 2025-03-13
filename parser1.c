/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:38:31 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/13 13:23:25 by qacjl            ###   ########.fr       */
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

#include "minishell.h"

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
			i = i + 2;
		else
		{
			new_count = new_count + 1;
			i++;
		}
	}
	new_tokens = malloc(sizeof(char *) * (new_count + 1));
	if (new_tokens == NULL)
		return (NULL);
	i = 0;
	new_count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0)
			i = i + 2;
		else
		{
			new_tokens[new_count] = ft_strdup(tokens[i]);
			new_count = new_count + 1;
			i++;
		}
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

	i = 0;
	new_count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<<") == 0)
			i = i + 2;
		else
		{
			new_count = new_count + 1;
			i = i + 1;
		}
	}
	new_tokens = malloc(sizeof(char *) * (new_count + 1));
	if (new_tokens == NULL)
		return (NULL);
	i = 0;
	new_count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<<") == 0)
		{
			*heredoc = ft_strdup(tokens[i + 1]);
			i = i + 2;
		}
		else
		{
			new_tokens[new_count] = ft_strdup(tokens[i]);
			new_count = new_count + 1;
			i = i + 1;
		}
	}
	new_tokens[new_count] = NULL;
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
	tokens = advanced_tokenize(expanded_raw);
	free(expanded_raw);
	heredoc = NULL;
	tokens = remove_hd_tokens(tokens, &heredoc);
	tokens = remove_redirection_tokens(tokens);
	cmd->args = tokens;
	cmd->heredoc_delim = heredoc;
	return (cmd);
}
