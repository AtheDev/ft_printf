/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:04:33 by adupuy            #+#    #+#             */
/*   Updated: 2020/12/08 15:17:51 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_newstr_s2(t_cf *ptr, char *str, int count)
{
	int		ret;
	char	*tmp;
	int		i;

	ret = 0;
	i = -1;
	if ((tmp = ft_malloc(ptr->fw)) == NULL)
		return (ret);
	while (++i < count)
		tmp[i] = str[i];
	while (i < ptr->fw)
		tmp[i++] = ' ';
	tmp[i] = '\0';
	ret = ft_write(tmp, ptr->fw, 0);
	free(tmp);
	return (ret);
}

int	ft_newstr_s(char *str, int count, int size, char c)
{
	char	*tmp;
	int		i;
	int		j;
	int		ret;

	ret = 0;
	j = -1;
	i = 0;
	if ((tmp = ft_malloc(count)) == NULL)
		return (ret);
	if (size > 0 || str[0] == '\0')
		while (++j < (count - size))
			tmp[j] = c;
	else
		j = 0;
	while (j < count)
		tmp[j++] = str[i++];
	tmp[j] = '\0';
	ret = ft_write(tmp, count, 0);
	free(tmp);
	return (ret);
}

int	ft_fw_sup(t_cf *ptr, char *str, int size)
{
	int	ret;

	if (ptr->minus == 0)
	{
		if (ptr->zero == 0)
		{
			if ((ptr->prcs < size && ptr->ci != 's') || ptr->prcs >= size)
				ret = ft_newstr_s(str, ptr->fw, size, ' ');
			else if (ptr->prcs < size && ptr->prcs > 0 && ptr->prcs < ptr->fw)
				ret = ft_newstr_s(str, ptr->fw, ptr->prcs, ' ');
			else
				ret = ft_newstr_s(str, ptr->fw, size - ptr->prcs, ' ');
		}
		else
			ret = ft_newstr_s(str, ptr->fw, size, '0');
	}
	if (ptr->minus == 1)
	{
		if (ptr->prcs >= size || ptr->prcs == 0)
			ret = ft_newstr_s2(ptr, str, size);
		else if (ptr->prcs > 0)
			ret = ft_newstr_s2(ptr, str, ptr->prcs);
	}
	return (ret);
}

int	ft_write_s_next(t_cf *ptr, char *str, int size)
{
	int	ret;

	ret = 0;
	if ((ptr->fw <= size) && ((ptr->prcs == 0) || (ptr->prcs >= size)))
		ret = ft_write(str, size, 0);
	else if (ptr->fw >= size)
		ret = ft_fw_sup(ptr, str, size);
	else if (ptr->fw < size)
	{
		if (ptr->prcs >= size)
			ret = ft_newstr_s(str, size, 0, 0);
		else if (ptr->fw > ptr->prcs)
		{
			if (ptr->minus == 0)
				ret = ft_newstr_s(str, ptr->fw, ptr->prcs, ' ');
			else
				ret = ft_newstr_s2(ptr, str, ptr->prcs);
		}
		else
			ret = ft_newstr_s(str, ptr->prcs, 0, 0);
	}
	return (ret);
}

int	ft_write_s(char *str, t_cf *ptr, va_list *ap)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (str == NULL)
		if ((str = va_arg(*ap, char *)) == NULL)
			str = "(null)";
	if (str == NULL)
		return (ft_write("(null)", 6, 0));
	if (ptr->prcs == -1)
		while (i++ < ptr->fw)
			ret += write(1, " ", 1);
	else
		ret = ft_write_s_next(ptr, str, ft_strlen(str));
	return (ret);
}
