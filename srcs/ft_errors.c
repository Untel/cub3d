/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 17:06:22 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/11 19:57:56 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_print_err(char *txt)
{
	ft_fprintf(2, txt);
	return (ERROR);
}

int
	ft_print_defined_err(void)
{
	perror("Error\n");
	strerror(errno);
	return (ERROR);
}
