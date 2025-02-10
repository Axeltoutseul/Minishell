/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:38:52 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/10 15:36:43 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirection(const char *file, int io_flag)
{
	int	fd;

	if (io_flag == O_RDONLY)
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			perror("Erreur lors de l'ouverture du fichier");
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		fd = open(file, io_flag, 0644);
		if (fd < 0)
		{
			perror("Erreur lors de l'ouverture du fichier");
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
	return (0);
}

void	handle_pipe(char *cmd1[], char *cmd2[])
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) == -1)
	{
		perror("Erreur lors de la création du pipe");
		exit(EXIT_FAILURE);
	}
	if ((pid1 = fork()) == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execve(cmd1[0], cmd1, NULL);
		perror("Erreur lors de l'exécution de la commande");
		exit(EXIT_FAILURE);
	}
	if ((pid2 = fork()) == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		execve(cmd2[0], cmd2, NULL);
		perror("Erreur lors de l'exécution de la commande");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
