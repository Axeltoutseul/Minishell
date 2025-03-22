/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:42:33 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/22 17:01:20 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_file(const char *target, int std_fd, int flags, int mode)
{
	int	fd;

	fd = open(target, flags, mode);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	if (dup2(fd, std_fd) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redirections(char **tokens)
{
	int		i;
	int		fd;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0)
		{
			fd = open(tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open");
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strcmp(tokens[i], ">>") == 0)
		{
			fd = open(tokens[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("open");
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strcmp(tokens[i], "<") == 0)
		{
			fd = open(tokens[i + 1], O_RDONLY);
			if (fd == -1)
			{
				perror("open");
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		i++;
	}
	return (0);
}

static void	free_redirections(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->op);
		free(redir->target);
		free(redir);
		redir = tmp;
	}
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
				free(pipeline->commands[i].args[j++]);
			free(pipeline->commands[i].args);
		}
		if (pipeline->commands[i].heredoc_delim)
			free(pipeline->commands[i].heredoc_delim);
		if (pipeline->commands[i].redirections)
			free_redirections(pipeline->commands[i].redirections);
		i++;
	}
	free(pipeline->commands);
	free(pipeline);
}
