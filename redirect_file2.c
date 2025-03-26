/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdirect_file2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:55:03 by quenalla          #+#    #+#             */
/*   Updated: 2025/03/26 15:55:21 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	get_redir_params(const char *op, int *flags, int *mode, int *std_fd)
{
	if (ft_strcmp(op, ">") == 0)
	{
		*flags = O_WRONLY | O_CREAT | O_TRUNC;
		*mode = 0644;
		*std_fd = STDOUT_FILENO;
	}
	else if (ft_strcmp(op, ">>") == 0)
	{
		*flags = O_WRONLY | O_CREAT | O_APPEND;
		*mode = 0644;
		*std_fd = STDOUT_FILENO;
	}
	else if (ft_strcmp(op, "<") == 0)
	{
		*flags = O_RDONLY;
		*mode = 0;
		*std_fd = STDIN_FILENO;
	}
	else
	{
		*flags = 0;
		*mode = 0;
		*std_fd = -1;
	}
}

static int	open_and_dup_file(const char *file, int std_fd, int flags, int mode)
{
	int		fd;

	fd = open(file, flags, mode);
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

static int	handle_single_redirection(const char *op, const char *file)
{
	int		flags;
	int		mode;
	int		std_fd;
	int		ret;

	get_redir_params(op, &flags, &mode, &std_fd);
	if (std_fd == -1)
		return (-1);
	ret = open_and_dup_file(file, std_fd, flags, mode);
	return (ret);
}

int	apply_redirections(char **tokens)
{
	int	i;
	int	ret;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0)
		{
			ret = handle_single_redirection(tokens[i], tokens[i + 1]);
			if (ret == -1)
				return (-1);
			i = i + 2;
		}
		else
			i = i + 1;
	}
	return (0);
}
