/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:32:52 by adupuy            #+#    #+#             */
/*   Updated: 2020/12/14 19:14:04 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_write_i_next2(t_cf *ptr, char *str, int minus, int ret)
{
	if (ptr->fw < (ft_strlen(str) + minus))
		ptr->fw = 0;
	if (ptr->prcs < (ft_strlen(str) + minus))
		ptr->prcs = 0;
	if (ptr->fw >= ft_strlen(str) && ptr->prcs >= (ft_strlen(str) + minus)
		&& ptr->prcs >= ptr->fw)
		ptr->fw = 0;
	if (ptr->fw == 0 && ptr->prcs != 0)
		ret = ft_newstr_i(ptr, str, ptr->prcs + minus, minus);
	else if (ptr->fw > 0)
		ret = ft_newstr_i(ptr, str, ptr->fw, minus);
	else
	{
		if (minus == 1)
			write(1, "-", ++ret);
		ret += ft_write(str, ft_strlen(str), 0);
	}
	return (ret);
}

char	*ft_write_i_next_dec_ns(t_cf *ptr, va_list *ap, unsigned int *dec_ns)
{
	char	*str;

	str = NULL;
	if (ptr->ci == 'u')
	{
		*dec_ns = va_arg(*ap, unsigned int);
		str = ft_itoa_unsig(*dec_ns);
	}
	else if (ptr->ci == 'x' || ptr->ci == 'X')
	{
		*dec_ns = va_arg(*ap, unsigned int);
		str = ft_convert_hexa(ptr, *dec_ns);
	}
	return (str);
}

char	*ft_write_i_next_dec_s(va_list *ap, int *dec_s, int *minus)
{
	long long int	a;

	a = 0;
	*dec_s = va_arg(*ap, int);
	if (*dec_s < 0)
	{
		*minus = 1;
		a = *dec_s;
		a *= -1;
		return (ft_itoa(a));
	}
	return (ft_itoa(*dec_s));
}

int		ft_write_i(t_cf *ptr, va_list *ap, int dec_s, unsigned int dec_ns)
{
	char	*str;
	int		i;
	int		minus;
	int		ret;

	minus = 0;
	i = 0;
	ret = 0;
	if (ptr->ci == 'u' || ptr->ci == 'x' || ptr->ci == 'X')
		str = ft_write_i_next_dec_ns(ptr, ap, &dec_ns);
	else
		str = ft_write_i_next_dec_s(ap, &dec_s, &minus);
	if ((dec_s == 0 || dec_ns == 0) && ptr->prcs == -1)
	{
		if (ptr->fw > 0)
			while (i++ < ptr->fw)
			{
				write(1, " ", 1);
				ret++;
			}
		return (ret);
	}
	ret = ft_write_i_next2(ptr, str, minus, 0);
	free(str);
	return (ret);
}
