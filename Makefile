
###################################################################################
###									PROGRAM										###
###################################################################################

NAME					=		philo

###################################################################################
###									COMPILE										###
###################################################################################

CC						=		cc

###################################################################################
###									DIRECTORY									###
###################################################################################

OBJ_DIR					=		obj
SRC_DIR					=		src
PARS_DIR				=		parsing
EXEC_DIR				=		execution

###################################################################################
###									FLAGS										###
###################################################################################

CFLAGS					=		-Wall -Wextra -Werror

###################################################################################
###									FILES										###
###################################################################################

FILES_PARS				=		atoi_atot.c\
								init.c\
								lk_ls_fork.c\
								lk_ls_philo.c\
								param_check.c

FILES_EXEC				=		

FILES_ROOT					=	main.c\
								utils.c\

SRC						=		$(addprefix $(SRC_DIR)/, $(FILES_ROOT)) \
								$(addprefix $(SRC_DIR)/$(PARS_DIR)/, $(FILES_PARS)) \
								$(addprefix $(SRC_DIR)/$(EXEC_DIR)/, $(FILES_EXEC))
								
INCLUDE				=		-Iinclude
HEADER					=		include/philo.h
OBJ						=		$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

###################################################################################
###									ARCHIVES									###
###################################################################################

all: $(NAME)

$(NAME): $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
			$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)
			mkdir -p $(OBJ_DIR)/$(PARS_DIR)
			mkdir -p $(OBJ_DIR)/$(EXEC_DIR)

re: fclean
			$(MAKE) all

fclean: clean
			rm -f $(NAME)

clean: 
			rm -rf $(OBJ_DIR)

.PHONY: all clean fclean re