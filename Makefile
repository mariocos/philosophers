NAME = philo

SRC_PATH = ./srcs
OBJ_DIR = ./objs

SRCS = $(SRC_PATH)/init.c \
	   $(SRC_PATH)/get_set.c \
	   $(SRC_PATH)/print.c \
	   $(SRC_PATH)/time.c \
	   $(SRC_PATH)/safe.c \
	   $(SRC_PATH)/dinner.c \
	   $(SRC_PATH)/dinner_utils.c \
	   $(SRC_PATH)/lib.c \
	   $(SRC_PATH)/error.c \
	   $(SRC_PATH)/killer.c \
	   $(SRC_PATH)/main.c \



OBJ = $(SRCS:$(SRC_PATH)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -pthread #-fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re