/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:39:10 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 03:17:10 by cjeon            ###   ########.fr       */
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
	char	left_sign;		// 오른쪽 정렬 + ZEROPADDING 일 때 맨 왼쪽에 부호를 위한 자리
	char	prefix[3];		// # 옵션에서 0x 또는 위에 조건에 해당하지 않을때 부호 를 위한 자리
	size_t	mid_padding;	// precision 이 활성화 되었을 때 ZEROPADDING 개수
	char	*main_part;		// 
	size_t	total_len;
};

typedef struct s_string_info (*t_arg_to_stringf)(char *buf, union u_arg *arg, struct s_format_info *fi);
typedef void (*t_get_argf)(union u_arg *arg, va_list *va);
typedef int (*t_sign_handlerf)(unsigned int flag);

int handle_positive_sign(unsigned int flag);
int handle_negative_sign(unsigned int flag);

struct s_string_info int_to_string(char *buf, union u_arg *arg, struct s_format_info *fi);
struct s_string_info uint_to_string(char *buf, union u_arg *arg, struct s_format_info *fi);
struct s_string_info char_to_string(char *buf, union u_arg *arg, struct s_format_info *fi);
struct s_string_info percent_sign_to_string(char *buf, union u_arg *arg, struct s_format_info *fi);
struct s_string_info string_to_string(char *buf, union u_arg *arg, struct s_format_info *fi);
struct s_string_info pointer_to_string(char *buf, union u_arg *arg, struct s_format_info *fi);
struct s_string_info uhex_low_to_string(char *buf, union u_arg *arg, struct s_format_info *fi);
struct s_string_info uhex_high_to_string(char *buf, union u_arg *arg, struct s_format_info *fi);

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
int int_selector(int x, int y, int select);
size_t size_selector(size_t x, size_t y, int select);

ssize_t __normal(const char *format, va_list *va);
ssize_t __format(const char *format, va_list *va);
ssize_t __end(const char *format, va_list *va);

const char *do_nothing(const char *format, struct s_format_info *fi);
void *pointer_selector(void *when_false, void *when_true, int select);

void init_si(struct s_string_info *si);
int itoa_int(char *buf, int n);
int itoa_ulong(char *buf, unsigned long long n, int base, const char *base_digit);
#endif