/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:55:11 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/28 16:48:25 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	remove_ptr(t_vars *vars, void *ptr)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->to_free.size)
	{
		if (vars->to_free.ptrs[i] == ptr)
		{
			vars->to_free.ptrs[i] = NULL;
			j = i;
			while (++j < vars->to_free.size)
				vars->to_free.ptrs[j - 1] = vars->to_free.ptrs[j];
			vars->to_free.size--;
		}
		i++;
	}
}

void	free_ptr_split(t_vars *vars, char **split)
{
	ft_free_split(split);
	remove_ptr(vars, split);
}

char	**add_ptr_split(t_vars *vars, char **split)
{
	int		i;
	void	**ptrs;

	if (!split)
		return (NULL);
	if (vars->to_free.size == vars->to_free.alloc_size)
	{
		ptrs = malloc(sizeof(void *) * (vars->to_free.size + 1));
		if (!ptrs)
			free_and_exit1(vars);
		i = 0;
		while (i < vars->to_free.size)
		{
			ptrs[i] = vars->to_free.ptrs[i];
			i++;
		}
		vars->to_free.alloc_size++;
		free(vars->to_free.ptrs);
	}
	else
		ptrs = vars->to_free.ptrs;
	ptrs[vars->to_free.size] = (void *)split;
	vars->to_free.size++;
	vars->to_free.ptrs = ptrs;
	return ((char **)split);
}

void	free_all(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->to_free.size)
	{
		if (!vars->to_free.ptrs[i])
		{
			i++;
			continue ;
		}
		ft_free_split(vars->to_free.ptrs[i]);
		vars->to_free.ptrs[i] = NULL;
		i++;
	}
	free(vars->to_free.ptrs);
	vars->to_free.ptrs = NULL;
	vars->to_free.size = 0;
}
