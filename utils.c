/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:04:00 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/22 18:42:06 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void initialize(char **env,t_mini *shell)
{
	shell->env = env;
	shell->line = NULL;
	shell->newline = NULL;
	shell->flag = 0;
	shell->command = NULL;
	shell->length_command = 0;
	shell->add_char = ft_calloc(1,2);
	shell->lst = NULL;
	shell->simple_command = NULL;
	shell->simplecommand = NULL;
}
char *add_char(char *str,char c)
{
	char *newstr;
	int i;

	i = 0;
	newstr = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	while(str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = c;
	free(str);
	return(newstr);
}
int find_length(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}
void print_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		printf("%s\n",tab[i++]);
}

