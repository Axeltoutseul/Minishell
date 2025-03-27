/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:56:26 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/27 11:11:13 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_output_redirect(char **tokens, int *index)
{
	int	fd;

	if (tokens[*index + 1] == 0)
	{
		ft_printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	fd = open(tokens[*index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*index = *index + 2;
	return (0);
}

int	process_input_redirect(char **tokens, int *index)
{
	int	fd;

	if (tokens[*index + 1] == 0)
	{
		ft_printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	fd = open(tokens[*index + 1], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*index = *index + 2;
	return (0);
}

int	process_append_redirect(char **tokens, int *index)
{
	int	fd;

	if (tokens[*index + 1] == 0)
	{
		ft_printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	fd = open(tokens[*index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*index = *index + 2;
	return (0);
}

int	process_redirections_loop(char **tokens, int i, int ret)
{
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0)
		{
			ret = process_output_redirect(tokens, &i);
			if (ret < 0)
				return (-1);
		}
		else if (ft_strcmp(tokens[i], ">>") == 0)
		{
			ret = process_append_redirect(tokens, &i);
			if (ret < 0)
				return (-1);
		}
		else if (ft_strcmp(tokens[i], "<") == 0)
		{
			ret = process_input_redirect(tokens, &i);
			if (ret < 0)
				return (-1);
		}
		else
			i = i + 1;
	}
	return (0);
}
