/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 17:06:22 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/19 13:00:09 by adda-sil         ###   ########.fr       */
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

int
	ft_generate_cos_sin_table(t_game *game)
{
	int		i;
	double	teth;
	double	teth0;

	if (!(game->win.sin = malloc(sizeof(double) * game->win.width))
		|| !(game->win.cos = malloc(sizeof(double) * game->win.width)))
		return (ft_print_defined_err("Allocating cos/sin table failed"));
	i = -1;
	teth = -M_PI / 3 / (game->win.width - 1);
	teth0 = M_PI / 6;
	while (++i < game->win.width)
	{
		game->win.sin[i] = sin(teth0);
		game->win.cos[i] = cos(teth0);
		teth0 += teth;
	}
	return (SUCCESS);
}

int
	ft_check_opts(char *opts, char key)
{
	if (opts[key] == 1)
		return (ft_print_err("A key has been set twice."));
	opts[key] = 1;
	return (SUCCESS);
}
