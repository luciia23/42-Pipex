/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:45:20 by lcollado          #+#    #+#             */
/*   Updated: 2024/04/04 12:53:22 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_paths(char **envp)
{
	char	*paths;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	paths = *envp + 5;
	return (ft_split(paths, ':'));
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

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
	char	**split_return;
	int		start;
	int		end;
	int		i;

	cmds = (char ***)malloc((data->n_cmds + 1) * sizeof(char *));
	end = argc - 2;
	start = 2;
	if (data->here_doc)
		start = 3;
	i = start;
	if (!cmds)
		return (NULL);
	while (i <= end)
	{
		split_return = ft_split(argv[i], ' ');
		if (!split_return)
		{
			free(cmds);
			return (NULL);
		}
		cmds[i - start] = split_return;
		i++;
	}
	cmds[data->n_cmds] = NULL;
	return (cmds);
}
