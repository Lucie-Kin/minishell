/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:22 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/03 18:31:31 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_param(void **to_be_swap, void **swap_with)
{
	void	*tmp;

	tmp = *to_be_swap;
	*to_be_swap = *swap_with;
	*swap_with = tmp;
}

void	swap_node(t_list **s1, t_list **s2)
{
	swap_param((void **)(*s1)->key, (void **)(*s2)->key);
	swap_param((void **)(*s1)->value, (void **)(*s2)->value);
}

t_list	*alpha_order_list(t_list **env2)
{
	t_list	*start;
	t_list	*ordered;

	ordered = *env2;
	start = *env2;
	while (ordered && ordered->next)
	{
		if (ft_strcmp(ordered->value, ordered->next->value) > 0)
		{
			if (ft_strcmp(ordered->value, start) == 0)
				start = ordered->next->value;
			swap_node(ordered, ordered->next);
			ordered = start;
		}
		else
			ordered = ordered->next;
	}
	return (start);
}

int	iskey(char *key)
{
	int	i;

	i = 0;
	if (key[0] == '_' && !key[1])
		return (FALSE);
	else if (ft_isdigit(key[0]) == TRUE)
		return (FALSE);
	else if (ft_isalpha(key[0]) == TRUE || key[0] == '_')
	{
		while (key[++i])
		{
			if (!(ft_isalnum(key[i]) == TRUE || key[i] == '_'))
				return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}

char	*findtwin_and_erase(char *s, char c)
{
	int		i;
	int		j;
	int		twin;
	char	*clean;

	i = 0;
	j = 0;
	twin = 0;
	if (!s)
		return (NULL);
	clean = ft_calloc(ft_strlen(s) - 1, sizeof(char));
	while (s[i])
	{
		if (s[i++] == c && twin < 2)
			twin++;
		else
			clean[j++] = s[i++];
	}
	if (twin == 2)
		return (clean);
	free(clean);
	return (NULL);
}

char	*parse_value(char *value)
{
	char	*tmp;

	if (findtwin_and_erase(value, '\"'))
	
	if (value[0] == '\"' && value[ft_strlen(value)] == '\"')
	{
		tmp = ft_strdup(value + 1);
	}
	// interprete \\ = \ --> \\  + accepte tous les caractères ASCII
	else if (value[0] == '\'' && value[ft_strlen(value)] == '\'')
	// n'interprete pas \\ = \ et \ --> \\\\ 
	else
	// n'accepte aucun caractère interprétables
	;
}

void	bigerrno_export(t_list **env2, char **arg, int export)
{
	t_list	*alpha_order;
	t_list	*var;
	char	**key_value;
	int		n;
	char	*separator;

	n = 0;
	alpha_order = alpha_order_list(env2);
	if (!arg[export + 1])
		print_list(&alpha_order, MSG_EXPORT, TRUE);
	else
	{
		while (arg[export + 1 + n])
		{
			separator = ft_strchr(arg[export + 1 + n], '=');
			if (separator)
				*separator = ';';
			key_value = ft_split(arg[export + 1 + n], ';');
			if (key_value[2])
				strerror(ERR_EXPORT);
			else if (iskey(key_value[0]) == TRUE)
			{
				var = find_key(&alpha_order, key_value[0]);
				if (var && isvalue(key_value[1]) == TRUE)
					var->value = key_value[1];
				else if (isvalue(key_value[1]) == TRUE)
					add_node(env2, key_value[0], key_value[1]);
				else
					strerror(ERR_EXPORT);
			}
			else
				strerror(ERR_EXPORT);
			free_tab(key_value);
			n++;
			// Find if key exists == update value // parse key
			// else create new_node
		}
	}
	free_list(alpha_order);
}
