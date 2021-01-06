/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:28:11 by adupuy            #+#    #+#             */
/*   Updated: 2020/12/14 19:13:38 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int		ft_write(const char *str, int i, int i2)
{
	int	ret;

	if (!str || i < 0 || i2 < 0)
		return (0);
	ret = i - i2;
	while (i2 < i)
	{
		write(1, &str[i2], 1);
		i2++;
	}
	return (ret);
}

char	*ft_malloc(int size)
{
	char *str;

	if (!(str = malloc(sizeof(char) * (size + 1))))
	{
		str = NULL;
		return (str);
	}
	return (str);
}

int		ft_convert_cf(char *str, t_cf *ptr, va_list *ap)
{
	int				ret;
	int				dec_s;
	unsigned int	dec_ns;

	ret = 0;
	dec_ns = 0;
	dec_s = 0;
	if (ptr->ci == 'c')
		ret = ft_write_c(ptr, ap);
	else if (ptr->ci == 's' && ptr->zero == 0)
		ret = ft_write_s(str, ptr, ap);
	else if (ptr->ci == 'p' && ptr->zero == 0)
		ret = ft_write_p(ptr, ap);
	else if (ptr->ci == 'd' || ptr->ci == 'i')
		ret = ft_write_i(ptr, ap, dec_s, -1);
	else if (ptr->ci == 'u' || ptr->ci == 'x' || ptr->ci == 'X')
		ret = ft_write_i(ptr, ap, -1, dec_ns);
	else
		ret = ft_write_s(str, ptr, ap);
	return (ret);
}
