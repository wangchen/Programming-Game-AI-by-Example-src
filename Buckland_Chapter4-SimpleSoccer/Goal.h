#ifndef GOAL_H
#define GOAL_H
//------------------------------------------------------------------------
//
//Name:   Goal.h
//
//Desc:   class to define a goal for a soccer pitch. The goal is defined
//        by two 2D vectors representing the left and right posts.
//
//        Each time-step the method Scored should be called to determine
//        if a goal has been scored.
//
//Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "SoccerBall.h"
#include "2D/Vector2D.h"
#include "2D/geometry.h"



class Goal 
{

private:

  Vector2D   m_vLeftPost;
  Vector2D   m_vRightPost;

  //a vector representing the facing direction of the goal
  Vector2D   m_vFacing;

  //the position of the center of the goal line
  Vector2D   m_vCenter;

  //each time Scored() detects a goal this is incremented
  int        m_iNumGoalsScored;

public:

  Goal(Vector2D left, Vector2D right, Vector2D facing):m_vLeftPost(left),
                                                       m_vRightPost(right),
                                                       m_vCenter((left+right)/2.0),
                                                       m_iNumGoalsScored(0),
                                                       m_vFacing(facing)
  {  }

  //Given the current ball position and the previous ball position,
  //this method returns true if the ball has crossed the goal line 
  //and increments m_iNumGoalsScored
  inline bool Scored(const SoccerBall*const ball);

  //-----------------------------------------------------accessor methods
  Vector2D Center()const{return m_vCenter;}
  Vector2D Facing()const{return m_vFacing;}
  Vector2D LeftPost()const{return m_vLeftPost;}
  Vector2D RightPost()const{return m_vRightPost;}

  int      NumGoalsScored()const{return m_iNumGoalsScored;}
  void     ResetGoalsScored(){m_iNumGoalsScored = 0;}
};


/////////////////////////////////////////////////////////////////////////

bool Goal::Scored(const SoccerBall*const ball)
{
  if (LineIntersection2D(ball->Pos(), ball->OldPos(), m_vLeftPost, m_vRightPost))
  {
    ++m_iNumGoalsScored;

    return true;
  }

  return false;
}


#endif