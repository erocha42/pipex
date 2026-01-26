/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzorolinux <enzorolinux@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:53:14 by erocha--          #+#    #+#             */
/*   Updated: 2026/01/26 00:27:44 by enzorolinux      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_stacks(char **stacks)
{
	int	i;

	i = 0;
	while (stacks[i])
	{
		free(stacks[i]);
		i++;
	}
	free(stacks);
}

void	clean_exit(t_data *data, int error_code)
{
	if (data->command)
		free_stacks(data->command);
    if (data->path)
		free(data->path);
	exit (error_code);
}
