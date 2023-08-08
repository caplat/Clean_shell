/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:59:02 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/08 16:39:37 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_lex *simplecommand)
{
	int		fd;
	char	*del;
	t_lex	*current;
	t_lex *next;

	current = simplecommand;
	del = NULL;
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("open error");
		exit(1);
	}
	while (current)
	{
		next = current->next;
		if (ft_strncmp(current->str, "<<", 3) == 0 && next)
		{
			del = ft_strdup(next->str);
			delete_node(&simplecommand,current);
			current = next;
			delete_node(&simplecommand,current);
			if(too_much(fd,del) == 1)
				break;
	 		safe_free(&del);
		}
		current = current->next;
	}
	safe_free(&del);
	close(fd);
}

int too_much(int fd,char *del)
{
	char *buffer;
	
	while(1)
	{
		buffer = readline(">");
		if(!buffer)
		{
			perror("readline error");
			too_much_bis(fd);
		}
		if(strncmp(buffer,del,ft_strlen(del) + 1) == 0)
		{
			free(buffer);
			return(1);
		}
		if(write(fd,buffer,ft_strlen(buffer)) == -1)
		{
			perror("write error");
			free(buffer);
			too_much_bis(fd);
		}
		write(fd,"\n",1);
		free(buffer);
	}
	return(0);
}
void too_much_bis(int fd)
{
	close(fd);
	exit(1);
}
