/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:02:07 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/08 18:30:36 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_output_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("open error");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_output(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("open error");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_input(char *file,t_mini *shell)
{
	int	fd;
	(void)shell;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n",file);
		return;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}