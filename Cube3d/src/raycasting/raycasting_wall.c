/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:36:17 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static int	get_wall_texture(int side, double ray_dir_x, double ray_dir_y,
		char cell)
{
	if (cell == '2')
		return (TEX_WALL2);
	if (cell == '3')
		return (TEX_WALL3);
	(void)side;
	(void)ray_dir_x;
	(void)ray_dir_y;
	return (TEX_NORTH);
}

static double	get_perp_distance(t_ray *r)
{
	double	perp;

	perp = (r->side == 0) ? r->side_dist_x - r->delta_dist_x
		: r->side_dist_y - r->delta_dist_y;
	if (perp < 1e-6)
		perp = 1e-6;
	return (perp);
}

static void	compute_draw_bounds(t_ray *r, int line_h)
{
	r->draw_start = -line_h / 2 + HEIGHT / 2;
	r->draw_end = line_h / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
}

static void	compute_texture_coords(t_game *game, t_ray *r, double perp,
		int line_h)
{
	r->wall_x = (r->side == 0) ? game->player.y + perp * r->ray_dir_y
		: game->player.x + perp * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_id = get_wall_texture(r->side, r->ray_dir_x, r->ray_dir_y,
			game->map[r->map_y][r->map_x]);
	r->tex_x = (int)(r->wall_x * game->tex[r->tex_id].width);
	if (r->side == 0 && r->ray_dir_x > 0)
		r->tex_x = game->tex[r->tex_id].width - r->tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		r->tex_x = game->tex[r->tex_id].width - r->tex_x - 1;
	r->line_height = line_h;
	r->perp_dist = perp;
}

void	compute_wall(t_game *game, t_ray *r)
{
	double	perp;
	int		line_h;

	perp = get_perp_distance(r);
	line_h = (int)(HEIGHT / perp);
	compute_draw_bounds(r, line_h);
	compute_texture_coords(game, r, perp, line_h);
}
