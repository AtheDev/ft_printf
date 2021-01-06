/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:49:49 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/06 10:19:33 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct	s_cf
{
	int		minus;
	int		zero;
	int		fw;
	int		prcs;
	char	ci;
}				t_cf;

/*
	********* ft_printf.c *********
*/
int				ft_printf(const char *str, ...);
int				ft_printf_next(const char *str, int *i, va_list *ap);
int				ft_is_letter(const char *str, int *i, int *i2);

/*
	********* ft_printf_utils.c *********
*/
int				ft_strlen(const char *str);
int				ft_write(const char *str, int i, int i2);
char			*ft_malloc(int size);
int				ft_convert_cf(char *str, t_cf *ptr, va_list *ap);

/*
	********* ft_parsing.c *********
*/
int				ft_check_cf(const char *str, t_cf *ptr, int i, va_list *ap);
int				ft_check_flags(const char *str, t_cf *ptr, int i);
int				ft_check_width(const char *str, t_cf *ptr, int i, va_list *ap);
int				ft_check_precision
					(const char *str, t_cf *ptr, int i, va_list *ap);
int				ft_check_type(const char *str, t_cf *ptr, int i);

/*
	********* ft_parsing_utils.c *********
*/
int				ft_atoi(char *str);
void			ft_init_struct_cf(t_cf *cf);
void			ft_if_isnot_number(int size, va_list *ap, t_cf *ptr);
int				ft_if_is_number(const char *str, t_cf *ptr, int i, int r);

/*
	********* ft_write_c.c *********
*/
int				ft_write_c(t_cf *ptr, va_list *ap);
int				ft_new_str_c(t_cf *ptr, unsigned char c, int i, int r);

/*
	********* ft_write_p.c *********
*/
int				ft_write_p(t_cf *ptr, va_list *ap);
void			ft_fw_inf(t_cf *ptr, int count, int *size);
int				ft_newstr_p(t_cf *ptr, int size, unsigned long adr, int r);
int				ft_newstr_p_next(t_cf *ptr, char *str, int size, int r);
int				ft_count_base(unsigned long adr);

/*
	********* ft_write_s.c *********
*/
int				ft_write_s(char *str, t_cf *ptr, va_list *ap);
int				ft_write_s_next(t_cf *ptr, char *str, int size);
int				ft_fw_sup(t_cf *ptr, char *str, int size);
int				ft_newstr_s(char *str, int count, int size, char c);
int				ft_newstr_s2(t_cf *ptr, char *str, int count);

/*
	********* ft_write_i.c *********
*/
int				ft_write_i
					(t_cf *ptr, va_list *ap, int dec_s, unsigned int dec_ns);
char			*ft_write_i_next_dec_s(va_list *ap, int *dec_s, int *minus);
char			*ft_write_i_next_dec_ns
				(t_cf *ptr, va_list *ap, unsigned int *dec_ns);
int				ft_write_i_next2(t_cf *ptr, char *str, int minus, int ret);

/*
	********* ft_write_i_utils.c *********
*/
int				ft_newstr_i(t_cf *ptr, char *str, int size, int minus);
void			ft_newstr_i_next(t_cf *ptr, char *tmp, char *str, int minus);
void			ft_newstr_i_next2(t_cf *ptr, char *tmp, char *str, int minus);
char			*ft_convert_hexa(t_cf *ptr, unsigned int n);

/*
	********* ft_itoa.c *********
*/
char			*ft_itoa_unsig(unsigned long long int n);
char			*ft_itoa(long long int n);
int				ft_size_nb(long long int n);

#endif
