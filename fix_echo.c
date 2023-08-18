/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:29:39 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/18 15:02:13 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fix_echo(t_mini *shell)
{
	echo_list(shell);
} 

void echo_list(t_mini *shell)
{
	int i;
	char *str;

	i = -1;
	str = ft_calloc(1,1);

	while(shell->newline_bis[++i])
	{
		set_flag(shell->newline_bis,shell,i);
		printf("%d\n",shell->flag);
		str = add_char(str,shell->newline_bis[i]);
		printf("str-->%s\n",str);
		if(shell->newline_bis[i + 1] == '|' 
			&& shell->flag == 0 && shell->newline_bis[i + 1])
		{
			printf("allo\n");
			add_element_bis(&shell->echo_list,ft_strdup(str));
			str = ft_calloc(1,1);
			i++;
		}
	}
	add_element_bis(&shell->echo_list,ft_strdup(str));
	free(str);
	str = NULL;
	printlist_bis(shell->echo_list);
}
