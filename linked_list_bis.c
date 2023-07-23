/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:57:03 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/23 12:56:29 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void processlist_chevron(t_elem *head,char targetchar,char newdata)
{
    t_elem *current;
    
    current = head;
    while(current != NULL)
    {
        if(current->data == targetchar)
        {
            if(current->prev != NULL)
                insert_after(current->prev,newdata);
            if(current->next != NULL && current->next->data != targetchar)
            {
                insert_after(current,newdata);
                current = current->next;
            }
            if(current->next != NULL && current->next->data == targetchar)
            {    
                current = current->next;
                insert_after(current,newdata);
                current = current->next;
            }
        }
        current = current->next;
    }
}
char *convert_to_str(t_elem *head)
{
    int i;
    char *str;
    t_elem *current;
    
    i = 0;
    if(head == NULL)
        return NULL;
    current = head;
    while(current != NULL)
    {
        i++;
        current = current->next;
    }
    str = malloc(sizeof(char) * (i + 1));
    str[i] = '\0';
    current = head;
    i = 0;
    while(current != NULL)
    {
        str[i] = current->data;
        current = current->next;
        i++;
    }
    str[i] = '\0';
    return(str);
}
