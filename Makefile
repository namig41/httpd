FILE_HTTPD 	= \
			main \
			http \
			net \
			request \
			response \
			header \
			status \
			page \
			utilities \

DIR_SRC			= ./src/
DIR_INC			= ./include/
DIR_OBJ 		= ./obj/

OBJ_HTTPD 		= \
				  	$(addprefix $(DIR_OBJ), $(addsuffix .o, $(FILE_HTTPD)))

CC 	   			= gcc
NAME   			= httpd
#CFLAGS 	   		= -Wall -Werror -Wextra -O2 -I$(DIR_INC)
CFLAGS 	   		=  -O2 -g -I$(DIR_INC)

all: $(NAME)

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(NAME): $(DIR_OBJ) $(OBJ_HTTPD)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_HTTPD)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
 
clean:
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
