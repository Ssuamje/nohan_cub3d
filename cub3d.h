/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:25:43 by hyungseok         #+#    #+#             */
/*   Updated: 2023/06/23 15:15:44 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# define OPEN_ERROR -1
# define READ_ELEMENTS 1
# define READ_MAP 1
# define FILLED 1
# define UNFILLED 0
# define NO_MORE_TO_READ NULL

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define WINDOW_EXIT 17

enum	e_errno{
	ERR_ELEM_INVALID,
	ERR_ELEM_LACK,
	ERR_MAP_FILE,
	ERR_MAP_INVALID,
	ERR_MAP_INVALID_PLAYER,
	ERR_ARG,
	ERR_WALL_INVALID,
};

/**
 * MAC_OS 키맵에 따른 값
*/
enum	e_key{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_ESC = 53,
};

typedef struct s_map
{
	char			*line;
	struct s_map	*prev;
	struct s_map	*next;
}	t_map;

enum e_textures
{
	NORTH = 0,
	SOUTH,
	EAST,
	WEST,
};

typedef struct s_info
{
	int				fd; // 얘도 없어도 됨
	char			*textures[4];
	char			*north_path; // path to textures
	char			*south_path;
	char			*west_path;
	char			*east_path;
	int				f_rgb[3]; // color 하나로 표현하기
	int				c_rgb[3];
	struct s_map	*map; // 없애기
	int				map_width;
	int				map_height;
	int				**world_map;
}	t_info;

typedef struct s_game
{
	int				**map;
	int				map_row;
	int				map_col;
	char			texture[]
	
} t_game;

typedef struct s_vector
{
    double x;
    double y;
} t_vec;

typedef struct s_int_vector 
{
	int x;
	int y;
} t_int_vec;
/**
 * curr_time : 현재 프레임의 시각
 * old_time : 이전 프레임의 시각
*/
typedef struct s_fps
{
	double curr_time;
	double old_time;
}	t_fps;

/* ./cub3d_utils.c */

int		is_extension_valid(char *filename);
int		elements_filled(int elements_cnt[]);
void	check_comma(char *str);
void	check_file_order(char *line);
int		get_last(t_map *map);

char	*ft_linedup(char *s1);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
int		ft_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);

/* ./parsing/elements_init.c */

void	elements_cnt_init(int elements_cnt[]);
void	check_path(t_info *info, char *line, int elements_cnt[]);
void	check_f_rgb(t_info *info, char *line, int elements_cnt[]);
void	check_c_rgb(t_info *info, char *line, int elements_cnt[]);
void	elements_init(t_info *info);

/* ./parsing/check_wall.c */

void	check_side(t_map *map, int i, int j, int last);
void	check_closed(t_map *map, int i, int j, int last);
void	recursion(char **board, int x, int y, int last);
void	check_island(t_map *map, int i, int j, int last);
void	check_wall(t_map *map);

/* ./parsing/info_init.c */

void	check_char(t_map *map);
void	info_init(t_info *info, char *filename);

/* ./parsing/map_init.c */

int		check_validity(char *line);
void	check_empty_line(t_map *map);
void	map_start(t_info *info);
void	map_init(t_info *info);

void	copy_map(t_info	*info);

/* ./get_next_line/get_next_line_utils.c */

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);

/* ./get_next_line/get_next_line.c */

char	*get_next_line(int fd);

/* ./error/exit_error.c */

char	*get_msg_by_errno(int errno);
void	exit_error(int errno);


#endif