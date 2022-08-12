#include "Raven_Game.h"
#include "Raven_ObjectEnumerations.h"
#include "misc/WindowUtils.h"
#include "misc/Cgdi.h"
#include "Raven_SteeringBehaviors.h"
#include "lua/Raven_Scriptor.h"
#include "navigation/Raven_PathPlanner.h"
#include "game/EntityManager.h"
#include "2d/WallIntersectionTests.h"
#include "Raven_Map.h"
#include "Raven_Door.h"
#include "Raven_UserOptions.h"
#include "Time/PrecisionTimer.h"
#include "Raven_SensoryMemory.h"
#include "Raven_WeaponSystem.h"
#include "messaging/MessageDispatcher.h"
#include "Raven_Messages.h"
#include "GraveMarkers.h"

#include "armory/Raven_Projectile.h"
#include "armory/Projectile_Rocket.h"
#include "armory/Projectile_Pellet.h"
#include "armory/Projectile_Slug.h"
#include "armory/Projectile_Bolt.h"

#include "goals/Goal_Think.h"
#include "goals/Raven_Goal_Types.h"



//uncomment to write object creation/deletion to debug console
//#define  LOG_CREATIONAL_STUFF


//----------------------------- ctor ------------------------------------------
//-----------------------------------------------------------------------------
Raven_Game::Raven_Game():m_pSelectedBot(NULL),
                         m_bPaused(false),
                         m_bRemoveABot(false),
                         m_pMap(NULL),
                         m_pPathManager(NULL),
                         m_pGraveMarkers(NULL)
{
  //load in the default map
  LoadMap(script->GetString("StartMap"));
}


//------------------------------ dtor -----------------------------------------
//-----------------------------------------------------------------------------
Raven_Game::~Raven_Game()
{
  Clear();
  delete m_pPathManager;
  delete m_pMap;
  
  delete m_pGraveMarkers;
}


//---------------------------- Clear ------------------------------------------
//
//  deletes all the current objects ready for a map load
//-----------------------------------------------------------------------------
void Raven_Game::Clear()
{
#ifdef LOG_CREATIONAL_STUFF
    debug_con << "\n------------------------------ Clearup -------------------------------" <<"";
#endif

  //delete the bots
  std::list<Raven_Bot*>::iterator it = m_Bots.begin();
  for (it; it != m_Bots.end(); ++it)
  {
#ifdef LOG_CREATIONAL_STUFF
    debug_con << "deleting entity id: " << (*it)->ID() << " of type "
              << GetNameOfType((*it)->EntityType()) << "(" << (*it)->EntityType() << ")" <<"";
#endif

    delete *it;
  }

  //delete any active projectiles
  std::list<Raven_Projectile*>::iterator curW = m_Projectiles.begin();
  for (curW; curW != m_Projectiles.end(); ++curW)
  {
#ifdef LOG_CREATIONAL_STUFF
    debug_con << "deleting projectile id: " << (*curW)->ID() << "";
#endif

    delete *curW;
  }

  //clear the containers
  m_Projectiles.clear();
  m_Bots.clear();

  m_pSelectedBot = NULL;


}

