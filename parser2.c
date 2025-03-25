/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:21:24 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/22 21:31:22 by qacjl            ###   ########.fr       */
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
	char		*trimmed;

	raw_cmds = split_pipeline(line);
	if (!raw_cmds)
		return (NULL);
	i = 0;
	while (raw_cmds[i])
	{
		trimmed = ft_strtrim(raw_cmds[i], " \t");
		if (!trimmed || trimmed[0] == '\0')
		{
			ft_printf("bash: erreur de syntaxe près du symbole inattendu `|'\n");
			if (trimmed)
				free(trimmed);
			free_2d_array(raw_cmds);
			return (NULL);
		}
		free(trimmed);
		i++;
	}
	count = count_raw_cmds(raw_cmds);
	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
	{
		free_2d_array(raw_cmds);
		return (NULL);
	}
	pipeline->count = count;
	pipeline->commands = malloc(sizeof(t_command) * count);
	if (!pipeline->commands)
	{
		free(pipeline);
		free_2d_array(raw_cmds);
		return (NULL);
	}
	if (!fill_pipeline(pipeline, raw_cmds, count))
	{
		free_2d_array(raw_cmds);
		free(pipeline->commands);
		free(pipeline);
		return (NULL);
	}
	i = 0;
	while (raw_cmds[i])
	{
		free(raw_cmds[i]);
		i++;
	}
	free(raw_cmds);
	return (pipeline);
}
