/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:25:43 by hyungseok         #+#    #+#             */
/*   Updated: 2023/02/24 12:02:16 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define OPEN_ERROR -1
# define READ_ELEMENTS 1
# define READ_MAP 1
# define FILLED 1
# define UNFILLED 0
# define NO_MORE_TO_READ NULL

typedef struct s_map
{
	char			*line;
	struct s_map	*prev;
	struct s_map	*next;
}	t_map;

typedef struct s_info
{
	int				fd;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	int				f_rgb[3];
	int				c_rgb[3];
	struct s_map	*map;
}	t_info;

//cub3d
int		check_arg(char *filename);
void	err_msg(char *s);
void	check_comma(char *str);
void	check_file_order(char *line);
int		get_last(t_map *map);
void	check_wall(t_map *map);
void	info_init(t_info *info, char *filename);
int		elements_filled(int elements_cnt[]);
void	elements_init(t_info *info);
void	map_init(t_info *info);

//libft
int		ft_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	*ft_linedup(char *s1);
char	**ft_split(char const *s, char c);

//get_next_line
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*get_next_line(int fd);

#endif