/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 09:45:34 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/06 10:10:48 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_size_nb(long long int n)
{
	int	count;

	count = 1;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(long long int n)
{
	char			*str;
	int				i;
	int				size;

	size = ft_size_nb(n);
	if (size == 1)
		++size;
	if ((str = ft_malloc(--size)) == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	i = 0;
	str[size--] = '\0';
	while (n > 0)
	{
		str[size--] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}

char	*ft_itoa_unsig(unsigned long long int n)
{
	char					*str;
	int						i;
	int						size;

	size = ft_size_nb(n);
	if (size == 1)
		++size;
	if ((str = ft_malloc(--size)) == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	i = 0;
	str[size--] = '\0';
	while (n > 0)
	{
		str[size--] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}