//-------------------------------- Update -------------------------------------
//
//  calls the update function of each entity
//-----------------------------------------------------------------------------
void Raven_Game::Update()
{ 
  //don't update if the user has paused the game
  if (m_bPaused) return;

  m_pGraveMarkers->Update();

  //get any player keyboard input
  GetPlayerInput();
  
  //update all the queued searches in the path manager
  m_pPathManager->UpdateSearches();

  //update any doors
  std::vector<Raven_Door*>::iterator curDoor =m_pMap->GetDoors().begin();
  for (curDoor; curDoor != m_pMap->GetDoors().end(); ++curDoor)
  {
    (*curDoor)->Update();
  }

  //update any current projectiles
  std::list<Raven_Projectile*>::iterator curW = m_Projectiles.begin();
  while (curW != m_Projectiles.end())
  {
    //test for any dead projectiles and remove them if necessary
    if (!(*curW)->isDead())
    {
      (*curW)->Update();

      ++curW;
    }
    else
    {    
      delete *curW;

      curW = m_Projectiles.erase(curW);
    }   
  }
  
  //update the bots
  bool bSpawnPossible = true;
  
  std::list<Raven_Bot*>::iterator curBot = m_Bots.begin();
  for (curBot; curBot != m_Bots.end(); ++curBot)
  {
    //if this bot's status is 'respawning' attempt to resurrect it from
    //an unoccupied spawn point
    if ((*curBot)->isSpawning() && bSpawnPossible)
    {
      bSpawnPossible = AttemptToAddBot(*curBot);
    }
    
    //if this bot's status is 'dead' add a grave at its current location 
    //then change its status to 'respawning'
    else if ((*curBot)->isDead())
    {
      //create a grave
      m_pGraveMarkers->AddGrave((*curBot)->Pos());

      //change its status to spawning
      (*curBot)->SetSpawning();
    }

    //if this bot is alive update it.
    else if ( (*curBot)->isAlive())
    {
      (*curBot)->Update();
    }  
  } 

  //update the triggers
  m_pMap->UpdateTriggerSystem(m_Bots);

  //if the user has requested that the number of bots be decreased, remove
  //one
  if (m_bRemoveABot)
  { 
    if (!m_Bots.empty())
    {
      Raven_Bot* pBot = m_Bots.back();
      if (pBot == m_pSelectedBot)m_pSelectedBot=0;
      NotifyAllBotsOfRemoval(pBot);
      delete m_Bots.back();
      m_Bots.remove(pBot);
      pBot = 0;
    }

    m_bRemoveABot = false;
  }
}


//----------------------------- AttemptToAddBot -------------------------------
//-----------------------------------------------------------------------------
bool Raven_Game::AttemptToAddBot(Raven_Bot* pBot)
{
  //make sure there are some spawn points available
  if (m_pMap->GetSpawnPoints().size() <= 0)
  {
    ErrorBox("Map has no spawn points!"); return false;
  }

  //we'll make the same number of attempts to spawn a bot this update as
  //there are spawn points
  int attempts = m_pMap->GetSpawnPoints().size();

  while (--attempts >= 0)
  { 
    //select a random spawn point
    Vector2D pos = m_pMap->GetRandomSpawnPoint();

    //check to see if it's occupied
    std::list<Raven_Bot*>::const_iterator curBot = m_Bots.begin();

    bool bAvailable = true;

    for (curBot; curBot != m_Bots.end(); ++curBot)
    {
      //if the spawn point is unoccupied spawn a bot
      if (Vec2DDistance(pos, (*curBot)->Pos()) < (*curBot)->BRadius())
      {
        bAvailable = false;
      }
    }

    if (bAvailable)
    {  
      pBot->Spawn(pos);

      return true;   
    }
  }

  return false;
}

//-------------------------- AddBots --------------------------------------
//
//  Adds a bot and switches on the default steering behavior
//-----------------------------------------------------------------------------
void Raven_Game::AddBots(unsigned int NumBotsToAdd)
{ 
  while (NumBotsToAdd--)
  {
    //create a bot. (its position is irrelevant at this point because it will
    //not be rendered until it is spawned)
    Raven_Bot* rb = new Raven_Bot(this, Vector2D());

    //switch the default steering behaviors on
    rb->GetSteering()->WallAvoidanceOn();
    rb->GetSteering()->SeparationOn();

    m_Bots.push_back(rb);

    //register the bot with the entity manager
    EntityMgr->RegisterEntity(rb);

    
#ifdef LOG_CREATIONAL_STUFF
  debug_con << "Adding bot with ID " << ttos(rb->ID()) << "";
#endif
  }
}

