#pragma once

# include <vector>
# include <string>

class Server;
class Client;
class ACommand
{
public:
	virtual ~ACommand() {}
	virtual int execute(Server& server, Client& Client,
						const std::vector<std::string>& args) = 0;
};