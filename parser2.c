/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:39:01 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/21 16:44:17 by axbaudri         ###   ########.fr       */
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
		i++;
	}
}

t_pipeline	*parse_input(const char *line)
{
	t_pipeline	*pipeline;
	char		**raw_cmds;
	int			count;
	int			i;

	raw_cmds = split_pipeline(line);
	count = count_raw_cmds(raw_cmds);
	pipeline = malloc(sizeof(t_pipeline));
	if (pipeline == NULL)
		return (NULL);
	pipeline->count = count;
	pipeline->commands = malloc(sizeof(t_command) * count);
	if (pipeline->commands == NULL)
	{
		free(pipeline);
		return (NULL);
	}
	fill_pipeline(pipeline, raw_cmds, count);
	i = 0;
	while (raw_cmds[i])
		free(raw_cmds[i++]);
	free(raw_cmds);
	return (pipeline);
}
