//
// Created by minha on 11/5/2024.
//

#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H


#include <iostream>
#include <vector>


using std::string, std::vector;


class Command {
private:
	string command;
	string effect;
public:
	explicit Command(const string &command);
	void saveEffect(const string &effect);

	string getCommand();
	string getEffect();
};

class CommandProcessor {
	public:
		vector<Command*> commands;
		CommandProcessor();
		explicit CommandProcessor(CommandProcessor*);
		~CommandProcessor() = default;

		string getCommand();
		void validate(const void* ptr);

private:
	Command *currentCommand{};

	string readCommand();
	void saveCommand(const string&);


};



#endif //COMMANDPROCESSOR_H
