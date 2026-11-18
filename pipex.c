/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:48:12 by erocha--          #+#    #+#             */
/*   Updated: 2026/02/05 16:50:30 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	data_init(t_data *data)
{
	data->path = NULL;
	data->command = NULL;
	data->fd_infile = -1;
	data->fd_outfile = -1;
}

static void	fork1(t_data *data, char **argv, char **envp)
{
	close(data->end[0]);
	data->fd_infile = open(argv[1], O_RDONLY);
	if (data->fd_infile < 0)
	{
		perror(argv[1]);
		clean_exit(127, data);
	}
	data->command = ft_split(argv[2], ' ');
	if (data->command == NULL || data->command[0] == NULL)
	{
		close(data->end[1]);
		clean_exit(127, data);
	}
	if (access(data->command[0], F_OK) == 0)
		data->path = ft_strdup(data->command[0]);
	else
		parsing(data, ft_strjoin("/", data->command[0]), envp);
	dup2(data->fd_infile, STDIN_FILENO);
	dup2(data->end[1], STDOUT_FILENO);
	close(data->fd_infile);
	close(data->end[1]);
	execve(data->path, data->command, envp);
	perror("execve");
	clean_exit(127, data);
}

static void	fork2(t_data *data, char **argv, char **envp)
{
	close(data->end[1]);
	data->fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_outfile < 0)
	{
		perror(argv[4]);
		clean_exit(1, data);
	}
	data->command = ft_split(argv[3], ' ');
	if (data->command == NULL || data->command[0] == NULL)
		clean_exit(127, data);
	if (access(data->command[0], F_OK) == 0)
		data->path = ft_strdup(data->command[0]);
	else
		parsing(data, ft_strjoin("/", data->command[0]), envp);
	dup2(data->end[0], STDIN_FILENO);
	dup2(data->fd_outfile, STDOUT_FILENO);
	close(data->fd_outfile);
	close(data->end[0]);
	execve(data->path, data->command, envp);
	perror("execve");
	clean_exit(127, data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		status;

	if (argc != 5)
		return (1);
	data_init(&data);
	if (pipe(data.end) == -1)
	{
		perror("pipe");
		clean_exit(1, &data);
	}
	data.pid1 = fork();
	if (data.pid1 == 0)
		fork1(&data, argv, envp);
	data.pid2 = fork();
	if (data.pid2 == 0)
		fork2(&data, argv, envp);
	close(data.end[0]);
	close(data.end[1]);
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	clean_exit(status, &data);
}
