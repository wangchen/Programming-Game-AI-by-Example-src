#include "Raven_Goal_Types.h"


GoalTypeToString* GoalTypeToString::Instance()
{
  static GoalTypeToString instance;
  return &instance;
}

std::string GoalTypeToString::Convert(int gt)
{
  switch(gt)
  {
  case goal_explore:

    return "explore";

  case goal_think:

    return "think";

  case goal_arrive_at_position:

    return "arrive_at_position";

  case goal_seek_to_position:

    return "seek_to_position";

  case goal_follow_path:

    return "follow_path";

  case goal_traverse_edge:

    return "traverse_edge";

  case goal_move_to_position:

    return "move_to_position";

  case goal_get_health:

    return "get_health";

  case goal_get_shotgun:

    return "get_shotgun";

  case goal_get_railgun:

    return "get_railgun";

  case goal_get_rocket_launcher:

    return "get_rocket_launcher";

  case goal_wander:

    return "wander";

  case goal_negotiate_door:

    return "negotiate_door";

  case goal_attack_target:

    return "attack_target";

  case goal_hunt_target:

    return "hunt_target";

  case goal_strafe:

    return "strafe";

  case goal_adjust_range:

    return "adjust_range";

  case goal_say_phrase:

    return "say_phrase";

  default:

    return "UNKNOWN GOAL TYPE!";

  }//end switch
}