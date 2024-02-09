
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct
{
  char player_name[MAX];
  char player_last[MAX];
  int player_age;
  int player_ranking;
  int round_score;

} pga_records_t;

void display_menu();
void hardcode_plrs(pga_records_t arr[MAX]);
void add_plrs(pga_records_t arr[MAX], int * num_ptr);
void display_plyrs(pga_records_t arr[MAX], int * num_ptr);
int search_plyrs(pga_records_t arr[MAX], int * num_ptr, char plyr_search[MAX]);
int delete_plyrs(pga_records_t arr[MAX], int * num_ptr, char plyr_search[MAX]);
void print_to_doc(pga_records_t arr[MAX], int * num_ptr, FILE * ou_data);

int main()
{

  FILE * outp;
  outp = fopen("golf_tournament_data.txt", "w");

  pga_records_t tournament_playrs[MAX];

  char srch[MAX];

  int player_record = 6;
  int * ptr_p_r = &player_record;

  int counter = 0;

  int i_found = 0;

  int idx_found = 0;

  int option = 0;

  char deleteName[MAX];

  printf("*******************************************************\n");
  printf("Welcome to the UCF's golf tournament database!\n");
  printf("*******************************************************\n");

  hardcode_plrs(tournament_playrs);

  do
  {
    display_menu();

    printf("Enter Option: ");
    scanf("%d", &option);
    printf("\n");

    switch(option)
    {
      case 1:
        add_plrs(tournament_playrs, ptr_p_r);
        break;
      case 2:
        display_plyrs(tournament_playrs, ptr_p_r);
        break;
      case 3:
        printf("Enter Only the fisrt name of the player: ");
        scanf("%s", srch);
        printf("--------------------------------------------------------\n");
        i_found = search_plyrs(tournament_playrs, ptr_p_r, srch);
        if (i_found == -1)
        {
          printf("Name: %s Not in the database please select option (1) and add player\n", srch);
        }
        else
        {
          printf("\n");
          printf("*******************************************************\n");
          printf("Player stored in Database securely\n");
          printf("Player name: %s\n", srch);
          printf("*******************************************************\n");
          printf("\n");
        }

        break;
      case 4:
        printf("Which Player do you want to remove\n");
        printf("Player's first name Only: ");
        scanf("%s", deleteName);

        idx_found = delete_plyrs(tournament_playrs, ptr_p_r, deleteName);

        if (idx_found == -1)
        {
          printf("NO player found in Ddatabase to be deleted\n");
        }
        else
        {
          for (int i = idx_found; i < player_record; ++i)
          {
            strcpy(tournament_playrs[i].player_name, tournament_playrs[i+1].player_name);
            strcpy(tournament_playrs[i].player_last, tournament_playrs[i+1].player_last);
            tournament_playrs[i].player_age = tournament_playrs[i+1].player_age;
            tournament_playrs[i].player_ranking = tournament_playrs[i+1].player_ranking;
            tournament_playrs[i].round_score = tournament_playrs[i+1].round_score;
          }
          player_record = player_record - 1;
        }
        printf("\n*******************************************************\n");
        printf("You have deleted %s from the database\n", deleteName);
        printf("*******************************************************\n\n");
        break;
    }
  } while (option != 5);

  print_to_doc(tournament_playrs, ptr_p_r, outp);

  fclose(outp);
}

void display_menu()
{
  printf("----------------------Database Menu-------------------\n");
  printf("Press (1) - Add a player\n");
  printf("Press (2) - Display list of payers\n");
  printf("Press (3) - Search for players\n");
  printf("Press (4) - Remove Players\n");
  printf("Press (5) - Exit and print data base to txt file\n");
  printf("*******************************************************\n");
}

