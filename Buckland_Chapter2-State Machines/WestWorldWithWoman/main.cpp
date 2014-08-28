#include <fstream>
#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"



std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //create a miner
  Miner Bob(ent_Miner_Bob);

  //create his wife
  MinersWife Elsa(ent_Elsa);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<20; ++i)
  { 
    Bob.Update();
    Elsa.Update();

    Sleep(800);
  }

  //wait for a keypress before exiting
  PressAnyKeyToContinue();

  return 0;
}






