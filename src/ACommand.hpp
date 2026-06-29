#pragma once

# include <string>

class ACommand
{
private:
	std::string args[10];
public:
	virtual int execute() = 0;
};