//---------------------------- NotifyAllBotsOfRemoval -------------------------
//
//  when a bot is removed from the game by a user all remianing bots
//  must be notifies so that they can remove any references to that bot from
//  their memory
//-----------------------------------------------------------------------------
void Raven_Game::NotifyAllBotsOfRemoval(Raven_Bot* pRemovedBot)const
{
    std::list<Raven_Bot*>::const_iterator curBot = m_Bots.begin();
    for (curBot; curBot != m_Bots.end(); ++curBot)
    {
      Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                              SENDER_ID_IRRELEVANT,
                              (*curBot)->ID(),
                              Msg_UserHasRemovedBot,
                              pRemovedBot);

    }
}
//-------------------------------RemoveBot ------------------------------------
//
//  removes the last bot to be added from the game
//-----------------------------------------------------------------------------
void Raven_Game::RemoveBot()
{
  m_bRemoveABot = true;
}

//--------------------------- AddBolt -----------------------------------------
//-----------------------------------------------------------------------------
void Raven_Game::AddBolt(Raven_Bot* shooter, Vector2D target)
{
  Raven_Projectile* rp = new Bolt(shooter, target);

  m_Projectiles.push_back(rp);
  
  #ifdef LOG_CREATIONAL_STUFF
  debug_con << "Adding a bolt " << rp->ID() << " at pos " << rp->Pos() << "";
  #endif
}

//------------------------------ AddRocket --------------------------------
void Raven_Game::AddRocket(Raven_Bot* shooter, Vector2D target)
{
  Raven_Projectile* rp = new Rocket(shooter, target);

  m_Projectiles.push_back(rp);
  
  #ifdef LOG_CREATIONAL_STUFF
  debug_con << "Adding a rocket " << rp->ID() << " at pos " << rp->Pos() << "";
  #endif
}

//------------------------- AddRailGunSlug -----------------------------------
void Raven_Game::AddRailGunSlug(Raven_Bot* shooter, Vector2D target)
{
  Raven_Projectile* rp = new Slug(shooter, target);

  m_Projectiles.push_back(rp);
  
  #ifdef LOG_CREATIONAL_STUFF
  debug_con << "Adding a rail gun slug" << rp->ID() << " at pos " << rp->Pos() << "";
#endif
}

//------------------------- AddShotGunPellet -----------------------------------
void Raven_Game::AddShotGunPellet(Raven_Bot* shooter, Vector2D target)
{
  Raven_Projectile* rp = new Pellet(shooter, target);

  m_Projectiles.push_back(rp);
  
  #ifdef LOG_CREATIONAL_STUFF
  debug_con << "Adding a shotgun shell " << rp->ID() << " at pos " << rp->Pos() << "";
#endif
}


//----------------------------- GetBotAtPosition ------------------------------
//
//  given a position on the map this method returns the bot found with its
//  bounding radius of that position.
//  If there is no bot at the position the method returns NULL
//-----------------------------------------------------------------------------
Raven_Bot* Raven_Game::GetBotAtPosition(Vector2D CursorPos)const
{
  std::list<Raven_Bot*>::const_iterator curBot = m_Bots.begin();

  for (curBot; curBot != m_Bots.end(); ++curBot)
  {
    if (Vec2DDistance((*curBot)->Pos(), CursorPos) < (*curBot)->BRadius())
    {
      if ((*curBot)->isAlive())
      {
        return *curBot;
      }
    }
  }

  return NULL;
}

//-------------------------------- LoadMap ------------------------------------
//
//  sets up the game environment from map file
//-----------------------------------------------------------------------------
bool Raven_Game::LoadMap(const std::string& filename)
{  
  //clear any current bots and projectiles
  Clear();
  
  //out with the old
  delete m_pMap;
  delete m_pGraveMarkers;
  delete m_pPathManager;

  //in with the new
  m_pGraveMarkers = new GraveMarkers(script->GetDouble("GraveLifetime"));
  m_pPathManager = new PathManager<Raven_PathPlanner>(script->GetInt("MaxSearchCyclesPerUpdateStep"));
  m_pMap = new Raven_Map();

  //make sure the entity manager is reset
  EntityMgr->Reset();


  //load the new map data
  if (m_pMap->LoadMap(filename))
  { 
    AddBots(script->GetInt("NumBots"));
  
    return true;
  }

  return false;
}


//------------------------- ExorciseAnyPossessedBot ---------------------------
//
//  when called will release any possessed bot from user control
//-----------------------------------------------------------------------------
void Raven_Game::ExorciseAnyPossessedBot()
{
  if (m_pSelectedBot) m_pSelectedBot->Exorcise();
}


