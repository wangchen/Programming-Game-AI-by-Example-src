#ifndef PARAMLOADER_H
#define PARAMLOADER_H
//-----------------------------------------------------------------------------
//
//  Name:   ParamLoader.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to parse a parameter file for the steering behavior project
//-----------------------------------------------------------------------------
#include "constants.h"
#include "misc/iniFileLoaderBase.h"
#include "misc/utils.h"



#define Prm (*ParamLoader::Instance())


class ParamLoader : public iniFileLoaderBase
{
private:
  
    ParamLoader():iniFileLoaderBase("params.ini")
  {
    NumAgents               = GetNextParameterInt();
    NumObstacles            = GetNextParameterInt();
    MinObstacleRadius       = GetNextParameterFloat();
    MaxObstacleRadius       = GetNextParameterFloat();

    NumCellsX               = GetNextParameterInt();
    NumCellsY               = GetNextParameterInt();

    NumSamplesForSmoothing  = GetNextParameterInt();

    SteeringForceTweaker    = GetNextParameterFloat();
    MaxSteeringForce        = GetNextParameterFloat() * SteeringForceTweaker;
    MaxSpeed                = GetNextParameterFloat();
    VehicleMass             = GetNextParameterFloat();
    VehicleScale            = GetNextParameterFloat();

    SeparationWeight        = GetNextParameterFloat() * SteeringForceTweaker;
    AlignmentWeight         = GetNextParameterFloat() * SteeringForceTweaker;
    CohesionWeight          = GetNextParameterFloat() * SteeringForceTweaker;
    ObstacleAvoidanceWeight = GetNextParameterFloat() * SteeringForceTweaker;
    WallAvoidanceWeight     = GetNextParameterFloat() * SteeringForceTweaker;
    WanderWeight            = GetNextParameterFloat() * SteeringForceTweaker;
    SeekWeight              = GetNextParameterFloat() * SteeringForceTweaker;
    FleeWeight              = GetNextParameterFloat() * SteeringForceTweaker;
    ArriveWeight            = GetNextParameterFloat() * SteeringForceTweaker;
    PursuitWeight           = GetNextParameterFloat() * SteeringForceTweaker;
    OffsetPursuitWeight     = GetNextParameterFloat() * SteeringForceTweaker;
    InterposeWeight         = GetNextParameterFloat() * SteeringForceTweaker;
    HideWeight              = GetNextParameterFloat() * SteeringForceTweaker;
    EvadeWeight             = GetNextParameterFloat() * SteeringForceTweaker;
    FollowPathWeight        = GetNextParameterFloat() * SteeringForceTweaker;

    ViewDistance            = GetNextParameterFloat();
    MinDetectionBoxLength   = GetNextParameterFloat();
    WallDetectionFeelerLength=GetNextParameterFloat();

    prWallAvoidance         = GetNextParameterFloat();
    prObstacleAvoidance     = GetNextParameterFloat();  
    prSeparation            = GetNextParameterFloat();
    prAlignment             = GetNextParameterFloat();
    prCohesion              = GetNextParameterFloat();
    prWander                = GetNextParameterFloat();
    prSeek                  = GetNextParameterFloat();
    prFlee                  = GetNextParameterFloat();
    prEvade                 = GetNextParameterFloat();
    prHide                  = GetNextParameterFloat();
    prArrive                = GetNextParameterFloat();

    MaxTurnRatePerSecond    = Pi;
  }

public:

  static ParamLoader* Instance();

  int	NumAgents;
  int	NumObstacles;
  double MinObstacleRadius;
  double MaxObstacleRadius;

  //number of horizontal cells used for spatial partitioning
  int   NumCellsX;
  //number of vertical cells used for spatial partitioning
  int   NumCellsY;

  //how many samples the smoother will use to average a value
  int   NumSamplesForSmoothing;

  //used to tweak the combined steering force (simply altering the MaxSteeringForce
  //will NOT work!This tweaker affects all the steering force multipliers
  //too).
  double SteeringForceTweaker;

  double MaxSteeringForce;
  double MaxSpeed;
  double VehicleMass;

  double VehicleScale;
  double MaxTurnRatePerSecond;

  double SeparationWeight;
  double AlignmentWeight ;
  double CohesionWeight  ;
  double ObstacleAvoidanceWeight;
  double WallAvoidanceWeight;
  double WanderWeight    ;
  double SeekWeight      ;
  double FleeWeight      ;
  double ArriveWeight    ;
  double PursuitWeight   ;
  double OffsetPursuitWeight;
  double InterposeWeight ;
  double HideWeight      ;
  double EvadeWeight     ;
  double FollowPathWeight;

  //how close a neighbour must be before an agent perceives it (considers it
  //to be within its neighborhood)
  double ViewDistance;

  //used in obstacle avoidance
  double MinDetectionBoxLength;

  //used in wall avoidance
  double WallDetectionFeelerLength;

  //these are the probabilities that a steering behavior will be used
  //when the prioritized dither calculate method is used
  double prWallAvoidance;
  double prObstacleAvoidance;
  double prSeparation;
  double prAlignment;
  double prCohesion;
  double prWander;
  double prSeek;
  double prFlee;
  double prEvade;
  double prHide;
  double prArrive;
  
};





#endif