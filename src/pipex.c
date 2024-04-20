/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:53:15 by lcollado          #+#    #+#             */
/*   Updated: 2024/04/20 16:11:51 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(t_pipex *data, char **envp, int index)
{
	data->cmd = get_cmd(data->cmd_paths, data->cmd_args[index][0]);
	if (!data->cmd)
	{
		free_stuff(data);
		error("command not found");
	}
	execve(data->cmd, data->cmd_args[index], envp);
	perror("exec failed:");
	exit(EXIT_FAILURE);
}

void	dupandfd(t_pipex *data, int index)
{
	if (index == 0)
		dup2(data->infile, STDIN_FILENO);
	else
		dup2(data->fd_prev[0], STDIN_FILENO);
	if (index < data->n_cmds - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	else
		dup2(data->outfile, STDOUT_FILENO);
}

void	close_pipes(t_pipex *data, int index)
{
	if (index > 0)
		close(data->fd_prev[0]);
	if (index < data->n_cmds - 1)
		data->fd_prev[0] = data->fd[0]; // Transfer read-end for the next command
	else 
		close(data->fd[0]); // Close the last read-end
	close(data->fd[1]); // Close the write-end
}

void	create_process(t_pipex *data, char **envp, int index)
{
	pid_t	pid;

	if ((index < data->n_cmds - 1) && pipe(data->fd) < 0)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		//Child process
		dupandfd(data, index);
		exec_cmd(data, envp, index);
	}
	//Parent process
	close_pipes(data, index);
}

void	make_pipex(t_pipex *data, char **envp)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < data->n_cmds)
	{
		create_process(data, envp, i);
		i++;
	}
	i = 0;
	//parent process waits for all the childs to finish
	while (++i < data->n_cmds)
		waitpid(-1, &status, 0);
}
