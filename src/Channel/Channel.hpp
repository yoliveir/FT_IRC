/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 13:12:36 by yurolive          #+#    #+#             */
/*   Updated: 2026/07/15 13:07:44 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include "User.hpp"

class Channel
{
private:
	std::string				_name;
	std::string				_topic;
	std::string				_key;	// senha do canal
	std::map<int, User*>	_members;
	std::map<int, bool>		_operators;

public:
	Channel(const std::string& name);
	~Channel();

	const std::string&	getName() const;

	void	addMember(User& user);
	void	removeMember(int fd);
	bool	hasMember(int fd) const;
	bool	isEmpty() const;

	void	addOperator(int fd);
	bool	isOperator(int fd) const;

	const std::string&	getKey() const;
	void	setKey(const std::string& key);
	bool	hasKey() const;

	const std::string&	getTopic() const;
	void	setTopic(const std::string& topic);

	void	broadcast(const std::string& message, int excludeFd = -1);
	std::string	getNamesList() const;
};
