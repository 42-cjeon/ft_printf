/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:55:35 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 06:30:23 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_get_arg			g_get_arg_table[10] = {
	get_arg_as_pointer,
	get_arg_as_char,
	get_arg_as_int,
	get_arg_as_string,
	get_arg_as_uint,
	get_arg_as_uint,
	NULL,
	get_arg_as_int,
	get_arg_as_uint,
	get_percent_sign
};

static const t_arg_to_string	g_arg_to_string_table[10] = {
	pointer_to_string,
	char_to_string,
	int_to_string,
	string_to_string,
	uhex_high_to_string,
	uint_to_string,
	NULL,
	int_to_string,
	uhex_low_to_string,
	percent_sign_to_string
};

size_t	print_arg_with_format(struct s_format_info *fi, va_list *va)
{
	union u_arg				arg;
	char					buf[30];
	struct s_string_info	si;
	size_t					len;

	g_get_arg_table[fi->type % 14](&arg, va);
	si = g_arg_to_string_table[fi->type % 14](buf, &arg, fi);
	len = 0;
	len += print_left_sign(&si);
	len += putchar_repeat(int_selector(' ', '0', (fi->flag & ZERO_PAD) && !(fi->flag & PRECISION)), \
											(si.total_len < fi->min_len) \
											* (fi->min_len - si.total_len) \
											* ((fi->flag & LEFT_ALIGN) == 0));
	len += print_prefix(&si);
	len += putchar_repeat('0', si.mid_padding);
	len += write(1, si.main_part, calc_main_part_len(&si));
	len += putchar_repeat(' ', (si.total_len < fi->min_len) \
								* (fi->min_len - si.total_len) \
								* ((fi->flag & LEFT_ALIGN) != 0));
	return (len);
}

size_t	ft_printf(const char *format, ...)
{
	va_list	va;
	ssize_t	total_len;

	total_len = 0;
	va_start(va, format);
	total_len = parse_normal_string(format, &va);
	va_end(va);
	return (total_len);
}
