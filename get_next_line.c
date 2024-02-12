#include "get_next_line.h"

#define BUFFER_SIZE 6

size_t	ft_strlen(const char *s)
{
	size_t length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

char	*ft_strcpy(char *dest, char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *s1, const char *s2)
{
	int		a;
	int		b;
	char	*tmp;
	char	*s1_for_free;

	s1_for_free = s1;
	a = ft_strlen(s1);
	b = 0;
	tmp = s1;
	s1 = (char*)malloc((ft_strlen(s1) + ft_strlen((char*)s2)) + 1);
	ft_strcpy(s1, tmp);
	while (s2[b])
		s1[a++] = s2[b++];
	s1[a] = '\0';
	free(s1_for_free);
	return (s1);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			*str;

	str = (char *)s;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	if (str[i] == (char)c)
		return (&str[i]);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	str_len;
	char			*substr;

	if (!s)
		return (0);
	str_len = ft_strlen(s);
	if (start >= str_len)
		len = 0;
	if (len > str_len - start)
		len = str_len - start;
	substr = malloc(len + 1);
	if (!substr)
		return (0);
	i = 0;
	while (i < len && s[start])
	{
		substr[i] = s[start];
		start++;
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		++j;
		++i;
	}
	free(s1);
	str[i] = '\0';
	return (str);
}

char	*read_one_line(int fd)
{
	char	*str_read = NULL;
	char	*str = NULL;
	char	*str_temp = NULL;
	int		buffer_counter;

	buffer_counter = 1;
	str_read = malloc(sizeof(char) * (BUFFER_SIZE * buffer_counter));
	read(fd, str_read, BUFFER_SIZE);
	while (!ft_strchr(str_read, '\n'))
	{
		if (str)
		{
			str_temp = malloc(sizeof(char) * (BUFFER_SIZE * buffer_counter));
			ft_strcpy(str_temp, str);
			read(fd, str_read, BUFFER_SIZE);
			str = ft_strjoin(str, str_read);
			free(str_temp);
		}
		else 
		{
			str = malloc(sizeof(char) * (BUFFER_SIZE * buffer_counter));
			ft_strcpy(str, str_read);
		}
		buffer_counter++;
	}
	free(str_read);
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
		full_str = ft_strjoin(tail_str, str_read);
		finded_index = ft_strchr(full_str, '\n') - &full_str[0];
		full_str_len = ft_strlen(full_str);
		str = ft_substr(full_str, 0, finded_index + 1);
		tail_str = ft_substr(full_str, finded_index + 1, full_str_len - finded_index);
		free(str_read);
	}
	else 
	{
		full_str = (const char *)read_one_line(fd);
		finded_index = ft_strchr(full_str, '\n') - &full_str[0];
		full_str_len = ft_strlen(full_str);
		str = ft_substr(full_str, 0, finded_index + 1);
		tail_str = ft_substr(full_str, finded_index + 1, full_str_len - finded_index);
	}
	free((char *)full_str);
	return (str);
}

int main()
{
	int fd = open("test", O_RDONLY);
	char *a = get_next_line(fd);
	char *b = get_next_line(fd);
	puts(a);
	puts(b);
	free(a);
	free(b);
}