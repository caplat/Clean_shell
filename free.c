/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:13:26 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/23 16:58:34 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_shell(t_mini *shell)
{
    free_arr(shell->command);
    safe_free(&shell->line);
    safe_free(&shell->newline);
    safe_free(&shell->add_char);
    free_list(shell->lst);
    free_arr(shell->simple_command);
    free_list_bis(shell->simplecommand);
    // free_list_bis(shell->redir);
    free(shell);
}

void free_arr(char **arr)
{
	size_t i;
	
	i = 0;
    if(arr == NULL)
        return;
	while(arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
void free_list(t_elem *head)
{
    t_elem *current;
    t_elem *temp;

    if(head == NULL)
        return;
    current = head;
    while(current != NULL)
    {
        temp = current->next;
        free(current);
        current = temp;
    }
}

void free_list_bis(t_lex *head)
{
    t_lex *current;
    t_lex *temp;

    if(head == NULL)
        return;
    current = head;
    while(current != NULL)
    {
        temp = current->next;
        free(current);
        current = temp;
    }
}

void safe_free(char **str)
{
    if(str != NULL && *str != NULL)
        free(*str);
    *str = NULL;
}