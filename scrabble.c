#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/print_board.h"
#include "util/scrabble.h"

#define SIZE 15
#define SIZE_Alfabet 26
char game_board[SIZE][SIZE];
int scor_litere[SIZE_Alfabet];



//citeste un numar aflat singur pe o linie
int citeste_N(){
    char str[10];
    fgets(str, 10, stdin);
    if (str[strlen(str) - 1] == '\n'){
        str[strlen(str) - 1] = '\0';
    }
    return atoi(str);
}


//citeste un string aflat pe o linie
char *citeste_string(char str[], int nr){
    fgets(str, nr, stdin);
    if (str[strlen(str) - 1] == '\n'){
        str[strlen(str) - 1] = '\0';
    }
    return str;
}


//codeaza coordonatele, directia si
char *code_line(char linie[SIZE + 8], int Y, int X, 
int D, char cuvant[]){
    if (Y > 9){
        linie[0] = Y / 10 + '0';
        linie[1] = Y % 10 + '0';
        linie[2] = ' ';
        if (X > 9){
            linie[3] = X / 10 + '0';
            linie[4] = X % 10 + '0';
            linie[5] = ' ';
            linie[6] = D + '0';
            linie[7] = ' ';
            linie[8] = '\0';
        } else {
            linie[3] = X + '0';
            linie[4] = ' ';
            linie[5] = D + '0';
            linie[6] = ' ';
            linie[7] = '\0';
        }
    } else {
        linie[0] = Y + '0';
        linie[1] = ' ';
        if (X > 9){
            linie[2] = X / 10 + '0';
            linie[3] = X % 10 + '0';
            linie[4] = ' ';
            linie[5] = D + '0';
            linie[6] = ' ';
            linie[7] = '\0';
        } else {
            linie[2] = X + '0';
            linie[3] = ' ';
            linie[4] = D + '0';
            linie[5] = ' ';
            linie[6] = '\0';
        }
    }

    strcat(linie, cuvant);
    
    return linie;
}

//scrierea cuvantului in locul indicat si pe 
//directia indicata:
void scrie_cuvant(char linie[]){
    unsigned int i;
    int Y, X, D;
    char cuvant[SIZE];

    Y = atoi(strtok(linie, " "));
    X = atoi(strtok(NULL, " "));
    D = atoi(strtok(NULL, " "));

    //am folosit un pointer p deoarece cuvant
    //nu putea fi folosit in strtok pentru ca nu este
    //un pointer a carui valoare o pot modifica
    char *p;
    p = strtok(NULL, " ");
    strcpy(cuvant, p);

    if (D == 0){
        for (i = X; i < X + strlen(cuvant); i++){
            game_board[Y][i] = cuvant[i-X];
        }
    } else {
        for (i = Y; i < Y + strlen(cuvant); i++){
            game_board[i][X] = cuvant[i-Y];
        }
    }

}


//initializeaza vectorul de scor cu valorile date:
void set_scor(){
    unsigned int i;
    char str[11];

    strcpy(str, "AEILNORSTU");
    for (i = 0; i < strlen(str); i++){
        scor_litere[str[i] - 'A'] = 1;
    }

    scor_litere['D' - 'A'] = 2;
    scor_litere['G' - 'A'] = 2;

    strcpy(str, "BCMP");
    for (i = 0; i < strlen(str); i++){
        scor_litere[str[i] - 'A'] = 3;
    }

    strcpy(str, "FHVWY");
    for (i = 0; i < strlen(str); i++){
        scor_litere[str[i] - 'A'] = 4;
    }

    scor_litere['K' - 'A'] = 5;

    scor_litere['J' - 'A'] = 8;
    scor_litere['X' - 'A'] = 8;

    scor_litere['Q' - 'A'] = 10;
    scor_litere['Z' - 'A'] = 10;
}


//calculeaza scorul unui cuvant:
int scor_cuv(char str[]){
    set_scor();
    int scor = 0;
    unsigned int i;

    for (i = 0; i < strlen(str); i++){
        scor += scor_litere[str[i] - 'A'];
    }
    return scor;
}


