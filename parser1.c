/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:38:31 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/24 18:35:44 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0)
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
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0)
			i = i + 2;
		else
			new_tokens[new_count++] = ft_strdup(tokens[i++]);
	}
	new_tokens[new_count] = NULL;
	free_2d_array(tokens);
	return (new_tokens);
}

static int	count_non_redir_tokens(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0)
			i = i + 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static char	**build_new_tokens(char **tokens, t_redirection **redir,
				int new_size)
{
	int				i;
	int				j;
	char			**new_tokens;
	t_redirection	*new_redir;

	i = 0;
	j = 0;
	new_tokens = malloc(sizeof(char *) * (new_size + 1));
	if (!new_tokens)
		return (NULL);
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0)
		{
			new_redir = malloc(sizeof(t_redirection));
			if (!new_redir)
				return (NULL);
			new_redir->op = ft_strdup(tokens[i]);
			new_redir->target = ft_strdup(tokens[i + 1]);
			new_redir->next = *redir;
			*redir = new_redir;
			i = i + 2;
		}
		else
			new_tokens[j++] = ft_strdup(tokens[i++]);
	}
	new_tokens[j] = NULL;
	return (new_tokens);
}

static char	**extract_redirections(char **tokens, t_redirection **redir)
{
	int		non_redir_count;
	char	**new_tokens;

	non_redir_count = count_non_redir_tokens(tokens);
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
	tokens = advanced_tokenize(expanded_raw);
	free(expanded_raw);
	heredoc = NULL;
	tokens = remove_hd_tokens(tokens, &heredoc);
	cmd->heredoc_delim = heredoc;
	cmd->redirections = NULL;
	tokens = extract_redirections(tokens, &cmd->redirections);
	cmd->args = tokens;
	return (cmd);
}
