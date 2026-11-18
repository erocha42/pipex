/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:53:14 by erocha--          #+#    #+#             */
/*   Updated: 2026/02/05 16:48:38 by erocha--         ###   ########.fr       */
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
	if (data->fd_infile > -1)
		close(data->fd_infile);
	if (data->fd_outfile > -1)
		close(data->fd_outfile);
	if (data->end[0] > 2)
		close(data->end[0]);
	if (data->end[1] > 2)
		close(data->end[1]);
	exit(code_error);
}