//calculeaza scorul final al unui cuvant cu tot cu
//bonusuri:
int scor_final_cuv(char cuvant[], int Y, int X, int D,
char str_X2[], char str_X3[]){

    unsigned int i;

    int scor = scor_cuv(cuvant);
    char *p;

    p = strstr(cuvant, str_X2);
    if (p != NULL){
        if (D == 0){
            for (i = X; i < X + strlen(cuvant); i++){
                if (bonus_board[Y][i] == 1){
                    scor = scor * 2;
                }
            }
        } else {
            for (i = Y; i < Y + strlen(cuvant); i++){
                if (bonus_board[i][X] == 1){
                    scor = scor * 2;
                }
            }
        }
    }

    
    if (strcmp(cuvant + strlen(cuvant) - 2, str_X3) == 0){
        if (D == 0){
            for (i = X; i < X + strlen(cuvant); i++){
                if (bonus_board[Y][i] == 2){
                    scor = scor * 3;
                }
            }
        } else {
            for (i = Y; i < Y + strlen(cuvant); i++){
                if (bonus_board[i][X] == 2){
                    scor = scor * 3;
                }
            }
        }
    }
    return scor;
}

//Calculeaza scorul pentru fiecare player
int scor_final_player(int player, char linii_jucate[100][SIZE + 8], 
int N, char str_X2[], char str_X3[]){

    int scor, scor_final = 0;
    int i;

    int Y, X, D;
    char cuvant[SIZE];
    if (player == 1){
        for (i = 0; i < N; i = i + 2){

            Y = atoi(strtok(linii_jucate[i], " "));
            X = atoi(strtok(NULL, " "));
            D = atoi(strtok(NULL, " "));

            //am folosit un pointer p deoarece cuvant
            //nu putea fi folosit in strtok pentru ca nu este
            //un pointer a carui valoare o pot modifica
            char *p;
            p = strtok(NULL, " ");
            strcpy(cuvant, p);

            scor = scor_final_cuv(cuvant, Y, X, D, str_X2, str_X3);
            scor_final += scor;
        }
    }

    if (player == 2){
        for (i = 1; i < N; i = i + 2){
            Y = atoi(strtok(linii_jucate[i], " "));
            X = atoi(strtok(NULL, " "));
            D = atoi(strtok(NULL, " "));

            //am folosit un pointer p deoarece cuvant
            //nu putea fi folosit in strtok pentru ca nu este
            //un pointer a carui valoare o pot modifica
            char *p;
            p = strtok(NULL, " ");
            strcpy(cuvant, p);

            scor = scor_final_cuv(cuvant, Y, X, D, str_X2, str_X3);
            scor_final += scor;
        }
    }
    return scor_final;
}


//verifica daca un cuvant a fost jucat sau nu:
int verf_jucat(char cuvant[], 
char cuvinte_jucate[100][SIZE], int N){
    int i;

    for (i = 0; i < N; i++){
        if (strcmp(cuvant, cuvinte_jucate[i]) == 0){
            return 0;
        }
    }
    return 1;
}


//pune doar '.' in fiecare loc de pe tabla:
void task_0(){
    int i, j;
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            game_board[i][j] = '.';
        }
    }
}


//scrie cuvintele pe tabla
void task_1(){
    task_0();
    int N;

    N = citeste_N();

    char linie[SIZE + 6];
    int k;

    for (k = 0; k < N; k++){
        //am folosit un sir de caractere linie pe care
        //l-am divizat folosind functia strtok
        strcpy(linie, citeste_string(linie, SIZE + 6));
        
        scrie_cuvant(linie);

    }
    print_board(game_board);
}


//calculeaza scorul fiecarui player fara bonusuri
void task_2(){
    int Player1_scor, Player2_scor;

    int N;
    
    N = citeste_N();

    char linie[SIZE + 6];
    char cuvant[SIZE];
    int k;
    char *p;

    Player1_scor = 0;
    Player2_scor = 0;

    for (k = 0; k < N; k++){
        //am folosit un sir de caractere linie pe care
        //l-am divizat folosind functia strtok
        strcpy(linie, citeste_string(linie, SIZE + 6));
        
        //am folosit un pointer p deoarece cuvant
        //nu putea fi folosit in strtok pentru ca nu este
        //un pointer a carui valoare o pot modifica
        p = strtok(linie, " ");
        p = strtok(NULL, " ");
        p = strtok(NULL, " ");

        p = strtok(NULL, " ");
        strcpy(cuvant, p);

        if (k % 2 == 0){
            Player1_scor += scor_cuv(cuvant);
        } else {
            Player2_scor += scor_cuv(cuvant);
        }
    }

    printf("Player 1: %d Points\n", Player1_scor);
    printf("Player 2: %d Points\n", Player2_scor);
}


