//
// Created by minha on 11/5/2024.
//

#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H


#include <fstream>
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

		virtual ~CommandProcessor() = default;

		string getCommand();
		void validate(const void* ptr);

private:
	Command *currentCommand{};

	virtual string readCommand();
	void saveCommand(const string&);

	friend class FileCommandProcessorAdapter;
};


class FileCommandProcessorAdapter : public CommandProcessor {
	public:
	explicit FileCommandProcessorAdapter(const string& fileName);

	string readCommand() override;

private:
	std::ifstream file;
};

#endif //COMMANDPROCESSOR_H
