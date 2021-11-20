/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:38:51 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/20 21:20:46 by cjeon            ###   ########.fr       */
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

int int_selector(int when_false, int when_true, int select)
{
	int arr[2];

	arr[0] = when_false;
	arr[1] = when_true;
	return (arr[select != 0]);
}

size_t size_selector(size_t when_false, size_t when_true, int select)
{
	size_t arr[2];

	arr[0] = when_false;
	arr[1] = when_true;
	return (arr[select != 0]);
}

void *pointer_selector(void *when_false, void *when_true, int select)
{
	void *arr[2];

	arr[0] = when_false;
	arr[1] = when_true;
	return (arr[select != 0]);
}

long long abs_64(long long x)
{
	return (0);
}