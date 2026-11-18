/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:07:55 by erocha--          #+#    #+#             */
/*   Updated: 2026/02/06 09:24:15 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	**the_line(t_data *data, char **envp, char *command)
{
	int	i;

	i = 0;
	if (!envp)
	{
		free(command);
		ft_putstr_fd("Command not found\n", 2);
		clean_exit(127, data);
	}
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	free(command);
	ft_putstr_fd("Command not found\n", 2);
	clean_exit(127, data);
	return (NULL);
}

void	parsing(t_data *data, char *command, char **envp)
{
	int		i;
	char	**paths;
	char	*linkcommand;

	paths = the_line(data, envp, command);
	i = 0;
	while (paths[i])
	{
		linkcommand = ft_strjoin(paths[i], command);
		if (access(linkcommand, F_OK) == 0)
		{
			data->path = ft_strdup(linkcommand);
			free_paths(paths);
			free(linkcommand);
			free(command);
			return ;
		}
		free(linkcommand);
		i++;
	}
	free_paths(paths);
	free(command);
	ft_putstr_fd("Command not found\n", 2);
	clean_exit(127, data);
}
