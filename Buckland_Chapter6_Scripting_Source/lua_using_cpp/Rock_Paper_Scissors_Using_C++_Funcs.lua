
--Name:   rock_paper_scissors2.lua

--Author: Mat Buckland 2003

--Desc:   lua script to implement a rock paper scissors game

---------------------------------------------------------------
--[[ seed the random number generator ]]--

math.randomseed(os.time());

--[[these global variables will hold the scores of the player
  and the computer]]

user_score = 0;
comp_score = 0;



--[[    main game loop     ]]--

loop = true;
while loop == true do

    --let the user know the current score
    print("\n\nUser: "..user_score.." Computer: "..comp_score)

    print("Input your guess r/p/s  [enter q to quit]")

    --grab input from the user via the keyboard
    user_guess = io.stdin:read '*l';

    --create a table to convert user input into a play string
    local possible_moves = {s = "scissors", r = "rock", p = "paper"};
    
    if user_guess == "q" then

        loop = false;   --quit the game if user enters 'q'

    elseif (user_guess == "r") or (user_guess == "p") or (user_guess == "s") then 

        comp_guess = cpp_GetAIMove();

        --get the updated scores from the C++ function EvaluateTheGuesses
        user_score, comp_score = cpp_EvaluateTheGuesses(possible_moves[user_guess],
                                                        comp_guess,
                                                        user_score,
                                                        comp_score);

    else

        print ("Invalid input, try again");

    end   
end;






