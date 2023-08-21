/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_custom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:14:38 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/21 18:37:09 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int word_nb(char *str,char del,t_mini *shell)
{
	int i;
	int word;

	i = 0;
	word = 0;
	while(str[i])
	{
		check_flag_4(str,shell,i);
		// printf("i--> %d\n",i);
		// printf("flag --> %d\n",shell->flag);
		while(str[i] == del && str[i])
			i++;
		if(str[i])
			word++;
		while((str[i] != del && str[i]) ||
			(str[i] == del && shell->flag != 0))
			i++;
	}
	return(word);
}

void	check_flag_4(char *line, t_mini *shell, int i)
{
	if (line[i] == '\"' && shell->flag == 0)
		shell->flag = 2;
	else if (line[i] == '\"' && shell->flag == 2)
		shell->flag = 0;
	else if (line[i] == '\'' && shell->flag == 0)
		shell->flag = 1;
	else if (line[i] == '\'' && shell->flag == 1)
		shell->flag = 0;
	i++;
}
