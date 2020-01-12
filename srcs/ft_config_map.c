/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 21:10:15 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/12 21:14:04 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_fill_map(t_game *game, char *str)
{
	static int	line = 0;
	char		*ptr;
	int			i;
	int			x;

	i = 0;
	if (!*str)
		return (ft_print_err("Map cannot have blank lines."));
	while (*str)
		if (*str == ' ')
			str++;
		else if ((i == 0 || line == 0 || (line > 0 && (i + 1) == game->map.width))
			&& *str != '1')
			return (ft_print_err("There is an hole in your map"));
		else if (ft_strchr("NSWE", *str))
		{
			if (ft_set_player_position(game, *str++, line, ++i) == ERROR)
				return (ERROR);
		}
		else
		{
			x = (*str - '0');
			if (x < 0 || x > 2)
				return (ft_print_err("A character in map is unknown."));
			if (i > MAX_MAP_WIDTH - 1)
				return (ft_print_err("Map is too large"));
			game->map.grid[line][i++] = x;
			str++;
		}
	if (line == 0)
		game->map.width = i;
	else if (game->map.width != i)
		return (ft_print_err("Map don't have same width on each line."));
	game->map.height = line;
	if (line > MAX_MAP_HEIGHT - 1)
		return (ft_print_err("Map is too hight"));
	line++;
	return (2);
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
	ft_set_image(t_game *game, t_image *img, char *path)
{
	int		i;
	int		j;
	char	tmp[BUFFER_SIZE];
	char	*trimmed;

	trimmed = ft_strtrim(path, " ");
	if (ft_check_ext(trimmed, ".xpm") == ERROR)
	{
		free(trimmed);
		return (ft_print_err("Only .xpm files are supported."));
	}
	if (!(img->ref = mlx_xpm_file_to_image(game->mlx, trimmed, &(img->width), &(img->height))))
	{
		free(trimmed);
		ft_sprintf(tmp, "Cannot open file '%s'", trimmed);
		return (ft_print_defined_err(tmp));
	}
	if (!(img->data = mlx_get_data_addr(img->ref, &(img->bits), &(img->s_line), &(img->endian))))
	{
		free(trimmed);
		ft_sprintf(tmp, "Cannot open file '%s'", trimmed);
		return (ft_print_defined_err(tmp));
	}
	free(trimmed);
	return (SUCCESS);
}

int
	ft_set_player_position(t_game *game, char dir, int x, int y)
{
	if (game->player.pos.y > 0 || game->player.pos.y > 0)
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