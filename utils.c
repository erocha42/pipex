/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:53:14 by erocha--          #+#    #+#             */
/*   Updated: 2026/01/22 14:27:12 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_stacks(char **stacks)
{
	int	i;

	i = 0;
	while (stacks[i])
		free(stacks[i]);
	free(stacks);
}

void	clean_exit(t_data *data, int error_code)
{
	if (data->path)
		free(data->path);
	exit (error_code);
}