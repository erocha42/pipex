/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:07:55 by erocha--          #+#    #+#             */
/*   Updated: 2026/01/22 14:47:11 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**the_line(t_data *data, char **envp)
{
	int	i;
	int	j;
	char *line;
	
	line = ft_strdup("PATH=");
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == line[j])
			j++;
		if (line[j] == '\0')
		{
			free(line);
			return (ft_split(envp[i] + 5, ':'));
		}
		i++;
	}
	free(line);
	clean_exit(data, 1);
	return (NULL);
}

static void	free_paths(char *linkls, char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	free(linkls);
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
			return ;
		}
		free(linkcommand);
		linkcommand = ft_strjoin(paths[i], command);
		i++;
	}
	free_paths(linkcommand, paths);
	ft_putstr_fd("Command not found : ", 2);
	ft_putendl_fd(command, 2);
	clean_exit(data, 0);
}
