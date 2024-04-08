/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:25:11 by lcollado          #+#    #+#             */
/*   Updated: 2024/04/08 12:23:27 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init(t_pipex *data)
{
	data->infile = -1;
	data->outfile = -1;
	data->here_doc = 0;
	data->n_cmds = 0;
	data->cmd_args = NULL;
	data->cmd_paths = NULL;
	data->cmd = NULL;
	data->fd_prev[0] = -1;
	data->fd_prev[1] = -1;
}

void	check_leaks(void)
{
	system("leaks -q pipex");
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	*pipex;
	
	// atexit(check_leaks);
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (parse(pipex, argc, argv))
	{
		pipex->cmd_paths = find_paths(envp);
		pipex->cmd_args = get_cmdargs(pipex, argc, argv);
		make_pipex(pipex, envp);
		free_stuff(pipex);
	}
	else
		print_msg("Invalid arguments");
	free(pipex);
	return (0);
}
