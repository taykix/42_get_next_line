/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:46:44 by tayki             #+#    #+#             */
/*   Updated: 2024/10/22 17:42:24 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct list
{
	char		*str;
	struct list	*next;
}				t_list;

char			*get_next_line(int fd);
void			write_to_buffer(t_list **list, int fd);
void			append(t_list **list, t_list *new_node);
int				has_endline(t_list **list);
char			*get_line(t_list *list);
int				count_line(t_list *list);
void			clean_line(t_list **head);
t_list			*create_node(char *content);
void			clean_list(t_list **list);
char			*ft_strdup(const char *s);

#endif
