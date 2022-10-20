/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:46:10 by avancoll          #+#    #+#             */
/*   Updated: 2022/10/20 15:52:54 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *save)
{
	int		i;
	char	*res;

	if (!save)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	res = malloc(sizeof(char) * (i + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		res[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		res[i] = save[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_after_line(char *save)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return (ft_free(save, NULL));
	res = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!res)
		return (ft_free(save, NULL));
	i++;
	j = 0;
	while (save[i])
		res[j++] = save[i++];
	res[j] = 0;
	free(save);
	return (res);
}

char	*ft_read(int fd, char *save)
{
	char	*buff;
	int		check;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	check = 1;
	while (!ft_strchr(save, '\n') && check)
	{
		check = read(fd, buff, BUFFER_SIZE);
		if (check == -1)
			return (ft_free(buff, save));
		buff[check] = 0;
		save = ft_strjoin_free(save, buff);
		if (!save)
			return (ft_free(buff, NULL));
	}
	free(buff);
	if (save[0] == 0 && check == 0)
		return (ft_free(save, NULL));
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	save[fd] = ft_read(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = ft_get_line(save[fd]);
	if (!line)
		return (ft_free(save[fd], NULL));
	save[fd] = ft_after_line(save[fd]);
	return (line);
}
