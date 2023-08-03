/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:46:21 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/03 15:46:43 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void pwd(t_mini *shell)
{	
	char *cwd;
	t_lex *current;

	current = shell->args;
	while(current)
	{
		shell->tab = ft_split(current->str,' ');
		if(ft_strncmp(shell->tab[0],"pwd",4) == 0)
		{	
			cwd = getcwd(NULL, 0);
			if(cwd == NULL)
			{
				perror("error current directory");
				return;
			}
			printf("%s\n",cwd);
			free(cwd);
		}
		free_arr(shell->tab);
		shell->tab = NULL;
		current = current->next;
	}
}
