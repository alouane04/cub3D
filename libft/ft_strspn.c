/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariahi <ariahi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:58:06 by ariahi            #+#    #+#             */
/*   Updated: 2022/12/30 17:36:55 by ariahi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *charset)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_strchr(charset, s[i]))
		i++;
	return (i);
}
