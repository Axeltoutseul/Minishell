/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:21:15 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/25 05:14:57 by qacjl            ###   ########.fr       */
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
				ft_printf("bash: erreur de syntaxe près du symbole inattendu `newline'\n");
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

	i = 0;
	new_count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<<") == 0)
			i += 2;
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
		if (ft_strcmp(tokens[i], "<<") == 0)
		{
			*heredoc = ft_strdup(tokens[i + 1]);
			i += 2;
		}
		else
			new_tokens[new_count++] = ft_strdup(tokens[i++]);
	}
	new_tokens[new_count] = NULL;
	free_2d_array(tokens);
	return (new_tokens);
}

static char	**build_new_tokens(char **tokens, t_redirection **redir, int new_size)
{
	int				i;
	int				j;
	char			**new_tokens;
	t_redirection	*new_redir;
	char			*temp;

	i = 0;
	j = 0;
	new_tokens = malloc(sizeof(char *) * (new_size + 1));
	if (!new_tokens)
		return (NULL);
	while (tokens[i])
	{
		temp = ft_strtrim(tokens[i], " \t");
		if (!temp)
		{
			free_2d_array(new_tokens);
			return (NULL);
		}
		if (ft_strcmp(temp, ">") == 0 ||
			ft_strcmp(temp, ">>") == 0 ||
			ft_strcmp(temp, "<") == 0)
		{
			free(temp);
			if (!tokens[i + 1])
			{
				ft_printf("bash: erreur de syntaxe près du symbole inattendu `newline'\n");
				free_2d_array(new_tokens);
				return (NULL);
			}
			temp = ft_strtrim(tokens[i + 1], " \t");
			if (!temp)
			{
				free_2d_array(new_tokens);
				return (NULL);
			}
			if (temp[0] == '\0')
			{
				ft_printf("bash: erreur de syntaxe près du symbole inattendu `newline'\n");
				free(temp);
				free_2d_array(new_tokens);
				return (NULL);
			}
			new_redir = malloc(sizeof(t_redirection));
			if (!new_redir)
			{
				free(temp);
				free_2d_array(new_tokens);
				return (NULL);
			}
			{
				char	*op;
				op = ft_strtrim(tokens[i], " \t");
				if (!op)
				{
					free(new_redir);
					free(temp);
					free_2d_array(new_tokens);
					return (NULL);
				}
				new_redir->op = ft_strdup(op);
				free(op);
			}
			new_redir->target = ft_strdup(temp);
			free(temp);
			new_redir->next = *redir;
			*redir = new_redir;
			i += 2;
		}
		else
		{
			new_tokens[j] = ft_strdup(temp);
			free(temp);
			j++;
			i++;
		}
	}
	new_tokens[j] = NULL;
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
		if (ft_strcmp(tokens[i], ">") == 0 ||
			ft_strcmp(tokens[i], ">>") == 0 ||
			ft_strcmp(tokens[i], "<") == 0)
		{
			if (!tokens[i + 1])
				return (-1);
			i += 2;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static char	**extract_redirections(char **tokens, t_redirection **redir)
{
	int		non_redir_count;
	char	**new_tokens;

	non_redir_count = count_non_redir_tokens(tokens);
	if (non_redir_count == -1)
	{
		ft_printf("bash: erreur de syntaxe près du symbole inattendu `newline'\n");
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
