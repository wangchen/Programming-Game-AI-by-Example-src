
-----------------------------Lua script to define the class: Animal

class 'Animal'

function Animal:__init(num_legs, noise_made)

    self.NoiseMade = noise_made
    self.NumLegs = num_legs

end

function Animal:Speak()

    print(self.NoiseMade)

end

function Animal:GetNumLegs()

    return self.NumLegs

end


-------------------------------- example of use

cat = Animal(4, "meow")

cat:Speak()

print ("a cat has "..cat:GetNumLegs().." legs")



------------------------------- an example of a derived class

class 'Pet' (Animal)

function Pet:__init(name, num_legs, noise_made) super(num_legs, noise_made)

    self.Name = name

end

function Pet:GetName()

    return self.Name

end

---------------------------------and an example of use

dog = Pet("Albert", 4, "woof")

dog:Speak()

print ("my dogs name is "..dog:GetName())