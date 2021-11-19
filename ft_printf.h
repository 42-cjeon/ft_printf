/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:39:10 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/19 08:57:51 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdint.h>
# include <stdarg.h>

union u_arg
{
	int				i;
	long long		li;
	unsigned int	u;
	char			*s;
	char			c;
	uintptr_t		p;
};

struct s_format_info
{
	unsigned char	flag;
	size_t			min_len;
	size_t			max_len;
	int				type;
};

enum e_flags
{
	ALT_MOD = 1,
	EMPTY_SPACE = 2,
	POS_SIGN = 4,
	ZERO_PAD = 8,
	RIGHT_ALIGN = 16
};

typedef size_t (*t_arg_to_stringf)(char **string, union u_arg *arg, struct s_format_info *fi);
typedef void (*t_get_argf)(union u_arg *arg, va_list *va);
typedef int (*t_sign_handlerf)(char *sign_place, unsigned int flag);

int handle_positive_sign(char *sign_place, unsigned int flag);
int handle_negative_sign(char *sign_place, unsigned int flag);
size_t int_to_string(char **string, union u_arg *arg, struct s_format_info *fi);
size_t uint_to_string(char **string, union u_arg *arg, struct s_format_info *fi);
size_t	char_to_string(char **string, union u_arg *arg, struct s_format_info *fi);
size_t	percent_sign_to_string(char **string, union u_arg *arg, struct s_format_info *fi);
size_t	string_to_string(char **string, union u_arg *arg, struct s_format_info *fi);
size_t pointer_to_string(char **string, union u_arg *arg, struct s_format_info *fi);
size_t uhex_low_to_string(char **string, union u_arg *arg, struct s_format_info *fi);
size_t uhex_high_to_string(char **string, union u_arg *arg, struct s_format_info *fi);
unsigned int search_flag_char(char c);
int search_type(char c);
const char *process_type(const char *format, struct s_format_info *fi);
const char *process_max_len(const char *format, struct s_format_info *fi);
const char *process_min_len(const char *format, struct s_format_info *fi);
const char *process_flags(const char *format, struct s_format_info *fi);
const char *parse_format(const char *format, struct s_format_info *fi);
void ft_putchar_repeat(char c, size_t r);
size_t print_arg_with_format(struct s_format_info *fi, va_list *va);
size_t ft_printf(const char *format, ...);
void get_arg_as_uint(union u_arg *arg, va_list *va);
void get_arg_as_int(union u_arg *arg, va_list *va);
void get_arg_as_char(union u_arg *arg, va_list *va);
void get_arg_as_string(union u_arg *arg, va_list *va);
void get_arg_as_pointer(union u_arg *arg, va_list *va);
void get_percent_sign(union u_arg *arg, va_list *va);
void ft_strrev(char *str, size_t left, size_t right);
size_t max(size_t x, size_t y);
size_t min(size_t x, size_t y);
int	is_digit(char c);
size_t ft_strlen(char *str);

#endif