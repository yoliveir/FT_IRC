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

echo -e "NAME = $name\n" > $file

echo -e "INC_DIR = ./inc" >> $file
echo -e "SRC_DIR = ./src/" >> $file
echo -e "OBJS_DIR = ./objs/\n" >> $file

echo -e "CPP = c++" >> $file
echo -e 'CPPFLAGS =	-I$(INC_DIR) -Wextra -Wall -Werror' >> $file
echo -e 'CPPFLAGS += -fsanitize=address' >> $file
echo -e "CPPFLAGS += -std=c++98\n" >> $file

echo -e "RM = rm -rf\n" >> $file

echo -e "SRCS = ` ls $path/src | grep .cpp | sed 's/^/$(SRC_DIR)/g'| tr '\n' ' '`\n" >> $file
echo -e 'OBJS = $(patsubst $(SRC_DIR)%.cpp, $(OBJS_DIR)%.o, $(SRCS))\n' >> $file
echo 'GREEN = \033[0;32m
GRAY = \033[0;90m
STD = \033[0m' >> $file
echo -e "\n.PHONY: clean all fclean re\n" >> $file

#------- Compilation part --------------------
echo -e 'all: $(NAME)\n' >> $file

echo -e '$(NAME): $(OBJS)' >> $file
echo -e '	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)' >> $file
echo -e '	@echo "\\n$(GREEN)Compilation finished.$(STD)"\n' >> $file

echo -e '$(OBJS_DIR)%.o: $(SRC_DIR)%.cpp' >> $file
echo -e '	@echo "$(GRAY)Compiling file  →   $< $(STD)"' >> $file
echo -e '	@mkdir -p $(OBJS_DIR)' >> $file
echo -e '	$(CPP) -c -MMD $(CPPFLAGS) -o $@ $<\n' >> $file

echo -e 'clean:' >> $file
echo -e '	@$(RM) objs\n' >> $file

echo -e 'fclean: clean' >> $file
echo -e '	@rm $(NAME)\n' >> $file

echo -e 're: fclean all\n' >> $file

echo -e '-include $(OBJS_DIR)/*.d' >> $file
#--------------------------------------------------------------------------