//-------------------------- ClickRightMouseButton -----------------------------
//
//  this method is called when the user clicks the right mouse button.
//
//  the method checks to see if a bot is beneath the cursor. If so, the bot
//  is recorded as selected.
//
//  if the cursor is not over a bot then any selected bot/s will attempt to
//  move to that position.
//-----------------------------------------------------------------------------
void Raven_Game::ClickRightMouseButton(POINTS p)
{
  Raven_Bot* pBot = GetBotAtPosition(POINTStoVector(p));

  //if there is no selected bot just return;
  if (!pBot && m_pSelectedBot == NULL) return;

  //if the cursor is over a different bot to the existing selection,
  //change selection
  if (pBot && pBot != m_pSelectedBot)
  { 
    if (m_pSelectedBot) m_pSelectedBot->Exorcise();
    m_pSelectedBot = pBot;

    return;
  }

  //if the user clicks on a selected bot twice it becomes possessed(under
  //the player's control)
  if (pBot && pBot == m_pSelectedBot)
  {
    m_pSelectedBot->TakePossession();

    //clear any current goals
    m_pSelectedBot->GetBrain()->RemoveAllSubgoals();
  }

  //if the bot is possessed then a right click moves the bot to the cursor
  //position
  if (m_pSelectedBot->isPossessed())
  {
    //if the shift key is pressed down at the same time as clicking then the
    //movement command will be queued
    if (IS_KEY_PRESSED('Q'))
    {
      m_pSelectedBot->GetBrain()->QueueGoal_MoveToPosition(POINTStoVector(p));
    }
    else
    {
      //clear any current goals
      m_pSelectedBot->GetBrain()->RemoveAllSubgoals();

      m_pSelectedBot->GetBrain()->AddGoal_MoveToPosition(POINTStoVector(p));
    }
  }
}

//---------------------- ClickLeftMouseButton ---------------------------------
//-----------------------------------------------------------------------------
void Raven_Game::ClickLeftMouseButton(POINTS p)
{
  if (m_pSelectedBot && m_pSelectedBot->isPossessed())
  {
    m_pSelectedBot->FireWeapon(POINTStoVector(p));
  }
}

//------------------------ GetPlayerInput -------------------------------------
//
//  if a bot is possessed the keyboard is polled for user input and any 
//  relevant bot methods are called appropriately
//-----------------------------------------------------------------------------
void Raven_Game::GetPlayerInput()const
{
  if (m_pSelectedBot && m_pSelectedBot->isPossessed())
  {
      m_pSelectedBot->RotateFacingTowardPosition(GetClientCursorPosition());
   }
}


//-------------------- ChangeWeaponOfPossessedBot -----------------------------
//
//  changes the weapon of the possessed bot
//-----------------------------------------------------------------------------
void Raven_Game::ChangeWeaponOfPossessedBot(unsigned int weapon)const
{
  //ensure one of the bots has been possessed
  if (m_pSelectedBot)
  {
    switch(weapon)
    {
    case type_blaster:
      
      PossessedBot()->ChangeWeapon(type_blaster); return;

    case type_shotgun:
      
      PossessedBot()->ChangeWeapon(type_shotgun); return;

    case type_rocket_launcher:
      
      PossessedBot()->ChangeWeapon(type_rocket_launcher); return;

    case type_rail_gun:
      
      PossessedBot()->ChangeWeapon(type_rail_gun); return;

    }
  }
}

//---------------------------- isLOSOkay --------------------------------------
//
//  returns true if the ray between A and B is unobstructed.
//------------------------------------------------------------------------------
bool Raven_Game::isLOSOkay(Vector2D A, Vector2D B)const
{
  return !doWallsObstructLineSegment(A, B, m_pMap->GetWalls());
}

