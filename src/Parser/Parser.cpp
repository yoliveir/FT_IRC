#include "Parser.hpp"

void Parser::splitArgs(std::string	&str_to_spl, std::vector<std::string>	&args) const
{
	int space_is_here = str_to_spl.find(SPACE);

	if (space_is_here == SPACE_NOT_FOUND)
	{
		args.push_back(str_to_spl);
	}
	else
	{
		args.push_back(str_to_spl.substr(0, space_is_here)); // encasqueta el primer argumeento

		str_to_spl = str_to_spl.substr(space_is_here); // salta el primer argumento

		while (true)
		{
			str_to_spl = str_to_spl.substr(str_to_spl.find_first_not_of(SPACE)); // salta los espacios
			space_is_here = str_to_spl.find(SPACE);
			if (space_is_here == SPACE_NOT_FOUND)
				break;
			args.push_back(str_to_spl.substr(0, space_is_here)); // encasqueta otro argumento

			str_to_spl = str_to_spl.substr(space_is_here); // salta otro arguumento
		}

		args.push_back(str_to_spl); // encasqueta ultimo argumento
	}

	for (int i  = 0; i < args.size(); i++)
	{
		std::cout << args.at(i) << "[" << i << "]" << "\n";
	}
}

std::vector<std::string>	Parser::extractArgs(const std::string &raw_msg) const
{
	std::vector<std::string>	args;
	std::string					pre_dots_string;
	std::string					post_dots_string;

	int	dots_index = raw_msg.find(SPACE":"); //INDEX DOS PUNTOS

	if (dots_index != -1)
	{
		pre_dots_string = raw_msg.substr(0, dots_index);
		post_dots_string = raw_msg.substr(dots_index + 1);
	}
	else
	{
		pre_dots_string = raw_msg;
	}

	splitArgs(pre_dots_string, args);

	if (dots_index != -1)
		args.push_back(post_dots_string);

	return (args);
}

bool Parser::cmdExist(const std::vector <std::string> &args)
{
	const std::string string_array[CMDS_QUANTITY] =
	{
		"PASS",
		"NICK",
		"USER",
		"JOIN",
		"PRIVMSG",
		"KICK",
		"INVITE",
		"TOPIC",
		"MODE",
		"QUIT"
	};

	for (int i = 0; i < CMDS_QUANTITY; ++i)
	{
		if (args.at(0) == string_array[i])
			return (true);
	}
	return (false);
}


void	Parser::parseMsg(std::string raw_msg, int origin_fd, Server &server)
{
	std::vector	<std::string>	args = extractArgs(raw_msg);

	CommandManager	commandManager();
	commandManager.execute(server, user?!, args);

}