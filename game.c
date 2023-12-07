/* ------------------------------------------------------------------------------------
This game has 4 players. There is a banker and three other players. 
The banker rolls a pair of dice. Each of the player guesses the sum of the result. 
The banker has an initial capital of PhP 100,000.00. 
The players each has PhP 20,000.00. 
Every time a player guesses the resulting sum, a corresponding bet is placed. 
If the player guesses the right sum, the banker pays him/her with an amount equivalent to his/her bet. 
The money of the banker and the player must be updated. 
The game must terminate if the banker's money has dwindled down to PhP 10,000.00. 
It should also stop if there is only one player playing against the banker. 
You have to ask the player if he/she wants to continue the game or not. 
A player must stop playing if his/her money has dwindled down to PhP 100.00. 
Checks must be made by the program. A player cannot bet an amount that cannot be covered by his current money. 
If the total sum of the bets from the players exceeds the capital of the banker the players must re-enter bets.
------------------------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Create a structure whose that has the player data 
struct player_data
{
    int money;
    char name[12];
    int guess;
    int bet;
};

// Initally asks the player if they want to play
int dialogue() {
    char playerInput;
    printf("Press Y to start or Q to quit.\n");
    scanf("%c[\n]", &playerInput);
    switch (playerInput)
    {
    case 'Y': case 'y':
        return 1;
        break;
    
    case 'Q': case 'q':
        return 0; 

    default:
        return 0;
        break;
    }
}

// Prints an asterisk line
void printLine() {
    int i;
    for(i = 25; i > 0; i--) {
        printf("*");
    }
    printf("\n");
}

// Randomly generates two dice rolls
int sum_of_two_dice() {
    int i, n = 2, sum = 0, dice = 0;

    for(i = 1; i <= 2; i++) {
        dice = rand()%6 + 1;
        sum += dice;
        printf("One of the dice is: %d\n", dice);
    }

    printf("The sum of the dice is %i.\n", sum);

    return sum;
}

// Function to get the guess of the player and set the guess value inside the struct to the given value
void get_guesses(struct player_data *p) {
    int guessing = 1, guess;

     do
        {
        printf("Player %s try to guess the sum from 2 - 12.\n", p->name);
        scanf(" %i", &guess);

        if(guess >= 2 && guess <= 12) {
            guessing = 0;
        }
        else {
            printf("Invalid guess, please enter another guess.\n");
        }
    } while (guessing);
    p->guess = guess;
}

// Function to get the bet of the player and set the bet value inside the struct to the given value
void get_bets(struct player_data *p) {
    int bet, betting = 1;
        do {
             printf("Player %s, place a bet:\n", p->name);
            scanf(" %i", &bet);

            if (bet > p->money) {
                printf("Invalid amount, Please bet again.\n You have %i in your account.\n", p->money);
            }
            else {
                betting = 0;
            }

        } while (betting);

        p->bet = bet;
}

// We pass pointers to the values to be able edit the original values
void player_betting(int *banker, int *money_array[]) {

    int bet_array[3] = {0,0,0}, sum;

    // Loop until the players bet is equal to or less than the 
    do {
        sum = 0;
        //get_bets(money_array, bet_array);
        for(int i = 0; i < 3; i++) {
            sum += bet_array[i];
        }
        if (sum > *banker) {
            printf("The bets exceed the money of the banker.\n");
        }
    } while (sum > *banker);


}

/* Apparently you can't remove an element from an array in c.
So you have to create a custom function to create a new array*/
// Pass the array, size of the array, and the element you want to remove. 
void removeElement(struct player_data data_array[], int *size, int indexToRemove) {
    for (int i = indexToRemove; i < *size - 1; i++) {
        data_array[i] = data_array[i + 1];
    }
    (*size)--;
}

// Set the current array to the original values using a duplicate array.
void resetArray(struct player_data data_array[], struct player_data resetArray[], int array_size) {
    for (int i = 0; i < array_size; i++) {
        data_array[i] = resetArray[i];
    }
}

