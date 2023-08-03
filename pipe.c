/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:55:14 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/03 12:02:23 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_nb_node(t_lex *head)
{
	t_lex *current;
	int i;

	i = 0;
	current = head;
	while(current)
	{
		current = current->next;
		i++;
	}
	return(i);
}
void do_the_pipe(t_mini *shell)
{
    int nb_node;
    int pipe_fd[2];
    int prev_pipe_read = 0;
	pid_t child_pid;
	int i;

	nb_node = get_nb_node(shell->args);
	i = -1;
    while(++i < nb_node) 
	{
        if (pipe(pipe_fd) == -1) 
		{
            perror("pipe error\n");
            return;
        }
        child_pid = fork();
        if (child_pid == -1) 
		{
            perror("fork error\n");
            return;
        }
        if (child_pid == 0) 
		{
            close(pipe_fd[0]);
            if (i > 0) 
			{
                dup2(prev_pipe_read, STDIN_FILENO);
                close(prev_pipe_read);
            }
            if (i < nb_node - 1) 
                dup2(pipe_fd[1], STDOUT_FILENO);
            exec_all(shell, i);
            exit(0);
        } 
		else 
		{
            close(pipe_fd[1]);
            if (i > 0) 
				close(prev_pipe_read);
            prev_pipe_read = pipe_fd[0];
        }
    }
    close(prev_pipe_read);
	i = -1;
    while(++i < nb_node)
        wait(NULL);
}
