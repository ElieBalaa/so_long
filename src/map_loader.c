#include "../includes/so_long.h"

static char	**read_lines(int fd, char **map)
{
	char	*line;
	int		i;
	int		len;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		map[i++] = line;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	if (i == 0)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

char	**read_map(char *filename)
{
	int		fd;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * MAX_MAP_HEIGHT);
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	map = read_lines(fd, map);
	close(fd);
	return (map);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
