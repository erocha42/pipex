/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:36:31 by erocha--          #+#    #+#             */
/*   Updated: 2026/02/04 16:53:57 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "unistd.h"
# include "stdio.h"
# include "fcntl.h"
# include "sys/wait.h"

typedef struct s_data
{
	char	*path;
	char	**command;
	int		fd_infile;
	int		fd_outfile;
	pid_t	pid1;
	pid_t	pid2;
	int		end[2];
}			t_data;

void	parsing(t_data *data, char *command, char **envp);
void	free_stacks(char **stacks);
void	clean_exit(int code_error, t_data *data);

#endif