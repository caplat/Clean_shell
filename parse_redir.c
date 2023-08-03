/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:44:47 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/01 09:50:58 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	parse_redir(t_lex **simple_command, t_mini *shell)
// {
// 	t_lex	*current;
// 	t_lex	*next_node;
// 	t_lex	*prev_node;
// 	char	*redir_str;
// 	char	*str;

// 	current = *simple_command;
// 	str = ft_strdup("");
// 	free_list_bis(shell->redir);
// 	shell->redir = NULL;
// 	while (current)
// 	{
// 		next_node = current->next;
// 		if (next_node && (ft_strncmp(current->str, ">", 2) == 0
// 			|| ft_strncmp(current->str, "<", 2) == 0
// 			|| ft_strncmp(current->str, ">>", 3) == 0
// 			|| ft_strncmp(current->str, "<<", 3) == 0))
// 		{
// 			redir_str = ft_strjoin(current->str, " ");
// 			redir_str = ft_strjoin(redir_str, next_node->str);
// 			add_element_bis(&shell->redir, ft_strdup(redir_str));
// 			if (current == *simple_command)
// 				*simple_command = next_node->next;
// 			else
// 			{
// 				prev_node = *simple_command;
// 				while (prev_node && prev_node->next != current)
// 					prev_node = prev_node->next;
// 				if (prev_node)
// 					prev_node->next = next_node->next;
// 			}
// 			free(current->str);
// 			free(current);
// 			free(next_node->str);
// 			free(next_node);
// 			free(redir_str);
// 			current = next_node->next;
// 		}
// 		else
// 			current = next_node;
// 	}
// 	free(str);
// }

// void parse_redir(t_lex **simple_command, t_mini *shell) {
//     t_lex *current = *simple_command;
//     t_lex *next_node;
//     t_lex *prev_node;
//     char *redir_str;

//     free_list_bis(shell->redir);
//     shell->redir = NULL;

//     while (current) {
//         next_node = current->next;
//         if (next_node && (ft_strncmp(current->str, ">", 2) == 0
//                         || ft_strncmp(current->str, "<", 2) == 0
//                         || ft_strncmp(current->str, ">>", 3) == 0
//                         || ft_strncmp(current->str, "<<", 3) == 0)) {
//             redir_str = ft_strjoin(current->str, " ");
//             redir_str = ft_strjoin(redir_str, next_node->str);
//             add_element_bis(&shell->redir, redir_str);

//             if (current == *simple_command)
//                 *simple_command = next_node->next;
//             else {
//                 prev_node = *simple_command;
//                 while (prev_node && prev_node->next != current)
//                     prev_node = prev_node->next;
//                 if (prev_node)
//                     prev_node->next = next_node->next;
//             }

//             free(current->str);
//             free(current);
//             free(next_node);

//             Do not free redir_str here,
// 	as it has been added to shell->redir list.
//         }

//         current = next_node;
//     }
// }

void	parse_redir(t_lex *simplecommand,t_mini *shell)
{
	t_lex *current;
	char *str;

	current = simplecommand;
	while (current)
	{
		str = ft_calloc(1,1);
		if ((ft_strncmp(current->str, ">", 1) == 0 || 
			(ft_strncmp(current->str,"<", 1) == 0)) && (current->next))
		{
			str = ft_strjoin(current->str," ");
			current = current->next;
			str = ft_strjoin(str,current->str);
			add_element_bis(&shell->redir,str);
		}
		current = current->next;
	}
	free(str);
}

void remove_redir(t_lex **simplecommand)
{
    t_lex *current = *simplecommand;
    t_lex *next_node;
	
	current = *simplecommand;
    while (current != NULL)
    {
        next_node = current->next;

        if (ft_strncmp(current->str, ">", 1) == 0 || ft_strncmp(current->str, "<", 1) == 0)
        {
            delete_node(simplecommand, current);
        }
        current = next_node;
    }
}
