#include "Parser.hpp"


const std::string Parser::_string_array[CMDS_QUANTITY] =
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

#define SPACE_NOT_FOUND -1
void splitArgs(std::string	&str_to_spl, std::vector<std::string>	&args)
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
	std::string	pre_dots_string;
	std::string	post_dots_string;

	int	dots_index = raw_msg.find(" :"); //INDEX DOS PUNTOS

	if (dots_index != -1)
	{
		pre_dots_string = raw_msg.substr(0, dots_index - 1);
		post_dots_string = raw_msg.substr(dots_index);
	}
	else
	{
		pre_dots_string = raw_msg;
	}

	splitArgs(pre_dots_string, args);
/* 
	int	space_index = pre_dots_string.find(" ");

	while (space_index != -1)
	{
		args.push_back(pre_dots_string.substr(0, space_index));
		pre_dots_string = pre_dots_string.substr(space_index + 1);
		space_index = pre_dots_string.find(" ", 0);
	}
	args.push_back(pre_dots_string);


	if (dots_index != -1)
		args.push_back(post_dots_string);
 */
	return (args);
}


void	Parser::parseMsg(std::string raw_msg, int origin_fd)
{
	// std::string command = extractCmd();
	std::vector	<std::string>	args = extractArgs(raw_msg);
	int cases = 0;
	// while (cases < CMDS_QUANTITY)
	// {
	// 	if (_string_array[cases] == command)
	// 	{
	// 		break ;
	// 	}
	// 	cases++;
	// }
	// std::string command = extractCmd();
	// CommandManager	commandManager();

	// // Necesito el FD de cliente
	// commandManager.execute(*this, _fd_list_sockets[i].fd, command);

}