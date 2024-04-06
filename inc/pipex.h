/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:14:31 by lcollado          #+#    #+#             */
/*   Updated: 2024/04/05 21:22:07 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
#include <fcntl.h>
# include <sys/wait.h>

# include "../libft/libft.h"

# define HEREDOC_TMP ".heredoc_file"


typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		here_doc;
	int		n_cmds;
	char	**cmd_paths;
	char	***cmd_args;
	char	*cmd;
	int		fd[2];
	int		fd_prev[2];
}					t_pipex;

// UTILS
void		error(char *msg);
void	free_stuff(t_pipex *pipex);
void	print_msg(char *msg);

// PARSE
int parse(t_pipex *pipex, int argc, char **argv);

// IO
char	**find_paths(char **envp);
char	*get_cmd(char **paths, char *cmd);
char ***get_cmdargs(t_pipex *data, int argc, char *argv[]);

// PIPEX
void make_pipex(t_pipex *data, char **envp);

#endif