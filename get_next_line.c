#include "get_next_line.h"

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);

char	*read_one_line(int fd)
{
	char	str_read[BUFFER_SIZE + 1];
	char	*str;
	int 	count = 1;
	int		i;

	i = -1;
	while (++i <= BUFFER_SIZE)
		str_read[i] = '\0';

	while ((count > 0) && (!ft_strchr(str_read, '\n')))
	{
		count = read(fd, str_read, BUFFER_SIZE);
		if (str)
		{
			if (count > 0)
				str = ft_strjoin(str, str_read);
		}
		else 
			str = ft_strdup(str_read);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char		*str = NULL;
	const char	*full_str = NULL;
	static char	*tail_str;
	int			finded_index;
	int			full_str_len;
	char 		*str_read;

	if (tail_str)
	{
		str_read = read_one_line(fd);
		if (str_read)
			full_str = ft_strjoin(tail_str, str_read);
		else 
			full_str = ft_strdup(tail_str);
		finded_index = ft_strchr(full_str, '\n') - &full_str[0] + 1;
		full_str_len = ft_strlen(full_str);
		str = ft_substr(full_str, 0, finded_index);
		tail_str = ft_substr(full_str, finded_index, full_str_len - finded_index);
		free(str_read);
	}
	else 
	{
		full_str = (const char *)read_one_line(fd);
		int full_str_len = ft_strlen(full_str);
		finded_index = ft_strchr(full_str, '\n') - &full_str[0] + 1;
		full_str_len = ft_strlen(full_str);
		str = ft_substr(full_str, 0, finded_index);
		tail_str = ft_substr(full_str, finded_index, full_str_len - finded_index);
	}
	free((char *)full_str);
	return (str);
}

int main()
{
	int fd = open("test", O_RDONLY);
	char *a = get_next_line(fd);
	char *b = get_next_line(fd);
	// char *c = get_next_line(fd);
	// char *a1 = get_next_line(fd);
	// char *b1 = get_next_line(fd);
	// char *c1 = get_next_line(fd);
	// char *d = get_next_line(fd);
	// char *e = get_next_line(fd);
	puts(a);
	puts(b);
	// puts(c);
	// puts(a1);
	// puts(b1);
	// puts(c1);
	// puts(d);
	// puts(e);
	// free(a);
	// free(b);
	// system("leaks a.out");
}