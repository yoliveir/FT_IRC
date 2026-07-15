#pragma once

# include <vector>
# include <string>

typedef std::vector<std::string> string_vector;

class Server;
class User;
class ACommand
{
public:
	virtual ~ACommand() {}
	virtual int execute(Server &server, User &user, const string_vector &args) = 0;
};