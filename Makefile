####### COLORS #######
_BOLD		=\e[1m
_R			=\e[0m
_RED		=\e[91m
_GREEN		=\e[92m
_YELLOW		=\e[93m
_BLUE		=\e[94m
_MAGENTA	=\e[35m
_CYAN		=\e[96m
_WHITE		=\e[97m
######################

NAME = webserv

SRC = main.cpp \
		Config.cpp \
		ServerManager.cpp \
		Request.cpp \
		utils.cpp \
		Server.cpp \
		Reponse.cpp \
		Client.cpp \
		CGI.cpp \
		Uri.cpp

### Librairies ###
HEADERS = ./includes/
INC = minishell.h
vpath %.h $(HEADERS)

### Sources ###
PATHSRCS = ./srcs
SRCS = $(addprefix $(PATHSRCS)/,$(SRC))

### Objets ###
OBJ_DIR = obj
OBJ = $(addprefix obj/,$(SRC:.cpp=.o))
vpath %.cpp $(PATHSRCS)

### Flags ###
FLAGS = -Wall -Wextra -Werror -std=c++98 #-g -fsanitize=address

all: $(NAME)

$(OBJ_DIR)/%.o: $(PATHSRCS)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@clang++ $(FLAGS) -I $(HEADERS) -c $< -o $@
	@printf "$(_YELLOW)Compiling :$(_WHITE) $<$(_R)\n"

$(NAME): titre $(OBJ)
	@printf "$(_YELLOW)Compilation completed.$(_R)\n"
	@(clang++ $(FLAGS) -I $(HEADERS) $(OBJ) -o $(NAME))
	@(printf "$(_YELLOW)Executable $(NAME) created.$(_R)\n")

clean:
	@printf "$(_BLUE)Clean$(_R)\n"
	@(rm -rf ./srcs/*.o)
	@(rm -rf $(OBJ_DIR))

fclean:	clean
	@printf "$(_BLUE)Fclean$(_R)\n"
	@(rm -rf $(NAME))

re:	fclean all

titre:
	@printf "\e[1;93mWebserv - 42 project -$(_R)\n"
	@printf "\e[1;93m______________________$(_R)\n"

.PHONY:	all clean fclean re titre
