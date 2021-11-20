/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:43:30 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/20 14:03:08 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

#include <stdio.h>
void get_arg_as_string(union u_arg *arg, va_list *va)
{
	arg->s = va_arg(*va, char *);
}

void get_arg_as_pointer(union u_arg *arg, va_list *va)
{
	arg->p = (uintptr_t)va_arg(*va, void *);
}

void get_percent_sign(union u_arg *arg, va_list *va)
{
	arg->c = '%';
}
