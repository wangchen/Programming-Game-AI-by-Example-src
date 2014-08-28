#ifndef GOAL_ENUMERATIONS_H
#define GOAL_ENUMERATIONS_H

#include <string>
#include "misc/TypeToString.h"

enum
{
  goal_think,
  goal_explore,
  goal_arrive_at_position,
  goal_seek_to_position,
  goal_follow_path,
  goal_traverse_edge,
  goal_move_to_position,
  goal_get_health,
  goal_get_shotgun,
  goal_get_rocket_launcher,
  goal_get_railgun,
  goal_wander,
  goal_negotiate_door,
  goal_attack_target,
  goal_hunt_target,
  goal_strafe,
  goal_adjust_range,
  goal_say_phrase
  
};

class GoalTypeToString : public TypeToString
{

  GoalTypeToString(){}

public:

  static GoalTypeToString* Instance();
  
  std::string Convert(int gt);
};

#endif
