
-------------------------------------------------------------------------------

-- create the GoHome state

-------------------------------------------------------------------------------
State_GoHome = {}


State_GoHome["Enter"] = function(miner)

  print ("[Lua]: Walkin home in the hot n' thusty heat of the desert")

end


State_GoHome["Execute"] = function(miner)

  print ("[Lua]: Back at the shack. yer siree!")

  if miner:Fatigued() then

    miner:GetFSM():ChangeState(State_Sleep)

  else

    miner:GetFSM():ChangeState(State_GoToMine)

  end

end

  
State_GoHome["Exit"] = function(miner)

  print ("[Lua]: Puttin' mah boots on n' gettin' ready for a day at the mine")

end



-------------------------------------------------------------------------------

-- create the Sleep state

-------------------------------------------------------------------------------

State_Sleep = {}


State_Sleep["Enter"] = function(miner)

  print ("[Lua]: Miner "..miner:Name().." is dozin off")

end


State_Sleep["Execute"] = function(miner)

  if miner:Fatigued() then

    print ("[Lua]: ZZZZZZ... ")

    miner:DecreaseFatigue()

  else

    miner:GetFSM():ChangeState(State_GoToMine)

  end

end

State_Sleep["Exit"] = function(miner)

  print ("[Lua]: Miner "..miner:Name().." is feelin' mighty refreshed!")

end


-------------------------------------------------------------------------------

-- create the GoToMine state

-------------------------------------------------------------------------------


State_GoToMine = {}


State_GoToMine["Enter"] = function(miner)

  print ("[Lua]: Miner "..miner:Name().." enters goldmine")

end


State_GoToMine["Execute"] = function(miner)

  miner:IncreaseFatigue()

  miner:AddToGoldCarried(2)

  print ("[Lua]: Miner "..miner:Name().." has got "..miner:GoldCarried().." nuggets")


  if miner:GoldCarried() > 4 then
  
    print ("[Lua]: Miner "..miner:Name().." decides to go home, with his pockets full of nuggets")

    miner:GetFSM():ChangeState(State_GoHome)

  end

end


State_GoToMine["Exit"] = function(miner)

  print ("[Lua]: Miner "..miner:Name().." exits goldmine")

  end




 