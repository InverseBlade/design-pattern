#ifndef CHAIN_H
#define CHAIN_H

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class AbstractLogger
{
public:
  const static int INFO;
  const static int DEBUG;
  const static int ERROR;

  void setNextLogger(shared_ptr<AbstractLogger> nextLogger)
  {
    this->nextLogger = nextLogger;
  }

  void log(int level, string msg)
  {
    if (level >= this->level)
    {
      write(msg);
    }
    if (nextLogger != nullptr)
    {
      nextLogger->log(level, msg);
    }
  }

protected:
  virtual void write(string msg) = 0;

  int level;
  shared_ptr<AbstractLogger> nextLogger;
};

const int AbstractLogger::INFO = 1;
const int AbstractLogger::DEBUG = 2;
const int AbstractLogger::ERROR = 3;

class ConsoleLogger : public AbstractLogger
{
public:
  ConsoleLogger(int level)
  {
    this->level = level;
  }

protected:
  void write(string msg) override
  {
    cout << "Standard Console::Logger: " + msg << endl;
  }
};

class ErrorLogger : public AbstractLogger
{
public:
  ErrorLogger(int level)
  {
    this->level = level;
  }

protected:
  void write(string msg) override
  {
    cout << "Error Console::Logger: " + msg << endl;
  }
};

class FileLogger : public AbstractLogger
{
public:
  FileLogger(int level)
  {
    this->level = level;
  }

protected:
  void write(string msg) override
  {
    cout << "File::Logger: " + msg << endl;
  }
};

shared_ptr<AbstractLogger> getLogger()
{
  auto errorLogger = make_shared<ErrorLogger>(AbstractLogger::ERROR);
  auto debugLogger = make_shared<FileLogger>(AbstractLogger::DEBUG);
  auto consoleLogger = make_shared<ConsoleLogger>(AbstractLogger::INFO);
  errorLogger->setNextLogger(debugLogger);
  debugLogger->setNextLogger(consoleLogger);
  return errorLogger;
}

void ChainTest()
{
  auto logger = getLogger();
  logger->log(AbstractLogger::INFO, "正常信息。");
  logger->log(AbstractLogger::DEBUG, "这是一条调试信息。");
  logger->log(AbstractLogger::ERROR, "这是一条错误信息。");
}

#endif