//------------------------- isPathObstructed ----------------------------------
//
//  returns true if a bot cannot move from A to B without bumping into 
//  world geometry. It achieves this by stepping from A to B in steps of
//  size BoundingRadius and testing for intersection with world geometry at
//  each point.
//-----------------------------------------------------------------------------
bool Raven_Game::isPathObstructed(Vector2D A,
                                  Vector2D B,
                                  double    BoundingRadius)const
{
  Vector2D ToB = Vec2DNormalize(B-A);

  Vector2D curPos = A;

  while (Vec2DDistanceSq(curPos, B) > BoundingRadius*BoundingRadius)
  {   
    //advance curPos one step
    curPos += ToB * 0.5 * BoundingRadius;
    
    //test all walls against the new position
    if (doWallsIntersectCircle(m_pMap->GetWalls(), curPos, BoundingRadius))
    {
      return true;
    }
  }

  return false;
}


//----------------------------- GetAllBotsInFOV ------------------------------
//
//  returns a vector of pointers to bots within the given bot's field of view
//-----------------------------------------------------------------------------
std::vector<Raven_Bot*>
Raven_Game::GetAllBotsInFOV(const Raven_Bot* pBot)const
{
  std::vector<Raven_Bot*> VisibleBots;

  std::list<Raven_Bot*>::const_iterator curBot = m_Bots.begin();
  for (curBot; curBot != m_Bots.end(); ++curBot)
  {
    //make sure time is not wasted checking against the same bot or against a
    // bot that is dead or re-spawning
    if (*curBot == pBot ||  !(*curBot)->isAlive()) continue;

    //first of all test to see if this bot is within the FOV
    if (isSecondInFOVOfFirst(pBot->Pos(),
                             pBot->Facing(),
                             (*curBot)->Pos(),
                             pBot->FieldOfView()))
    {
      //cast a ray from between the bots to test visibility. If the bot is
      //visible add it to the vector
      if (!doWallsObstructLineSegment(pBot->Pos(),
                              (*curBot)->Pos(),
                              m_pMap->GetWalls()))
      {
        VisibleBots.push_back(*curBot);
      }
    }
  }

  return VisibleBots;
}

//---------------------------- isSecondVisibleToFirst -------------------------

bool
Raven_Game::isSecondVisibleToFirst(const Raven_Bot* pFirst,
                                   const Raven_Bot* pSecond)const
{
  //if the two bots are equal or if one of them is not alive return false
  if ( !(pFirst == pSecond) && pSecond->isAlive())
  {
    //first of all test to see if this bot is within the FOV
    if (isSecondInFOVOfFirst(pFirst->Pos(),
                             pFirst->Facing(),
                             pSecond->Pos(),
                             pFirst->FieldOfView()))
    {
      //test the line segment connecting the bot's positions against the walls.
      //If the bot is visible add it to the vector
      if (!doWallsObstructLineSegment(pFirst->Pos(),
                                      pSecond->Pos(),
                                      m_pMap->GetWalls()))
      {
        return true;
      }
    }
  }

  return false;
}

