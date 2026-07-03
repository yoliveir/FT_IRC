#pragma once

# include <vector>
# include <string>

class Server;
class User;
class ACommand
{
public:
	virtual ~ACommand() {}
	virtual int execute(Server& server, User& user,
						const std::vector<std::string>& args) = 0;
};