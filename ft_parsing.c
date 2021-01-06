/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 14:32:41 by adupuy            #+#    #+#             */
/*   Updated: 2020/12/09 11:26:43 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_flags(const char *str, t_cf *ptr, int i)
{
	if (str[i] == '-')
	{
		ptr->minus = 1;
		return (ft_check_flags(str, ptr, i + 1));
	}
	if ((str[i]) == '0')
	{
		ptr->zero = 1;
		return (ft_check_flags(str, ptr, i + 1));
	}
	return (i);
}

int	ft_check_width(const char *str, t_cf *ptr, int i, va_list *ap)
{
	int	size;

	size = 0;
	if (str[i] == '*' || ((str[i] >= '1') && (str[i] <= '9')))
	{
		if (str[i] != '*')
			i = ft_if_is_number(str, ptr, i, 0);
		else
		{
			size = va_arg(*ap, int);
			if (size < 0)
			{
				ptr->minus = 1;
				ptr->zero = 0;
				size *= -1;
			}
			ptr->fw = size;
			i++;
		}
		return (i);
	}
	return (i);
}

int	ft_check_precision(const char *str, t_cf *ptr, int i, va_list *ap)
{
	int	size;

	size = 0;
	if (str[i] == '.')
	{
		i++;
		if (str[i] == '*' || ((str[i] >= '0') && (str[i] <= '9')))
		{
			if (str[i] != '*')
			{
				i = ft_if_is_number(str, ptr, i, 1);
				if (ptr->prcs == 0)
					ptr->prcs = -1;
				return (i);
			}
			else
				ft_if_isnot_number(size, ap, ptr);
			return (++i);
		}
		ptr->prcs = -1;
		return (i);
	}
	return (i);
}

int	ft_check_type(const char *str, t_cf *ptr, int i)
{
	if (str[i] == 'c' || str[i] == 's' || str[i] == 'p' || str[i] == 'd'
		|| str[i] == 'i' || str[i] == 'u' || str[i] == 'x' || str[i] == 'X')
	{
		ptr->ci = str[i];
		if (str[i] == 'd' || str[i] == 'i' || str[i] == 'u' || str[i] == 'x'
			|| str[i] == 'X')
		{
			if (ptr->prcs != 0)
				ptr->zero = 0;
		}
		i++;
	}
	return (i);
}

int	ft_check_cf(const char *str, t_cf *ptr, int i, va_list *ap)
{
	i = ft_check_flags(str, ptr, i);
	if ((ptr->minus == 1) && (ptr->zero == 1))
		ptr->zero = 0;
	i = ft_check_width(str, ptr, i, ap);
	i = ft_check_precision(str, ptr, i, ap);
	i = ft_check_type(str, ptr, i);
	return (i);
}
