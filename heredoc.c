/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:04:07 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/19 15:17:48 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(const char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
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
			new_tokens[new_count++] = ft_strdup(tokens[i++]);
	}
	new_tokens[new_count] = NULL;
	free_2d_array(tokens);
	return (new_tokens);
}
