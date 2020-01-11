/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:10:39 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/11 19:04:47 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_next_number(char **str)
{
	int nb;
	int i;

	i = 0;
	while (!ft_isdigit((*str)[i]))
		i++;
	if (!*str)
		return (ERROR);
	nb = ft_atoi(*str + i);
	while (ft_isdigit((*str)[i]))
		i++;
	*str += i;
	return (nb);
}

int
	ft_set_color(char *key, int *color, char *str)
{
	int r;
	int g;
	int b;

	
	r = ft_get_next_number(&str);
	g = ft_get_next_number(&str);
	b = ft_get_next_number(&str);
	if (!(r >= 0 && r <= 255
		&& g >= 0 && g <= 255
		&& b >= 0 && b <= 255)
		|| *str)
		return (ft_print_err("Error\nSetting color failed."));
	*color = (b << 16) + (g << 8) + r;
	return (SUCCESS);
}

int
	ft_set_path(char *key, char *buffer, char *str)
{
	if (ft_strlen(str) >= PATH_URL_SIZE)
		return (ERROR);
	ft_strcpy(buffer, str);
	return (SUCCESS);
}

int
	ft_set_window_size(t_game *game, char *str)
{
	game->win.width = ft_get_next_number(&str);
	game->win.height = ft_get_next_number(&str);
	if (game->win.width < 1 || game->win.height < 1)
		return (ft_print_err("Error\nWin size incorrect.\n"));
	return (SUCCESS);
}

int
	ft_set_player_position(t_game *game, char dir, int x, int y)
{
	game->player.pos.y = (double)x + .5;
	game->player.pos.x = (double)y + .5;
	game->map.grid[y][x] = 0;
	if (dir == 'S')
		game->player.angle = M_PI_2;
	else if (dir == 'N')
		game->player.angle = M_PI + M_PI_2;
	else if (dir == 'W')
		game->player.angle = M_PI;
	else
		game->player.angle = 0;
    update_orientation(game->player.angle, &(game->player.dir));
	return (SUCCESS);
}

int
	ft_fill_map(t_game *game, char *str)
{
	static int	line = 0;
	char		*ptr;
	int			i;
	int			x;

	i = -1;
	while (*str)
		if (*str == ' ')
			str++;
		else if (ft_strchr("NSWE", *str))
			ft_set_player_position(game, *str++, line, ++i);
		else
		{
			x = (*str - '0');
			if (x < 0 || x > 8)
				return (ft_print_err("Error\nA character in map is unknown."));
			game->map.grid[line][++i] = x;
			str++;
		}
	if (line == 0)
		game->map.width = i;
	else if (game->map.width != i)
		return (ft_print_err("Error\nMap don't have same width on each line."));
	game->map.height = line;
	line++;
	return (SUCCESS);
}

int
	ft_verify_map(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map.width)
		if (game->map.grid[0][i] != WALL
			&& game->map.grid[game->map.height - 1][i] != WALL)
			return (ERROR);
	i = -1;
	while (++i < game->map.height)
		if (game->map.grid[i][0] != WALL
			&& game->map.grid[i][game->map.width - 1] != WALL)
			return (ERROR);
	return (SUCCESS);
}

int
	ft_set_image(t_game *game, t_image *img, char *path)
{
	int i;
	int j;
	char tmp;

	if (!(img->ref = mlx_xpm_file_to_image(game->mlx, path, &(img->width), &(img->height))))
		return (ft_print_err("Error\nCannot open file."));
	if (!(img->data = mlx_get_data_addr(img->ref, &(img->bits), &(img->s_line), &(img->endian))))
		return (ft_print_err("Error\nCannot get data address file."));
	return (SUCCESS);
}

