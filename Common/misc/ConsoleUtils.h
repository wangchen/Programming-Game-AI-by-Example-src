#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H
//------------------------------------------------------------------------
//
//  Name:   ConsoleUtils.h
//
//  Desc:   Just a few handy utilities for dealing with consoles
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <windows.h>
#include <conio.h>
#include <iostream>

//default text colors can be found in wincon.h
inline void SetTextColor(WORD colors)
{
  HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
  
  SetConsoleTextAttribute(hConsole, colors);
}

inline void PressAnyKeyToContinue()
{
  //change text color to white
  SetTextColor(FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN);

  std::cout << "\n\nPress any key to continue" << std::endl; 

  while (!kbhit()){}

  return;
}


#endif