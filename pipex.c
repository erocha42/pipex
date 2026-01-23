/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:48:12 by erocha--          #+#    #+#             */
/*   Updated: 2026/01/23 15:07:37 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	data_init(t_data *data)
{
	data->path = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	data_init(&data);
	if (argc != 5)
		return (1);
	if (pipe(data.end) == -1)
	{
		perror("pipe");
		clean_exit(&data, 1);
	}
	data.pid1 = fork();
	if (data.pid1 == 0)
	{
		char	**elements_file;

		elements_file = ft_split(argv[2], ' ');
		parsing(&data, ft_strjoin("/", elements_file[0]), envp);
		if (elements_file == NULL || elements_file[0] == NULL)
		{
			free(elements_file);
			clean_exit(&data, 127);
		}
		data.fd_infile = open(argv[1], O_RDONLY);
		if (data.fd_infile < 0)
		{
			close(data.end[1]);
			close(data.end[0]);
			perror(argv[1]);
			clean_exit(&data, 1);
		}
		dup2(data.fd_infile, STDIN_FILENO);
		dup2(data.end[1], STDOUT_FILENO);
		close(data.fd_infile);
		close(data.end[0]);
		execve(data.path, elements_file, envp);
		free(elements_file);
		perror("execve");
		clean_exit(&data, 127);
	}
	data.pid2 = fork();
	if (data.pid2 == 0)
	{
		char	**elements_file;
		int		i;

		i = 0;
		elements_file = ft_split(argv[3], ' ');
		parsing(&data, ft_strjoin("/", elements_file[0]), envp);
		if (elements_file == NULL || elements_file[0] == NULL)
		{
			free(elements_file);
			clean_exit(&data, 127);
		}
		data.fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(data.end[0], STDIN_FILENO);
		dup2(data.fd_outfile, STDOUT_FILENO);
		close(data.fd_outfile);
		close(data.end[1]);
		execve(data.path, elements_file, envp);
		free(elements_file);
		perror("execve");
		clean_exit(&data, 127);
	}
	int	status;
	status = 0;
	close(data.end[0]);
    close(data.end[1]);
    waitpid(data.pid1, NULL, 0);
    waitpid(data.pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	clean_exit(&data, 0);
	return (1);
}
