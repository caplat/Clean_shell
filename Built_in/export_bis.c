/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:42:55 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/10 19:09:25 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_character(char *str, char c)
{
	char	*found;

	found = ft_strchr(str, c);
	if (found != NULL)
		return ((int)(found - str));
	return (-1);
}

void	add_quotes(char **env_cpy)
{
	int	i;
	int	pos;

	i = 0;
	while (env_cpy[i])
	{
		pos = find_character(env_cpy[i], '=');
		if (pos != -1)
		{
			insert_char(&env_cpy[i], '\"', pos + 1);
		}
		i++;
	}
	i = 0;
	while (env_cpy[i])
	{
		pos = find_character(env_cpy[i], '=');
		if (pos != -1)
			env_cpy[i] = ft_strjoin(env_cpy[i], "\"");
		i++;
	}
}

char	**do_export(t_mini *shell)
{
	env_cpy(shell);
	sort_tab(shell->env_cpy);
	declare_x(shell->env_cpy);
	add_quotes(shell->env_cpy);
	return (shell->env_cpy);
}

void	export(t_mini *shell)
{
	int		length;
	t_lex	*current;
	int		i;

	current = shell->args;
	i = 1;
	while (current)
	{
		shell->tab = ft_split(current->str, ' ');
		length = find_length(shell->tab);
		if (ft_strncmp(shell->tab[0], "export", 7) == 0 && length == 1)
			print_tab(shell->env_cpy);
		else if (ft_strncmp(shell->tab[0], "export", 7) == 0 && length > 1)
		{
			while (shell->tab[i])
			{
				add_var_export(shell->tab[i], shell);
				add_var_env(shell->tab[i], shell);
				i++;
			}
		}
		free_arr(shell->tab);
		shell->tab = NULL;
		current = current->next;
	}
}

void	add_var_export(char *str, t_mini *shell)
{
	int		res;
	int		pos;
	int		new_pos;
	char	*newstr;

	pos = find_character(str, '=');
	res = check_dup(shell->env_cpy, str);
	if (res != -1)
		remove_str_from_tab(&shell->env_cpy, res);
	newstr = ft_strjoin("declare -x ", str);
	new_pos = find_character(newstr, '=');
	if (new_pos != -1 && newstr[new_pos + 1] == '\0')
	{
		newstr = ft_strjoin(newstr, "\"");
		newstr = ft_strjoin(newstr, "\"");
	}
	else if (pos != -1)
	{
		insert_char(&newstr, '\"', new_pos + 1);
		newstr = ft_strjoin(newstr, "\"");
	}
	add_str_to_tab(&shell->env_cpy, newstr);
	sort_tab(shell->env_cpy);
	free(newstr);
}
