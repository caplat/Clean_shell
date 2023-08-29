/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:42:55 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/29 18:15:17 by acaplat          ###   ########.fr       */
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
	t_exp	var;

	var.current = shell->echo_lst;
	var.i = 1;
	while (var.current)
	{
		var.cpy = ft_strdup(var.current->str);
		replace_char(var.cpy, ' ', 31, shell);
		shell->tab = ft_split(var.cpy, 31);
		var.length = find_length(shell->tab);
		if (ft_strncmp(shell->tab[0], "export", 7) == 0 && var.length == 1 /*&& var.current->next == NULL*/)
			print_tab(shell->env_cpy);
		else if (ft_strncmp(shell->tab[0], "export", 7) == 0 && var.length > 1)
		{
			while (shell->tab[var.i] && parse_export(shell->tab) == 1)
			{
				add_var_export(shell->tab[var.i], shell);
				add_var_env(shell->tab[var.i], shell);
				var.i++;
			}
		}
		norme_export_bis(shell, var.cpy);
		var.current = var.current->next;
	}
	safe_free(&var.cpy);
}

void	add_var_export(char *str, t_mini *shell)
{
	int		res;
	int		pos;
	int		new_pos;
	char	*newstr;

	pos = find_character(str, '=');
	delete_char(str, '\'', '\"', pos);
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
