/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:39:10 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 05:58:23 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdint.h>
# include <stdarg.h>
# include <unistd.h>

union u_arg
{
	int				i;
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
	LEFT_ALIGN = 16,
	PRECISION = 32
};

struct	s_string_info
{
	char	left_sign;
	char	prefix[3];
	size_t	mid_padding;
	char	*main_part;
	size_t	total_len;
};

typedef struct s_string_info	(*t_arg_to_string)(char *buf, \
								union u_arg *arg, struct s_format_info *fi);
typedef void					(*t_get_arg)(union u_arg *arg, va_list *va);
typedef int						(*t_itoa_ulong)(char *buf, \
					unsigned long long n, int base, const char *base_digit);
typedef const char				*(*t_atoi_size_t)(const char *format, \
															size_t *result);
typedef size_t					(*t_strnlen)(const char *str, size_t max_len);
typedef const char				*(*t_process_type)(const char *format, \
													struct s_format_info *fi);
typedef const char				*(*t_process_flags)(const char *format, \
													struct s_format_info *fi);
typedef const char				*(*t_process)(const char *format, \
													struct s_format_info *fi);
typedef ssize_t					(*t_putchar_repeat)(char c, size_t r);
typedef ssize_t					(*t_parser)(const char *format, va_list *va);
typedef size_t					(*t_find_normal_end)(const char *format);

struct s_string_info	char_to_string(char *buf, union u_arg *arg, \
												struct s_format_info *fi);
struct s_string_info	percent_sign_to_string(char *buf, union u_arg *arg, \
												struct s_format_info *fi);
struct s_string_info	string_to_string(char *buf, union u_arg *arg, \
												struct s_format_info *fi);
struct s_string_info	pointer_to_string(char *buf, union u_arg *arg, \
												struct s_format_info *fi);
struct s_string_info	uhex_low_to_string(char *buf, union u_arg *arg, \
												struct s_format_info *fi);
struct s_string_info	uhex_high_to_string(char *buf, union u_arg *arg, \
												struct s_format_info *fi);
struct s_string_info	int_to_string(char *buf, union u_arg *arg, \
												struct s_format_info *fi);
struct s_string_info	uint_to_string(char *buf, union u_arg *arg, \
												struct s_format_info *fi);

int						itoa_ulong(char *buf, unsigned long long n, int base, \
													const char *base_digit);
int						itoa_ulong_end(char *buf, unsigned long long n, \
											int base, const char *base_digit);
int						itoa_int(char *buf, int n);
const char				*atoi_size_t(const char *format, size_t *result);
const char				*end_atoi_size_t(const char *format, size_t *result);

unsigned int			search_flag_char(char c);
int						search_type(char c);
const char				*do_nothing(const char *format, \
													struct s_format_info *fi);

size_t					find_normal_end(const char *format);
size_t					end_find_normal_end(const char *format);
ssize_t					parse_normal_string(const char *format, va_list *va);
ssize_t					parse_format_string(const char *format, va_list *va);
ssize_t					end_parse_string(const char *format, va_list *va);

const char				*process_type(const char *format, \
													struct s_format_info *fi);
const char				*end_process_type(const char *format, \
													struct s_format_info *fi);
const char				*process_flags(const char *format, \
													struct s_format_info *fi);
const char				*end_process_flags(const char *format, \
													struct s_format_info *fi);
const char				*parse_format(const char *format, \
													struct s_format_info *fi);
const char				*process_max_len(const char *format, \
													struct s_format_info *fi);
const char				*process_min_len(const char *format, \
													struct s_format_info *fi);

size_t					print_arg_with_format(struct s_format_info *fi, \
																 va_list *va);
size_t					ft_printf(const char *format, ...);

void					get_arg_as_uint(union u_arg *arg, va_list *va);
void					get_arg_as_int(union u_arg *arg, va_list *va);
void					get_arg_as_char(union u_arg *arg, va_list *va);
void					get_arg_as_string(union u_arg *arg, va_list *va);
void					get_arg_as_pointer(union u_arg *arg, va_list *va);
void					get_percent_sign(union u_arg *arg, va_list *va);

ssize_t					print_left_sign(const struct s_string_info *si);
ssize_t					print_prefix(const struct s_string_info *si);
ssize_t					putchar_repeat(char c, size_t r);
ssize_t					end_putchar_repeat(char c, size_t r);
size_t					calc_main_part_len(struct s_string_info *si);

size_t					strnlen(const char *str, size_t max_len);
size_t					end_strnlen(const char *str, size_t max_len);
void					copy_null(char *buf);

int						is_digit(char c);
int						int_selector(int when_false, int when_true, \
																int select);
size_t					size_selector(size_t when_false, size_t when_true, \
																int select);
void					*pointer_selector(void *when_false, void *when_true, \
																int select);
void					init_si(struct s_string_info *si);

#endif