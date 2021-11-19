/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:42:52 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/19 01:43:23 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

void get_arg_as_uint(union u_arg *arg, va_list *va)
{
	arg->u = va_arg(*va, unsigned int);
}

void get_arg_as_int(union u_arg *arg, va_list *va)
{
	arg->i = va_arg(*va, int);
}

void get_arg_as_char(union u_arg *arg, va_list *va)
{
	arg->c = (char)va_arg(*va, int);
}
