/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:42:26 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/13 16:23:43 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_count_words(char const *s, char c)
{
	int	l;
	int	i;

	i = 0;
	l = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			l++;
		while (s[i] != c && s[i])
			i++;
	}
	return (l);
}

static int	ft_fill_split(char **split, char const *s, char c, int l)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < l)
	{
		while (s[j] == c && s[j])
			j++;
		k = 0;
		while (s[j + k] != c && s[j + k])
			k++;
		split[i] = malloc((k + 1) * sizeof(char));
		if (!split[i])
			return (0);
		k = 0;
		while (s[j] != c && s[j])
			split[i][k++] = s[j++];
		split[i][k] = '\0';
		i++;
	}
	split[l] = NULL;
	return (1);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split(char const *s, char c)
{
	int		l;
	char	**split;

	if (!s)
		return (NULL);
	l = ft_count_words(s, c);
	split = (char **) malloc((l + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	if (!ft_fill_split(split, s, c, l))
	{
		ft_free_split(split);
		return (NULL);
	}
	return (split);
}
