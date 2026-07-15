#pragma once

#include <string>
#include <vector>

#include "../Commands/CommandManager.hpp"
#include "User.hpp"
//#include "Server.hpp"
#include <ostream>

#define CMDS_QUANTITY 10
#define SPACE " "
#define SPACE_NOT_FOUND -1
#define CR_LF "\r\n"
#define CR_LF_NOT_FOUND -1

typedef std::vector<std::string> string_vector;
class	Parser
{
	private:
		string_vector	extractArgs(const std::string &raw_msg) const;
		void						splitArgs(std::string	&str_to_spl, string_vector	&args) const;
		void						printMsg(string_vector &args, int origin_fd) const;
	public:
		void	parseMsg(std::string raw_msg, int origin_fd, Server &server);
};

