#include "../includes/so_long.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P' ||
			c == 'T' || c == 'M');
}

int	check_borders(char **map, int rows, int cols)
{
	int	i;

	i = 0;
	while (i < cols)
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	count_chars(char **map, int *p, int *e, int *c)
{
	int	row;
	int	col;

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (!is_valid_char(map[row][col]))
				return (0);
			if (map[row][col] == 'P')
				(*p)++;
			if (map[row][col] == 'E')
				(*e)++;
			if (map[row][col] == 'C')
				(*c)++;
			col++;
		}
		row++;
	}
	return (1);
}

int	check_map_dimensions(char **map)
{
	int	row;
	int	len;

	if (!map || !map[0])
		return (0);
	row = 0;
	len = ft_strlen(map[0]);
	while (map[row])
	{
		if ((int)ft_strlen(map[row]) != len)
			return (0);
		row++;
	}
	return (row);
}

int	validate_map(char **map)
{
	int	row;
	int	p;
	int	e;
	int	c;

	p = 0;
	e = 0;
	c = 0;
	row = check_map_dimensions(map);
	if (!row)
		return (0);
	if (!check_borders(map, row, ft_strlen(map[0])))
		return (0);
	if (!count_chars(map, &p, &e, &c))
		return (0);
	if (!is_path_valid(map))
		return (0);
	return (p == 1 && e == 1 && c >= 1);
} 
