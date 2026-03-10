/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:36:17 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static int	cell_blocks_ray(t_game *game, t_ray *r)
{
	char	c;

	if (r->map_x >= ft_strlen(game->map[r->map_y]))
		return (1);
	c = game->map[r->map_y][r->map_x];
	if (c == '1' || c == '2' || c == '3' || c == ' ')
		return (1);
	if (c == 'D' && !door_is_open(game, r->map_y, r->map_x))
		return (1);
	if (c == 'P' && !cell_is_pushed(game, r->map_y, r->map_x))
		return (1);
	return (0);
}

static void	advance_dda_step(t_ray *r)
{
	if (r->side_dist_x < r->side_dist_y)
	{
		r->side_dist_x += r->delta_dist_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_dist_y += r->delta_dist_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
}

static int	check_dda_stop(t_game *game, t_ray *r)
{
	if (r->map_x < 0 || r->map_x >= game->map_width
		|| r->map_y < 0 || r->map_y >= game->map_height)
		return (1);
	if (r->map_x >= ft_strlen(game->map[r->map_y]))
	{
		r->hit = 1;
		return (1);
	}
	if (cell_blocks_ray(game, r))
	{
		r->hit = 1;
		r->hit_door = (game->map[r->map_y][r->map_x] == 'D');
		return (1);
	}
	return (0);
}

void	dda_step(t_game *game, t_ray *r)
{
	while (!r->hit)
	{
		advance_dda_step(r);
		if (check_dda_stop(game, r))
			break ;
	}
}
