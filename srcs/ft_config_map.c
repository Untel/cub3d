/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 21:10:15 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/19 15:22:19 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_set_line_config(char *str, t_game *game, int line, int i)
{
	int	x;

	while (*str)
		if (*str == ' ')
			str++;
		else if ((i == 0 || line == 0 ||
			(line > 0 && (i + 1) == game->map.width))
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
	return (i);
}

int
	ft_fill_map(t_game *game, char *str)
{
	static int	line = 0;
	char		*ptr;
	int			i;

	if (!*str)
		return (ft_print_err("Map cannot have blank lines."));
	i = ft_set_line_config(str, game, line, 0);
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
	if (!(img->ref = mlx_xpm_file_to_image(game->mlx,
		trimmed, &(img->width), &(img->height)))
		|| !(img->data = mlx_get_data_addr(img->ref, &(img->bits),
		&(img->s_line), &(img->endian))))
	{
		ft_sprintf(tmp, "Cannot open file '%s'", trimmed);
		free(trimmed);
		return (ft_print_defined_err(tmp));
	}
	free(trimmed);
	return (SUCCESS);
}

int
	ft_set_player_position(t_game *game, char dir, int x, int y)
{
	if (game->p.pos.y > 0 || game->p.pos.y > 0)
		return (ft_print_err("Player position has been set more than once."));
	game->p.pos.y = (double)x + .5;
	game->p.pos.x = (double)y + .5;
	game->map.grid[y][x] = 0;
	if (dir == 'S')
		game->p.angle = M_PI_2;
	else if (dir == 'N')
		game->p.angle = M_PI + M_PI_2;
	else if (dir == 'W')
		game->p.angle = M_PI;
	else
		game->p.angle = 0;
	update_orientation(game->p.angle, &(game->p.dir));
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
