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

# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.005

#ifndef SCREEN_WIDTH
# define SCREEN_WIDTH 640
#endif
#ifndef SCREEN_HEIGHT
# define SCREEN_HEIGHT 480
#endif
#ifndef GAME_NAME
# define GAME_NAME "cub3D"
#endif
#ifndef TEXTURE_WIDTH
# define TEXTURE_WIDTH 64
#endif
#ifndef TEXTURE_HEIGHT
# define TEXTURE_HEIGHT 64
#endif

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
enum	e_key
{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_ESC = 53,
};

enum	e_key_indexes
{
	W = 0,
	A,
	S,
	D,
	LEFT,
	RIGHT,
	ESC,
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

enum e_key_events
{
	PRESS = 2,
	RELEASE = 3,
	EXIT = 17,
};

enum e_key_masks
{
	MASK_PRESS = 1L<<0,
	MASK_RELEASE = 1L<<1,
	MASK_EXIT = 1L<<17,
};

typedef struct s_info
{
	int				fd; // 얘도 없어도 됨
	char			*north_path; // path to textures
	char			*south_path;
	char			*west_path;
	char			*east_path;
	int				f_rgb[3]; // color 하나로 표현하기
	int				c_rgb[3];
	struct s_map	*map; // 없애기
	int				map_width;
	int				map_height;
}	t_info;

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

typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		size_l;
	int		endian;
}	t_img;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*img_data;
	int				bits_per_pixel;
	int				img_line_size;
	int				endian;
	char			*texture[4];
	t_img			texture_imgs[4];
	int				**map;
	int				map_row;
	int				map_col;
	int				ceiling; // 천장 색깔
	int				floor; // 바닥 색깔
	int				keys[7]; // 키보드 입력에 따른 키 배열
	t_vec			pos; // position, 현재 플레이어의 위치 - 소수점 포함
	t_vec			coord; // coordination, 현재 플레이어가 위치한 칸의 좌표 - 소수점 미포함
	t_vec			dir; // direction, 방향 벡터
	t_vec			old_dir; // old_direction, 방향 벡터
	t_vec			ray_dir; // ray-direction, ray의 방향 벡터
	
	t_vec			plane; // plane, 방향 벡터에 직교하는 벡터
	int				camera_x; // camera_x, 현재 카메라의 x 좌표 (-1 ~ 1)
	t_vec			side_dist; // side-distance, 현재 플레이어가 위치한 칸과 다음 x 또는 y 방향의 칸 사이의 거리
	t_vec			delta_dist; // delta-distance, side-dist에서 다음 x 또는 y 방향의 칸 사이의 거리
	double			perp_wall_dist; // perpendicular-wall-distance, ray가 맞는 지점까지의 수직거리
	t_vec			step; // step, ray가 한 칸씩 이동할 때의 x 또는 y 방향의 증가량
	int				color; // pixel의 color
	int				side; // ray가 맞은 면의 방향
	int				line_height; // line-height, 세로선의 높이
	int				draw_start; // draw-start, 세로선의 시작점
	int				draw_end; // draw-end, 세로선의 끝점
	t_fps			fps; // fps, 프레임 속도
	//아래는 삭제의 여지가 있음(막 만들었음)
	int				wall_texture_x; // wall_texture_x, 벽 텍스처의 x 좌표
	int				wall_texture_y; // wall_texture_y, 벽 텍스처의 y 좌표
	double			wall_x; // wall_x, 벽의 x 좌표
	double			step_texture; // step_texture, 벽 텍스처의 y 좌표가 얼마나 증가하는지
	double			texture_pos; // texture_pos, 벽 텍스처의 y 좌표
} t_game;

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

/* ./parsing/game_init.c */
void	free_info_map(t_info *info);
void	copy_map(t_info	*info, t_game *game);
void	copy_texture(t_info *info, t_game *game);
void	game_init(t_info *info, t_game *game);

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

void    set_ray_direction(t_game *game);
void    set_map_position(t_game *game);
void    set_delta_distance(t_game *game);
void    set_step(t_game *game);
void    set_side_distance(t_game *game);
void    dda(t_game *game);
int     ternary(int condition, int if_true, int if_false);
#endif