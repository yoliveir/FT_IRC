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

typedef std::map<std::string, ACommand*>::iterator iteradorComando;
CommandManager::~CommandManager()
{
	for (iteradorComando it = _commands.begin();
		it != _commands.end(); ++it)
		delete it->second;
}

// en un futuro tambien debera recivir channel
void CommandManager::execute(Server &server, User &user, const string_vector &args) //hemos cambiado comands con args y en vez de ser un string es vector entero
{
	iteradorComando it = _commands.find(args[0]);

	if (it == _commands.end())
	{
		std::cerr << "Unknown command\n"; //! Falta avisar al user
		return ;
	}

	it->second->execute(server, user, args);
}