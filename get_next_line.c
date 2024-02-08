#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 20

size_t	ft_strlen(const char *s)
{
	size_t length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}
char	*ft_strcpy(char *dst, const char *src)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = dst;
	while (src[i])
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strcat(char *s1, const char *s2)
{
	int a;
	int b;
	char *tmp;

	a = ft_strlen(s1);
	b = 0;
	tmp = s1;
	s1 = (char*)malloc((ft_strlen(s1) + ft_strlen((char*)s2)) + 1);
	ft_strcpy(s1, tmp);
	while (s2[b])
		s1[a++] = s2[b++];
	s1[a] = '\0';
	return (s1);
}


int chack_if_new_line(char *str)
{
	while (*str != '\0')
	{
		if (*str == '\n')
			return 1;
		str++;
	}
	return (0);
}

char *get_next_line(int fd)
{
	char	*str_read;
	char	*str;
	char	*str_temp;
	int		buffer_counter;

	buffer_counter = 1;
	str_read = malloc(sizeof(char) * (BUFFER_SIZE * buffer_counter));
	read(fd, str_read, BUFFER_SIZE);
	while (!chack_if_new_line(str_read))
	{
		if (str)
		{
			str_temp = malloc(sizeof(char) * (BUFFER_SIZE * buffer_counter));
			ft_strcpy(str_temp, str);
			free(str);
		}
		buffer_counter++;
		str = malloc(sizeof(char) * (BUFFER_SIZE * buffer_counter));
		if (str_temp)
			ft_strcpy(str, str_temp);
		else
			ft_strcpy(str, str_read);
		read(fd, str_read, BUFFER_SIZE);
		str = ft_strcat(str, str_read);
	}
	return (str);
}

int main()
{
	int fd = open("test", O_RDONLY);
	puts(get_next_line(fd));
}