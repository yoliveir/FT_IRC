#pragma once

#include <map>
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::string> string_vector;

class ACommand;
class Server;
class User;

class CommandManager
{
private:
	std::map<std::string, ACommand*> _commands;

public:
	CommandManager();
	~CommandManager();

	void execute(Server &server, User &user, const string_vector &command);
};