//calculeaza scorul fiecarui player cu bonusuri
void task_3(){

    //citeste stringul pentru bonus X2
    char str_X2[10];
    strcpy(str_X2, citeste_string(str_X2, 10));

    //citeste stringul pentru bonus X3
    char str_X3[10];
    strcpy(str_X3, citeste_string(str_X3, 10));

    int N;

    N = citeste_N();

    int k;
    //am folosit un vector de linii jucate pentru a inregistra
    //aceste linii si a folosi datele in functia scor_final_player
    char linii_jucate[100][SIZE + 8];

    for (k = 0; k < N; k++){
        strcpy(linii_jucate[k], citeste_string(linii_jucate[k], SIZE + 6));
    }

    printf("Player 1: %d Points\n", 
    scor_final_player(1, linii_jucate, N, str_X2, str_X3));
    printf("Player 2: %d Points\n", 
    scor_final_player(2, linii_jucate, N, str_X2, str_X3));
}


// verifica daca un cuvant din words poate fi scris:
// (cuvant o sa fie luat din words)
// intoarce -1 daca nu se poate scrie cuvantul respectiv
// intoarce 0 daca se poate scrie pe orizontala
// intoarce 1 daca se poate scrie pe verticala
int verf_cuvant(char cuvant[], int Y, int X){
    int i;

    //verifica daca are prima litera cea dorita
    if (cuvant[0] != game_board[Y][X]){
        return -1;
    }

    //verifica daca incape in tabla
    if (strlen(cuvant) > (unsigned)(SIZE - X) && strlen(cuvant) > (unsigned)(SIZE - Y)){
        return -1;
    }

    //daca incape pe orizontala si nu are se suprapune atunci
    //OK ramane 0, daca se suprapune OK devine 1
    int OK = -1;
    if (strlen(cuvant) <= (unsigned)(SIZE - X)){
        OK = 0;
        for (i = 1; (unsigned)i < strlen(cuvant) && OK == 0; i++){
            if (game_board[Y][X + i] != '.'){
                OK = -1;
            }
        }
    } 

    //daca nu a incaput pe orizontala, dar incape pe verticala si
    //nu se suprapune atunci OK ramane 1, dar daca se suprapune atunci
    //OK devine -1
    if (strlen(cuvant) <= (unsigned)(SIZE - Y) && OK == -1){
        OK = 1;
        for (i = 1; (unsigned)i < strlen(cuvant) && OK == 1; i++){
            if (game_board[Y + i][X] != '.'){
                OK = -1;
            }
        }
    }
    return OK;
}


//scrie cuvantul pentru playerul 2 pentru task 4
void alege_cuvant_task_4(char cuvinte_jucate[100][SIZE], int N){
    int i = 0, j = -1, k = -1;
    int OK = 0;
    int control;

    while (k < 100 && OK == 0){
        k++;

        //verific daca a mai fost scris cuvantul:
        //control = 1 cuvantul nu a mai fost scris
        //control = 0 cuvantul a mai fost scris
        control = verf_jucat(words[k], cuvinte_jucate, N);

        if (control){
            i = 0;
            j = -1;

            while (i < SIZE && OK == 0){
                j++;

                if (j >= SIZE){
                    j = -1;
                    i++;
                }

                if (words[k][0] == game_board[i][j] && 
                verf_cuvant(words[k], i, j) > -1){

                    OK = 1;
                }
            }
        }
    }

    char linie[SIZE + 8];
    strcpy(linie, code_line(linie, i, j, 
    verf_cuvant(words[k], i, j), words[k]));
    scrie_cuvant(linie);
}


//face citirea si scrie cuvantul potrivit pentru player 2
void task_4(){
    task_0();
    int N;

    //citeste stringul pentru bonus X2
    char str_X2[10];
    strcpy(str_X2, citeste_string(str_X2, 10));

    //citeste stringul pentru bonus X3
    char str_X3[10];
    strcpy(str_X3, citeste_string(str_X3, 10));

    N = citeste_N();

    char linie[SIZE + 8];
    char linie_help[SIZE + 8];
    char cuvant[SIZE];
    int k;
    char cuvinte_jucate[100][SIZE];
    char *p;
    
    for (k = 0; k < N; k++){
        //am folosit un sir de caractere linie pe care
        //l-am divizat folosind functia strtok
        strcpy(linie, citeste_string(linie, SIZE + 6));
        strcpy(linie_help, linie);
        scrie_cuvant(linie_help);

        p = strtok(linie, " ");
        p = strtok(NULL, " ");
        p = strtok(NULL, " ");

        //am folosit un pointer p deoarece cuvant
        //nu putea fi folosit in strtok pentru ca nu este
        //un pointer a carui valoare o pot modifica
        p = strtok(NULL, " ");
        strcpy(cuvant, p);
        
        strcpy(cuvinte_jucate[k], cuvant);

    }

    alege_cuvant_task_4(cuvinte_jucate, N);
    print_board(game_board);
}

