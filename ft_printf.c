/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:55:35 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 03:25:37 by cjeon            ###   ########.fr       */
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

#include <stdio.h>

/*
	print_left_sign()
	print_prefix()
	print_main()
*/

ssize_t	print_left_sign(const struct s_string_info *si)
{
	return write(1, si->prefix, si->left_sign != 0);
}

ssize_t put_prefix(const struct s_string_info *si)
{
	ssize_t ret;

	ret = write(1, si->prefix, (si->prefix[0] != '\0') && (si->left_sign == 0));
	ret += write(1, si->prefix + 1, (si->prefix[1] != '\0') && (si->left_sign == 0));
	return (ret);
}

ssize_t putchar_repeat(char c, size_t r);
ssize_t end_putchar_repeat(char c, size_t r);
typedef ssize_t (*putchar_repeatf)(char c, size_t r);
const static putchar_repeatf putchar_repeat_next_function[2] = {putchar_repeat, end_putchar_repeat};
ssize_t putchar_repeat(char c, size_t r)
{
	ssize_t ret;

	ret = write(1, &c, r != 0);
	return (putchar_repeat_next_function[r == 0](c, r - 1) + ret);
}
ssize_t end_putchar_repeat(char c, size_t r)
{
	(void)c;
	(void)r;
	return (0);
}

size_t calc_main_part_len(struct s_string_info* si)
{
	size_t total_len;

	total_len = si->total_len;
	total_len -= (si->prefix[0] != '\0');
	total_len -= (si->prefix[1] != '\0');
	total_len -= si->mid_padding;

	return (total_len);
}

size_t print_arg_with_format(struct s_format_info *fi, va_list *va)
{
	union u_arg arg;
	char buf[30];
	struct s_string_info si;
	size_t len;

	g_get_argf_table[fi->type % 14](&arg, va);
	si = g_arg_to_stringf_table[fi->type % 14](buf, &arg, fi);
	len = 0;
	len += print_left_sign(&si);
	len += putchar_repeat(int_selector(' ', '0', fi->flag & ZERO_PAD), (si.total_len < fi->min_len) * (fi->min_len - si.total_len) * ((fi->flag & LEFT_ALIGN) == 0));
	len += put_prefix(&si);
	len += putchar_repeat('0', si.mid_padding);
	len += write(1, si.main_part, calc_main_part_len(&si));
	len += putchar_repeat(' ', (si.total_len < fi->min_len) * (fi->min_len - si.total_len) * ((fi->flag & LEFT_ALIGN) != 0));
	return (len);
}

typedef ssize_t (*parserf)(const char *format, va_list *va);
static const parserf with_end_state_normal[2] = {__normal, __end};
static const parserf with_end_state_format[2] = {__format, __end};

typedef size_t (*find_normal_endf)(const char *format);
size_t end_find_normal_end(const char *format);
size_t find_normal_end(const char *format);
static const find_normal_endf find_normal_endf_next_function[2] = {find_normal_end, end_find_normal_end};
size_t find_normal_end(const char *format)
{
	size_t result;

	result = (*format && *format != '%');
	return find_normal_endf_next_function[!result](format + 1) + result;
}

size_t end_find_normal_end(const char *format)
{
	(void)format;
	return (0);
}

ssize_t __normal(const char *format, va_list *va)
{
	ssize_t result;
	size_t word_len;

	word_len = find_normal_end(format);

	result = write(1, format, word_len);
	format += word_len;
	return (with_end_state_format[*format == '\0'](format + 1, va) + result);
}

ssize_t __format(const char *format, va_list *va)
{
	ssize_t result;
	struct s_format_info fi;

	format = parse_format(format, &fi);
	result = print_arg_with_format(&fi, va);
	return (with_end_state_normal[*format == '\0'](format + 1, va) + result);
}

ssize_t __end(const char *format, va_list *va)
{
	return (0);
}

size_t ft_printf(const char *format, ...)
{
	va_list va;
	ssize_t total_len;
	
	total_len = 0;
	va_start(va, format);
	total_len = __normal(format, &va);
	va_end(va);
	return total_len;
}