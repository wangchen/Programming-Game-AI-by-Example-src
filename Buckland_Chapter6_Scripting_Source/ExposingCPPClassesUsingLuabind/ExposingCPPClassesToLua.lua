-- ExposingCPPClassesToLua.lua

--create an animal object and call its methods

cat = Animal("Meow", 4);

print ("\n[Lua]: A cat has "..cat:NumLegs().. " legs.");

cat:Speak();


print ("\n\n----------------------------------------------------");

MyPet = Pet("Scooter", "Meow", 4);

print ("\n[Lua]: My pet is called "..MyPet:GetName());

MyPet:Speak(); 