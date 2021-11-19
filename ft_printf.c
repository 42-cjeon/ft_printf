/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:55:35 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/19 08:58:08 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static const t_get_argf g_get_argf_table[10] = \
{
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

static const t_arg_to_stringf g_arg_to_stringf_table[10] = \
{
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

void ft_putchar_repeat(char c, size_t r)
{
	while(r--)
		write(1, &c, 1);
}

size_t print_arg_with_format(struct s_format_info *fi, va_list *va)
{
	union u_arg arg;
	char buf[30];
	size_t padding[4];
	char *p_buf;
	size_t len;
	
	p_buf = buf;
	g_get_argf_table[fi->type % 14](&arg, va);
	len = g_arg_to_stringf_table[fi->type % 14](&p_buf, &arg, fi);
	padding[0] = (len < fi->min_len) * (fi->min_len - len) * ((fi->flag & RIGHT_ALIGN) == 0);
	padding[1] = (len < fi->min_len) * (fi->min_len - len) * ((fi->flag & RIGHT_ALIGN) != 0);
	padding[2] = ' ';
	padding[3] = '0';
	ft_putchar_repeat(padding[((fi->flag & ZERO_PAD) != 0) + 2], padding[0]);
	write(1, p_buf, len);
	ft_putchar_repeat(padding[((fi->flag & ZERO_PAD) != 0) + 2], padding[1]);
	return (max(len, fi->min_len));
}

size_t ft_printf(const char *format, ...)
{
	va_list va;
	size_t total_len;
	struct s_format_info fi;
	size_t word_len;
	const char *word;
	
	total_len = 0;
	va_start(va, format);
	while (*format)
	{
		word = format;
		word_len = 0;
		while(*format && *format++ != '%')
			word_len++;
		write(1, word, word_len);
		format = parse_format(format, &fi);
		total_len += print_arg_with_format(&fi, &va) + word_len;
		*format && format++;
	}
	va_end(va);
	return total_len;
}