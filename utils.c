/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:53:14 by erocha--          #+#    #+#             */
/*   Updated: 2026/01/29 16:27:52 by erocha--         ###   ########.fr       */
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

void	clean(t_data *data)
{
	if (data->command)
		free_stacks(data->command);
    if (data->path)
		free(data->path);
	if (data->end[0] > 2)
		close(data->end[0]);
	if (data->end[1] > 2)
		close(data->end[1]);
}
