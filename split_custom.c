/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_custom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:14:38 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/25 15:11:43 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int word_count(t_mini *shell,char *str,char del)
{
    int i;
    int word;

    i = 0;
    word = 0;
    while(str[i])
    {
        check_flag_4(str,shell,i);
        if(str[i] != del)
        {
            word++;
            while(str[i] && (str[i] != del || (str[i] == del && shell->flag != 0)))
            {
                check_flag_4(str,shell,i);
                i++;
            }
        }
        i++;
    }
    shell->flag = 0;
    return(word);
}

int word_length(t_mini *shell,char *str,char del)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while(str[i])
    {
        check_flag_4(str,shell,i);
        while(str[i] && str[i] == del && shell->flag == 0)
            i++;
        while(str[i] && (str[i] != del || (str[i] == del && shell->flag != 0)))
        {
            check_flag_4(str,shell,i);
            i++;
            len++;
        }
        break;
    }
    shell->flag = 0;
    return(len);
}
