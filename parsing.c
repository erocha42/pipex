/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:07:55 by erocha--          #+#    #+#             */
/*   Updated: 2026/01/29 17:08:46 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**the_line(t_data *data, char **envp)
{
	int	i;
	
	i = 0;
	if (!envp)
    {
		clean(data);
		exit(1);
	}
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	clean(data);
	exit(1);
	return (NULL);
}

static void	free_paths(char *linkcommand, char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	free(linkcommand);
}

void	parsing(t_data *data, char *command, char **envp)
{
	int		i;
	char 	**paths;
	char 	*linkcommand;

	paths = the_line(data, envp);
	i = 0;
	linkcommand = ft_strjoin(paths[i], command);
	while (paths[i])
	{
		if (access(linkcommand, F_OK) == 0)
		{
			data->path = ft_strdup(linkcommand);
			free_paths(linkcommand, paths);
			free(command);
			return ;
		}
		free(linkcommand);
		linkcommand = ft_strjoin(paths[i], command);
		i++;
	}
	free_paths(linkcommand, paths);
	free(command);
	ft_putstr_fd("Command not found", 2);
	clean(data);
	exit(0);
}
