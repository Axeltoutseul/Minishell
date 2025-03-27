/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:21:24 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/27 13:42:14 by qacjl            ###   ########.fr       */
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

t_pipeline	*parse_input(const char *line)
{
	t_pipeline	*pipeline;
	char		**raw_cmds;
	int			count;
	int			i;

	raw_cmds = split_pipeline(line);
	if (!raw_cmds)
		return (NULL);
	count = count_raw_cmds(raw_cmds);
	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (free_2d_array(raw_cmds), NULL);
	pipeline->count = count;
	pipeline->commands = malloc(sizeof(t_command) * count);
	if (!pipeline->commands)
		return (free(pipeline), free_2d_array(raw_cmds), NULL);
	if (!fill_pipeline(pipeline, raw_cmds, count))
		return (free_2d_array(raw_cmds),
			free(pipeline->commands), free(pipeline), NULL);
	i = -1;
	while (raw_cmds[++i])
		free(raw_cmds[i]);
	return (free(raw_cmds), pipeline);
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
			i = i + 2;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**build_tokens_without_redir(char **tokens, int non_redir_count)
{
	int		i;
	int		count;
	char	**new_tokens;

	new_tokens = malloc(sizeof(char *) * (non_redir_count + 1));
	if (!new_tokens)
		return (NULL);
	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0)
			i = i + 2;
		else
		{
			new_tokens[count++] = ft_strdup(tokens[i]);
			i++;
		}
	}
	new_tokens[count] = NULL;
	return (new_tokens);
}
