#ifndef DEBUG_CONSOLE_H
#define DEBUG_CONSOLE_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
// Name:   DebugConsole.h
//
// Desc:   Creates a resizable console window for recording and displaying
//         debug info.
//
//         use the debug_con macro to send text and types to the console
//         window via the << operator (just like std::cout). Flush the
//         buffer using "" or the flush macro.  eg. 
//
//        debug_con << "Hello World!" << "";
//
// Author: Mat Buckland 2001 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <vector>
#include <windows.h>
#include <iosfwd>
#include <fstream>

#include "misc/utils.h"
#include "misc/WindowUtils.h"


//need to define a custom message
const int UM_SETSCROLL = WM_USER + 32;

//maximum number of lines shown in console before the buffer is flushed to 
//a file
const int MaxBufferSize = 500;

//initial dimensions of the console window
const int DEBUG_WINDOW_WIDTH  = 400;
const int DEBUG_WINDOW_HEIGHT = 400;

//undefine DEBUG to send all debug messages to hyperspace (a sink - see below)
//#define DEBUG
#ifdef DEBUG
#define debug_con *(DebugConsole::Instance())
#else
#define debug_con *(CSink::Instance())
#endif

//use these in your code to toggle output to the console on/off
#define debug_on  DebugConsole::On();
#define debug_off DebugConsole::Off();


//this little class just acts as a sink for any input. Used in place
//of the DebugConsole class when the console is not required
class CSink
{
private:

  CSink(){};

  //copy ctor and assignment should be private
  CSink(const CSink&);
  CSink& operator=(const CSink&);
  
public:

  static CSink* Instance(){static CSink instance; return &instance;}
  
  template<class T>
  CSink& operator<<(const T&)
  {
	  return *this;
  }
};



class DebugConsole
{
private:

  static HWND	         m_hwnd;
  
  //the string buffer. All input to debug stream is stored here
  static std::vector<std::string> m_Buffer;
  
  //if true the next input will be pushed into the buffer. If false,
  //it will be appended.
  static bool          m_bFlushed;  
  
  //position of debug window
  static int           m_iPosTop;
  static int           m_iPosLeft;

  //set to true if the window is destroyed
  static bool          m_bDestroyed;

  //if false the console will just disregard any input
  static bool          m_bActive;

  //default logging file
  static std::ofstream m_LogOut;



  //the debug window message handler
  static LRESULT CALLBACK DebugWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

  //this registers the window class and creates the window(called by the ctor)
  static bool             Create();

  static void             DrawWindow(){InvalidateRect(m_hwnd, NULL, TRUE); UpdateWindow(m_hwnd);}

private:

  DebugConsole(){}
 
  //copy ctor and assignment should be private
  DebugConsole(const DebugConsole&);
  DebugConsole& operator=(const DebugConsole&);

public:

  ~DebugConsole(){WriteAndResetBuffer(); }

  static DebugConsole* Instance();

             
  void ClearBuffer(){m_Buffer.clear(); flush();}


  static void flush()
  {
    if (!m_bDestroyed)
    {
      m_bFlushed = true; SendMessage(m_hwnd, UM_SETSCROLL, NULL, NULL);
    }
  }

  //writes the contents of the buffer to the file "debug_log.txt", clears
  //the buffer and resets the appropriate scroll info
  void WriteAndResetBuffer();

  //use to activate deactivate
  static void  Off(){m_bActive = false;}
  static void  On()  {m_bActive = true;}

  bool Destroyed()const{return m_bDestroyed;}
 

  //overload the << to accept any type
  template <class T>
  DebugConsole& operator<<(const T& t)
  {
    if (!m_bActive || m_bDestroyed) return *this;
   
    //reset buffer and scroll info if it overflows. Write the excess
    //to file
    if (m_Buffer.size() > MaxBufferSize)
    {
       WriteAndResetBuffer();
    }
    
    std::ostringstream ss; ss << t;

    if (ss.str() == ""){flush(); return *this;}
    
    if (!m_bFlushed)
      {m_Buffer.back() += ss.str();}
    else
      {m_Buffer.push_back(ss.str());m_bFlushed = false;}

    return *this;
  }
};

 

#endif