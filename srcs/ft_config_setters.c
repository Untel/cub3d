/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:10:39 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/12 20:40:12 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_set_color(char *key, int *color, char *str)
{
	int		r;
	int 	g;
	int		b;
	char	tmp[BUFFER_SIZE];

	if (!((r = ft_get_next_number(&str, ' ')) != ERROR && *str == ',' && r >= 0 && r <= 255))
	{
		ft_sprintf(tmp, "Red value for key %s is incorrect", key);
		return (ft_print_err(tmp));
	}
	str++;
	if (!((g = ft_get_next_number(&str, ' ')) != ERROR && *str == ',' && g >= 0 && g <= 255))
	{
		ft_sprintf(tmp, "Green value for key %s is incorrect", key);
		return (ft_print_err(tmp));
	}
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
	ft_set_path(char *key, char *buffer, char *str)
{
	if (ft_strlen(str) >= PATH_URL_SIZE)
	{
		ft_print_err("URL size is too long.");
		return (ERROR);
	}
	ft_strcpy(buffer, str);
	return (SUCCESS);
}

int
	ft_set_window_size(t_game *game, char *str)
{
	game->win.width = ft_get_next_number(&str, ' ');
	game->win.height = ft_get_next_number(&str, ' ');
	if (game->win.width < 1 || game->win.height < 1)
		return (ft_print_err("Win size incorrect.\n"));
	if (game->win.width > MAX_WIDTH)
		game->win.width = MAX_WIDTH;
	if (game->win.height > MAX_HEIGHT)
		game->win.height = MAX_HEIGHT;
	return (SUCCESS);
}

int
	ft_set_sprite(t_game *game, t_sprite *spr, char *path)
{
	while (*path == ' ')
		path++;
	if (ft_isdigit(*path))
	{
		spr->frame_size.x = ft_get_next_number(&path, ' ');
		spr->frame_size.y = ft_get_next_number(&path, ' ');
		if (spr->frame_size.x == 0 || spr->frame_size.x == 0)
			return (ft_print_err("Incorrect size for sprite"));
		spr->frame_size.y = spr->frame_size.y > -1 ? spr->frame_size.y : spr->frame_size.x;
		spr->index.x = 0;
		spr->index.y = 0;
		path++;
	}
	else
		spr->frame_size = (t_ipos) { -1, -1 };
	if (ft_set_image(game, &(spr->img), path) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int
	ft_readline(t_game *game, char *line, char **opts)
{
	int ret;

	ret = SUCCESS;
	if (!ft_strncmp("R ", line, 2) && (ret = ft_check_opts(opts, 0)) != ERROR)
		ret = ft_set_window_size(game, &line[2]);
	else if (!ft_strncmp("NO", line, 2) && (ret = ft_check_opts(opts, 1)) != ERROR)
		ret = ft_set_image(game, &(game->env.NO), &line[2]);
	else if (!ft_strncmp("SO", line, 2) && (ret = ft_check_opts(opts, 2)) != ERROR)
		ret = ft_set_image(game, &(game->env.SO), &line[2]);
	else if (!ft_strncmp("WE", line, 2) && (ret = ft_check_opts(opts, 3)) != ERROR)
		ret = ft_set_image(game, &(game->env.WE), &line[2]);
	else if (!ft_strncmp("EA", line, 2) && (ret = ft_check_opts(opts, 4)) != ERROR)
		ret = ft_set_image(game, &(game->env.EA), &line[2]);
	else if (!ft_strncmp("S", line, 1) && (ret = ft_check_opts(opts, 5)) != ERROR)
		ret = ft_set_sprite(game, &(game->env.S), &line[1]);
	else if (!ft_strncmp("F", line, 1) && (ret = ft_check_opts(opts, 6)) != ERROR)
		ret = ft_set_color("F", &game->env.FLOOR, &line[1]);
	else if (!ft_strncmp("C", line, 1) && (ret = ft_check_opts(opts, 7)) != ERROR)
		ret = ft_set_color("C", &game->env.CEIL, &line[1]);
	else if (ret != ERROR && *line == '1')
	{
		ft_fill_map(game, line);
		return (2);
	}
	else if (*line == 0)
		return (SUCCESS);
	else if (ret != ERROR)
		return (ft_print_err("An unknown key has been provided."));
	return (SUCCESS);
}