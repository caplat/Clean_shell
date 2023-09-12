/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:29:39 by acaplat           #+#    #+#             */
/*   Updated: 2023/09/11 17:50:45 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fix_echo(t_mini *shell)
{
	t_lex	*newlist;

	newlist = NULL;
	replace_char(shell->newline_bis, ' ',31, shell);
	// printf("newline -->%s\n",shell->newline_bis);
	if (shell->newline_bis != NULL)
		newlist = echo_list(shell);
		// newlist = echo_list_bis(shell,shell->newline_bis,'|');
	printlist_bis(newlist);
}

t_lex *echo_list(t_mini *shell)
{
	int		i;
	char	*str;
	t_lex	*newlist;

	newlist = NULL;
	i = -1;
	str = ft_calloc(1, 1);
	while (shell->newline_bis[++i])
	{
		check_flag_4(shell->newline_bis, shell, i);
		str = add_char(str, shell->newline_bis[i]);
		if ((shell->newline_bis[i + 1] == '|' && shell->flag == 0
			&& shell->newline_bis[i + 1]) || (shell->newline_bis[i + 1] == '\0' && shell->flag == 0))
		{
			add_element_bis(&newlist, str);
			str = ft_calloc(1, 1);
			i++;
		}
	}
	// printf("%s\n",str);
	// add_element_bis(&newlist, str);
	shell->echo_lst = newlist;
	return (newlist);
}


// t_lex *echo_list(t_mini *shell)
// {
//     int i;
//     char *str;
//     t_lex *newlist;

//     newlist = NULL;
//     i = -1;
//     str = ft_calloc(1, 1);
//     if (!str)
//     {
//         // Gestion de l'échec d'allocation de mémoire
//         return NULL;
//     }

//     while (shell->newline_bis[++i])
//     {
//        check_flag_4(shell->newline_bis, shell, i);
//         str = add_char(str, shell->newline_bis[i]);

//         if (shell->newline_bis[i + 1] == '|' && shell->flag == 0)
//         {
//             add_element_bis(&newlist, ft_strdup(str));
//             // Libérer la mémoire de la chaîne str après l'ajout à newlist
//             free(str);
//             // Réinitialiser str à une nouvelle chaîne vide
//             str = ft_calloc(1, 1);
//             if (!str)
//             {
//                 // Gestion de l'échec d'allocation de mémoire
//                 // Vous pouvez ajouter ici la logique de gestion de l'erreur
//                 return NULL;
//             }
//             i++;
//         }
//     }

//     // Ajouter la dernière chaîne à newlist après la boucle
//     add_element_bis(&newlist, ft_strdup(str));
//     safe_free(&str);

//     shell->echo_lst = newlist;
//     return newlist;
// }

t_lex *echo_list_bis(t_mini *shell,char *str,char target)
{
	int i;
	t_lex *newlist;
	(void)target;
	char *cpy;

	newlist = NULL;
	i = 0;
	while(shell->newline_bis[i])
	{
		check_flag_4(str,shell,i);
		cpy = ft_calloc(1,1);
		cpy = add_char(cpy,shell->newline_bis[i]);
		if(shell->newline_bis[i] == '|' && shell->flag == 0)
		{

		}
		// printf("%c\n",shell->newline_bis[i]);
		// add_element_bis(&newlist,"aa");
		i++;
	}
	printlist_bis(newlist);
	return(newlist);
}