/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:45:20 by lcollado          #+#    #+#             */
/*   Updated: 2024/04/20 16:56:38 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_paths(char **envp)
{
	char	*paths;

	if (!envp)
		return NULL;
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp)
		return (NULL);
	paths = *envp + 5;
	return (ft_split(paths, ':'));
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

char	***get_cmdargs(t_pipex *data, int argc, char *argv[])
{
	char	***cmds;
	int		i;
	int		start;

	cmds = (char ***)malloc((data->n_cmds + 1) * sizeof(char *));
	if (!cmds)
		return (NULL);
	start = 2;
	if (data->here_doc)
		start++;
	i = start;
	while (i < argc - 1)
	{
		cmds[i - start] = ft_split(argv[i], ' ');
		if (!cmds[i - start])
		{
			while (--i >= start)
				free(cmds[i - start]);
			free(cmds);
			return (NULL);
		}
		i++;
	}
	cmds[data->n_cmds] = NULL;
	return (cmds);
}
