/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 23:35:55 by motelti           #+#    #+#             */
/*   Updated: 2025/03/18 15:12:58 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static	void	execute_command(char **cmd, char *const *envp)
{
	char	*path;

	path = path_cmd(cmd[0], envp);
	if (cmd && path)
	{
		execve(path, cmd, envp);
		ft_error(cmd[0]);
		free_split(cmd);
		exit(127);
	}
	else
	{
		write(STDERR_FILENO, "pipex: ", 7);
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		free_split(cmd);
		free(path);
		exit(127);
	}
}

static	void	first_child(char **av, char *const *envp, int *pipe, int *fd)
{
	char	**cmd;

	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(pipe[1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	close_fd(fd, pipe);
	cmd = ft_split(av[2], ' ');
	execute_command(cmd, envp);
}

static	void	second_child(char **av, char *const *envp, int *pipe, int *fd)
{
	char	**cmd;

	if (dup2(fd[1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	if (dup2(pipe[0], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close_fd(fd, pipe);
	cmd = ft_split(av[3], ' ');
	execute_command(cmd, envp);
}

static int	pipex(char **av, char *const *envp, int *fd)
{
	pid_t	pid;
	pid_t	pid2;
	int		fd_pipe[2];
	int		status;

	status = 0;
	if (pipe(fd_pipe) == -1)
		ft_error("Pipe: ");
	pid = fork();
	if (pid < 0)
		ft_error("Fork: ");
	if (pid == 0)
		first_child(av, envp, fd_pipe, fd);
	pid2 = fork();
	if (pid2 < 0)
		ft_error("Fork: ");
	if (pid2 == 0)
		second_child(av, envp, fd_pipe, fd);
	close_fd(fd, fd_pipe);
	waitpid(pid, NULL, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}

int	main(int ac, char **av, char *const *envp)
{
	int	fd[2];
	int	status;

	if (ac == 5)
	{
		fd[0] = open(av[1], O_RDONLY);
		if (fd[0] < 0)
			ft_error(av[1]);
		fd[1] = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd[1] < 0)
			ft_error(av[4]);
		status = pipex(av, envp, fd);
		exit(status);
	}
	else
	{
		write(2, "Usage: ./pipex [file1] [cmd1] [cmd2] [file2]\n", 45);
		exit(22);
	}
	return (0);
}
