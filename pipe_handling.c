/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:29:30 by qacjl             #+#    #+#             */
/*   Updated: 2025/02/18 18:03:05 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static void	create_first_child(char *cmd[], int pipe_fd[2])
{
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execve(cmd[0], cmd, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	create_second_child(char *cmd[], int pipe_fd[2])
{
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	execve(cmd[0], cmd, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	handle_pipe(char *cmd1[], char *cmd2[])
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = safe_fork();
	if (pid1 == 0)
		create_first_child(cmd1, pipe_fd);
	pid2 = safe_fork();
	if (pid2 == 0)
		create_second_child(cmd2, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

/*void	handle_pipe(char *cmd1[], char *cmd2[])
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
}*/

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
