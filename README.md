# CMSC 11 project

## The game is called 7-11 and it goes like this:

This game has 4 players. There is a banker and three other players. 
The banker rolls a pair of dice. 🎲🎲 Each of the players try to guess the sum and bet on it. 

## The general game setup
1. The banker has an initial capital of PhP 100,000.00. 
1. The players each has PhP 20,000.00. 
1. Every time a player guesses the resulting sum, a corresponding bet is placed. 
1. If the player guesses the right sum, the banker pays him/her with an amount equivalent to his/her bet. 
1. The money of the banker and the player must be updated. 

## Terminate conditions
1. The game must terminate if the banker's money has dwindled down to PhP 10,000.00. 
1. It should also stop if there is only one player playing against the banker. 
1. You have to ask the player if he/she wants to continue the game or not. 
1. A player must stop playing if his/her money has dwindled down to PhP 100.00. 

### Finer details
1. Checks must be made by the program. A player cannot bet an amount that cannot be covered by his current money. 
1. If the total sum of the bets from the players exceeds the capital of the banker the players must re-enter bets.
