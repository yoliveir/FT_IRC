#pragma once

#include <map>
#include <iostream>
#include <string>

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

	void execute(Server &server, User &user, const std::vector<std::string> &command);
};