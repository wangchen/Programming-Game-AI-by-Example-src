#include <unistd.h>
#include <iostream>

#include "EntityNames.h"
#include "Locations.h"
#include "Miner.h"

int main()
{
  //create a miner
  Miner miner(ent_Miner_Bob);

  //simply run the miner through a few Update calls
  for (int i = 0; i < 20; ++i) {
    miner.Update();
    sleep(1);
  }

  return 0;
}
