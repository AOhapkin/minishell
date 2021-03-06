/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 08:41:53 by gmyriah           #+#    #+#             */
/*   Updated: 2022/07/03 08:42:16 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*dest;

	dest = malloc(size);
	if (!dest)
		return (NULL);
	return (ft_memset(dest, 0, size));
}
