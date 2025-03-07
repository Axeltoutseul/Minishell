/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:38:31 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/07 18:08:27 by axbaudri         ###   ########.fr       */
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

/*static char	**build_new_tokens(char **tokens, char **heredoc, int new_count)
{
	int		i;
	int		j;
	char	**new_tokens;

	new_tokens = malloc(sizeof(char *) * (new_count + 1));
	if (new_tokens == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<<") == 0)
		{
			*heredoc = ft_strdup(tokens[i + 1]);
			i = i + 2;
		}
		else
		{
			new_tokens[j] = ft_strdup(tokens[i]);
			j++;
			i++;
		}
	}
	new_tokens[j] = NULL;
	return (new_tokens);
}

static char	**remove_heredoc_tokens(char **tokens, char **heredoc)
{
	int		new_count;
	char	**new_tokens;

	new_count = 0;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "<<") == 0)
			tokens = tokens + 2;
		else
		{
			new_count++;
			tokens++;
		}
	}
	tokens = advanced_tokenize("");
	new_tokens = build_new_tokens(tokens, heredoc, new_count);
	return (new_tokens);
}*/

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
			new_count++;
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
		if (ft_strcmp(tokens[i], "<<") == 0)
		{
			*heredoc = ft_strdup(tokens[i + 1]);
			i = i + 2;
		}
		else
			new_tokens[new_count++] = ft_strdup(tokens[i++]);
	}
	new_tokens[new_count] = NULL;
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
	cmd->args = tokens;
	cmd->heredoc_delim = heredoc;
	return (cmd);
}
