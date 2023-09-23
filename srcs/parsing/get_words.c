#include "minirt.h"

static ssize_t	count_file_size(char *filename)
{
	int		fd;
	char	buf[BUFFER_SIZE_RT];
	ssize_t	read_bytes;
	ssize_t	total;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (complain_int(OPEN_ERROR));
	total = 0;
	while (true)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE_RT);
		if (read_bytes == -1)
		{
			close(fd);
			return (complain_int(READ_ERROR));
		}
		total += read_bytes;
		if (read_bytes < BUFFER_SIZE_RT)
		{
			close(fd);
			return (total);
		}
	}
}

static char	*get_file_content(char *filename)
{
	int		fd;
	char	*res;
	ssize_t	bytes;
	ssize_t	total;

	total = count_file_size(filename);
	if (total == -1)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (complain_ptr(OPEN_ERROR));
	res = malloc((total + 1) * sizeof(char));
	if (res == NULL)
		return (close(fd), complain_ptr(MALLOC_ERROR));
	res[total] = '\0';
	bytes = read(fd, res, total);
	close(fd);
	if (bytes < total)
		return (free(res), complain_ptr(READ_ERROR));
	return (res);
}

static char	**get_lines(char *filename)
{
	char	*file_content;
	char	**lines;

	file_content = get_file_content(filename);
	if (file_content == NULL)
		return (NULL);
	lines = ft_split(file_content, '\n');
	free(file_content);
	if (lines == NULL)
		ft_putstr_fd(MALLOC_ERROR, STDERR_FILENO);
	return (lines);
}

char	***get_words(char *filename)
{
	char	**lines;
	char	***words;
	int		num_lines;
	int		i;

	lines = get_lines(filename);
	if (lines == NULL)
		return (NULL);
	num_lines = arrlen(lines);
	words = ft_calloc(num_lines + 1, sizeof(char **));
	i = 0;
	while (i < num_lines)
	{
		words[i] = ft_split_set(lines[i], SPACES);
		if (words[i] == NULL)
		{
			ft_free_double((void ***)&lines);
			ft_free_triple((void ****)&words);
			return (complain_ptr(MALLOC_ERROR));
		}
		++i;
	}
	ft_free_double((void ***)&lines);
	return (words);
}
