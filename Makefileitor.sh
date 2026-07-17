#!/bin/bash

clear

echo "
___  ___  ___   _   __ _____ ______  _____  _      _____  _____  _____  _____ ______ 
|  \/  | / _ \ | | / /|  ___||  ___||_   _|| |    |  ___||_   _||_   _||  _  || ___ \\
| .  . |/ /_\ \| |/ / | |__  | |_     | |  | |    | |__    | |    | |  | | | || |_/ /
| |\/| ||  _  ||    \ |  __| |  _|    | |  | |    |  __|   | |    | |  | | | ||    / 
| |  | || | | || |\  \| |___ | |     _| |_ | |____| |___  _| |_   | |  \ \_/ /| |\ \ 
\_|  |_/\_| |_/\_| \_/\____/ \_|     \___/ \_____/\____/  \___/   \_/   \___/ \_| \_|
                                                                                     
                                                                                     
"

STD='\e[39m'
GRAY='\e[90m'
RED='\e[31m'

tree -L 2 -P *.cpp -P Makefile 2>/dev/null
if [[ $? > 0 ]]; then
	echo -e $GRAY"A directory tree could not be executed."
	echo -e "Install *tree* if you want to see it"$STD
	ls -l
fi

echo -e "\n\n"
read -e -p "Please specify where you want this file to be created from where you are right now: " path
read -e -p "Write the program name: " name
echo A Makefile for the program $name is going to be created...

file=$path/Makefile

touch $file 2>/dev/null

if [[ $? > 0 ]]; then
	echo "ERROR: invalid path"
	exit
fi

#------------- -   MAKEFILE CREATION CODE   - -----------------------------

cat << EOF > $file
NAME = $name

SRC_DIR = ./src/
OBJS_DIR = ./objs/

INC_DIRS = \$(sort \$(dir \$(SRCS)))
SRC_DIRS = \$(INC_DIRS)

VPATH += \$(SRC_DIRS)

CPP = c++

CPPFLAGS += \$(addprefix -I, \$(INC_DIRS))

//CPPFLAGS += -Wextra -Wall -Werror
CPPFLAGS += -fsanitize=address
CPPFLAGS += -std=c++98

RM = rm -rf

SRCS = $(find $path/src/ -name "*.cpp" | sed 's|^\./src/|$(SRC_DIR)|' | awk 'NR==1{printf "%s", $0; next} {printf " \\\n\t%s", $0}')

OBJS = \$(addprefix \$(OBJS_DIR), \$(notdir \$(SRCS:.cpp=.o)))

GREEN = \033[0;32m
GRAY = \033[0;90m
STD = \033[0m

.PHONY: clean all fclean re

all: \$(NAME)

\$(NAME): \$(OBJS)
	\$(CPP) \$(CPPFLAGS) \$(OBJS) -o \$(NAME)
	@echo "\n\$(GREEN)Compilation finished.\$(STD)"

\$(OBJS_DIR)%.o: %.cpp
	@echo "\$(GRAY)Compiling file  →   \$< \$(STD)"
	@mkdir -p \$(OBJS_DIR)
	\$(CPP) -c -MMD \$(CPPFLAGS) -o \$@ \$<

clean:
	@\$(RM) objs

fclean: clean
	@rm \$(NAME)

re: fclean all

-include \$(OBJS_DIR)/*.d

EOF
