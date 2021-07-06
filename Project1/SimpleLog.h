#pragma once
#include "pch.h"
#include <fstream>
#include "SingletonBase.h"

using namespace std;

class Debug : public SingletonBase<Debug>
{
private:
	ofstream* logFileStream;
public:
	void Log(std::string msg)
	{
		if (logFileStream == NULL)
		{
			logFileStream = new ofstream();
			logFileStream->open("C:\\Users\\teakgeun\\Desktop\\log.txt");
		}
		if (logFileStream->is_open())
		{
			logFileStream->write(msg.c_str(), msg.length());
			logFileStream->write("\n", 1);
			logFileStream->flush();
		}
	}
	void Log(char* msg, int len)
	{
		if (logFileStream == NULL)
		{
			logFileStream = new ofstream();
			logFileStream->open("C:\\Users\\teakgeun\\Desktop\\log.txt");
		}
		if (logFileStream->is_open())
		{
			logFileStream->write(msg, len);
			logFileStream->write("\n", 1);
			logFileStream->flush();
		}
	}
};