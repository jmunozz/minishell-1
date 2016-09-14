/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 12:20:30 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/13 16:27:26 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_sappend(t_stream *stream)
{
	size_t				len;
	char				*kill;

	len = ft_strlen(stream->buf);
	if ((kill = stream->search))
	{
		stream->search = ft_strjoin(stream->search, stream->buf);
		ft_sprompt(stream);
		free(kill);
	}
}

void	ft_sdel(t_stream *stream)
{
	if (stream->search[0])
	{
		stream->search[ft_strlen(stream->search) - 1] = '\0';
		ft_sprompt(stream);
	}
}
