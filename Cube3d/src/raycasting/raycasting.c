/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:36:17 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/19 17:15:26 by jose-vda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static int	get_wall_texture(int side, double ray_dir_x, double ray_dir_y, char cell)
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

static void	dda_step(t_game *game, t_ray *r)
{
	while (!r->hit)
	{
		advance_dda_step(r);
		if (check_dda_stop(game, r))
			break ;
	}
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

static void	compute_wall(t_game *game, t_ray *r)
{
	double	perp;
	int		line_h;

	perp = get_perp_distance(r);
	line_h = (int)(HEIGHT / perp);
	compute_draw_bounds(r, line_h);
	compute_texture_coords(game, r, perp, line_h);
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
