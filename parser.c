/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:43:22 by qacjl             #+#    #+#             */
/*   Updated: 2025/02/21 17:06:49 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_raw_cmds(char **raw_cmds)
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

static char	**remove_hd_tokens(char **tokens, char **heredoc)
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

static t_command	*parse_command(char *raw)
{
	t_command	*cmd;
	char		**tokens;
	char		*heredoc;

	cmd = malloc(sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	tokens = advanced_tokenize(raw);
	heredoc = NULL;
	tokens = remove_hd_tokens(tokens, &heredoc);
	cmd->args = tokens;
	cmd->heredoc_delim = heredoc;
	return (cmd);
}

static void	fill_pipeline(t_pipeline *pipeline, char **raw_cmds, int count)
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

	raw_cmds = ft_split(line, '|');
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

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;
	int	j;

	if (pipeline == NULL)
		return ;
	i = 0;
	while (i < pipeline->count)
	{
		if (pipeline->commands[i].args)
		{
			j = 0;
			while (pipeline->commands[i].args[j])
			{
				free(pipeline->commands[i].args[j]);
				j++;
			}
			free(pipeline->commands[i].args);
		}
		if (pipeline->commands[i].heredoc_delim)
			free(pipeline->commands[i].heredoc_delim);
		i++;
	}
	free(pipeline->commands);
	free(pipeline);
}
