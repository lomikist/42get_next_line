/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 19:02:36 by arsargsy          #+#    #+#             */
/*   Updated: 2024/02/24 19:02:39 by arsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_one_line(char *str, int fd)
{
	char	str_read[BUFFER_SIZE + 1];
	int		count;

	count = -1;
	while (++count <= BUFFER_SIZE)
		str_read[count] = '\0';
	count = 1;
	while (!ft_strchr(str_read, '\n') && count)
	{
		count = read(fd, str_read, BUFFER_SIZE);
		if (count < 0 || (!count && !str))
			return (NULL);
		str_read[count] = '\0';
		if (str)
			str = ft_strjoin(str, str_read);
		else
			str = ft_strdup(str_read);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*tail_str;
	int			i;
	char		*str;
	char		*temp;	

	i = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	tail_str = read_one_line(tail_str, fd);
	if (!tail_str)
		return (NULL);
	while (tail_str[i] != '\n' && tail_str[i + 1])
		i++;
	str = ft_substr(tail_str, 0, i + 1);
	temp = tail_str;
	tail_str = ft_substr(tail_str, i + 1, ft_strlen(tail_str) - i - 1);
	free(temp);
	return (str);
}
