/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:32:59 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/03 18:22:17 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_pipeline(t_pipeline *pipeline, char **raw_cmds, int count)
{
	int			i;
	t_command	*cmd;

	i = 0;
	while (i < count)
	{
		cmd = parse_command(raw_cmds[i]);
		pipeline->commands[i] = *cmd;
		free(cmd);
		i = i + 1;
	}
}

t_pipeline	*parse_input(const char *line)
{
	t_pipeline	*pipeline;
	char		**raw_cmds;
	int			count;
	int			i;
	char		*expanded_line;

	expanded_line = expand_variables(line);
	raw_cmds = ft_split(expanded_line, '|');
	free(expanded_line);
	count = count_raw_cmds(raw_cmds);
	pipeline = malloc(sizeof(t_pipeline));
	if (pipeline == NULL)
		return (NULL);
	pipeline->count = count;
	pipeline->commands = malloc(sizeof(t_command) * count);
	if (pipeline->commands == NULL)
		return (free(pipeline), NULL);
	fill_pipeline(pipeline, raw_cmds, count);
	i = 0;
	while (raw_cmds[i] != NULL)
	{
		free(raw_cmds[i]);
		i = i + 1;
	}
	free(raw_cmds);
	return (pipeline);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;
	int	j;

	if (pipeline == NULL)
		return ;
	i = 0;
	while (i < pipeline->count)
	{
		if (pipeline->commands[i].args != NULL)
		{
			j = 0;
			while (pipeline->commands[i].args[j] != NULL)
			{
				free(pipeline->commands[i].args[j]);
				j = j + 1;
			}
			free(pipeline->commands[i].args);
		}
		if (pipeline->commands[i].heredoc_delim != NULL)
			free(pipeline->commands[i].heredoc_delim);
		i = i + 1;
	}
	free(pipeline->commands);
	free(pipeline);
}
