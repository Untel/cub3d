/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_setters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 12:53:31 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/19 22:03:41 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_set_color(char *key, int *color, char *str)
{
	int		r;
	int		g;
	int		b;
	char	tmp[BUFFER_SIZE];

	if (!((r = ft_get_next_number(&str, ' ')) != ERROR
		&& *str == ',' && r >= 0 && r <= 255)
		&& ft_sprintf(tmp, "Red value for key %s is incorrect", key))
		return (ft_print_err(tmp));
	str++;
	if (!((g = ft_get_next_number(&str, ' ')) != ERROR
		&& *str == ',' && g >= 0 && g <= 255)
		&& ft_sprintf(tmp, "Green value for key %s is incorrect", key))
		return (ft_print_err(tmp));
	str++;
	if (!((b = ft_get_next_number(&str, ' ')) != ERROR && b >= 0 && b <= 255))
	{
		ft_sprintf(tmp, "Blue value for key %s is incorrect", key);
		return (ft_print_err(tmp));
	}
	*color = (r << 16) + (g << 8) + b;
	return (SUCCESS);
}

int
	ft_set_sprite(t_game *game, t_sprite *spr, char *path)
{
	while (*path == ' ')
		path++;
	spr->collision = ft_isdigit(*path) && ft_get_next_number(&path, ' ');
	if (ft_isdigit(*path))
	{
		spr->frame_size.x = ft_get_next_number(&path, ' ');
		if (spr->frame_size.x == 0 || spr->frame_size.x == 0
			|| !ft_isdigit(*path))
			return (ft_print_err("Incorrect size for sprite"));
		spr->frame_size.y = ft_get_next_number(&path, ' ');
		spr->frame_size.y = spr->frame_size.y > -1 ?
			spr->frame_size.y : spr->frame_size.x;
		spr->index.x = 0;
		spr->index.y = 0;
	}
	else
		spr->frame_size = (t_ipos) { -1, -1 };
	if (ft_set_image(game, &(spr->img), path) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int
	ft_readline2(t_game *game, char *line, char opts[8], int ret)
{
	if (!ft_strncmp("F", line, 1) &&
		(ret = ft_check_opts(opts, 6)) != ERROR)
		ret = ft_set_color("F", &game->env.floor, &line[1]);
	else if (!ft_strncmp("C", line, 1) &&
		(ret = ft_check_opts(opts, 7)) != ERROR)
		ret = ft_set_color("C", &game->env.ceil, &line[1]);
	else if (ret != ERROR && *line == '1')
	{
		ft_fill_map(game, line);
		return (2);
	}
	else if (*line == 0)
		return (SUCCESS);
	else if (ret != ERROR)
		return (ft_print_err("An unknown key has been provided."));
	return (ret);
}

int
	ft_readline(t_game *game, char *line, char opts[8])
{
	int ret;

	ret = SUCCESS;
	if (!ft_strncmp("R ", line, 2) &&
		(ret = ft_check_opts(opts, 0)) != ERROR)
		ret = ft_set_window_size(game, &line[2]);
	else if (!ft_strncmp("NO", line, 2) &&
		(ret = ft_check_opts(opts, 1)) != ERROR)
		ret = ft_set_image(game, &(game->env.no), &line[2]);
	else if (!ft_strncmp("SO", line, 2) &&
		(ret = ft_check_opts(opts, 2)) != ERROR)
		ret = ft_set_image(game, &(game->env.so), &line[2]);
	else if (!ft_strncmp("WE", line, 2) &&
		(ret = ft_check_opts(opts, 3)) != ERROR)
		ret = ft_set_image(game, &(game->env.we), &line[2]);
	else if (!ft_strncmp("EA", line, 2) &&
		(ret = ft_check_opts(opts, 4)) != ERROR)
		ret = ft_set_image(game, &(game->env.ea), &line[2]);
	else if (!ft_strncmp("S", line, 1) &&
		(ret = ft_check_opts(opts, 5)) != ERROR)
		ret = ft_set_sprite(game, &(game->env.s), &line[1]);
	else
		return (ft_readline2(game, line, opts, ret));
	return (ret);
}
