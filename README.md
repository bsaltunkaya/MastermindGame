# MastermindGame
Simple command line Mastermind game, implemented completely in C++.
# How to play?
After configuration, you can play the game from the command line,
there are two modes you can set with the arguments.
# Rules of the game:
• A digit is a char element of this list = {0,1,2,3,4,5,6,7,8,9,a,b,c,d,e}
• A valid number is defined to be an N digit number (N ≤ 16) where the high-most (leftmost) digit cannot be 0
and any digit appears only once in the number.
• Your program chooses a valid number (secret number).
– First option is to generate a random number (it must be a valid number)
– Second option is to use a given number (a number will be provided as a command-line argument) • (At each turn) the code breaker (user) proposes a valid number. Turns are counted (Starting with 1).
• As response to the proposal, the code maker(your program) provides two counts:
– First count (Cexact): The count of digits of the proposed number that match in place of the secret number.
– Second count (Cmisplaced): The count of digits of the proposed number which do exist in the secret number but are not in place.
• A Cexact value of N stops the game and the turn-count is recorded; otherwise the game continues with accepting user proposals.
