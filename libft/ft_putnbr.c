/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:25:09 by epainter          #+#    #+#             */
/*   Updated: 2020/10/19 05:34:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int	tmp;
	int base;
	int flag;

	flag = 1;
	if (n < 0)
	{
		flag = -1;
		ft_putchar('-');
	}
	tmp = n;
	base = 1;
	while (tmp / 10)
	{
		tmp /= 10;
		base *= 10;
	}
	while (base)
	{
		ft_putchar(flag * ((n / base) % 10) + '0');
		base /= 10;
	}
}
