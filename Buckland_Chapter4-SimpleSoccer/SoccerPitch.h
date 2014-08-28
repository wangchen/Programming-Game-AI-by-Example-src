#ifndef SOCCERPITCH_H
#define SOCCERPITCH_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   SoccerPitch.h
//
//  Desc:   A SoccerPitch is the main game object. It owns instances of
//          two soccer teams, two goals, the playing area, the ball
//          etc. This is the root class for all the game updates and
//          renders etc
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <windows.h>
#include <vector>
#include <cassert>

#include "2D/Wall2D.h"
#include "2D/Vector2D.h"
#include "constants.h"

class Region;
class Goal;
class SoccerTeam;
class SoccerBall;
class SoccerTeam;
class PlayerBase;


class SoccerPitch
{ 
public:

  SoccerBall*          m_pBall;

  SoccerTeam*          m_pRedTeam;
  SoccerTeam*          m_pBlueTeam;

  Goal*                m_pRedGoal;
  Goal*                m_pBlueGoal;
   
  //container for the boundary walls
  std::vector<Wall2D>  m_vecWalls;

  //defines the dimensions of the playing area
  Region*              m_pPlayingArea;

  //the playing field is broken up into regions that the team
  //can make use of to implement strategies.
  std::vector<Region*> m_Regions;

  //true if a goal keeper has possession
  bool                 m_bGoalKeeperHasBall;

  //true if the game is in play. Set to false whenever the players
  //are getting ready for kickoff
  bool                 m_bGameOn;

  //set true to pause the motion
  bool                 m_bPaused;

  //local copy of client window dimensions
  int                  m_cxClient,
                       m_cyClient;  
  
  //this instantiates the regions the players utilize to  position
  //themselves
  void CreateRegions(double width, double height);


public:

  SoccerPitch(int cxClient, int cyClient);

  ~SoccerPitch();

  void  Update();

  bool  Render();

  void  TogglePause(){m_bPaused = !m_bPaused;}
  bool  Paused()const{return m_bPaused;}

  int   cxClient()const{return m_cxClient;}
  int   cyClient()const{return m_cyClient;}

  bool  GoalKeeperHasBall()const{return m_bGoalKeeperHasBall;}
  void  SetGoalKeeperHasBall(bool b){m_bGoalKeeperHasBall = b;}

  const Region*const         PlayingArea()const{return m_pPlayingArea;}
  const std::vector<Wall2D>& Walls(){return m_vecWalls;}                      
  SoccerBall*const           Ball()const{return m_pBall;}

  const Region* const GetRegionFromIndex(int idx)                                
  {
    assert ( (idx > 0) && (idx < m_Regions.size()) );

    return m_Regions[idx];
  }

  bool  GameOn()const{return m_bGameOn;}
  void  SetGameOn(){m_bGameOn = true;}
  void  SetGameOff(){m_bGameOn = false;}

};

#endif