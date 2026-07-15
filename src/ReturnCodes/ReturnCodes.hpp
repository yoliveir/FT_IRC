#pragma once

# include <stdexcept>

class ReturnCodes
{
public:
	class BadFormatting: public std::exception
	{
		public:
			const char	*what() const throw()
			{
				return ("BAD TERMINATOR: If you are using nc make sure to add the option -C");
			}
	};
};