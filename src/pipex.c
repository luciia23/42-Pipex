/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:53:15 by lcollado          #+#    #+#             */
/*   Updated: 2024/04/04 12:52:52 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(t_pipex *data, char **envp, int index)
{
	data->cmd = get_cmd(data->cmd_paths, data->cmd_args[index][0]);
	if (!data->cmd)
	{
		perror("error getting the cmd");
	}
	if (data->cmd[index])
	{
		execve(data->cmd, data->cmd_args[index], envp);
		perror("exec failed:");
		exit(EXIT_FAILURE);
	}
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
	if (index > 0)
		close(data->fd_prev[0]);
	close(data->fd[1]);
	if (index < data->n_cmds - 1)
		close(data->fd[1]);
}

void	close_pipes(t_pipex *data, int index)
{
	if (index > 0)
		close(data->fd[0]);
	if (index < data->n_cmds - 1)
	{
		close(data->fd[1]);
		data->fd_prev[0] = data->fd[0];
	}
	else
		close(data->fd[0]);
}

pid_t	create_process(t_pipex *data, char **envp, int index, int *fd_prev)
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
	return (pid);
}

void	make_pipex(t_pipex *data, char **envp)
{
	pid_t	*pids;
	int		i;

	pids = malloc(data->n_cmds * sizeof(pid_t));
	i = 0;
	while (i < data->n_cmds)
	{
		pids[i] = create_process(data, envp, i, data->fd_prev);
		i++;
	}
	i = 0;
	while (i++ < data->n_cmds)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
}
