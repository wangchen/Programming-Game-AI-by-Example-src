#ifndef STREAM_UTILITY_FUNCTIONS
#define STREAM_UTILITY_FUNCTIONS
//-----------------------------------------------------------------------------
//
//  Name:   Stream_Utility_Functions.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   various useful functions that operate on or with streams
//-----------------------------------------------------------------------------
#include <sstream>
#include <string>
#include <iomanip>


//------------------------------ ttos -----------------------------------------
//
//  convert a type to a string
//-----------------------------------------------------------------------------
template <class T>
inline std::string ttos(const T& t, int precision = 2)
{
  std::ostringstream buffer;

  buffer << std::fixed << std::setprecision(precision) << t;

  return buffer.str();
}

//------------------------------ ttos -----------------------------------------
//
//  convert a bool to a string
//-----------------------------------------------------------------------------
inline std::string btos(bool b)
{
  if (b) return "true";
  return "false";
}

//--------------------------- GetValueFromStream ------------------------------
//
//  grabs a value of the specified type from an input stream
//-----------------------------------------------------------------------------
template <typename T>
inline T GetValueFromStream(std::ifstream& stream)
{
  T val;

  stream >> val;

  //make sure it was the correct type
  if (!stream)
  {
    throw std::runtime_error("Attempting to retrieve wrong type from stream");
  }

  return val;
}


#endif