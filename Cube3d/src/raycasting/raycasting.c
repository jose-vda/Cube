/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:36:17 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	init_ray(int x, t_game *game, t_ray *r)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	r->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	r->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	r->map_x = (int)game->player.x;
	r->map_y = (int)game->player.y;
	r->delta_dist_x = (r->ray_dir_x == 0) ? DBL_MAX_DIST : fabs(1 / r->ray_dir_x);
	r->delta_dist_y = (r->ray_dir_y == 0) ? DBL_MAX_DIST : fabs(1 / r->ray_dir_y);
	r->step_x = (r->ray_dir_x < 0) ? -1 : 1;
	r->side_dist_x = (r->ray_dir_x < 0) ? (game->player.x - r->map_x)
		* r->delta_dist_x : (r->map_x + 1.0 - game->player.x) * r->delta_dist_x;
	r->step_y = (r->ray_dir_y < 0) ? -1 : 1;
	r->side_dist_y = (r->ray_dir_y < 0) ? (game->player.y - r->map_y)
		* r->delta_dist_y : (r->map_y + 1.0 - game->player.y) * r->delta_dist_y;
	r->hit = 0;
	r->hit_door = 0;
}

static int	get_ceiling_color(t_game *game)
{
	if (game->theme_sunny)
		return ((CEILING_SUNNY_R << 16) | (CEILING_SUNNY_G << 8)
			| CEILING_SUNNY_B);
	return (((int)(((game->ceiling_color >> 16) & 0xFF) * 0.7 + FOG_R * 0.3)
			<< 16)
		| ((int)(((game->ceiling_color >> 8) & 0xFF) * 0.7 + FOG_G * 0.3) << 8)
		| (int)((game->ceiling_color & 0xFF) * 0.7 + FOG_B * 0.3));
}

static void	cast_one_column(t_game *game, int x, t_ray *r, int ceiling_dark)
{
	init_ray(x, game, r);
	dda_step(game, r);
	compute_wall(game, r);
	if (game->has_ceiling_tex)
		draw_textured_ceiling(game, x, r->draw_start, r->ray_dir_x,
			r->ray_dir_y);
	else
		draw_vertical_line(&game->img, x, 0, r->draw_start, ceiling_dark);
	draw_textured_wall(game, x, r->draw_start, r->draw_end, r->line_height,
		r->tex_id, r->tex_x, r->hit_door, r->perp_dist);
	draw_textured_floor(game, x, r->draw_end, r->ray_dir_x, r->ray_dir_y);
}

void	raycasting(t_game *game)
{
	int		x;
	t_ray	r;
	int		ceiling_dark;

	ceiling_dark = get_ceiling_color(game);
	x = 0;
	while (x < WIDTH)
	{
		cast_one_column(game, x, &r, ceiling_dark);
		x++;
	}
}
