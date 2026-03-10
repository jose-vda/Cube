/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	init_parse_state(t_game *game, int *got)
{
	game->tex_path[0] = NULL;
	game->tex_path[1] = NULL;
	game->tex_path[2] = NULL;
	game->tex_path[3] = NULL;
	game->tex_path[4] = NULL;
	game->tex_path[5] = NULL;
	game->ceiling_tex_path = NULL;
	game->floor_color = -1;
	game->ceiling_color = -1;
	got[0] = 0;
	got[1] = 0;
	got[2] = 0;
	got[3] = 0;
	got[4] = 0;
	got[5] = 0;
}

static int	handle_id_phase(t_game *game, char *line, int *got,
		char **map_lines, int *map_count)
{
	int	i;

	i = parse_identifier(game, line, got);
	if (i == 0)
	{
		free(line);
		free_tex_paths(game);
		printf("Error\nInvalid or duplicate identifier\n");
		return (0);
	}
	if (i == 2 && is_map_line(line) && got[0] && got[1] && got[2]
		&& got[3] && got[4] && got[5])
	{
		map_lines[(*map_count)++] = line;
		return (2);
	}
	free(line);
	return (1);
}

static int	handle_map_phase(t_game *game, char *line,
		char **map_lines, int *map_count)
{
	if (!line[0])
	{
		free(line);
		return (1);
	}
	if (!is_map_line(line))
	{
		free(line);
		free_tex_paths(game);
		printf("Error\nInvalid character in map\n");
		return (0);
	}
	map_lines[(*map_count)++] = line;
	return (1);
}

static int	read_one_line_id(int *phase, t_game *game, char *line, int *got,
		char **map_lines, int *map_count)
{
	int	ret;

	ret = handle_id_phase(game, line, got, map_lines, map_count);
	if (ret == 0)
		return (0);
	if (ret == 2)
		*phase = 1;
	return (1);
}

static int	read_one_line_map(t_game *game, char *line,
		char **map_lines, int *map_count)
{
	int	ret;

	ret = handle_map_phase(game, line, map_lines, map_count);
	if (ret == 0)
		return (0);
	return (1);
}

static int	process_read_line(int *phase, t_game *game, char *line,
		int *got, char **map_lines, int *map_count)
{
	int	ret;

	trim_newline(line);
	if (*phase == 0)
	{
		ret = read_one_line_id(phase, game, line, got, map_lines, map_count);
		if (ret == 0)
			return (0);
	}
	else
	{
		ret = read_one_line_map(game, line, map_lines, map_count);
		if (ret == 0)
			return (0);
	}
	if (*map_count >= 4096)
		return (2);
	return (1);
}

int	read_file_loop(int fd, t_game *game, int *got,
		char **map_lines, int *map_count)
{
	char	*line;
	int		phase;
	int		status;

	phase = 0;
	*map_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		status = process_read_line(&phase, game, line, got,
				map_lines, map_count);
		if (status == 0)
			return (0);
		if (status == 2)
			break ;
	}
	return (1);
}

static void	compute_map_width(t_game *game, char **map_lines, int map_count)
{
	int	i;

	game->map_width = 0;
	i = 0;
	while (i < map_count)
	{
		if (ft_strlen(map_lines[i]) > game->map_width)
			game->map_width = ft_strlen(map_lines[i]);
		i++;
	}
}

static int	alloc_and_fill_map(t_game *game, char **map_lines, int map_count)
{
	int	i;

	game->map = malloc(sizeof(char *) * (map_count + 1));
	if (!game->map)
	{
		free_tex_paths(game);
		free_map_lines_arr(map_lines, map_count);
		return (0);
	}
	i = 0;
	while (i < map_count)
	{
		game->map[i] = map_lines[i];
		i++;
	}
	game->map[map_count] = NULL;
	free(map_lines);
	return (1);
}

int	build_game_map(t_game *game, char **map_lines, int map_count)
{
	game->map_height = map_count;
	compute_map_width(game, map_lines, map_count);
	if (!alloc_and_fill_map(game, map_lines, map_count))
		return (0);
	if (!find_and_set_spawn(game) || !validate_map_closed(game))
	{
		free_map_only(game->map, game->map_height);
		game->map = NULL;
		free_tex_paths(game);
		return (0);
	}
	return (1);
}
