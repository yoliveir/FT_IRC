#pragma once

#include <string>
#include <vector>

#include "../Commands/CommandManager.hpp"
#include "User.hpp"
//#include "Server.hpp"

#define CMDS_QUANTITY 10
#define SPACE " "
#define SPACE_NOT_FOUND -1


class	Parser
{
	private:
		std::vector<std::string>	extractArgs(const std::string &raw_msg) const;
		void						splitArgs(std::string	&str_to_spl, std::vector<std::string>	&args) const;

		bool cmdExist(const std::vector <std::string> &args);

	public:
		void parseMsg(std::string raw_msg, int origin_fd, Server &server);

};

