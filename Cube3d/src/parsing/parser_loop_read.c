/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_loop_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

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

int	process_read_line(int *phase, t_game *game, char *line,
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