void alege_cuvant_task_5(char cuvinte_jucate[100][SIZE], int N,
 int diferenta_scor, char str_X2[], char str_X3[]){

    int i = 0, j = -1, k = -1;
    int OK = 0;
    int control;

    //cuvant_maxim = cuvantul cu punctaj maxim:
    char cuvant_maxim[SIZE] = "\0";

    //pozitia pentru acest punctaj maxim:
    int i_max = -1, j_max = -1;

    //directia pe care ar trebui scris:
    int D_max;

    //scor maxim obtinut:
    int scor_maxim = 0;

    //posibil scor maxim:
    int scor_obtinut;

    //directia pentru cuvintele testate:
    int D;

    for (k = 0; k < 100; k++){
        
        //verific daca a mai fost scris cuvantul:
        //control = 1 cuvantul nu a mai fost scris
        //control = 0 cuvantul a mai fost scris
        control = verf_jucat(words[k], cuvinte_jucate, N);

        //daca nu a mai fost jucat
        if (control){

            for (i = 0; i < SIZE; i++){
                for (j = 0; j < SIZE; j++){
                   
                    if (words[k][0] == game_board[i][j] && 
                    verf_cuvant(words[k], i, j) > -1){
                        D = verf_cuvant(words[k], i, j);

                        if (scor_final_cuv(words[k], i, j, D,
                        str_X2, str_X3) >= diferenta_scor){

                            OK = 1;

                            scor_obtinut = scor_final_cuv(words[k], 
                            i, j, D, str_X2, str_X3);

                            if (scor_obtinut > scor_maxim){
                                scor_maxim = scor_obtinut;
                                i_max = i;
                                j_max = j;
                                D_max = D;
                                strcpy(cuvant_maxim, words[k]);
                            } else {
                                if (scor_obtinut == scor_maxim){
                                    if (i < i_max){
                                        i_max = i;
                                        j_max = j;
                                        D_max = D;
                                        strcpy(cuvant_maxim, words[k]);
                                    } else {
                                        if (i == i_max && j < j_max){
                                            i_max = i;
                                            j_max = j;
                                            D_max = D;
                                            strcpy(cuvant_maxim, words[k]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    char linie[SIZE + 8];

    if (OK == 1){
        strcpy(linie, code_line(linie, i_max, j_max, D_max, cuvant_maxim));
        scrie_cuvant(linie);
        print_board(game_board);
    } else {
        printf("Fail!\n");
    }
}


void task_5(){
    task_0();
    int N;

    //citeste stringul pentru bonus X2
    char str_X2[10];
    strcpy(str_X2, citeste_string(str_X2, 10));
    // puts(str_X2);
    //citeste stringul pentru bonus X3
    char str_X3[10];
    strcpy(str_X3, citeste_string(str_X3, 10));

    N = citeste_N();

    char cuvant[SIZE];
    int k;
    char cuvinte_jucate[100][SIZE];
    char linie[SIZE + 8];
    char linie_help[SIZE + 8];
    char linii_jucate[100][SIZE + 8];
    char *p;
    
    for (k = 0; k < N; k++){
        //am folosit un sir de caractere linie pe care
        //l-am divizat folosind functia strtok
        strcpy(linie, citeste_string(linie, SIZE + 6));
        strcpy(linie_help, linie);
        scrie_cuvant(linie_help);
        strcpy(linii_jucate[k], linie);
        p = strtok(linie, " ");
        p = strtok(NULL, " ");
        p = strtok(NULL, " ");

        //am folosit un pointer p deoarece cuvant
        //nu putea fi folosit in strtok pentru ca nu este
        //un pointer a carui valoare o pot modifica
        p = strtok(NULL, " ");
        strcpy(cuvant, p);
        
        strcpy(cuvinte_jucate[k], cuvant);

    }

    int diferenta_scor;
    diferenta_scor = scor_final_player(1, linii_jucate, N, str_X2, str_X3) -
    scor_final_player(2, linii_jucate, N, str_X2, str_X3);
    //print_board(game_board);

    alege_cuvant_task_5(cuvinte_jucate, N, diferenta_scor,
    str_X2, str_X3);
}


char *alege_cuvant_task_6(char linie[SIZE + 8], 
char cuvinte_jucate[100][SIZE],int N, 
char str_X2[], char str_X3[]){

    int i = 0, j = -1, k = -1;
    int control;

    //cuvant_maxim = cuvantul cu punctaj maxim:
    char cuvant_maxim[SIZE];

    //pozitia pentru acest punctaj maxim:
    int i_max = -1, j_max = -1;

    //directia pe care ar trebui scris:
    int D_max;

    //scor maxim obtinut:
    int scor_maxim = 0;

    //posibil scor maxim:
    int scor_obtinut;

    //directia pentru cuvintele testate:
    int D;

    for (k = 0; k < 100; k++){
        
        //verific daca a mai fost scris cuvantul:
        //control = 1 cuvantul nu a mai fost scris
        //control = 0 cuvantul a mai fost scris
        control = verf_jucat(words[k], cuvinte_jucate, N);

        //daca nu a mai fost jucat
        if (control){

            for (i = 0; i < SIZE; i++){
                for (j = 0; j < SIZE; j++){
                   
                    if (words[k][0] == game_board[i][j] && 
                    verf_cuvant(words[k], i, j) > -1){

                        D = verf_cuvant(words[k], i, j);

                        scor_obtinut = scor_final_cuv(words[k], 
                        i, j, D, str_X2, str_X3);

                        if (scor_obtinut > scor_maxim){
                            scor_maxim = scor_obtinut;
                            i_max = i;
                            j_max = j;
                            D_max = D;
                            strcpy(cuvant_maxim, words[k]);
                        } else {
                            if (scor_obtinut == scor_maxim){
                                if (i < i_max){
                                    i_max = i;
                                    j_max = j;
                                    D_max = D;
                                    strcpy(cuvant_maxim, words[k]);
                                } else {
                                    if (i == i_max && j < j_max){
                                        i_max = i;
                                        j_max = j;
                                        D_max = D;
                                        strcpy(cuvant_maxim, words[k]);
                                    }
                                }
                            }
                        }
                        
                    }
                }
            }
        }
    }

    strcpy(linie, code_line(linie, i_max, j_max, D_max, cuvant_maxim));

    return linie;
}

void who_won(char linii_jucate[100][SIZE + 8], int N, 
char str_X2[], char str_X3[]){
    int Player1_scor = 0, Player2_scor = 0;
    Player1_scor = scor_final_player(1, linii_jucate, N, 
    str_X2, str_X3);
    Player2_scor = scor_final_player(2, linii_jucate, N, 
    str_X2, str_X3);

    if (Player1_scor > Player2_scor){
        printf("Player 1 Won!\n");
    } else {
        printf("Player 2 Won!\n");
    }
}

void task_6(){
    task_0();

    int k;
    char str_X2[10];
    strcpy(str_X2, citeste_string(str_X2, 10));

    char str_X3[10];
    strcpy(str_X3, citeste_string(str_X3, 10));

    int N;
    
    N = citeste_N();


    char *p;
    char linie[SIZE + 8];
    char linie_help[SIZE + 8];
    char linii_jucate[100][SIZE + 8];
    char cuvinte_jucate[100][SIZE];
    char cuvant[SIZE];

    for (k = 0; k < N; k++){
        strcpy(linie, citeste_string(linie, SIZE + 8));
        strcpy(linie_help, linie);
        scrie_cuvant(linie_help);
        strcpy(linii_jucate[2 * k], linie);
        p = strtok(linie, " ");
        p = strtok(NULL, " ");
        p = strtok(NULL, " ");
        p = strtok(NULL, " ");
        strcpy(cuvant, p);

        strcpy(cuvinte_jucate[2 * k], cuvant);
        
        strcpy(linie, alege_cuvant_task_6(linie, cuvinte_jucate, 
        2 * k + 1, str_X2, str_X3));

        strcpy(linie_help, linie);
        scrie_cuvant(linie_help);

        strcpy(linii_jucate[2 * k + 1], linie);
        p = strtok(linie, " ");
        p = strtok(NULL, " ");
        p = strtok(NULL, " ");
        p = strtok(NULL, " ");

        strcpy(cuvant, p);

        strcpy(cuvinte_jucate[2 * k + 1], cuvant);
    }

    print_board(game_board);
    who_won(linii_jucate, 2 * N, str_X2, str_X3);
}

int main(){

    //pentru a nu citi cu scanf, am folosit fgets si atoi
    int cerinta;
    cerinta = citeste_N();

    switch(cerinta){

        case 0:{
            task_0();
            print_board(game_board);

            break;
        }

        case 1:{
            task_1();;

            break;
        }

        case 2:{
            task_2();

            break;
        }

        case 3:{
            task_3();

            break;
        }

        case 4:{
            task_4();

            break;
        }

        case 5:{
            task_5();

            break;
        }

        case 6:{
            task_6();

            break;
        }
    }

    return 0;
}