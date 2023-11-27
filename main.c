#include <stdio.h>      // printf(), scanf()
#include <stdlib.h>     // srand(), rand(), system(), Pause()
#include <time.h>       // time()

#define CMD_SIZE 80;

void init();
void menu();
void game();
void rules();
void coop();
void board(char *combinations, int *tips, int life);
char intToChar(int monInt);
void bufferManager();

//  Fonction principale.
int main(int argc, char *argv[]) {
    menu();
    return 0;
}

//  Procédure de rafraichissement de la console et d'affichage du header.
void init() {
    system("cls");
    int i;
    for (i = 0; i < (80 - 22) / 2; i++) printf(" ");
    printf("|                    |\n");
    for (i = 0; i < (80 - 22) / 2; i++) printf(" ");
    printf("|     Mastermind     |\n");
    for (i = 0; i < (80 - 22) / 2; i++) printf(" ");
    printf("|____________________|\n\n\n");
}

void menu() {
    int i, choice = 0;
    //  Boucle principale du programme.
    do {
        init();
        printf("\n");
        for (i = 0; i < 36; i++) printf(" ");
        printf("1 - Play\n");
        for (i = 0; i < 36; i++) printf(" ");
        printf("2 - Rules\n");
        for (i = 0; i < 36; i++) printf(" ");
        printf("0 - Exit\n\n\n");
        if (!(choice != 1 && choice != 2 && choice != 0)) { // Condition de détection d'une erreur.
            for (i = 0; i < 29; i++) printf(" ");
            printf("Please, make a choice :\n\n");
        } else {
            for (i = 0; i < 25; i++) printf(" ");
            printf("Please, make a CORRECT choice :\n\n");
        }
        for (i = 0; i < 39; i++) printf(" ");
        if (!scanf("%d", &choice)) choice = -1; // Condition de détection d'une erreur.
        bufferManager();
        switch (choice) {
            case 1 :
                game();
                choice = 0;
            break;
            case 2 :
                rules();
            break;
            case 0 :
            break;
            default :
            break;
        }
    } while (choice);
}

//  Procédure d'affichage des règles.
void rules() {
    init();
    printf(" Mastermind is a code-breaking game.\n");
    printf(" The goal is to discover the four-digit code by successively trying combinations of 6 colors.\n\n");
    printf(" Use the clues placed under each code after submit.\n");
    printf(" Read the instructions to understand the software.\n");
    printf(" Every time you submit a combination, you can see\n how many well-placed and how many missplaced you have.\n");
    printf(" You can see the board by writting S.\n\n");
    printf(" You win when you get 4 characters well-placed.\n");
    printf(" You lose if you don't break the code after 8 tests, when your life reaches 0.\n\n");
    system("pause");
}

