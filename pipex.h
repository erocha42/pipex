/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:36:31 by erocha--          #+#    #+#             */
/*   Updated: 2026/01/29 16:28:30 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX
# define PIPEX

#include "unistd.h"
#include "stdio.h"
#include "fcntl.h"
#include "sys/wait.h"

typedef struct s_data
{
	char	*path;
    char    **command;
	int		fd_infile;
	int		fd_outfile;
	pid_t	pid1;
	pid_t	pid2;
	int		end[2];
}			t_data;

void	parsing(t_data *data, char *command, char **envp);
void	free_stacks(char **stacks);
void	clean(t_data *data);

#include "libft/libft.h"

#endif