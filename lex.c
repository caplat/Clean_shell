/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:29:54 by acaplat           #+#    #+#             */
/*   Updated: 2023/09/06 17:07:28 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_element_bis(t_lex **head, char *simple_command)
{
	t_lex	*newelem;
	t_lex	*current;

	newelem = malloc(sizeof(t_lex));
	newelem->str = simple_command;
	newelem->next = NULL;
	if (*head == NULL)
	{
		newelem->prev = NULL;
		*head = newelem;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = newelem;
	newelem->prev = current;
}

void	printlist_bis(t_lex *head)
{
	t_lex	*current;

	current = head;
	while (current != NULL)
	{
		printf("printlist --> %s\n", current->str);
		current = current->next;
	}
}

t_lex	*get_my_element(t_mini *shell)
{
	t_lex	*newlist;
	int		i;

	newlist = NULL;
	i = 0;
	if (shell->newline == NULL)
		return (NULL);
	shell->simple_command = ft_split(shell->newline, ' ');
	while (shell->simple_command[i])
	{
		add_element_bis(&newlist, shell->simple_command[i]);
		i++;
	}
	return (newlist);
}

t_lex	*set_command(t_lex *head, t_mini *shell)
{
	t_lex	*newlist;
	t_lex	*current;
	int		i;
	char	*test;
	// char *test2;

	i = 0;
	newlist = NULL;
	current = head;
	test = ft_calloc(1, 1);
	while (current)
	{
		check_flag_bis(current, shell);
		test = ft_strjoin_bis(test, current->str);
		// free(test);
		test = ft_strjoin_bis(test, " ");
		// lex_norme(current,newlist,shell,test);
		if (current->next && ft_strncmp(current->next->str, "|", 2) == 0
			&& shell->flag == 0)
		{
			add_element_bis(&newlist,(test));
			current = current->next;
			test = ft_calloc(1,1);
		}
		current = current->next;
	}
	// printf("test 2--> %s\n",test2);
	// printf("test--> %s\n",test);
	// free(test2);
	norme_lex(&newlist, test);
	// printlist_bis(newlist);
	return (newlist);
}

void	check_flag_bis(t_lex *current, t_mini *shell)
{
	int	i;

	i = 0;
	while (current->str[i])
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
