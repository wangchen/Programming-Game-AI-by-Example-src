-- lua script to demonstrate exposing C++ functions to Lua using luaBind

-- Mat Buckland 2003

print("[lua]: About to call the C++ HelloWorld() function")

HelloWorld()


print("\n[lua]: About to call the C++ add() function")

a = 10
b = 5

print ("\n[lua]: "..a.." + "..b.." = "..add(a,b))