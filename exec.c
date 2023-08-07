/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:03:18 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/07 13:37:39 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_my_path(t_mini *shell)
{
	int i;

	i = 0;
	while(shell->env[i])
	{
		if (ft_strncmp("PATH", shell->env[i], 4) == 0)
		{
			shell->allpath = ft_split(ft_substr(shell->env[i], 5,
				ft_strlen(shell->env[i]) - 5), ':');
			break;
		}
		else
			i++;
	}
}

int verify(t_mini *shell,int j)
{
	int i;
	t_lex *current;
	char *path_part;

	i = 0;
	current = find_node(j,shell);
	if(current == NULL)
		return(0);
	if(shell->arg_bis != NULL)
		free_arr(shell->arg_bis);
	shell->arg_bis = ft_split(current->str,' ');
	ft_exit_code(shell->arg_bis,shell);
	while(shell->allpath[i++])
	{
		path_part = ft_strjoin(shell->allpath[i],"/");
		shell->exe = ft_strjoin(path_part,shell->arg_bis[0]);
		free(path_part);
		if(access(shell->exe,F_OK | X_OK) == 0)
			return(1);
		free(shell->exe);
	}
	if(get_nb_node(shell->args) > 1)
		check_built_in(shell);
	return(0);
}

int execute(t_mini *shell)
{
	if(ft_strncmp(shell->arg_bis[0],"echo",4) == 0)
		return(0);
	if(execve(shell->exe,shell->arg_bis,shell->env) == -1)
	{	
		if(shell->arg_bis[0] == NULL)
			return(0);
		if(verif_built_in(shell) == 0)	
			printf("minishell: %s: command not found\n",shell->arg_bis[0]);	
	}
	return(0);
}

t_lex *find_node(int i,t_mini *shell)
{
	int j;
	t_lex *current;

	current = shell->args;
	j = 0;
	while(j < i)
	{
		current = current->next;
		j++;
	}
	return(current);
}

void exec_all(t_mini *shell,int i)
{
	get_my_path(shell);
	verify(shell,i);
	execute(shell);
}
