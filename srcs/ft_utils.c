/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 08:55:41 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/12 20:50:16 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	*ft_free(void *ptr, void *res)
{
	ft_memdel(&ptr);
	return (res);
}

void
	to_intpos(t_ipos *ret, t_dpos pos)
{
	ret->x = (int)pos.x;
	ret->y = (int)pos.y;
}

double
	decim(double val)
{
	return (val - (int)val);
}

int
	ft_get_next_number(char **str, char ignorable)
{
	int nb;
	int i;

	i = 0;
	if (ignorable)
		while ((*str)[i] == ignorable)
			i++;
	if (!*str || !ft_isdigit((*str)[i]))
		return (ERROR);
	nb = ft_atoi(*str + i);
	while (ft_isdigit((*str)[i]))
		i++;
	*str += i;
	return (nb);
}

int
	ft_check_ext(char *path, char *ext)
{
	int ext_len;
	int path_len;
	int i;

	ext_len = ft_strlen(ext);
	path_len = ft_strlen(path);
	i = 0;
	if (path_len <= ext_len)
		return (ERROR);
	while (i < ext_len)
	{
		if (path[path_len - ext_len + i] != ext[i])
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}