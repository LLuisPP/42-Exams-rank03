/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:07:40 by lprieto-          #+#    #+#             */
/*   Updated: 2024/07/29 11:07:44 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)str);
		i++;
	}
	return (NULL);
}	

char	*ft_strcpy(char *s1, char const *s2)
{
	int	i;

	i =0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strdup(char const *s)
{
	size_t	len;
	char	*cpy;

	len = ft_strlen(s) + 1;
	cpy = malloc(len);
	if (!cpy)
		return (NULL);
	ft_strcpy(cpy, s);
	return (cpy);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*join;
	
	if(!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = malloc (len1 + len2 + 1);
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy((join + len1), s2);
	free(s1);
	return (join);	
}

char *get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int		tocpy;
	int		count;

	line = ft_strdup(buf);
	while(!(newline = ft_strchr(line, '\n'))&&(count =read(fd, buf, BUFFER_SIZE)))
	{
		buf[count] = '\0';
		line = ft_strjoin(line, buf);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);

	if (newline != NULL)
	{
		tocpy = newline - line + 1;
		ft_strcpy(buf, newline + 1);
	}
	else
	{
		tocpy = ft_strlen(line);
		buf[0] = '\0';
	}
	line[tocpy] = '\0';
	return (line);
}

