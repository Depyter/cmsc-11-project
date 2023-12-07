for (int i = 0; i < array_size; i++) {
            // Removes the player from the game if they have less than 100 money. 
            printf("i");
            if (data_array[i].money <= 100) {
                printf("%s does not have enough money to play anymore.\n", data_array[i].name);
                removeElement(data_array, &array_size, i);

                i = 0;
            }
        }