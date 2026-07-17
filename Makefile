NAME = ircserv

SRC_DIR = ./src/
OBJS_DIR = ./objs/

INC_DIRS = $(sort $(dir $(SRCS)))
SRC_DIRS = $(INC_DIRS)

VPATH += $(SRC_DIRS)

CPP = c++

CPPFLAGS += $(addprefix -I, $(INC_DIRS))

//CPPFLAGS += -Wextra -Wall -Werror
CPPFLAGS += -fsanitize=address
CPPFLAGS += -std=c++98

RM = rm -rf

SRCS = $(SRC_DIR)Commands/Quit.cpp \
	$(SRC_DIR)Commands/Pass.cpp \
	$(SRC_DIR)Commands/Join.cpp \
	$(SRC_DIR)Commands/ACommand.cpp \
	$(SRC_DIR)Commands/PrivMsg.cpp \
	$(SRC_DIR)Commands/CommandManager.cpp \
	$(SRC_DIR)Commands/Mode.cpp \
	$(SRC_DIR)Commands/Invite.cpp \
	$(SRC_DIR)Commands/UserCommand.cpp \
	$(SRC_DIR)Commands/Kick.cpp \
	$(SRC_DIR)Commands/Topic.cpp \
	$(SRC_DIR)Commands/Nick.cpp \
	$(SRC_DIR)Channel/Channel.cpp \
	$(SRC_DIR)Server/Server.cpp \
	$(SRC_DIR)signal/signal.cpp \
	$(SRC_DIR)User/User.cpp \
	$(SRC_DIR)ReturnCodes/ReturnCodes.cpp \
	$(SRC_DIR)main.cpp \
	$(SRC_DIR)Parser/Parser.cpp

OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.cpp=.o)))

GREEN = \033[0;32m
GRAY = \033[0;90m
STD = \033[0m

.PHONY: clean all fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "\n$(GREEN)Compilation finished.$(STD)"

$(OBJS_DIR)%.o: %.cpp
	@echo "$(GRAY)Compiling file  →   $< $(STD)"
	@mkdir -p $(OBJS_DIR)
	$(CPP) -c -MMD $(CPPFLAGS) -o $@ $<

clean:
	@$(RM) objs

fclean: clean
	@rm $(NAME)

re: fclean all

-include $(OBJS_DIR)/*.d

