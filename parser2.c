/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:21:24 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/25 16:29:01 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_pipeline(t_pipeline *pipeline, char **raw_cmds, int count)
{
	int			i;
	t_command	*cmd;

	i = 0;
	while (i < count)
	{
		cmd = parse_command(raw_cmds[i]);
		if (!cmd)
			return (0);
		pipeline->commands[i] = *cmd;
		free(cmd);
		i++;
	}
	return (1);
}

static void	trim_space(char **raw_cmds)
{
	char	*trimmed;
	int		i;

	i = -1;
	while (raw_cmds[++i])
	{
		trimmed = ft_strtrim(raw_cmds[i], " \t");
		if (!trimmed || trimmed[0] == '\0')
		{
			ft_printf("bash: erreur de syntaxe près du symbole inattendu `|'\n");
			if (trimmed)
				free(trimmed);
			return (free_2d_array(raw_cmds), NULL);
		}
		free(trimmed);
	}
}

t_pipeline	*parse_input(const char *line)
{
	t_pipeline	*pipeline;
	char		**raw_cmds;
	int			count;
	int			i;

	raw_cmds = split_pipeline(line);
	if (!raw_cmds)
		return (NULL);
	trim_space(raw_cmds);
	count = count_raw_cmds(raw_cmds);
	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (free_2d_array(raw_cmds), NULL);
	pipeline->count = count;
	pipeline->commands = malloc(sizeof(t_command) * count);
	if (!pipeline->commands)
		return (free(pipeline), free_2d_array(raw_cmds), NULL);
	if (!fill_pipeline(pipeline, raw_cmds, count))
		return (free_2d_array(raw_cmds), free(pipeline->commands), \
		free(pipeline), NULL);
	i = -1;
	while (raw_cmds[++i])
		free(raw_cmds[i]);
	return (free(raw_cmds), pipeline);
}

char	**build_new_tokens(char **tokens, t_redirection **redir, int size)
{
	int				i;
	int				j;
	char			**new_tokens;
	t_redirection	*new_redir;
	char			*temp;
	char			*op;

	i = 0;
	j = 0;
	new_tokens = malloc(sizeof(char *) * (size + 1));
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
		if (ft_strcmp(temp, ">") == 0
			|| ft_strcmp(temp, ">>") == 0
			|| ft_strcmp(temp, "<") == 0)
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

int	count_non_redir_tokens(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0)
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
