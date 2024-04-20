/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:50:10 by lcollado          #+#    #+#             */
/*   Updated: 2024/04/10 10:19:04 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	free_stuff(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	while (pipex->cmd_paths && pipex->cmd_paths[i])
		free(pipex->cmd_paths[i++]);
	free(pipex->cmd_paths);
	i = 0;
	while (pipex->cmd_args && pipex->cmd_args[i])
	{
		j = 0;
		while (pipex->cmd_args[i][j])
			free(pipex->cmd_args[i][j++]);
		free(pipex->cmd_args[i++]);
	}
	free(pipex->cmd_args);
	if (pipex->here_doc)
		unlink(HEREDOC_TMP);
	close(pipex->infile);
	close(pipex->outfile);
}
