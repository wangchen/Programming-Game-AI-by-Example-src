-- lua script to demonstrate global variables

--global string and number types

name   = "Spiderman";
age    = 29;


--global table creation

simple_table = {name="Dan Dare", age=20};


--a simple function to add two numbers

function add(a,b)
    
    return (a+b);

end;

 
print("[lua]: Finished running script \"cpp_using_lua.lua\"");