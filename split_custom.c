/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_custom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:14:38 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/22 19:33:34 by acaplat          ###   ########.fr       */
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
		if(str[i] == del && shell->flag == 0 && str[i])
		{
			while(str[i] == del)
				i++;
		}
		if(str[i] != del && str[i] && str[i + 1] != del)
		{
			word++;
			printf("i--> %d -->str %c\n",i,str[i]);
			printf("flag--> %d\n",shell->flag);
			while(str[i] != del && str[i])
			{
				check_flag_4(str,shell,i);
				i++;
			}
		}
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

int word_length(t_mini *shell,char *str,char del)
{
	int i;
	int length;

	i = 0;

}

char **custom_split(char *str, char del,t_mini *shell)
{
	char **tab;
	int i;
	int k;

	i = 0;
	k = 0;
	tab = malloc(sizeof(char *) * (word_nb(str,' ',shell)) + 1);
	if(!tab || !str)
		return(NULL);
	while(i < word_nb(str,' ',shell));
	{
		tab[i] = malloc(sizeof(char) * (word_length(shell,&str[k],' ')) + 1);
	}
	
}