void hardcode_plrs(pga_records_t arr[MAX])
{
  strcpy(arr[0].player_name, "Tiger");
  strcpy(arr[1].player_name, "Bryson");
  strcpy(arr[2].player_name, "Ricky");
  strcpy(arr[3].player_name, "John");
  strcpy(arr[4].player_name, "Phil");
  strcpy(arr[5].player_name, "Joaquin");

  strcpy(arr[0].player_last, "Woods");
  strcpy(arr[1].player_last, "DeChambou");
  strcpy(arr[2].player_last, "Fouler");
  strcpy(arr[3].player_last, "Daily");
  strcpy(arr[4].player_last, "Mickelson");
  strcpy(arr[5].player_last, "Niemann");

  arr[0].player_age = 44;
  arr[1].player_age = 49;
  arr[2].player_age = 50;
  arr[3].player_age = 30;
  arr[4].player_age = 50;
  arr[5].player_age = 29;

  arr[0].player_ranking = 1;
  arr[1].player_ranking = 3;
  arr[2].player_ranking = 5;
  arr[3].player_ranking = 10;
  arr[4].player_ranking = 6;
  arr[5].player_ranking = 9;

  arr[0].round_score = 63;
  arr[1].round_score = 66;
  arr[2].round_score = 69;
  arr[3].round_score = 65;
  arr[4].round_score = 70;
  arr[5].round_score = 71;

}

void add_plrs(pga_records_t arr[MAX], int *num_ptr)
{
  printf("*******************************************************\n");
  printf("---------------------Player %d--------------------------\n", *num_ptr + 1);
  printf("Player's name: ");
  scanf("%s", arr[*num_ptr].player_name);

  printf("Player's Last name: ");
  scanf("%s", arr[*num_ptr].player_last);

  printf("Enter Player's age: ");
  scanf("%d", &arr[*num_ptr].player_age);

  printf("Enter player's ranking: ");
  scanf("%d", &arr[*num_ptr].player_ranking);

  printf("Enter today's round score: ");
  scanf("%d", &arr[*num_ptr].round_score);
  *num_ptr = *num_ptr + 1;
  printf("*******************************************************\n");
  printf("\n");
}


void display_plyrs(pga_records_t arr[MAX], int * num_ptr)
{
  printf("--------------------------------------------------------\n");
  printf("*Currently displaying ALL registered tournament players*\n");
  printf("--------------------------------------------------------\n\n");
  for (int i = 0; i < * num_ptr; ++i)
  {
    printf("--------------------------------------------------------\n");
    printf("---------------------Player %d--------------------------\n", i+1);
    printf("--------------------------------------------------------\n");
    printf("Name: %s %s\n", arr[i].player_name, arr[i].player_last);
    printf("Age: %d\n", arr[i].player_age);
    printf("Ranking: #%d\n", arr[i].player_ranking);
    printf("Today's round score: %d\n", arr[i].round_score);
    printf("--------------------------------------------------------\n");
    printf("--------------------------------------------------------\n");
    printf("\n");
  }
}

int search_plyrs(pga_records_t arr[MAX], int * num_ptr, char plyr_search[MAX])
{
  int count = -1;

  for (int i = 0; i < * num_ptr; ++i)
  {
    if (strcmp(arr[i].player_name, plyr_search) == 0)
    {
      return i;
    }
  }
  return -1;
}

int delete_plyrs(pga_records_t arr[MAX], int * num_ptr, char plyr_search[MAX])
{
  int count = -1;

  for (int i = 0; i < * num_ptr; ++i)
  {
    if (strcmp(arr[i].player_name, plyr_search) == 0)
    {
      return i;
    }
  }
  return count;
}

void print_to_doc(pga_records_t arr[MAX], int * num_ptr, FILE * ou_data)
{
  for (int i = 0; i < * num_ptr; ++i)
  {
    fprintf(ou_data, "--------------------------------------------------------\n");
    fprintf(ou_data, "---------------------Player %d--------------------------\n", i+1);
    fprintf(ou_data, "--------------------------------------------------------\n");
    fprintf(ou_data, "Name: %s\n", arr[i].player_name);
    fprintf(ou_data, "Age: %d\n", arr[i].player_age);
    fprintf(ou_data, "Ranking: #%d\n", arr[i].player_ranking);
    fprintf(ou_data, "Today's round score: %d\n", arr[i].round_score);
    fprintf(ou_data, "\n");
  }
}
