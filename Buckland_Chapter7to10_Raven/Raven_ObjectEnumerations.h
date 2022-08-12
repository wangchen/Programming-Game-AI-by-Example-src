#ifndef RAVEN_OBJECTS_H
#define RAVEN_OBJECTS_H

#include <string>


enum 
{
  type_wall,
  type_bot,
  type_unused,
  type_waypoint,
  type_health,
  type_spawn_point,
  type_rail_gun,
  type_rocket_launcher,
  type_shotgun,
  type_blaster,
  type_obstacle,
  type_sliding_door,
  type_door_trigger
};



inline std::string GetNameOfType(int w)
{
  std::string s;
  
  switch (w)
  {
  case type_wall:
    
    s = "Wall"; break; 
    
  case type_waypoint:
    
    s = "Waypoint"; break;

  case type_obstacle:
    
    s = "Obstacle"; break;

  case type_health:
    
    s = "Health"; break;

  case type_spawn_point:
    
    s = "Spawn Point"; break;

  case type_rail_gun:
    
    s = "Railgun"; break;

  case type_blaster:
    
    s = "Blaster"; break;

  case type_rocket_launcher:
    
    s =  "rocket_launcher"; break;

  case type_shotgun:
    
    s =  "shotgun"; break;

  case type_unused:
    
    s =  "knife"; break;

  case type_bot:
    
    s =  "bot"; break;

  case type_sliding_door:
    
    s =  "sliding_door"; break;
    
  case type_door_trigger:
    
    s =  "door_trigger"; break;

  default:

    s = "UNKNOWN OBJECT TYPE"; break;

  }

  return s;
}


#endif