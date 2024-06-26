/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:10:40 by lcollado          #+#    #+#             */
/*   Updated: 2024/04/28 16:51:15 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_delimiter(char *buf, char *delimiter)
{
	size_t	i;
	size_t	buf_len;

	i = 0;
	buf_len = ft_strlen(buf) - 1;
	if (buf_len != ft_strlen(delimiter))
		return (-1);
	while (i < buf_len)
	{
		if (buf[i] != delimiter[i])
			return (-1);
		i++;
	}
	return (1);
}

void	here_doc(char *delimiter, t_pipex *data)
{
	char	*buf;
	int		fd;

	fd = open(HEREDOC_TMP, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
		return ;
	while (1)
	{
		write(1, "heredoc>", 9);
		buf = get_next_line(STDIN_FILENO);
		if (!buf)
			exit(1);
		if (check_delimiter(buf, delimiter) == 1)
			break ;
		// if (ft_strncmp(delimiter, buf, ft_strlen(delimiter)) == 0)
		// 	break ;
		write(fd, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(fd);
	data->infile = open(HEREDOC_TMP, O_RDONLY);
	if (data->infile < 0)
	{
		unlink(HEREDOC_TMP);
		error("here_doc error");
	}
}

int	fd_infile(t_pipex *data, char **argv)
{
	if (data->here_doc)
		here_doc(argv[2], data);
	else
		data->infile = open(argv[1], O_RDONLY);
	return (data->infile);
}

int	fd_outfile(t_pipex *data, char *argv)
{
	if (data->here_doc)
		data->outfile = open(argv, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		data->outfile = open(argv, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (data->outfile);
}

int	parse(t_pipex *pipex, int argc, char **argv)
{
	if (argc < 5)
		return (0);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argv[1])
		pipex->here_doc = 1;
	pipex->n_cmds = argc - 3 - pipex->here_doc;
	if (fd_infile(pipex, argv) == -1)
		return (0);
	if (fd_outfile(pipex, argv[argc - 1]) == -1)
		return (0);
	return (1);
}
