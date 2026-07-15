#include <string>
#include <vector>
#include <iostream>

typedef std::vector<std::string> string_vector;


string_vector splitCmd(std::string raw_msg)
{
	string_vector	cmds;
	std::string		aux;

	while (raw_msg[0])
	{
		int find_char = raw_msg.find("\r\n");
		aux = raw_msg.substr(0, find_char);
		if (find_char == -1 || aux.find("\n") != -1)
		{
			// throw ReturnCode::BadFormatting();
			std::cout << "ERROR CMD\n";
			break ;
		}
		cmds.push_back(aux);

		raw_msg = raw_msg.substr(find_char + 2);
	}

	return  (cmds);
}


int main()
{
	std::string string = "viva la vida\r\ncaca la vida\r\nvida la pis\ncaca la caca\r\n";
	string_vector cmd = splitCmd(string);
	for (int i = 0; i < cmd.size(); ++i)
	{
		std::cout << "_" << cmd[i] << "_\n";
	}
}
