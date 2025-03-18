/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:37:03 by motelti           #+#    #+#             */
/*   Updated: 2025/02/06 23:01:43 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	b;

	b = count * size;
	if (size && b / size != count)
		return (NULL);
	str = (char *)malloc(b);
	if (!str)
		return (NULL);
	ft_memset(str, 0, b);
	return (str);
}
