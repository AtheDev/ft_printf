/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:08:35 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/06 10:20:14 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

int	ft_printf_next(const char *str, int *i, va_list *ap)
{
	t_cf	cf;
	char	*tmp;
	int		ret;

	tmp = NULL;
	ret = 0;
	if (str[*i + 1] == ' ')
		ret += write(1, &str[++*i], 1);
	ft_init_struct_cf(&cf);
	*i = ft_check_cf(str, &cf, *i + 1, ap);
	if (cf.ci == 0)
	{
		if ((tmp = ft_malloc(1)) == NULL)
			return (0);
		tmp[0] = str[*i];
		tmp[1] = '\0';
	}
	ret += ft_convert_cf(tmp, &cf, ap);
	return (ret);
}

int	ft_is_letter(const char *str, int *i, int *i2)
{
	int ret;

	ret = 0;
	while (str[*i] != '\0' && str[*i] != '%')
		++*i;
	ret += ft_write(str, *i, *i2);
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	int			i;
	int			i2;
	va_list		ap;
	int			ret;

	i = 0;
	ret = 0;
	va_start(ap, str);
	while (str && (str[i] != '\0'))
	{
		i2 = i;
		if (str[i] != '%')
			ret += ft_is_letter(str, &i, &i2);
		else if ((str[i] == '%') && (str[i + 1] == '%'))
		{
			ret += write(1, &str[++i], 1);
			i++;
		}
		else
			ret += ft_printf_next(str, &i, &ap);
	}
	va_end(ap);
	return (ret);
}