//  Procédure de jeu.
void game() {
    srand(time(NULL));
    char input;
    char copyAnswer[4];
    char answer[4];
    char combinations[8][4];
    int life = 8;
    int tips[8][2];
    int i, j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 2; j++) {
            tips[i][j] = 0;
        }
    }
    // Mode 1 ou 2 joueurs
    do {
        init();
        if (i == -1) {
            for (i = 0; i < 25; i++) printf(" ");
            printf("Please, make a CORRECT choice :\n\n");
        }
        for (i = 0; i < 40 - 11; i++) printf(" ");
        printf("1 Player or 2 Players ?\n\n");
        for (i = 0; i < 39; i++) printf(" ");
        if (!scanf("%1d", &i)) i = -1;
        bufferManager();
        if (i == 1) { //  Mode 1 joueur.
            for (j = 0; j < 4; j++) {
                answer[j] = intToChar(rand() % 4);
            }
        } else if (i == 2) { //  Mode 2 joueurs.
            do {
                init();
                printf("Player 2 :\nPlease, enter a 4 characters code color.\n\n");
                printf("\t(R)ed\t(Y)ellow\n");
                printf("\t(G)reen\t(C)yan\n");
                printf("\t(B)lue\t(M)agenta\n");
                printf("\nYour code : ");
                scanf("%s", answer);
            } while (0); // sécurité !
        } else {
            i = -1;
        }
    } while (i != 1 && i != 2);
    //  Boucle secondaire du programme <=> Boucle principale de game.
    do {
        init();
        printf("life = %d.\n\n", life);
        printf("Player 1 :\nPlease, enter a 4 characters code color.\n\n");
        printf("\t(R)ed\t(Y)ellow\n");
        printf("\t(G)reen\t(C)yan\n");
        printf("\t(B)lue\t(M)agenta\n");
        printf("\nYour code : ");
        scanf("%s", combinations[8 - life]);
        scanf("%c", &input); // on vide le buffer : on élimine le '\0'.
        for (i = 0; i < 4; i++) { // recherche well-placed
            copyAnswer[i] = answer[i];
            if (combinations[8 - life][i] == copyAnswer[i]) {
                tips[8 - life][0]++;
                copyAnswer[i] = ' ';
            }
        }
        // on ne peut pas combiner cette for avec la précédente.
        for (i = 0; i < 4; i++) { // recherche missplaced
            if (copyAnswer[i] != ' ') {
                for (j = 0; j < 4; j++) {
                    if (combinations[8 - life][i] == copyAnswer[j]) {
                        tips[8 - life][1]++;
                        j = 4;
                    }
                }
            }
        }
        printf("\nThere is %d well-placed and %d missplaced !\n\n", tips[8 - life][0], tips[8 - life][1]);
        if (tips[8 - life][0] == 4) {
            init();
            printf("Congratulation ! You won !\n\n");
        } else if (life - 1 == 0) {
            init();
            printf("life = 0.\n\n");
            printf("Sorry, You lose...\n\n");
            life--;
        } else {
            life--;
        }
        printf("What do you want to do ? (E)xit, (C)ontinue, (S)ee the board.\n");
        scanf("%c", &input);
        switch (input) {
            case 'E' :
                life = 0;
                init();
            break;
            case 'S' :
                board(&combinations[0][0], &tips[0][0], life);
            break;
            default :
            break;
        }
    } while (!(combinations[8 - life][0] == answer[0] && combinations[8 - life][1] == answer[1] && combinations[8 - life][2] == answer[2] && combinations[8 - life][3] == answer[3]) && life != 0);
    printf("The code was : ");
    for (i = 0; i < 4; i++) {
        printf("%c", answer[i]);
    }
    printf("\n\n");
    system("pause");
}

//  Gère l'affichage du tableau spécifié dans le cahier des charges.
void board(char *combinations, int *tips, int life) {
    init();
    int i, j;
    for (i = 0; i < 40 - 11; i++) printf(" ");
    printf("%c", 201);
    for (i = 0; i < 20; i++) printf("%c", 205);
    printf("%c\n", 187);
    for (j = 0; j < 8 - life; j++) {
        for (i = 0; i < 40 - 11; i++) printf(" ");
        printf("%c ", 186);
        for (i = 0; i < 4; i++) printf("%c", combinations[4 * j + i]);
        printf("  WP: %d  MP: %d ", tips[2 * j], tips[2 * j + 1]);
        printf("%c\n", 186);
        for (i = 0; i < 40 - 11; i++) printf(" ");
        printf("%c", 186);
        for (i = 0; i < 20; i++) printf(" ");
        printf("%c\n", 186);
    }
    for (i = 0; i < 40 - 11; i++) printf(" ");
    printf("%c", 200);
    for (i = 0; i < 20; i++) printf("%c", 205);
    printf("%c\n\n", 188);
    system("pause");
}

//  Convertit chaque entier au caractère qui lui correspond.
char intToChar(int monInt) {
    switch (monInt) {
        case 0 :
            return 'R';
        break;
        case 1 :
            return 'G';
        break;
        case 2 :
            return 'B';
        break;
        case 3 :
            return 'Y';
        break;
        case 4 :
            return 'C';
        break;
        case 5 :
            return 'M';
        break;
    }
}

void bufferManager() {
    scanf ("%*[^\n]");
    getchar ();
}
