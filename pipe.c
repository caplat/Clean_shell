/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:55:14 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/09 17:41:32 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_node(t_lex *head)
{
	t_lex	*current;
	int		i;

	i = 0;
	current = head;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

// void	do_the_pipe(t_mini *shell)
// {
// 	int		pipe_fd[2];
// 	pid_t	child_pid;
//     t_pipe var;

// 	var.prev_pipe_read = 0;
// 	var.nb_node = get_nb_node(shell->args);
// 	var.i = -1;
// 	while (++var.i < var.nb_node)
// 	{
// 		if (pipe(pipe_fd) == -1)
// 		   norme_pipe_4();
// 	    child_pid = fork();
// 	    if (child_pid == -1)
// 		   norme_pipe_ter();
// 		if (child_pid == 0)
// 		{
// 			norme_pipe_bis(&pipe_fd[2],var);
// 			exec_all(shell, var.i);
// 			exit(0);
// 		}
// 		else
// 			norme_pipe(&pipe_fd[2], var);
// 	}
// 	close(var.prev_pipe_read);
// 	ft_wait(shell, child_pid, var);
// }

// void	ft_wait(t_mini *shell, pid_t child_pid, t_pipe var)
// {
// 	int	status;
// 	int	i;

// 	i = -1;
// 	while (++i < var.nb_node)
// 		waitpid(child_pid, &status, 0);
// 	if (WIFEXITED(status))
// 	{
// 		shell->exit_code = WEXITSTATUS(status);
// 	}
// }

// void	norme_pipe(int pipe_fd[2], t_pipe var)
// {
// 	close(pipe_fd[1]);
// 	if (var.i > 0)
// 		close(var.prev_pipe_read);
// 	var.prev_pipe_read = pipe_fd[0];
// }

// void	norme_pipe_bis(int pipe_fd[2],t_pipe var)
// {
// 	close(pipe_fd[0]);
// 	if (var.i > 0)
// 	{
// 		dup2(var.prev_pipe_read, STDIN_FILENO);
// 		close(var.prev_pipe_read);
// 	}
// 	if (var.i < var.nb_node - 1)
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// }

void do_the_pipe(t_mini *shell)
{
    int nb_node;
    int pipe_fd[2];
    int prev_pipe_read = 0;
	pid_t child_pid;
	int i;

	nb_node = get_nb_node(shell->args);
	i = -1;
	printf("--> nb_node %d\n",nb_node);
    while(++i < nb_node) 
	{
		printf("aaa\n");
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
    ft_wait(shell,child_pid,nb_node);
	// i = -1;
    // while(++i < nb_node)
    //     wait(NULL);
}

void ft_wait(t_mini *shell, pid_t child_pid,int nb_node)
{
    int status;
    int i;

    i = -1;
    while(++i < nb_node)
        waitpid(child_pid, &status,0);
    if(WIFEXITED(status))
    {
        shell->exit_code = WEXITSTATUS(status);
        // printf("--> exit_code = %d\n",shell->exit_code);
    }
}
