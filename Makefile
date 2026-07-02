NAME = ircserv

INC_DIR = ./inc
SRC_DIR = ./src/
OBJS_DIR = ./objs/

CPP = c++
CPPFLAGS =	-I$(INC_DIR) #-Wextra -Wall -Werror
CPPFLAGS += -fsanitize=address
CPPFLAGS += -std=c++98

RM = rm -rf

SRCS = $(SRC_DIR)User.cpp $(SRC_DIR)main.cpp $(SRC_DIR)Server.cpp 

OBJS = $(patsubst $(SRC_DIR)%.cpp, $(OBJS_DIR)%.o, $(SRCS))

GREEN = \033[0;32m
GRAY = \033[0;90m
STD = \033[0m

.PHONY: clean all fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "\n$(GREEN)Compilation finished.$(STD)"

$(OBJS_DIR)%.o: $(SRC_DIR)%.cpp
	@echo "$(GRAY)Compiling file  →   $< $(STD)"
	@mkdir -p $(OBJS_DIR)
	$(CPP) -c -MMD $(CPPFLAGS) -o $@ $<

clean:
	@$(RM) objs

fclean: clean
	@rm $(NAME)

re: fclean all

-include $(OBJS_DIR)/*.d
