//============================================================================
// Name        : Take Your Pills Video Encoder
// Author      : Raphaël GUILLORY
// Version     : Beta
// Copyright   : Please contact raphael.guillory@gmail.com
// Description : Video encoder for Take Your Pills
//============================================================================


#ifndef _COMMANDS_H
#define	_COMMANDS_H


#include <string>
#include <vector>


class command
{
public:
	std::string name;
	std::string id;
	int pass;
	std::string commandline;
};


class commands
{
public:
	std::vector<command> commandsSd;
	std::vector<command> commandsHd;
	std::vector<command> commandsPv;
};

#endif	/* _COMMANDS_H */
