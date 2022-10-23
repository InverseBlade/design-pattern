#pragma once

#include <iostream>
using namespace std;

class Scanner
{
public:
  void scan()
  {
    cout << "词法分析" << endl;
  }
};

class Parser
{
public:
  void Parse() { cout << "语法分析" << endl; }
};

class GenMidCode
{
public:
  void GenCode() { cout << "产生中间代码" << endl; }
};

class GenMachineCode
{
public:
  void GenCode() { cout << "产生机器码" << endl; }
};

class Compiler
{
public:
  void run()
  {
    Scanner scanner;
    Parser parser;
    GenMidCode genMidCode;
    GenMachineCode genMachineCode;

    scanner.scan();
    parser.Parse();
    genMidCode.GenCode();
    genMachineCode.GenCode();
  }
};

class FacadeTest
{
public:
  void test()
  {
    Compiler cc;
    cc.run();
  }
};
