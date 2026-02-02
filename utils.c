/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzorolinux <enzorolinux@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:53:14 by erocha--          #+#    #+#             */
/*   Updated: 2026/02/02 20:19:50 by enzorolinux      ###   ########.fr       */
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

void	clean_exit(int code_error, t_data *data)
{
	if (data->command)
		free_stacks(data->command);
    if (data->path)
		free(data->path);
	if (data->end[0] > 2)
		close(data->end[0]);
	if (data->end[1] > 2)
		close(data->end[1]);
    exit(code_error);
}
