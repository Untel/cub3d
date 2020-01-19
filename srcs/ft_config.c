/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:10:39 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/19 12:31:48 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_configure(t_game *game, char *filename)
{
	int		fd;
	int		ret;
	int		gnl_ret;
	char	*line;
	char	opts[8];

	gnl_ret = SUCCESS;
	ret = SUCCESS;
	if ((fd = open(filename, O_RDONLY)) == ERROR)
		return (ft_print_defined_err("Cannot open config file"));
	while (ret == SUCCESS && (gnl_ret = get_next_line(fd, &line)) == SUCCESS)
	{
		ret = ft_readline(game, line, opts);
		free(line);
		if (ret == -1)
			return (ret);
	}
	if (ft_verify_opts(opts) == ERROR)
		return (ERROR);
	return (ft_read_config_file(gnl_ret, ret, fd, game));
}

int
	ft_read_config_file(int gnl_ret, int ret, int fd, t_game *game)
{
	char *line;

	if (gnl_ret > 0 && ret == 2 && (ret = SUCCESS))
	{
		while (ret && (gnl_ret = get_next_line(fd, &line)))
		{
			ret = ft_fill_map(game, line) == 2;
			free(line);
		}
		if (gnl_ret == 0)
		{
			ret = ft_fill_map(game, line) == 2;
			free(line);
		}
	}
	else if (gnl_ret == 0 || ret != 2)
		return (ft_print_err("No map. Define a map at the end of .cub file."));
	if (gnl_ret == ERROR)
		return (ft_print_defined_err("Cannot read config file"));
	if (ret == SUCCESS)
		ret = ft_set_sprite(game, &(game->weapon), "215 127 ./pics/weapon.xpm");
	return (ret == SUCCESS ? SUCCESS : ERROR);
}

int
	init_config(t_game *game)
{
	game->p.ms = 0.12;
	game->p.rs = 0.04;
	game->p.view = 0;
	game->p.view2 = 0;
	game->p.hp = 999;
	game->p.max_hp = 999;
	game->collision = 1;
	game->hud = 0;
	game->shading = 0;
	game->p.jumping = 0;
	game->p.pos.y = 0;
	game->p.pos.x = 0;
	game->win.sin = NULL;
	game->win.cos = NULL;
	game->win.floor_dist = NULL;
	game->win.sky_dist = NULL;
	ft_memset(game->event, 0, EXIT + 1);
}

int
	ft_generate_floor_dist(t_game *game)
{
	int i;

	if (!(game->win.floor_dist = malloc(sizeof(double) * game->win.height))
		|| !(game->win.sky_dist = malloc(sizeof(double) * game->win.height)))
		return (ft_print_defined_err("Allocating sky/floor dist table failed"));
	i = -1;
	while (++i < game->win.height / 2)
	{
		game->win.floor_dist[i] = ((2. * game->win.height));
		game->win.sky_dist[game->win.height - i] = ((2. * game->win.height));
	}
	while (i < game->win.height)
	{
		game->win.floor_dist[i] =
			(game->win.height / (2. * (double)i - game->win.height));
		game->win.sky_dist[game->win.height - i] =
			(game->win.height / (2. * (double)i - game->win.height));
		i++;
	}
}

int
	ft_args(t_game *game, int ac, char **argv)
{
	int		ret;
	char	*trimmed;

	init_config(game);
	if (ac > 1 && (trimmed = ft_strtrim(*++argv, " ")))
	{
		if (ft_check_ext(trimmed, ".cub") == ERROR)
		{
			free(trimmed);
			return (ft_print_err("Your config file is not a .cub extension."));
		}
		ret = ft_configure(game, trimmed) == ERROR
			|| ft_generate_cos_sin_table(game) == ERROR;
		free(trimmed);
		if (ret)
			return (ERROR);
		if ((ret = -1) && game->p.pos.x == 0)
			return (ft_print_err("Player position is missing in the map."));
		while (++ret < game->map.width)
			if (game->map.grid[game->map.height][ret] != 1)
				return (ft_print_err("There is an hole in your map"));
	}
	else
		return (ft_print_err("No config file provided."));
	return (SUCCESS);
}
