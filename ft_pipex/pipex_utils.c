/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:39:19 by motelti           #+#    #+#             */
/*   Updated: 2025/03/18 15:13:30 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	close_fd(int *fd, int *pipe)
{
	close(fd[0]);
	close(fd[1]);
	close(pipe[0]);
	close(pipe[1]);
}

void	ft_error(const char *str)
{
	write(STDERR_FILENO, "pipex: ", 7);
	perror(str);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

char	**find_path(char *const *envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	if (!envp)
	{
		write(2, "Error: Invalid environment\n", 26);
		return (NULL);
	}
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (ft_strncmp(envp[i], "PATH", 4) == 0)
	{
		paths = ft_split(envp[i] + 5, ':');
		if (paths != NULL)
			return (paths);
	}
	free_split(paths);
	write(2, "Error: No path found\n", 21);
	return (NULL);
}

char	*path_cmd(char *cmd, char *const *envp)
{
	char	**env_path;
	char	*cmd_path;
	char	*join;
	int		i;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	env_path = find_path(envp);
	if (env_path == NULL)
		return (NULL);
	i = -1;
	while (env_path[++i])
	{
		join = ft_strjoin(env_path[i], "/");
		cmd_path = ft_strjoin(join, cmd);
		free(join);
		if (access(cmd_path, X_OK) == 0)
		{
			free_split(env_path);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_split(env_path);
	return (NULL);
}
