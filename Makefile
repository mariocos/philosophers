NAME = philo

SRC_PATH = ./srcs
OBJ_DIR = ./objs

SRCS = $(SRC_PATH)/errors/error.c \
	   $(SRC_PATH)/lib/lib.c \
	   $(SRC_PATH)/lib/init.c \
	   $(SRC_PATH)/lib/get_set.c \
	   $(SRC_PATH)/lib/print.c \
	   $(SRC_PATH)/lib/time.c \
	   $(SRC_PATH)/lib/safe.c \
	   $(SRC_PATH)/dinner/dinner.c \
	   $(SRC_PATH)/dinner/dinner_utils.c \
	   $(SRC_PATH)/main.c \



OBJ = $(SRCS:$(SRC_PATH)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

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