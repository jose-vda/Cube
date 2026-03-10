/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:59:14 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/19 17:04:30 by jose-vda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUBE_H
#  define CUBE_H

#  ifdef __APPLE__
#   include "mlx.h"
#  else
#   include "../minilibx/mlx.h"
#  endif
#  include <limits.h>
#  include <stdlib.h>
#  include <math.h>
#  include <unistd.h>
#  include <stdio.h>
#  include <fcntl.h>

#  define WIDTH 640
#  define HEIGHT 480
#  define BUFFER_SIZE 10000
#  define DBL_MAX_DIST 1e30
#  define TEX_NORTH 0
#  define TEX_SOUTH 1
#  define TEX_WEST  2
#  define TEX_EAST  3
#  define TEX_WALL2 4
#  define TEX_WALL3 5
#  define MINIMAP_TILE 6
#  define MINIMAP_OFFSET_X 10
#  define MINIMAP_OFFSET_Y 10
#  define MINIMAP_MAX_W 20
#  define MINIMAP_MAX_H 20
#  define MINIMAP_WALL 0x2a2a2a
#  define MINIMAP_FLOOR 0x404040
#  define MINIMAP_PLAYER 0x00ff00
#  define MINIMAP_DOOR 0x6b4423
#  define MINIMAP_KEY  0xFFD700
#  define MINIMAP_EXIT 0x00FF00
#  define MINIMAP_PUSH 0x8B4513
#  define MOUSE_SENS 0.002
#  define MAX_DOORS 64
#  define FOG_DIST 8.0
#  define FOG_R 24
#  define FOG_G 24
#  define FOG_B 28
#  define FOG_DIST_SUNNY 18.0
#  define FOG_R_SUNNY 200
#  define FOG_G_SUNNY 220
#  define FOG_B_SUNNY 255
#  define CEILING_SUNNY_R 135
#  define CEILING_SUNNY_G 206
#  define CEILING_SUNNY_B 235
#  define MAX_PUSH_WALLS 32
#  define DAMAGE_FLASH_FRAMES 8
#  define PICKUP_FLASH_FRAMES 5
#  define HUD_COLOR 0x00FF00
#  define HUD_BG_COLOR 0x000000

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_texture
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		line_len;
	int		bpp;
	int		endian;
}	t_texture;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		hit;
	int		hit_door;
	int		side;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_id;
	int		tex_x;
	int		line_height;
	double	perp_dist;
}	t_ray;

typedef struct s_door
{
	int	y;
	int	x;
}	t_door;

typedef struct s_push
{
	int	y;
	int	x;
}	t_push;

typedef struct s_game
{
	t_texture	tex[6];
	char		*tex_path[6];
	int			floor_color;
	int			ceiling_color;
	int			map_height;
	int			map_width;
	void		*mlx;
	void		*win;
	t_player	player;
	t_keys		keys;
	char		**map;
	t_img		img;
	char		*map_name;
	int			show_minimap;
	int			mouse_last_x;
	t_door		open_doors[MAX_DOORS];
	int			num_open_doors;
	t_texture	floor_tex;
	int			theme_sunny;
	t_texture	floor_tex_sunny;
	t_texture	ceiling_tex;
	char		*ceiling_tex_path;
	int			has_ceiling_tex;
	int			has_key;
	int			paused;
	t_push		pushed[MAX_PUSH_WALLS];
	int			num_pushed;
	int			exit_reached;
	int			damage_flash;
	int			pickup_flash;
}	t_game;

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	update_player(t_game *game);
void	do_move_forward(t_game *game, t_player *p, double speed);
void	do_move_back(t_game *game, t_player *p, double speed);
void	do_strafe_left(t_game *game, t_player *p, double speed);
void	do_strafe_right(t_game *game, t_player *p, double speed);
void	do_rotation(t_player *p, t_keys *k);

void	init_mlx(t_game *game);
void	init_image(t_game *game);

int		render(t_game *game);
void	clear_image(t_img *img, int color);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_rect(t_img *img, int x0, int y0, int w, int h, int color);
void	draw_minimap_grid(t_game *game, int start_row, int start_col);

int		close_window(t_game *game);
void	free_game(t_game *game);
void	free_map(t_game *game);
void	free_textures(t_game *game);
void	free_mlx(t_game *game);

void	raycasting(t_game *game);
void	draw_vertical_line(t_img *img, int x, int y_start, int y_end, int color);
void	draw_textured_wall(t_game *g, int x, int d_start, int d_end,
			int line_h, int tex_id, int tex_x, int is_door, double perp_dist);
void	draw_textured_floor(t_game *g, int x, int draw_end,
			double ray_dir_x, double ray_dir_y);
void	draw_textured_ceiling(t_game *g, int x, int draw_start,
			double ray_dir_x, double ray_dir_y);
void	draw_hud(t_game *game);
void	draw_pause_overlay(t_game *game);
void	draw_crosshair(t_game *game);
void	apply_screen_effects(t_game *game);
int		cell_is_pushed(t_game *game, int my, int mx);
void	push_wall_at(t_game *game, int my, int mx);
void	check_key_and_exit(t_game *game, double new_x, double new_y);
int		parse_map(t_game *game, char *filename);
int		has_cub_extension(char *filename);
char	*trim_newline(char *line);
char	*skip_spaces(char *s);
int		parse_rgb(char *s, int *out);
int		parse_identifier(t_game *game, char *line, int *got);
int		is_map_line(char *line);
void	init_parse_state(t_game *game, int *got);
int		read_file_loop(int fd, t_game *game, int *got,
			char **map_lines, int *map_count);
int		build_game_map(t_game *game, char **map_lines, int map_count);
int		find_and_set_spawn(t_game *game);
int		validate_map_closed(t_game *game);
void	free_tex_paths(t_game *game);
void	free_map_only(char **map, int height);
void	free_map_lines_arr(char **map_lines, int map_count);
void	draw_minimap(t_game *game);
int		mouse_move(int x, int y, void *param);
int		door_is_open(t_game *game, int my, int mx);
void	toggle_door_at(t_game *game, int my, int mx);

int		ft_strlen(char *str);
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(char *s);
int		ft_atoi(char *s);

char	*get_next_line(int fd);

# endif

