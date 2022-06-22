/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:49:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/21 17:23:23 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (s && s[counter])
		counter++;
	return (counter);
}

long long	calc_res(const char *str)
{
	long long	res;

	if (ft_strlen(str) > 10)
		return (-1);
	res = 0;
	while (str[0])
	{
		res = (res * 10) + (str[0] - '0');
		str++;
	}
	return (res);
}
