/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 17:06:22 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/12 17:26:26 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_print_err(char *txt)
{
	ft_fprintf(2, "Error\n");
	ft_fprintf(2, txt);
	ft_fprintf(2, "\n");
	return (ERROR);
}

int
	ft_print_defined_err(char *txt)
{
	ft_fprintf(2, "Error\n");
	perror(txt);
	return (ERROR);
}
