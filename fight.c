#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    char nameme[10];
    char namethem[10];
    int playerHP = 100;
    int monsterHP = 100;
    int mana = 50;
    int action = 0;
    int * prob = malloc(2 * sizeof(int));
    if (prob == NULL)
    {
        printf("Memory Allocation failed!\n");
        return 1;
    }

    printf("Welcome to fight.c!\nWhat's is your name?\n");
    scanf("%9s", nameme);
    printf("What's enemy name you want?\n");
    scanf("%9s", namethem);

    srand(time(NULL));

    while (playerHP > 0 && monsterHP > 0)
    {
        printf("%s's HP = %d\n%s's HP = %d\n%s's Mana = %d\nChoose your actions! (1 for Attack (Deal 15) 2 for Heal (Recover 5 HP) 3 for cast Magic(Mana Cost: 20))(Critical Chance = 30%%)\n", nameme , playerHP, namethem , monsterHP, nameme, mana);
        scanf("%d", &action);

        prob[0] = rand() % 100;

        if (action == 1 && prob[0] > 30)
        {
            monsterHP = monsterHP - 15;
            printf("%s dealed 15 damage!\n", nameme);

            action = 0;
        }
        else if (action == 1 && prob[0] <= 30)
        {
            printf("%s dealed critical damage!\n", nameme);
            monsterHP = monsterHP - 30;
            printf("%s dealed 30 damage\n", nameme);

            action = 0;
        }
        else if (action == 2)
        {
            playerHP = playerHP + 5;
            mana = mana + 5;
            printf("%s healed 5 HP!\n", nameme);

            action = 0;
        }
        else if (action == 3 && mana >= 20)
        {
            mana = mana - 20;
            monsterHP = monsterHP - 50;
            printf("%s cast magic and dealed 50 magic damage!\n", nameme);

            action = 0;
        }
        else if (action == 3 && mana < 20)
        {
            printf("Too bad!\n%s don't have enough mana to cast!\n", nameme);

            action = 0;
        }
        else if (action != 0 && action != 1 && action != 2 && action != 3)
        {
            printf("%s missed chance, you better choose carefully next time!\n", nameme);

            action = 0;
        }

        if (playerHP <= 0 || monsterHP <= 0)
        {
            break;
        }

        prob[1] = rand() % 100;
        
        if (prob[1] < 65 && prob[1] >= 15)
        {
            playerHP = playerHP - 10;
            printf("%s chooses Attack\n%s take 10 damage\n", namethem, nameme);
        }
        else if (prob[1] < 15)
        {
            playerHP = playerHP - 20;
            printf("%s chooses Attack and deal critical damage!\n%s take 20 damage\n", namethem, nameme);
        }
        else if (prob[1] >= 65)
        {
            monsterHP = monsterHP + 10;
            printf("%s chooses Heal\n%s heal 10 HP\n", namethem, namethem);
        }

        if (playerHP <= 0 || monsterHP <= 0)
        {
            break;
        }
    }
    free(prob);
    prob = NULL;

    if (monsterHP <= 0)
    {
        printf("You Win!\n");
    }
    else
    {
        printf("You lose\n");
    }
    return 0;
}
