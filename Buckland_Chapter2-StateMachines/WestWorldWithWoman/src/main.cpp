#include <unistd.h>

#include <fstream>
#include <iostream>

#include "EntityNames.h"
#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"

int main()
{
  //create a miner
  Miner Bob(ent_Miner_Bob);

  //create his wife
  MinersWife Elsa(ent_Elsa);

  //run Bob and Elsa through a few Update calls
  for (int i = 0; i < 20; ++i) {
    Bob.Update();
    Elsa.Update();

    sleep(1);
  }

  return 0;
}
