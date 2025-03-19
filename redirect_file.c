/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:42:33 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/19 15:13:10 by axbaudri         ###   ########.fr       */
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
