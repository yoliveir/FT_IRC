#pragma once

#include <string>
#include <vector>

#include "../Commands/CommandManager.hpp"

#define CMDS_QUANTITY 10

class	Parser
{
	private:
		std::vector<std::string> extractArgs(const std::string &raw_msg) const;

		static const std::string _string_array[CMDS_QUANTITY];


	public:
		void	parseMsg(std::string raw_msg, int origin_fd);

};