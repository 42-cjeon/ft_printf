/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:38:51 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/20 14:11:11 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t ft_strlen(const char *str)
{
	size_t len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

int	is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

size_t min(size_t x, size_t y)
{
	size_t arr[2];

	arr[0] = x;
	arr[1] = y;
	return (arr[(x > y)]);
}

size_t max(size_t x, size_t y)
{
	size_t arr[2];

	arr[0] = x;
	arr[1] = y;
	return (arr[(x < y)]);
}

void ft_strrev(char *str, size_t left, size_t right)
{
	char	temp;

	while(left < right)
	{
		temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		left++;
		right--;
	}
}

int int_selector(int x, int y, int select)
{
	int arr[2];

	arr[0] = x;
	arr[1] = y;
	return (arr[select != 0]);
}

size_t size_selector(size_t x, size_t y, int select)
{
	size_t arr[2];

	arr[0] = x;
	arr[1] = y;
	return (arr[select != 0]);
}