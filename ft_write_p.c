/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 09:22:12 by adupuy            #+#    #+#             */
/*   Updated: 2020/12/09 12:11:58 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_count_base(unsigned long adr)
{
	int	count;

	count = 0;
	while ((adr / 16) > 0)
	{
		count++;
		adr /= 16;
	}
	return (count);
}

int		ft_newstr_p_next(t_cf *ptr, char *str, int size, int r)
{
	char	*base;

	base = "0123456789abcdef";
	if (r == 2)
		while (size >= 2)
			str[size--] = '0';
	str[size--] = 'x';
	str[size--] = '0';
	if (r == 0)
		while (size >= 0)
			str[size--] = ' ';
	size = ft_write(str, ptr->fw, 0);
	free(str);
	return (size);
}

int		ft_newstr_p(t_cf *ptr, int size, unsigned long adr, int r)
{
	char		*str;
	const char	*base;

	base = "0123456789abcdef";
	if ((str = ft_malloc(size)) == NULL)
		return (0);
	str[size--] = '\0';
	if (r == 1)
	{
		r = ft_count_base(adr) + 2;
		while (size > r)
			str[size--] = ' ';
		size = r;
	}
	while ((adr / 16) > 0)
	{
		str[size--] = base[(adr % 16)];
		adr /= 16;
	}
	if ((r < 2 && ptr->prcs != -1) || (adr != 0 || ptr->fw == -1))
		str[size--] = base[(adr % 16)];
	return (ft_newstr_p_next(ptr, str, size, r));
}

void	ft_fw_inf(t_cf *ptr, int count, int *size)
{
	if (ptr->prcs > count)
		*size = ptr->prcs + 2;
	else
	{
		if (count == 0 && ptr->prcs == -1)
			*size = 2;
		else
			*size = count + 3;
	}
	ptr->fw = *size;
}

int		ft_write_p(t_cf *ptr, va_list *ap)
{
	unsigned long	adr;
	int				size;

	adr = va_arg(*ap, unsigned long);
	if (ptr->fw <= ft_count_base(adr))
	{
		ft_fw_inf(ptr, ft_count_base(adr), &size);
		size = ft_newstr_p(ptr, size, adr, 2);
	}
	else
	{
		if (adr == 0 && ptr->fw == 2 && ptr->prcs != -1)
			ptr->fw = 3;
		else if (ptr->fw - ft_count_base(adr) <= 2 && adr != 0)
			ptr->fw += 1;
		size = ptr->fw;
		if (ptr->minus == 0)
			size = ft_newstr_p(ptr, size, adr, 0);
		else
			size = ft_newstr_p(ptr, size, adr, 1);
	}
	return (size);
}
