#include "CommandManager.hpp"

#include "Pass.hpp"
#include "Nick.hpp"
#include "User.hpp"
#include "Join.hpp"
#include "PrivMsg.hpp"
#include "Kick.hpp"
#include "Invite.hpp"
#include "Topic.hpp"
#include "Mode.hpp"

CommandManager::CommandManager()
{
	_commands["PASS"] = new Pass();
	_commands["NICK"] = new Nick();
	//_commands["USER"] = new User();
	// _commands["JOIN"] = new Join();
	// _commands["PRIVMSG"] = new PrivMsg();
	// _commands["KICK"] = new Kick();
	// _commands["INVITE"] = new Invite();
	// _commands["TOPIC"] = new Topic();
	// _commands["MODE"] = new Mode();
}

CommandManager::~CommandManager()
{
	for (std::map<std::string, ACommand*>::iterator it = _commands.begin();
		it != _commands.end(); ++it)
		delete it->second;
}

// en un futuro tambien debera recivir channel
void CommandManager::execute(Server &server, User &user, const std::vector<std::string> &args) //hemos camb iado comands con args y en veez de ser un string es vector entero
{
	std::map<std::string, ACommand*>::iterator it = _commands.find(args.at(0));

	if (it == _commands.end())
	{
		std::cerr << "Unknown command\n";
		return ;
	}

	it->second->execute(server, user, args);
}