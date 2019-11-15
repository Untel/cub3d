/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:12:36 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/15 04:22:45 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H
# define MAX_WIDTH 1920
# define MAX_HEIGHT 1920
typedef struct	map_s
{
	int	width;
	int	height;
	int	grid[MAX_WIDTH][MAX_HEIGHT];
}				map_t;
typedef struct	player_s
{
	int	x;
	int	y;
}				player_t;
typedef struct	game_s
{
    void		*mlx_ptr;
    void		*mlx_win;
	map_t		map;
	player_t	player;
}				game_t;
game_t			game;

#endif