SRCS = src/main.c src/ft_data.c src/get_next_line/get_next_line.c src/ft_process_range.c src/ft_process_range2.c src/utils.c

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

LIBMLX = lib/mlx/libmlx.a

LIBFT = lib/libft/libft.a

${NAME}: ${SRCS} ${LIBMLX} ${LIBFT}
	${CC} ${FLAGS} ${CF} ${CI} ${SL} ${SRCS} ${LIBMLX}  ${LIBFT} -o ${NAME}

${BONUS}: ${SRCBS} ${LIBMLX}
	${CC} ${FLAGS} ${CF} ${CI} ${SL} ${SRCBS} ${LIBMLX} ${LIBFT} -o ${BONUS}

${LIBMLX}:
	make -C lib/mlx/

${LIBFT}:
	make -C lib/libft/

all: ${NAME}

clean: 
		${RM} ${OBJS}
		${RM} ${OBJBS} 

bonus: ${BONUS}

fclean: clean 
		${RM} ${NAME}
		${RM} ${BONUS}
		make clean -C lib/mlx/
		make fclean -C lib/libft/

re: fclean all

.PHONY: all clean fclean re bonus