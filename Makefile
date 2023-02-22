SRCS = main.c ft_data.c get_next_line/get_next_line.c ft_process_range.c ft_process_range2.c ft_process_utils.c	ft_process.c ft_process_objet.c ft_process_camera.c utils.c

SRCBS = 

OBJS = ${SRCS:.c=.o}

OBJBS = ${SRCBS:.c=.o}

NAME = miniRT

BONUS = miniRT_bonus

CC = gcc 

FLAGS = -Wall -Wextra -Werror

SL = -framework OpenGL -framework AppKit

CI = -I sl_inc/

RM = rm -f

LIBMLX = mlx/libmlx.a

LIBFT = libft/libft.a

${NAME}: ${SRCS} ${LIBMLX} ${LIBFT}
	${CC} ${FLAGS} ${CF} ${CI} ${SL} ${SRCS} ${LIBMLX}  ${LIBFT} -o ${NAME}

${BONUS}: ${SRCBS} ${LIBMLX}
	${CC} ${FLAGS} ${CF} ${CI} ${SL} ${SRCBS} ${LIBMLX} ${LIBFT} -o ${BONUS}

${LIBMLX}:
	make -C mlx/

${LIBFT}:
	make bonus -C libft/

all: ${NAME}

clean: 
		${RM} ${OBJS}
		${RM} ${OBJBS} 

bonus: ${BONUS}

fclean: clean 
		${RM} ${NAME}
		${RM} ${BONUS}
		make clean -C mlx/
		make fclean -C libft/

re: fclean all

.PHONY: all clean fclean re bonus
