/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:41:15 by epainter          #+#    #+#             */
/*   Updated: 2020/10/19 08:06:41 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	int		a;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = ft_memalloc(i + 1)))
		return (0);
	a = 0;
	while (*s1 != '\0')
	{
		str[a++] = *s1;
		s1++;
	}
	while (*s2 != '\0')
	{
		str[a++] = *s2;
		s2++;
	}
	str[a] = '\0';
	return (str);
}
