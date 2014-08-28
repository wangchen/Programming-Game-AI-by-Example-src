#ifndef ROCK_PAPER_SCISSORS_H
#define ROCK_PAPER_SCISSORS_H
#pragma warning (disable:4786)

#include "OpenLuaStates.h"
#include "misc/utils.h"
#include <string>
#include <iostream>


const int         NumPlayStrings = 3;
const std::string PossiblePlayStrings[NumPlayStrings] = {"scissors", "rock", "paper"};

//-------------------------- GetAIMove ----------------------------------------
//
//  this is GetAIMove as you would normally use it in C++
//-----------------------------------------------------------------------------
std::string GetAIMove()
{
  return PossiblePlayStrings[RandInt(0,2)];
}

//----------------------- cpp_GetAIMove ---------------------------------------
//
//  this is the wrapper written for GetAIMove to expose the function to lua
//-----------------------------------------------------------------------------
int cpp_GetAIMove(lua_State* pL)
{
  //get the number of parameters passed to this function from the lua
  //stack and make sure it is equal to the correct number of parameters
  //for GetAIMove
  int n = lua_gettop(pL);

  if (n!=0)
  {
    std::cout << "\n[C++]: Wrong number of arguments for cpp_GetAIMove";
    
    return 0;
  }

  //push the result from GetAIMove on the stack. Notice how the std::string 
  //is converted to a C type string first
  lua_pushstring(pL, GetAIMove().c_str());

  //return the number of return values
  return 1;
}

//------------------------ GuessToIndex ---------------------------------------
//
//  given a play string, this function returns its key in PossiblePlayStrings
//-----------------------------------------------------------------------------
int  GuessToIndex(const std::string& guess)
{
  for (int i=0; i<NumPlayStrings; ++i)
  {
    if (guess == PossiblePlayStrings[i]) return i;
  }

  //this value will force an error
  return -1;
}

 
//------------------------- EvaluateTheGuesses --------------------------------
//
//  Given the computer's play string and the users play string, and references
//  to the scores, this function decides who has won the round and assigns
//  points accordingly
//----------------------------------------------------------------------------- 
void EvaluateTheGuesses(std::string user_guess,
                        std::string  comp_guess,
                        int&   user_score,
                        int&   comp_score)
{

  static const int score_table[NumPlayStrings][NumPlayStrings] = 
  { 
    {0,-1,1},
    {1,0,-1},
    {-1,1,0}
  };

  std::cout << "\nuser guess..." + user_guess + "  comp guess..." + comp_guess;
  
  if (score_table[GuessToIndex(user_guess)][GuessToIndex(comp_guess)] == 1)
  {
    std::cout << "\nYou have won this round!";

    ++user_score;
  }
  else if (score_table[GuessToIndex(user_guess)][GuessToIndex(comp_guess)] == -1)
  {
    std::cout << "\nComputer wins this round.";

    ++comp_score;
  }

  else
  {
    std::cout << "\nIt's a draw!";
  }
}


//------------------------------ cpp_EvaluateTheGuesses -----------------------
//
//  the wrapper for EvaluateTheGuesses
//-----------------------------------------------------------------------------
int cpp_EvaluateTheGuesses(lua_State* pL)
{
  //get the number of parameters passed to this function from the lua
  //stack and make sure it is equal to the correct number of parameters
  //for EvaluateTheGuesses.
  int n = lua_gettop(pL);

  if (n!=4)
  {
    std::cout << "\n[C++]: Wrong number of arguments for cpp_EvaluateTheGuesses";
    
    return 0;
  }

   //check that the parameters are of the correct type. 
  if (!lua_isstring(pL, 1) || !lua_isstring(pL, 2) ||
      !lua_isnumber(pL, 3) || !lua_isnumber(pL, 4))
  {
    std::cout << "\n[C++]: ERROR: Invalid types passed to cpp_EvaluateTheGuesses";
  }

  //grab the parameters off the stack
  std::string user_guess = lua_tostring(pL, 1); 
  std::string comp_guess = lua_tostring(pL, 2); 
  int         user_score = (int)lua_tonumber(pL, 3); 
  int         comp_score = (int)lua_tonumber(pL, 4); 

  //call the C++ function proper
  EvaluateTheGuesses(user_guess, comp_guess, user_score, comp_score);

  //now push the updated scores onto the stack
  lua_pushnumber(pL, user_score);
  lua_pushnumber(pL, comp_score);

  //return the number of values pushed onto the stack
  return 2;
}


#endif