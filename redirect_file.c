/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:42:33 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/24 14:18:47 by qacjl            ###   ########.fr       */
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

int	apply_command_redirections(t_command *cmd)
{
	t_redirection	*redir;
	int				ret;

	redir = cmd->redirections;
	ret = 0;
	while (redir)
	{
		if (ft_strcmp(redir->op, ">") == 0)
			ret = redirect_file(redir->target, STDOUT_FILENO,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strcmp(redir->op, ">>") == 0)
			ret = redirect_file(redir->target, STDOUT_FILENO,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (ft_strcmp(redir->op, "<") == 0)
			ret = redirect_file(redir->target, STDIN_FILENO, O_RDONLY, 0);
		if (ret == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
