#ifndef PARAMLOADER
#define PARAMLOADER
#pragma warning(disable:4800)
//------------------------------------------------------------------------
//
//Name:  ParamLoader.h
//
//Desc:  singleton class to handle the loading of default parameter
//       values from an initialization file: 'params.ini'
//
//Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <fstream>
#include <string>
#include <cassert>


#include "constants.h"
#include "misc/iniFileLoaderBase.h"


#define Prm (*ParamLoader::Instance())

class ParamLoader : public iniFileLoaderBase
{
private:

  ParamLoader():iniFileLoaderBase("Params.ini")
  {    
       
    GoalWidth                   = GetNextParameterDouble(); 
    
    NumSupportSpotsX            = GetNextParameterInt();    
    NumSupportSpotsY            = GetNextParameterInt();  
    
    Spot_PassSafeScore                     = GetNextParameterDouble();
    Spot_CanScoreFromPositionScore         = GetNextParameterDouble();
    Spot_DistFromControllingPlayerScore     = GetNextParameterDouble();
    Spot_ClosenessToSupportingPlayerScore  = GetNextParameterDouble();
    Spot_AheadOfAttackerScore              = GetNextParameterDouble();

    SupportSpotUpdateFreq       = GetNextParameterDouble(); 
    
    ChancePlayerAttemptsPotShot = GetNextParameterDouble();
    ChanceOfUsingArriveTypeReceiveBehavior = GetNextParameterDouble();
    
    BallSize                    = GetNextParameterDouble();    
    BallMass                    = GetNextParameterDouble();    
    Friction                    = GetNextParameterDouble(); 
    
    KeeperInBallRange           = GetNextParameterDouble();    
    PlayerInTargetRange         = GetNextParameterDouble(); 
    PlayerKickingDistance       = GetNextParameterDouble(); 
    PlayerKickFrequency         = GetNextParameterDouble();


    PlayerMass                  = GetNextParameterDouble(); 
    PlayerMaxForce              = GetNextParameterDouble();    
    PlayerMaxSpeedWithBall      = GetNextParameterDouble();   
    PlayerMaxSpeedWithoutBall   = GetNextParameterDouble();   
    PlayerMaxTurnRate           = GetNextParameterDouble();   
    PlayerScale                 = GetNextParameterDouble();      
    PlayerComfortZone           = GetNextParameterDouble();  
    PlayerKickingAccuracy       = GetNextParameterDouble();

    NumAttemptsToFindValidStrike = GetNextParameterInt();


    
    MaxDribbleForce             = GetNextParameterDouble();    
    MaxShootingForce            = GetNextParameterDouble();    
    MaxPassingForce             = GetNextParameterDouble();  
    
    WithinRangeOfHome           = GetNextParameterDouble();    
    WithinRangeOfSupportSpot    = GetNextParameterDouble();    
    
    MinPassDist                 = GetNextParameterDouble();
    GoalkeeperMinPassDist       = GetNextParameterDouble();
    
    GoalKeeperTendingDistance   = GetNextParameterDouble();    
    GoalKeeperInterceptRange    = GetNextParameterDouble();
    BallWithinReceivingRange    = GetNextParameterDouble();
    
    bStates                     = GetNextParameterBool();    
    bIDs                        = GetNextParameterBool(); 
    bSupportSpots               = GetNextParameterBool();     
    bRegions                    = GetNextParameterBool();
    bShowControllingTeam        = GetNextParameterBool();
    bViewTargets                = GetNextParameterBool();
    bHighlightIfThreatened      = GetNextParameterBool();

    FrameRate                   = GetNextParameterInt();

    SeparationCoefficient       = GetNextParameterDouble(); 
    ViewDistance                = GetNextParameterDouble(); 
    bNonPenetrationConstraint   = GetNextParameterBool(); 


    BallWithinReceivingRangeSq = BallWithinReceivingRange * BallWithinReceivingRange;
    KeeperInBallRangeSq      = KeeperInBallRange * KeeperInBallRange;
    PlayerInTargetRangeSq    = PlayerInTargetRange * PlayerInTargetRange;   
    PlayerKickingDistance   += BallSize;
    PlayerKickingDistanceSq  = PlayerKickingDistance * PlayerKickingDistance;
    PlayerComfortZoneSq      = PlayerComfortZone * PlayerComfortZone;
    GoalKeeperInterceptRangeSq     = GoalKeeperInterceptRange * GoalKeeperInterceptRange;
    WithinRangeOfSupportSpotSq = WithinRangeOfSupportSpot * WithinRangeOfSupportSpot;
  }
  
public:

  static ParamLoader* Instance();

  double GoalWidth;

  int   NumSupportSpotsX;
  int   NumSupportSpotsY;

  //these values tweak the various rules used to calculate the support spots
  double Spot_PassSafeScore;
  double Spot_CanScoreFromPositionScore;
  double Spot_DistFromControllingPlayerScore;
  double Spot_ClosenessToSupportingPlayerScore;
  double Spot_AheadOfAttackerScore;  
  
  double SupportSpotUpdateFreq ;

  double ChancePlayerAttemptsPotShot; 
  double ChanceOfUsingArriveTypeReceiveBehavior;

  double BallSize;
  double BallMass;
  double Friction;

  double KeeperInBallRange;
  double KeeperInBallRangeSq;

  double PlayerInTargetRange;
  double PlayerInTargetRangeSq;
  
  double PlayerMass;
  
  //max steering force
  double PlayerMaxForce; 
  double PlayerMaxSpeedWithBall;
  double PlayerMaxSpeedWithoutBall;
  double PlayerMaxTurnRate;
  double PlayerScale;
  double PlayerComfortZone;

  double PlayerKickingDistance;
  double PlayerKickingDistanceSq;

  double PlayerKickFrequency; 

  double  MaxDribbleForce;
  double  MaxShootingForce;
  double  MaxPassingForce;

  double  PlayerComfortZoneSq;

  //in the range zero to 1.0. adjusts the amount of noise added to a kick,
  //the lower the value the worse the players get
  double  PlayerKickingAccuracy;

  //the number of times the SoccerTeam::CanShoot method attempts to find
  //a valid shot
  int    NumAttemptsToFindValidStrike;

  //the distance away from the center of its home region a player
  //must be to be considered at home
  double WithinRangeOfHome;

  //how close a player must get to a sweet spot before he can change state
  double WithinRangeOfSupportSpot;
  double WithinRangeOfSupportSpotSq;
 
  
  //the minimum distance a receiving player must be from the passing player
  double   MinPassDist;
  double   GoalkeeperMinPassDist;

  //this is the distance the keeper puts between the back of the net
  //and the ball when using the interpose steering behavior
  double  GoalKeeperTendingDistance;

  //when the ball becomes within this distance of the goalkeeper he
  //changes state to intercept the ball
  double  GoalKeeperInterceptRange;
  double  GoalKeeperInterceptRangeSq;

  //how close the ball must be to a receiver before he starts chasing it
  double  BallWithinReceivingRange;
  double  BallWithinReceivingRangeSq;


  //these values control what debug info you can see
  bool  bStates;
  bool  bIDs;
  bool  bSupportSpots;
  bool  bRegions;
  bool  bShowControllingTeam;
  bool  bViewTargets;
  bool  bHighlightIfThreatened;

  int FrameRate;

  
  double SeparationCoefficient;

  //how close a neighbour must be before an agent perceives it
  double ViewDistance;

  //zero this to turn the constraint off
  bool bNonPenetrationConstraint;

};

#endif