int
	ft_set_sprite(t_game *game, t_sprite *spr, char *path)
{
	if (ft_isdigit(*path))
	{
		spr->frame_size.x = ft_get_next_number(&path);
		spr->frame_size.y = ft_get_next_number(&path);
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
	ft_readline(t_game *game, char *line)
{
	int ret;

	if (!ft_strncmp("R ", line, 2))
		ret = ft_set_window_size(game, &line[2]);
	else if (!ft_strncmp("NO ", line, 3))
		ret = ft_set_image(game, &(game->env.NO), &line[3]);
	else if (!ft_strncmp("SO ", line, 3))
		ret = ft_set_image(game, &(game->env.SO), &line[3]);
	else if (!ft_strncmp("WE ", line, 3))
		ret = ft_set_image(game, &(game->env.WE), &line[3]);
	else if (!ft_strncmp("EA ", line, 3))
		ret = ft_set_image(game, &(game->env.EA), &line[3]);
	else if (!ft_strncmp("S ", line, 2))
		ret = ft_set_sprite(game, &(game->env.S), &line[2]);
	else if (!ft_strncmp("F ", line, 2))
		ret = ft_set_color("Floor color", &game->env.FLOOR, &line[2]);
	else if (!ft_strncmp("C ", line, 2))
		ret = ft_set_color("Ceil color", &game->env.CEIL, &line[2]);
	else if (*line == '1' || ft_isdigit(*line))
		ret = ft_fill_map(game, line);
	else
		ret = !*line ? SUCCESS : ERROR;
	return (ret);
}

int
	ft_configure(t_game *game, char *filename)
{
	int		fd;
	int		ret;
	char	*line;

	if ((fd = open(filename, O_RDONLY)) == ERROR)
		return (ft_print_err("Error\nCannot open file."));
	ret = SUCCESS;
	while (ret == SUCCESS && (ret = get_next_line(fd, &line)) == SUCCESS)
	{
		ret = ft_readline(game, line);
		free(line);
	}
	if (ret == 0)
	{
		ret = ft_readline(game, line);
		free(line);
	}
	else
		return (ret);
	ret = ft_set_sprite(game, &(game->weapon), "215 127 ./pics/weapon.xpm");
	// ret = ft_set_sprite(game, &(game->weapon), "64 64 ./pics/fire_64.xpm");
	return (ret);
}

int
	init_config(t_game *game)
{
	game->player.ms = 0.12;
	game->player.rs = 0.04;
	game->player.view = 0;
	game->player.view2 = 0;
	game->player.hp = 999;
	game->player.max_hp = 999;
	game->collision = 1;
	game->hud = 0;
	game->shading = 0;
	game->player.jumping = 0;
	ft_memset(game->event, 0, EXIT + 1);
}

int
	ft_generate_cos_sin_table(t_game *game)
{
	int i;
	double dtheta;
	double theta0;

	if (!(game->win.sin = malloc(sizeof(double) * game->win.width))
		|| !(game->win.cos = malloc(sizeof(double) * game->win.width))
	)
		return (ft_print_defined_err("Error\nMalloc cos/sin table failed"));
	i = -1;
    dtheta = -M_PI / 3 / (game->win.width - 1);
    theta0 = M_PI / 6;
    while (++i < game->win.width)
    {
        game->win.sin[i] = sin(theta0);
        game->win.cos[i] = cos(theta0);
        theta0 += dtheta;
    }
}

int
	ft_generate_floor_dist(t_game *game)
{
	int i;

	if (!(game->win.floor_dist = malloc(sizeof(double) * game->win.height))
		|| !(game->win.sky_dist = malloc(sizeof(double) * game->win.height)))
		return (ft_print_defined_err("Error\nMalloc sky/floor dist failed"));

	i = -1;
	while (++i < game->win.height / 2)
	{
		game->win.floor_dist[i] = ((2. * game->win.height));
		game->win.sky_dist[game->win.height - i] = ((2. * game->win.height));
	}
	while (i < game->win.height)
	{
		game->win.floor_dist[i] = (game->win.height / (2. * (double)i - game->win.height));
		game->win.sky_dist[game->win.height - i] = (game->win.height / (2. * (double)i - game->win.height));
		i++;
	}
}

int
	ft_args(t_game *game, int ac, char **argv)
{
	int ret;

	ret = SUCCESS;
	if (ac > 1)
	{
		if (ret == SUCCESS)
			ret = init_config(game);
		if (ret == SUCCESS)		
			ret = ft_configure(game, *++argv);
		if (ret == SUCCESS)		
			ret = ft_generate_cos_sin_table(game);
	}
	else
		ret = ERROR;
	return (ret);
}
