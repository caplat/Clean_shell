/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:40:18 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/20 18:25:59 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norme_export(void)
{
	perror("Memory alloc failed\n");
	return ;
}

void	norme_lex(t_lex **newlist, char *test)
{
	add_element_bis(newlist, ft_strdup(test));
	free(test);
}

int error_child(pid_t child_pid)
{
    if(child_pid == -1)
    {    
        perror("fork error\n");
        return(0);
    }
    return(1);
}

int	parse_export(char **tab)
{
	int	i;

	i = 1;
	if ((65 <= tab[i][0] && tab[i][0] <= 90) || (97 <= tab[i][0]
			&& tab[i][0] <= 122) || tab[i][0] == 95)
            return 1;
    else
	    {
		    printf("minishell: export: `%s': not a valid identifier\n", tab[i]);
		    return (0);
	    }
	return (1);
}

void check_flag_ter(t_lex *current,t_mini *shell)
{
    int i;

    i = 0;
    while(current->str[i])
    {
        if (current->str[i] == '\"' && shell->flag == 0)
            shell->flag = 2;
        else if (current->str[i] == '\"' && shell->flag == 2)
            shell->flag = 0;
        else if (current->str[i] == '\'' && shell->flag == 0)
            shell->flag = 1;
        else if (current->str[i] == '\'' && shell->flag == 1)
            shell->flag = 0;
        i++;
    }
}
