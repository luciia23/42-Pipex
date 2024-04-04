/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:50:10 by lcollado          #+#    #+#             */
/*   Updated: 2024/04/04 12:52:05 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *msg)
{
	write(1, "ERROR: ", 7);
	write(1, msg, ft_strlen(msg));
	exit(0);
}

void	free_stuff(t_pipex *pipex)
{
	//TODO : free
	//free cmd_paths
	if (pipex->here_doc)
		unlink(HEREDOC_TMP);
	close(pipex->infile);
	close(pipex->outfile);
}
