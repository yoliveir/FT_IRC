#include "Parser.hpp"
#include "ReturnCodes.hpp"

void Parser::splitArgs(std::string &str_to_spl, string_vector &args) const
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

	// for (int i  = 0; i < args.size(); i++)
	// {
	// 	std::cout << args.at(i) << "[" << i << "]" << "\n";
	// }
}

string_vector	Parser::extractArgs(const std::string &raw_msg) const
{
	string_vector	args;
	std::string					pre_dots_string;
	std::string					post_dots_string;

	int	dots_index = raw_msg.find(SPACE":"); //INDEX DOS PUNTOS
	int	new_line_index; // INDEX DEL "\r\n"

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

void	Parser::printMsg(string_vector &args, int origin_fd) const
{
	std::cout << "User [" << origin_fd << "] sent [";
	for (int i = 0; i < args.size(); ++i)
	{
		std::cout << args[i];
		if (i == args.size() - 1)
			std::cout << "]\n";
		else
			std::cout << " ";
	}
}

string_vector splitCmd(std::string raw_msg)
{
	string_vector	cmds;
	std::string		aux;

	while (raw_msg[0])
	{
		int find_char = raw_msg.find("\r\n");
		aux = raw_msg.substr(0, find_char);
		if (find_char == -1 || aux.find("\n") != -1)
			throw ReturnCodes::BadFormatting();
		cmds.push_back(aux);

		raw_msg = raw_msg.substr(find_char + 2);
	}

	return  (cmds);
}

void	Parser::parseMsg(User &user, Server &server)
{
	string_vector	cmds = splitCmd(user.getBuffer());

	for (int i = 0; i < cmds.size(); ++i)
	{
		string_vector	args = extractArgs(cmds[i]);
		printMsg(args, user.get_fd_socket());

		CommandManager	commandManager;
		commandManager.execute(server, user, args);
	}
}