//--------------------- GetPosOfClosestSwitch -----------------------------
//
//  returns the position of the closest visible switch that triggers the
//  door of the specified ID
//-----------------------------------------------------------------------------
Vector2D 
Raven_Game::GetPosOfClosestSwitch(Vector2D botPos, unsigned int doorID)const
{
  std::vector<unsigned int> SwitchIDs;
  
  //first we need to get the ids of the switches attached to this door
  std::vector<Raven_Door*>::const_iterator curDoor;
  for (curDoor = m_pMap->GetDoors().begin();
       curDoor != m_pMap->GetDoors().end();
       ++curDoor)
  {
    if ((*curDoor)->ID() == doorID)
    {
       SwitchIDs = (*curDoor)->GetSwitchIDs(); break;
    }
  }

  Vector2D closest;
  double ClosestDist = MaxDouble;
  
  //now test to see which one is closest and visible
  std::vector<unsigned int>::iterator it;
  for (it = SwitchIDs.begin(); it != SwitchIDs.end(); ++it)
  {
    BaseGameEntity* trig = EntityMgr->GetEntityFromID(*it);

    if (isLOSOkay(botPos, trig->Pos()))
    {
      double dist = Vec2DDistanceSq(botPos, trig->Pos());

      if ( dist < ClosestDist)
      {
        ClosestDist = dist;
        closest = trig->Pos();
      }
    }
  }

  return closest;
}




    
//--------------------------- Render ------------------------------------------
//-----------------------------------------------------------------------------
void Raven_Game::Render()
{
  m_pGraveMarkers->Render();
  
  //render the map
  m_pMap->Render();

  //render all the bots unless the user has selected the option to only 
  //render those bots that are in the fov of the selected bot
  if (m_pSelectedBot && UserOptions->m_bOnlyShowBotsInTargetsFOV)
  {
    std::vector<Raven_Bot*> 
    VisibleBots = GetAllBotsInFOV(m_pSelectedBot);

    std::vector<Raven_Bot*>::const_iterator it = VisibleBots.begin();
    for (it; it != VisibleBots.end(); ++it) (*it)->Render();

    if (m_pSelectedBot) m_pSelectedBot->Render();
  }

  else
  {
    //render all the entities
    std::list<Raven_Bot*>::const_iterator curBot = m_Bots.begin();
    for (curBot; curBot != m_Bots.end(); ++curBot)
    {
      if ((*curBot)->isAlive())
      {
        (*curBot)->Render();
      }
    }
  }
  
  //render any projectiles
  std::list<Raven_Projectile*>::const_iterator curW = m_Projectiles.begin();
  for (curW; curW != m_Projectiles.end(); ++curW)
  {
    (*curW)->Render();
  }

 // gdi->TextAtPos(300, WindowHeight - 70, "Num Current Searches: " + ttos(m_pPathManager->GetNumActiveSearches()));

  //render a red circle around the selected bot (blue if possessed)
  if (m_pSelectedBot)
  {
    if (m_pSelectedBot->isPossessed())
    {
      gdi->BluePen(); gdi->HollowBrush();
      gdi->Circle(m_pSelectedBot->Pos(), m_pSelectedBot->BRadius()+1);
    }
    else
    {
      gdi->RedPen(); gdi->HollowBrush();
      gdi->Circle(m_pSelectedBot->Pos(), m_pSelectedBot->BRadius()+1);
    }


    if (UserOptions->m_bShowOpponentsSensedBySelectedBot)
    {
      m_pSelectedBot->GetSensoryMem()->RenderBoxesAroundRecentlySensed();
    }

    //render a square around the bot's target
    if (UserOptions->m_bShowTargetOfSelectedBot && m_pSelectedBot->GetTargetBot())
    {  
      
      gdi->ThickRedPen();

      Vector2D p = m_pSelectedBot->GetTargetBot()->Pos();
      double   b = m_pSelectedBot->GetTargetBot()->BRadius();
      
      gdi->Line(p.x-b, p.y-b, p.x+b, p.y-b);
      gdi->Line(p.x+b, p.y-b, p.x+b, p.y+b);
      gdi->Line(p.x+b, p.y+b, p.x-b, p.y+b);
      gdi->Line(p.x-b, p.y+b, p.x-b, p.y-b);
    }



    //render the path of the bot
    if (UserOptions->m_bShowPathOfSelectedBot)
    {
      m_pSelectedBot->GetBrain()->Render();
    }  
    
    //display the bot's goal stack
    if (UserOptions->m_bShowGoalsOfSelectedBot)
    {
      Vector2D p(m_pSelectedBot->Pos().x -50, m_pSelectedBot->Pos().y);

      m_pSelectedBot->GetBrain()->RenderAtPos(p, GoalTypeToString::Instance());
    }

    if (UserOptions->m_bShowGoalAppraisals)
    {
      m_pSelectedBot->GetBrain()->RenderEvaluations(5, 415);
    } 
    
    if (UserOptions->m_bShowWeaponAppraisals)
    {
      m_pSelectedBot->GetWeaponSys()->RenderDesirabilities();
    }

   if (IS_KEY_PRESSED('Q') && m_pSelectedBot->isPossessed())
    {
      gdi->TextColor(255,0,0);
      gdi->TextAtPos(GetClientCursorPosition(), "Queuing");
    }
  }
}
