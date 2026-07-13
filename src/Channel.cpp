/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurolive <yurolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 12:24:24 by yurolive          #+#    #+#             */
/*   Updated: 2026/07/13 15:44:20 by yurolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const std::string& name) : _name(name), _topic("")
{
}

Channel::~Channel()
{
}

const std::string& Channel::getName() const
{
	return _name;
}

void Channel::addMember(User& user)
{
	_members.insert(std::make_pair(user.get_fd_socket(), &user));
}

void Channel::removeMember(int fd)
{
	_members.erase(fd);
	_operators.erase(fd);
}

bool Channel::hasMember(int fd) const
{
	return _members.find(fd) != _members.end();
}

bool Channel::isEmpty() const
{
	return _members.empty();
}

void Channel::addOperator(int fd)
{
	_operators[fd] = true;
}

bool Channel::isOperator(int fd) const
{
	std::map<int, bool>::const_iterator it = _operators.find(fd);
	return it != _operators.end() && it->second;
}

const std::string& Channel::getKey() const
{
	return _key;
}

void Channel::setKey(const std::string& key)
{
	_key = key;
}

bool Channel::hasKey() const
{
	return !_key.empty();
}

const std::string& Channel::getTopic() const
{
	return _topic;
}

void Channel::setTopic(const std::string& topic)
{
	_topic = topic;
}

void Channel::broadcast(const std::string& message, int excludeFd)
{
	std::map<int, User*>::iterator it;
	for (it = _members.begin(); it != _members.end(); ++it)
	{
		if (it->first != excludeFd)
			it->second->sendMessage(message);
	}
}

std::string Channel::getNamesList() const
{
	std::string names;
	std::map<int, User*>::const_iterator it;
	for (it = _members.begin(); it != _members.end(); ++it)
	{
		if (isOperator(it->first))
			names += "@";
		names += it->second->getNickname();
		names += " ";
	}
	return names;
}