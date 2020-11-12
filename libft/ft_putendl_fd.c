/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:05:50 by epainter          #+#    #+#             */
/*   Updated: 2020/11/12 01:24:47 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int		ft_putendl_fd(char const *s, int fd)
{
	return (write(fd, s, ft_strlen(s)) + write(fd, "\n", 1));
}
