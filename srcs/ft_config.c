/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:10:39 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/12 17:07:40 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_get_next_number(char **str, char ignorable)
{
	int nb;
	int i;

	i = 0;
	while ((*str)[i] == ignorable)
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

	r = ft_get_next_number(&str, ',');
	g = ft_get_next_number(&str, ',');
	b = ft_get_next_number(&str, ',');
	if (!(r >= 0 && r <= 255
		&& g >= 0 && g <= 255
		&& b >= 0 && b <= 255)
		|| *str)
		return (ft_print_err("Setting color failed."));
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
	return (SUCCESS);
}

int
	ft_set_player_position(t_game *game, char dir, int x, int y)
{
	if (game->player.pos.y > -1. || game->player.pos.y > -1)
		return (ft_print_err("Player position has been set more than once."));
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
	if (!*str)
		return (ft_print_err("Map cannot have blank lines."));
	while (*str)
		if (*str == ' ')
			str++;
		else if (ft_strchr("NSWE", *str))
			ft_set_player_position(game, *str++, line, ++i);
		else
		{
			x = (*str - '0');
			if (x < 0 || x > 2)
				return (ft_print_err("A character in map is unknown."));
			game->map.grid[line][++i] = x;
			str++;
		}
	if (line == 0)
		game->map.width = i;
	else if (game->map.width != i)
		return (ft_print_err("Map don't have same width on each line."));
	game->map.height = line;
	line++;
	return (2);
}

int
	ft_set_image(t_game *game, t_image *img, char *path)
{
	int i;
	int j;
	char tmp;

	if (!(img->ref = mlx_xpm_file_to_image(game->mlx, path, &(img->width), &(img->height))))
		return (ft_print_defined_err());
	if (!(img->data = mlx_get_data_addr(img->ref, &(img->bits), &(img->s_line), &(img->endian))))
		return (ft_print_defined_err());
	return (SUCCESS);
}

int
	ft_set_sprite(t_game *game, t_sprite *spr, char *path)
{
	if (ft_isdigit(*path))
	{
		spr->frame_size.x = ft_get_next_number(&path, ' ');
		spr->frame_size.y = ft_get_next_number(&path, ' ');
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
	ft_check_opts(char *opts, char key)
{
	if (opts[key] == 1)
		return (ft_print_err("A key has been set twice."));
	opts[key] = 1;
	return (SUCCESS);
}

int
	ft_readline(t_game *game, char *line, char **opts)
{
	int ret;

	ret = 0;
	if (!ft_strncmp("R ", line, 2) && ft_check_opts(opts, 0) != ERROR)
			ret = ft_set_window_size(game, &line[2]);
	else if (!ft_strncmp("NO ", line, 3) && ft_check_opts(opts, 1) != ERROR)
		ret = ft_set_image(game, &(game->env.NO), &line[3]);
	else if (!ft_strncmp("SO ", line, 3) && ft_check_opts(opts, 2) != ERROR)
		ret = ft_set_image(game, &(game->env.SO), &line[3]);
	else if (!ft_strncmp("WE ", line, 3) && ft_check_opts(opts, 3) != ERROR)
		ret = ft_set_image(game, &(game->env.WE), &line[3]);
	else if (!ft_strncmp("EA ", line, 3) && ft_check_opts(opts, 4) != ERROR)
		ret = ft_set_image(game, &(game->env.EA), &line[3]);
	else if (!ft_strncmp("S ", line, 2) && ft_check_opts(opts, 5) != ERROR)
		ret = ft_set_sprite(game, &(game->env.S), &line[2]);
	else if (!ft_strncmp("F ", line, 2) && ft_check_opts(opts, 6) != ERROR)
		ret = ft_set_color("F", &game->env.FLOOR, &line[2]);
	else if (!ft_strncmp("C ", line, 2) && ft_check_opts(opts, 7) != ERROR)
		ret = ft_set_color("C", &game->env.CEIL, &line[2]);
	else if (*line == '1' || ft_isdigit(*line))
		ft_fill_map(game, line) && (ret = 2);
	else
		ret = !*line ? SUCCESS : 0;
	return (ret);
}

int
	ft_verify_opts(char *opts)
{
	if (opts[0] != 1)
		return (ft_print_err("Key 'R' for resolution is missing in config file."));
	if (opts[1] != 1)
		return (ft_print_err("Key 'NO' for north wall texture path is missing in config file."));
	if (opts[2] != 1)
		return (ft_print_err("Key 'SO' for south wall texture path is missing in config file."));
	if (opts[3] != 1)
		return (ft_print_err("Key 'WE' for west wall texture path is missing in config file."));
	if (opts[4] != 1)
		return (ft_print_err("Key 'EA' for east wall texture path is missing in config file."));
	if (opts[5] != 1)
		return (ft_print_err("Key 'S' for sprite texture path is missing in config file."));
	if (opts[6] != 1)
		return (ft_print_err("Key 'F' for floor color is missing in config file."));
	if (opts[6] != 1)
		return (ft_print_err("Key 'C' for ceil color is missing in config file."));
	return (SUCCESS);
}

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
		return (ft_print_err("Cannot open file."));
	while (ret == SUCCESS && (gnl_ret = get_next_line(fd, &line)) == SUCCESS)
	{
		ret = ft_readline(game, line, opts);
		free(line);
	}
	if (gnl_ret > 0 && ret == 2 && (ret = SUCCESS))
	{
		while (ret == SUCCESS && (gnl_ret = get_next_line(fd, &line)) == SUCCESS)
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
	else
		return (ft_print_err("No map. Defined a map at the end of .cub file."));
	if (gnl_ret == -1)
		return (ft_print_defined_err());
	if (ret == SUCCESS)
		ret = ft_set_sprite(game, &(game->weapon), "215 127 ./pics/weapon.xpm");
	return (ret == SUCCESS ? SUCCESS : ERROR);
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
	game->player.pos.y = -1.;
	game->player.pos.x = -1.;
	ft_memset(game->event, 0, EXIT + 1);
}

int
	ft_generate_cos_sin_table(t_game *game)
{
	int i;
	double dtheta;
	double theta0;

	if (!(game->win.sin = malloc(sizeof(double) * game->win.width))
		|| !(game->win.cos = malloc(sizeof(double) * game->win.width)))
		return (ft_print_defined_err());
	i = -1;
    dtheta = -M_PI / 3 / (game->win.width - 1);
    theta0 = M_PI / 6;
    while (++i < game->win.width)
    {
        game->win.sin[i] = sin(theta0);
        game->win.cos[i] = cos(theta0);
        theta0 += dtheta;
    }
	return (SUCCESS);
}

int
	ft_generate_floor_dist(t_game *game)
{
	int i;

	if (!(game->win.floor_dist = malloc(sizeof(double) * game->win.height))
		|| !(game->win.sky_dist = malloc(sizeof(double) * game->win.height)))
		return (ft_print_defined_err());

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

	init_config(game);
	if (ac > 1)
	{
		ret = ft_configure(game, *++argv);
		printf("End? %d\n", ret);
		if (ret == SUCCESS)		
			ret = ft_generate_cos_sin_table(game);
	}
	else
		return (ft_print_err("No config map provided."));
	printf("End? %d\n", ret);
	return (ret);
}