int main() {

    // Initalize the money for each player
    int guessed = 0, runGame = 0, betting = 1, bet_sum = 0;
    char playerInput;

    // Used to randomize the generated dice
    time_t t1; 
    
    // Create a custom struct for each player
    struct player_data player_one;
    struct player_data player_two;
    struct player_data player_three;
    struct player_data banker;
    
    // Initialize Money and player name
    banker.money = 100000;
    player_one.money = 20000;
    strcpy(player_one.name, "Harley"); 
    player_two.money = 20000;
    strcpy(player_two.name, "Venice");
    player_three.money = 20000;
    strcpy(player_three.name, "AJ");

    // Pass the custom structures to a struct array and have one has a reference array
    struct player_data data_array[3] = {player_one, player_two, player_three};
    struct player_data reset_array[3] = {player_one, player_two, player_three};
    int array_size = sizeof(data_array) / sizeof(data_array[0]);

    runGame = dialogue();
    // Main loop where we run the game and call functions for guessing and betting
    while (runGame) {

        // Used to randomize dice rolls for the rand() function
        srand ((unsigned)time(&t1)); 

        // Take each guess for each player
        for (int i = 0; i < array_size; i++) {
            get_guesses(&data_array[i]);
        }

        // Takes the bets of each player but checks player bet exceeds banker money.
        do {
            for (int i = 0; i < array_size; i++) {
                if (!(data_array[i].money <= 100)) {
                    get_bets(&data_array[i]);
                    bet_sum += data_array[i].money;
                }
            }

            if(!(bet_sum > banker.money)) {
                betting = 0;
            }
            else {
                printf("Overall bet is exceeds the bankers money (%i), please bet again.\n", banker.money);
            }
        } while (betting);

        printLine();
        int sum = sum_of_two_dice();
        printLine();

        for (int i = 0; i < 3; i++) {
            if (data_array[i].guess == sum) {
                guessed++;
                printf("Player %s guessed it right.\n", data_array[i].name);
                banker.money -= data_array[i].bet;
                data_array[i].money += data_array[i].bet;
                printLine();
                printf("The banker now has %i.\n", banker.money);
                printLine();
            }
            else {
                banker.money += data_array[i].bet;
                data_array[i].money -= data_array[i].bet;
            }
        }

        if(!guessed) {
            printf("No one guessed it right.\n");
        }

        printf("Money of each player and the banker is:\n");
        printf("Banker:%i\n", banker.money);
        for (int i = 0; i < array_size; i++) {
            printf("%s's money is: %i.\n",data_array[i].name, data_array[i].money);
        }
        printLine();
        
        int i = 0;
        while (i < array_size) {
            // Removes the player from the game if they have less than 100 money. 
            if (data_array[i].money <= 100) {
                printf("%s does not have enough money to play anymore.\n", data_array[i].name);
                removeElement(data_array, &array_size, i);
                i = 0;
            } else {
                i++;
            }

        }

        if (array_size > 1) {
            printf("Should we continue?\nPress Y to continue.\nPress R to restart.\nQ to quit.\n");
            scanf(" %c", &playerInput);

            switch (playerInput)
            {     
            case 'Y': case 'y':
                continue;   
            case 'R': case 'r':
                resetArray(data_array, reset_array, 3);
                banker.money = 100000;
                printf("Reseted the money");
                continue;
                
            case 'Q': case 'q':
                return 0;

            default:
                return 0;
            } 
        } 
        // If one player is left, then ask the player if they want to quit or reset the game
        else {
            printf("There is only one player left.\nPress R to restart the game.\nQ to quit.\n");
            
            scanf(" %c", &playerInput);
            switch (playerInput)
            {     
            case 'R': case 'r':
                resetArray(data_array, reset_array, 3);
                banker.money = 100000;
                printf("The money is reset.");
                continue;
                
            case 'Q': case 'q':
                return 0;

            default:
                return 0;
            }
        }
    }

    return 0;
}