/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:40:55 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/11 16:51:23 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_isdigit(int c)
{
	int	digit;
	int	letter;

	digit = (c >= '0' && c <= '9');
	letter = ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
	return (digit || letter);
}

static int	hex_digit_to_int(int c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'F')
		return (10 + (c - 'A'));
	if (c >= 'a' && c <= 'f')
		return (10 + (c - 'a'));
	else
		return (0);
}

static int	ft_ise(int c)
{
	return ((c >= 9 && c <= 13) || c == 0 || c == 32);
}

unsigned int	ft_atoui(const char *nptr)
{
	int				i;
	unsigned int	n;

	i = 0;
	n = 0;
	while (ft_ise(nptr[i]) && nptr[i])
		i++;
	while (ft_isdigit(nptr[i]) && nptr[i])
		n = n * 16 + hex_digit_to_int(nptr[i++]);
	return (n);
}
