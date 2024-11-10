//
// Created by minha on 11/5/2024.
//

#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H


#include <fstream>
#include <iostream>
#include <vector>
#include "../LoggingObserver/LoggingObserver.h"

using std::string, std::vector;


class Command :public ILoggable, Subject{
private:
	string command;
	string effect;
public:
	explicit Command(const string &command);
	void saveEffect(const string &effect);
	string stringToLog() override;
	string getCommand();
	string getEffect();
};

class CommandProcessor : public ILoggable, Subject {
	public:
		vector<Command*> commands;
		CommandProcessor();
		explicit CommandProcessor(CommandProcessor*);
		virtual ~CommandProcessor() = default;

		string stringToLog() override;
        vector<string> splitCommand(const string command);
		string getCommand();
		void validate(const void* ptr);
        bool validate(const string command);

private:
	Command *currentCommand{};

	virtual string readCommand();
	void saveCommand(const string&);

	friend class FileCommandProcessorAdapter;
};


class FileCommandProcessorAdapter : public CommandProcessor {
	public:
	FileCommandProcessorAdapter();
	explicit FileCommandProcessorAdapter(const string& fileName);

	string readCommand() override;

private:
	std::ifstream file;
};

extern CommandProcessor* commandProcessor;

#endif //COMMANDPROCESSOR_H