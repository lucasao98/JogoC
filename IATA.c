#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> //FULLSCREEN
#include <time.h>
#define MAX_HEIGHT 25  //Resolution: 25x60
#define MAX_WIDTH 60
#define LOGO_HEIGHT 32   //Max Line Logo32x81
#define LOGO_WIDTH 81  //Max Column Logo
#define MAP_HEIGHT 5
#define MAP_WIDTH 126
#define N_ENEMY_1 10    //Amount of enemies on Stage 1//6 enemies
#define N_ENEMY_2 20   //Amount of enemies on Stage 2//8 enemies
#define N_ENEMY_3 30   //Amount of enemies on Stage 3//5 enemies
#define STEP_STAGE1 120 //120
#define STEP_STAGE2 160 //160
#define STEP_STAGE3 100 //100


//struct sprite, Load_Data, stage_1
//
struct sprite{
  int x, y, vx, vy, v_shoot;
  char img[3][4];
};
//
void textcolor (int iColor){
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes&= 0x00F0;
    SetConsoleTextAttribute(hl, bufferInfo.wAttributes |= iColor);
}
void Load_Data_Menu();
void Menu_Init(char logo_screen[][LOGO_WIDTH]);
void Arch_To_Array(FILE *arch, char logo[][LOGO_WIDTH]);
void Update_Menu(char logo_screen[][LOGO_WIDTH], char logo[][LOGO_WIDTH], int *line_screen);
void Write_Menu(char logo_screen[][LOGO_WIDTH]);
void Menu();
void Load_Data(char screen[][MAX_WIDTH], char map[][MAP_WIDTH]);
void Map_To_Array(FILE *arch, char map[][MAP_WIDTH]);
void Draw_Screen(char screen[][MAX_WIDTH], int *Life);
void Load_Living_Enemies();
void Load_Sprite(struct sprite *person, int x, int y, int vx, int vy, int option);
void Update_Data(char screen[][MAX_WIDTH], char map[][MAP_WIDTH], int *Life, int vel_j, int vel_ad);
void Update_Player(char screen[][MAX_WIDTH], int *Life);
void Jump(char input);
void Move_Player(char input);
void Update_Floor(char screen[][MAX_WIDTH], char map[][MAP_WIDTH]);
void Stage_1(char screen[][MAX_WIDTH], int vel_j, int vel_ad);
void Stage_2(char screen[][MAX_WIDTH], int vel_j, int vel_ad);
void Stage_3(char screen[][MAX_WIDTH], int vel_j, int vel_ad);
void Generate_Bullet(struct sprite *person, char screen[][MAX_WIDTH], int mode);
void Update_Bullet(char screen[][MAX_WIDTH], int *Life);
void Destroy_Enemy(char screen[][MAX_WIDTH]);
void ceu(char buffer[][MAX_WIDTH]);
void ceuNoturno(char buffer[][MAX_WIDTH]);
void ceuChuvoso(char buffer[][MAX_WIDTH]);
void nuvem(char buffer[][MAX_WIDTH], int i, int j, int vel_j);
void cumullus(char buffer[][MAX_WIDTH], int vel_j);
void arvore(char buffer[][MAX_WIDTH], int vel_j, int j);
void arvoreM2(char buffer[][MAX_WIDTH], int vel_j, int j);
void arvoreM3(char buffer[][MAX_WIDTH], int vel_j, int j);
void arvoreM4(char buffer[][MAX_WIDTH], int vel_j, int j);
void moita(char buffer[][MAX_WIDTH], int vel_j, int j);
void moitaM2(char buffer[][MAX_WIDTH], int vel_j, int j);
void floresta(char buffer[][MAX_WIDTH], int vel_x);
void florestaM2(char buffer[][MAX_WIDTH], int vel_x);
void florestaM3(char buffer[][MAX_WIDTH], int vel_x);
void montanha(char buffer[][MAX_WIDTH], int i, int j);
void montanhaM2(char buffer[][MAX_WIDTH], int i, int j);
void cordilheira(char buffer[][MAX_WIDTH]);
void Enemy_Jump(char screen[][MAX_WIDTH]);
void Enemy_Features_S1(char screen[][MAX_WIDTH]);
void Enemy_Features_S2(char screen[][MAX_WIDTH]);
void Enemy_Features_S3(char screen[][MAX_WIDTH]);
void logo_end_game();
void game_over();
void Hist1();
void Hist2();
void Hist3();
void airdropC(char buffer[][MAX_WIDTH], int vel_i, int vel_j, int i, int j);
void Catch_airdrop(char screen[][MAX_WIDTH], int *Life, int mode);
void Boss_Spawn(char screen[][MAX_WIDTH]);
void Boss_Features(char screen[][MAX_WIDTH]);
          //Global Variable
int PLAY=0;// <----------------------Look it------------------------------------
struct sprite player, soldier;
int POSITION_ON_FLOOR = (MAX_HEIGHT-MAP_HEIGHT)-3;
int mid=0;            //Bool Variable to Middle of Screen
int Steps = 0;
int Airdrop = 0;      //Bool Variable to Airdrop
int Move_Map_Var = 0;//Bool Variable to Move Map
int Enemy = 0;      //Bool Variable to Check the existence of Enemy
int Stage = 1;      //Control of Stages
int controller_map=0;   //Variable to Scroll the map
int count=0; //count of Time Shoot
int Cad_P_Shoot=0, Enemy_Shoot=0;
int enemy_stage_1[N_ENEMY_1]; // Bool Variable to load enemies on Stages
int enemy_stage_2[N_ENEMY_2];
int enemy_stage_3[N_ENEMY_3];
char P_Bullet = 207;
char E_Bullet = 'z';
int cont;
int end_game = 0;
int E_Jump = 0;// count of enemy jump
int Boss = 0, Life_Boss=100;
int airdropFixo=0;
int caduntDrop=0;
int DEF_CAD_P_SHOOT = 10;




int main(void){
  char screen[MAX_HEIGHT][MAX_WIDTH], map[MAP_HEIGHT][MAP_WIDTH];
  int Life = 100;
  int inNatura=0,vel_ad = 0;


  //                                         MENU
  Load_Data_Menu();
  //                                  Loading Data Game
  Load_Data(screen, map);


  while(Life>0 && end_game==0){
    if(Cad_P_Shoot != 0){
	    Cad_P_Shoot --;
    }
    Draw_Screen(screen, &Life);
    //sleep(1);
    Update_Data(screen, map, &Life, inNatura, vel_ad);

    inNatura+=3;
  	if(inNatura==4*MAX_WIDTH){
  		inNatura=0;
  	}
    if(Steps>=100){
      vel_ad++;
      caduntDrop=1;
      if(Steps==120){
         vel_ad=0;
      }
    }

    system("cls");

  }


  //                              CONGRATULATIONS OR GAME OVER
  if(end_game==1){
    logo_end_game();
  }else{
    game_over();
  }

  return 0;
}

void Load_Data_Menu(){
  char logo_screen[LOGO_HEIGHT][LOGO_WIDTH];
  for(int i=0; i<LOGO_HEIGHT; i++){
    for(int j=0; j<LOGO_WIDTH; j++){
      logo_screen[i][j] = ' ';
    }
  }
  Menu_Init(logo_screen);
}

void Menu_Init(char logo_screen[][LOGO_WIDTH]){
  FILE *arch;
  int line_screen=0, press_buttom=0; //controller of while//controller of screen's line
  char start, logo[LOGO_HEIGHT][LOGO_WIDTH];

  arch = fopen("Nome.txt","r");
  if(arch == NULL){
    printf("\nError Reading Arch File(Nome.txt not founded)...\n\n");
    system("pause");
    exit(1);
  }
  Arch_To_Array(arch, logo);  // Import arch to Array

  while(press_buttom == 0){

    Update_Menu(logo_screen, logo, &line_screen); // Load Data Menu
    Write_Menu(logo_screen);       //Write Data Menu

    if(kbhit()){               //exit this while pressing 'S'
      start=getch();
      if(start=='s'){
        press_buttom = 1;
      }
    }
  }

  Menu();

}

void Arch_To_Array(FILE *arch, char logo[][LOGO_WIDTH]){
  //                               Reading Arc File .txt

  for(int i=0; i<LOGO_HEIGHT; i++){   //Creating empty Array
    for(int j=0; j<LOGO_WIDTH; j++){

      logo[i][j] = ' ';
    }
  }

  for(int i=0; i<LOGO_HEIGHT; i++){     //Importing Arch_to_array
    for(int j=0; j<LOGO_WIDTH; j++){

      logo[i][j] = fgetc(arch);
      if(logo[i][j] == '\n'){
        j = LOGO_WIDTH;
      }

    }
  }

}

void Update_Menu(char logo_screen[][LOGO_WIDTH], char logo[][LOGO_WIDTH], int *line_screen){

  int line_logo = LOGO_HEIGHT-1;
  int position_j = 50;

  for(int i=*line_screen; i>=0; i--){ // Updating MENU LOGO SCREEN ARRAY TO SCROLL
    position_j = 0;
    for(int j=0; j<LOGO_WIDTH; j++){

      logo_screen[i][position_j] = logo[line_logo][j];
      if(logo[line_logo][j] == '\n'){
        logo_screen[i][position_j] = ' ';
      }
      position_j++;
    }
    if(line_logo>0)
    line_logo--;
  }
  if(*line_screen<LOGO_HEIGHT-1)
  (*line_screen)++;
}

void Write_Menu(char logo_screen[][LOGO_WIDTH]){


  for(int i=0; i<LOGO_HEIGHT; i++){
    for(int j=0;j<LOGO_WIDTH; j++){
      textcolor(3); printf("%c", logo_screen[i][j]);
    }
    printf("\n");
  }

  system("cls");




}

void Menu(){
  char text[100],text2[50],text3[50],text4[50], nome[40];  //Armazena a string do arquivo
  FILE *arch1,*arch2; //Ponteiro de arquivo
  char esc; //Para guardar a opção que o usuario escolherá



  arch1=fopen("Menu.txt","r");
     while(PLAY == 0){
       rewind(arch1);  //Função para retornar para o inicio do arquivo
       while(fgets(text,100,arch1)!=NULL){
         printf("%s\n",text);
       }
       system("cls");

       if(kbhit()){
         esc=getch();  //Waiting User's choice

         if(esc=='1'){

           Hist1();

           PLAY=1;
         }
         else if(esc=='2'){
           arch2=fopen("Inst.txt","r");
            while(fgets(text3,50,arch2)!=NULL){
              printf("%s",text3);
            }
          system("PAUSE");
          fclose(arch2);
        }
         else if(esc=='3'){
           arch2=fopen("Rank.txt","r");
            while(fgets(text4,50,arch2)!=NULL){
              printf("%s",text4);
            }
            printf("\n");
           system("PAUSE");
           fclose(arch2);
         }
         else if(esc=='4'){
           arch2=fopen("Creditos.txt","r");
             while(fgets(text2,50,arch2)!=NULL){
               printf("%s",text2);
             }
             system("PAUSE");
             fclose(arch2);
         }
         else if(esc=='5'){
           printf("\n\n\n\n\t\t\t\t\t\t :D OBRIGADO POR TESTAR :D\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
           exit(1);
         }
       }
     }
  fclose(arch1);
}

void Load_Data(char screen[][MAX_WIDTH], char map[][MAP_WIDTH]){

  FILE *arch;
  unsigned int k;//Control Var

  for(int i=0; i<MAX_HEIGHT; i++){
    for(int j=0; j<MAX_WIDTH; j++){
      screen[i][j] = ' ';
    }
  }

  Load_Living_Enemies();  // Load Enemies Position '-'

  //                               Reading Arc File .txt
  arch = fopen("Stage_1.txt","r");
  if(arch == NULL){
      printf("\nError Reading Arch File(Stage_1.txt not founded)...\n\n");
      system("pause");
      exit(1);
  }


  Map_To_Array(arch, map);   // Importing Map to Array
  k=0;
  for(int i=MAX_HEIGHT-MAP_HEIGHT; i<MAX_HEIGHT; i++){
    for(int j=0; j<MAX_WIDTH; j++){   //Importing Map to Screen
      screen[i][j] = map[k][j];

    }
    k++;
  }
  fclose(arch);


  Load_Sprite(&player, 1, POSITION_ON_FLOOR, 0, 0, 1);//Loading Sprite
  for(int i=0;i<3;i++){
    for(int j=0;j<4;j++){
      screen[player.y+i][player.x+j] = player.img[i][j];
    }
  }

}

void Map_To_Array(FILE *arch, char map[][MAP_WIDTH]){

    for(int i=0; i<5; i++){   //Creating empty Array
      for(int j=0; j<MAP_WIDTH; j++){

        map[i][j] = ' ';
      }
    }

    for(int i=0; i<5; i++){     //Importing Arch_to_array
      for(int j=0; j<MAP_WIDTH; j++){

        map[i][j] = fgetc(arch);
        if(map[i][j] == '\n'){
          j = MAP_WIDTH;
        }
      }
    }

}

void Draw_Screen(char screen[][MAX_WIDTH], int *Life){
  printf("Life: %d\t", *Life);
  if(Boss==1){
      printf("Boss : %d", Life_Boss);
  }

  printf("Steps: %d\t Stage: %d\n", Steps, Stage);

    for (int i=0;i<MAX_HEIGHT;i++){
    for(int j=0; j<MAX_WIDTH; j++){
      printf("%c", screen[i][j]);
    }
    printf("\n");
  }
}

void Load_Living_Enemies(){ // To use Boolean variable on Stages 1 2 3

  for(int i=0; i<N_ENEMY_1;i++){
    enemy_stage_1[i] = 1;
  }
  for(int i=0; i<N_ENEMY_2;i++){
    enemy_stage_2[i] = 1;
  }
  for(int i=0; i<N_ENEMY_3;i++){
    enemy_stage_3[i] = 1;
  }

}

void Load_Sprite(struct sprite *person, int x, int y, int vx, int vy, int option){
  person->x = x;
  person->y = y;
  person->vx = vx;
  person->vy = vy;
  if(option==1){      //Load Player
    person->img[0][0] = ' ';
    person->img[0][1] = 157;
    person->img[0][2] = ' ';
    person->img[0][3] = ' ';
    person->img[1][0] = 189;
    person->img[1][1] = 173;
    person->img[1][2] = 201;
    person->img[1][3] = 203;
    person->img[2][0] = ' ';
    person->img[2][1] = 148;
    person->img[2][2] = ' ';
    person->img[2][3] = ' ';
  }
  if(option==2){        //Load Soldier
    person->img[0][0] = ' ';
    person->img[0][1] = ' ';
    person->img[0][2] = 'q';
    person->img[0][3] = ' ';
    person->img[1][0] = '=';
    person->img[1][1] = '<';
    person->img[1][2] = '#';
    person->img[1][3] = ']';
    person->img[2][0] = ' ';
    person->img[2][1] = '/';
    person->img[2][2] = '/';
    person->img[2][3] = ' ';
  }
  if(option==3){
    person->img[0][0] = ' ';
    person->img[0][1] = ' ';
    person->img[0][2] = 157;
    person->img[0][3] = ' ';
    person->img[1][0] = 203;
    person->img[1][1] = 187;
    person->img[1][2] = 173;
    person->img[1][3] = 232;
    person->img[2][0] = ' ';
    person->img[2][1] = ' ';
    person->img[2][2] = 148;
    person->img[2][3] = ' ';
  }
}

void Update_Data(char screen[][MAX_WIDTH], char map[][MAP_WIDTH], int *Life, int vel_j, int vel_ad){

  if(Stage == 1){
    Stage_1(screen, vel_j, vel_ad);
  }else if(Stage == 2){
    Stage_2(screen, vel_j, vel_ad);
  }else if(Stage == 3){
    Stage_3(screen, vel_j, vel_ad);
  }

  Update_Player(screen, Life);
  Update_Floor(screen, map);
  Update_Bullet(screen, Life);
  if(Enemy==1){
    Enemy_Jump(screen);
  }

  if(Stage == 1 &&Steps==STEP_STAGE1){

    Hist2();

    Stage = 2;
    Steps = 0;
    count = 0;    //Clearring Parameters of Enemy Features
    E_Jump = 0;   //Clearring Parameters of Enemy Features
  }else if(Stage == 2 && Steps == STEP_STAGE2){

    Hist3();

    Stage = 3;
    Steps = 0;
    count = 0;    //Clearring Parameters of Enemy Features
    E_Jump = 0;   //Clearring Parameters of Enemy Features
  }else if(Stage ==3 && Steps == STEP_STAGE3){
    Steps = 0;
    count=0;
    E_Jump = 0;
    if(Boss==0){
      Boss = 1;
    }
    else if(Boss==1&&Life_Boss<=0){
      end_game = 1;
    }

  }


}

void Update_Player(char screen[][MAX_WIDTH], int *Life){
  char input;
        //                Clearing Last Player Position
  for(int i=0;i<3;i++){
    for(int j=0;j<4;j++){
      screen[player.y+i][player.x+j] = ' ';
    }
  }

              //                Updating Player Position
  player.y = player.y + player.vy;
  player.x = player.x + player.vx;

  for (int i=0;i<3;i++){  //    Drawing Player Position
    for(int j=0;j<4;j++){
      if(screen[player.y+i][player.x+j]!= E_Bullet){
        screen[player.y+i][player.x+j] = player.img[i][j];
      }
    }
  }
  //                Scaning input
  if(kbhit()){
    input = getch();
  }
  //            Condition for Jump
  Jump(input);
            //        Move
  Move_Player(input);
  if(Stage==2){
    Catch_airdrop(screen, Life, 1);
  }
  else if(Stage==3){
    Catch_airdrop(screen, Life, 2);
  }
                    //Control Shoot
  if((input == 'J' || input == 'j') && Cad_P_Shoot == 0){
    Generate_Bullet(&player, screen, 1);
  }

}

void Jump(char input){
  int gravity = 1;
  if(input == 'W' || input == 'w' && player.y == POSITION_ON_FLOOR){
      player.vy = -3;
  }else{
    if(player.y< POSITION_ON_FLOOR){//If is jumping
      player.vy = player.vy + gravity;
    }else{
      player.vy = 0;
    }
  }
}

void Move_Player(char input){

  if(player.vx !=0){
    player.vx = 0;
  }

  if(input =='D' || input == 'd'){

    if(mid<MAX_WIDTH/2 && Airdrop == 0){
      mid++;
      Steps++;
      player.vx = +1;

    }else if(mid >= MAX_WIDTH/2 && Airdrop == 0 && Enemy == 0){
      Steps++;
      Move_Map_Var = 1;
    }
  }

  if(input == 'A' || input == 'a'){

    if(mid > 1){
      mid--;
      Steps--;
      player.vx = -1;
    }
  }
}

void Update_Floor(char screen[][MAX_WIDTH], char map[][MAP_WIDTH]){
  unsigned int k; //Control Var

  textcolor(10);

  if(Move_Map_Var == 1){
    controller_map++;   //Set controller (0 to 1)
      Move_Map_Var = 0;
      //if(Stage==1)
      k=0;
      for(int i=MAX_HEIGHT-MAP_HEIGHT;i<MAX_HEIGHT;i++){
        for(int j=0;j<MAX_WIDTH;j++){

          if(map[k][j+controller_map]=='\n'){
            j++;
          }

          if(controller_map==(MAP_WIDTH-1)){//If the controller reaches the end of the map
            controller_map = 0;           //Restart Controller
          }

          if(j+controller_map>=MAP_WIDTH){
            screen[i][j] = map[k][(j+controller_map)-MAP_WIDTH];

          }else{
            screen[i][j] = map[k][j+controller_map];
          }

        }
        k++;
      }

    //else if(Stage==2)
    //else if(Stage==3)
  }
}

void Stage_1(char screen[][MAX_WIDTH],  int vel_j, int vel_ad){

  ceuNoturno(screen);
  floresta(screen, Steps);
  Enemy_Features_S1(screen);
}

void Stage_2(char screen[][MAX_WIDTH], int vel_j, int vel_ad){

	  ceu(screen);
    //nuvem(screen, 8, 51, vel_j);
    cordilheira(screen);
    cumullus(screen, vel_j);
    //arvore(screen, 50, Steps);
    florestaM2(screen, Steps);
    Enemy_Features_S2(screen);
    airdropC(screen, vel_ad, vel_ad, 2, MAX_WIDTH-20);
}

void Stage_3(char screen[][MAX_WIDTH], int vel_j, int vel_ad){

	ceuChuvoso(screen);
	cordilheira(screen);
	florestaM3(screen, Steps);
  Enemy_Features_S3(screen);
  airdropC(screen, vel_ad, vel_ad, 2, MAX_WIDTH-20);
}

void Generate_Bullet(struct sprite *person, char screen[][MAX_WIDTH], int mode){


  if(mode == 1){    //Generate Player Bullet
    screen[person->y+1][person->x+4] = P_Bullet;
    Cad_P_Shoot = DEF_CAD_P_SHOOT;

  }else if(mode == 2){    //Generate Enemy Bullet
    screen[person->y+1][person->x-1] = E_Bullet;

  }
}

void Update_Bullet(char screen[][MAX_WIDTH], int *Life){

  for(int i = POSITION_ON_FLOOR-5;i<POSITION_ON_FLOOR+2;i++){
     for(int j = 0; j<MAX_WIDTH;j++){

       if(screen[i][j]==P_Bullet && screen[i][j+1]==E_Bullet){
         screen[i][j] = E_Bullet;
         screen[i][j+1] = P_Bullet;
         j++;
       }
       if(screen[i][j]==P_Bullet&&screen[i][j+1]==E_Bullet&&screen[i][j+1]!= ' '){
         screen[i][j] = E_Bullet;
         screen[i][j+2] = P_Bullet;
         j++;
       }

       //Condition to Enemy's Death
       if(screen[i][j] == P_Bullet&& Enemy==1){
         if(j+1 ==soldier.x && i-1 == soldier.y){
            Enemy = 0;
            screen[i][j] = ' ';//Remove P_Bullet
            if(Boss==0){
              Destroy_Enemy(screen);
            }else if(Boss==1){
              Life_Boss-=5;
            }


          }else  if(j+1==soldier.x && i==soldier.y){
            Enemy = 0;
            screen[i][j] = ' ';//Remove P_Bullet
            if(Boss==0){
              Destroy_Enemy(screen);
            }else if(Boss==1){
              Life_Boss-=5;
            }


          }else  if(j+1==soldier.x && i-2==soldier.y){
            Enemy = 0;
            screen[i][j] = ' ';//Remove P_Bullet
            if(Boss==0){
              Destroy_Enemy(screen);
            }else if(Boss==1){
              Life_Boss-=5;
            }


          }else  if(j==soldier.x && i-2==soldier.y){
            Enemy = 0;
            screen[i][j] = ' ';//Remove P_Bullet
            if(Boss==0){
              Destroy_Enemy(screen);
            }else if(Boss==1){
              Life_Boss-=5;
            }


          }
       }

       if(screen[i][j] == P_Bullet){	//Updating Player Bullet
            screen[i][j] = ' ';
            screen[i][j+1] = P_Bullet;
            j++;
       }
     }

     if(screen[i][MAX_WIDTH-1]== P_Bullet){   //Destroy Bullet
       screen[i][MAX_WIDTH-1] = ' ';
     }
   }

   for(int i = POSITION_ON_FLOOR-5;i<POSITION_ON_FLOOR+2;i++){
      for(int j = 0; j<MAX_WIDTH;j++){


        if(screen[i][j]==P_Bullet && screen[i][j+1]==E_Bullet){
         screen[i][j] = E_Bullet;
         screen[i][j+1] = P_Bullet;
        }
        if(screen[i][1]== E_Bullet){   //Destroy Enemy_Bullet
          screen[i][1] = ' ';
        }
        if(screen[i][2]==E_Bullet){
          screen[i][2]= ' ';
        }
        if(screen[i][3]==E_Bullet){
          screen[i][3] = ' ';
        }

        //Condition to Player Damage
        if(screen[i][j] == E_Bullet){
          if(j-4 ==player.x && i-1 == player.y){
             (*Life) -=10 ;
             screen[i][j] = ' ';//Remove E_Bullet
           }
           else if(j-3==player.x && i-1==player.y){
             (*Life) -=10;
             screen[i][j] = ' ';//Remove E_Bullet
           }
           else if(j-2==player.x && i-1==player.y){
             (*Life) -=10;
             screen[i][j] = ' ';//Remove E_Bullet
           }
           else if(j-1==player.x && i-1==player.y){
             (*Life) -=10;
             screen[i][j] = ' ';//Remove E_Bullet
           }
           else if(j==player.x && i-1==player.y){
             (*Life) -=10;
             screen[i][j] = ' ';//Remove E_Bullet
           }
           else if(j-3==player.x && i==player.y){
             (*Life) -=10;
             screen[i][j] = ' ';//Remove E_Bullet
           }
           else if(j-4==player.x && i-2==player.y){
             (*Life) -=10;
             screen[i][j] = ' ';//Remove E_Bullet
           }
           else if(j-3==player.x && i-2==player.y){
             (*Life) -=10;
             screen[i][j] = ' ';//Remove E_Bullet
           }
           else if(j-2==player.x && i-2==player.y){
             (*Life) -=10;
             screen[i][j] = ' ';//Remove E_Bullet
           }
           else if(j-1==player.x && i-2==player.y){
             (*Life) -=10;
             screen[i][j] = ' ';//Remove E_Bullet
           }
           else if(j==player.x && i-2==player.y){
             (*Life) -=10;
             screen[i][j] = ' ';//Remove E_Bullet
           }
        }

        if(screen[i][j] == E_Bullet){	//Updating Enemy_Bullet
             screen[i][j] = ' ';
             screen[i][j-soldier.v_shoot] = E_Bullet;
        }
      }
    }
}

void Destroy_Enemy(char screen[][MAX_WIDTH]){
  for(int i=soldier.y;i<soldier.y+3;i++){
    for(int j=soldier.x;j<MAX_WIDTH;j++){
      screen[i][j] = ' ';

    }
  }
}

void ceu(char buffer[][MAX_WIDTH]){


	int i=0, j=0, ceu=177;
	for(i=0;i<MAX_HEIGHT-5;i++){
		for(j=0;j<MAX_WIDTH;j++){
		      if(buffer[i][j]== P_Bullet){
		        j++;
		      }
		      if(buffer[i][j]== E_Bullet){
		        j++;
		      }
		      if(soldier.y == i && soldier.x == j){
		        j=MAX_WIDTH;
		      }
		      if(soldier.y+1 == i && soldier.x == j){
		        j=MAX_WIDTH;
		      }
		      if(soldier.y+2 == i && soldier.x == j){
		        j=MAX_WIDTH;
		      }
			buffer[i][j] = ' ';
		}
	}
}

void ceuNoturno(char buffer[][MAX_WIDTH]){
	int i=0, j=0, ceu=177, star=0, dStar=46;
	srand(time(NULL));
	for(i=0;i<MAX_HEIGHT-5;i++){
		for(j=0;j<MAX_WIDTH;j++){
			star = rand()%10000;
		      if(buffer[i][j]== P_Bullet){
		        j++;
		      }
		      if(buffer[i][j]== E_Bullet){
		        j++;
		      }
		      if(soldier.y == i && soldier.x == j){
		        j=MAX_WIDTH;
		      }
		      if(soldier.y+1 == i && soldier.x == j){
		        j=MAX_WIDTH;
		      }
		      if(soldier.y+2 == i && soldier.x == j){
		        j=MAX_WIDTH;
		      }
			  if(star>0 && star<=MAX_WIDTH){
				  buffer[i][j] = dStar;
			  }
			  else{
				  buffer[i][j] = ' ';
			  }
		}
	}
}

void ceuChuvoso(char buffer[][MAX_WIDTH]){
	int i=0, j=0, ceu=177, pingC=0, pingo=47;
	srand(time(NULL));
	for(i=0;i<MAX_HEIGHT-5;i++){
		for(j=0;j<MAX_WIDTH;j++){
			pingC = rand()%10000;
		      if(buffer[i][j]== P_Bullet){
		        j++;
		      }
		      if(buffer[i][j]== E_Bullet){
		        j++;
		      }
		      if(soldier.y == i && soldier.x == j){
		        j=MAX_WIDTH;
		      }
		      if(soldier.y+1 == i && soldier.x == j){
		        j=MAX_WIDTH;
		      }
		      if(soldier.y+2 == i && soldier.x == j){
		        j=MAX_WIDTH;
		      }
			  if(pingC>0 && pingC<=MAX_WIDTH){
				  buffer[i][j] = pingo;
			  }
			  else{
				  buffer[i][j] = ' ';
			  }
		}
	}
}

void nuvem(char buffer[][MAX_WIDTH], int i, int j, int vel_j){
	int dobraEsq = 40, dobraDir = 41, separador = 47, base = 95;
	//int i=8, j=51;
	if(j - vel_j <= MAX_WIDTH-1 && j-vel_j>=0){
		j = j - vel_j;
		buffer[i][j] = base;
		//lado direito
		buffer[i+1][j+1] = dobraDir;
		buffer[i+1][j+2] = base;
		buffer[i+2][j+1] = separador;
		buffer[i+2][j+3] = dobraDir;
		buffer[i+2][j+4] = base;
		buffer[i+2][j+5] = base;
		buffer[i+3][j+6] = dobraDir;
		buffer[i+3][j+5] = base;
		buffer[i+3][j+4] = base;
		buffer[i+3][j+3] = base;
		buffer[i+3][j+2] = base;
		buffer[i+3][j+1] = base;
		buffer[i+3][j] = base;
		//lado esquerdo
		buffer[i+1][j-1] = dobraEsq;
		buffer[i+1][j-2] = base;
		buffer[i+2][j-1] = separador;
		buffer[i+2][j-3] = dobraEsq;
		buffer[i+2][j-4] = base;
		buffer[i+2][j-5] = base;
		buffer[i+3][j-6] = dobraEsq;
		buffer[i+3][j-5] = base;
		buffer[i+3][j-4] = base;
		buffer[i+3][j-3] = base;
		buffer[i+3][j-2] = base;
		buffer[i+3][j-1] = base;
	}
}

void cumullus(char buffer[][MAX_WIDTH], int vel_j){
	nuvem(buffer, 8, 84, vel_j);
	nuvem(buffer, 5, 90, vel_j);
	nuvem(buffer, 8, 110, vel_j);
	nuvem(buffer, 3, 115, vel_j);
	nuvem(buffer, 8, 112, vel_j);
	nuvem(buffer, 3, 118, vel_j);
	nuvem(buffer, 5, 130, vel_j);
	nuvem(buffer, 3, 150, vel_j);
	nuvem(buffer, 8, 190, vel_j);
	nuvem(buffer, 5, 210, vel_j);
	nuvem(buffer, 3, 215, vel_j);
	nuvem(buffer, 8, 212, vel_j);
	nuvem(buffer, 3, 218, vel_j);
	nuvem(buffer, 5, 230, vel_j);
	nuvem(buffer, 3, 235, vel_j);
}

void arvore(char buffer[][MAX_WIDTH], int vel_j, int j){
	int arbustoCima = 219, arbusto = 220, galhoEsq = 185, galhoDir = 204, caule = 186, extCima = 202, ext = 205;
	int i=14;
	//magia da natureza. São 3h da manhã eu to viajando. Conversei com mercúrio que tá ali no céu. Muito bom o papo. Ele me ensinou isso
	if(j - vel_j <= MAX_WIDTH-10 && j-vel_j>=0){
		j = j - vel_j;

		if(buffer[i][j] != P_Bullet && buffer[i][j] != E_Bullet){
			buffer[i][j] = arbustoCima;
		}
		if(buffer[i+1][j] != P_Bullet && buffer[i+1][j] != E_Bullet){
			buffer[i+1][j] = galhoEsq;
  		}
		if(buffer[i+1][j-1] != P_Bullet && buffer[i+1][j-1] != E_Bullet){
			buffer[i+1][j-1] = ext;
		}
		if(buffer[i+1][j-2] != P_Bullet && buffer[i+1][j-2] != E_Bullet){
			buffer[i+1][j-2] = arbusto;
		}
		if(buffer[i+2][j] != P_Bullet && buffer[i+2][j] != E_Bullet){
			buffer[i+2][j] = galhoDir;
		}
		if(buffer[i+2][j+1] != P_Bullet && buffer[i+2][j+1] != E_Bullet){
			buffer[i+2][j+1] = extCima;
		}
		if(buffer[i+2][j+2] != P_Bullet && buffer[i+2][j+2] != E_Bullet){
			buffer[i+2][j+2] = arbusto;
		}
		if(buffer[i+3][j] != P_Bullet && buffer[i+3][j] != E_Bullet){
			buffer[i+3][j] = caule;
		}
		if(buffer[i+4][j] != P_Bullet && buffer[i+4][j] != E_Bullet){
			buffer[i+4][j] = caule;
		}
		if(buffer[i+5][j] != P_Bullet && buffer[i+5][j] != E_Bullet){
			buffer[i+5][j] = caule;
		}
	}
}

void arvoreM2(char buffer[][MAX_WIDTH], int vel_j, int j){
	int arbustoCima = 203, arbusto = 220, galhoEsq = 185, galhoDir = 204, caule = 186, ext = 202;
	int i=16;
	//magia da natureza. São 3h da manhã eu to viajando. Conversei com mercúrio que tá ali no céu. Muito bom o papo. Ele me ensinou isso
	if(j - vel_j <= MAX_WIDTH-10 && j-vel_j>=0){
		j = j - vel_j;

		if(buffer[i][j] != P_Bullet && buffer[i][j] != E_Bullet){
			buffer[i][j] = arbustoCima;
		}

		if(buffer[i+1][j] != P_Bullet && buffer[i+1][j] != E_Bullet){
			buffer[i+1][j] = galhoEsq;
		}
		if(buffer[i+1][j-1] != P_Bullet && buffer[i+1][j-1] != E_Bullet){
			buffer[i+1][j-1] = arbusto;
		}
		if(buffer[i+2][j] != P_Bullet && buffer[i+2][j] != E_Bullet){
			buffer[i+2][j] = galhoDir;
		}
		if(buffer[i+2][j+1] != P_Bullet && buffer[i+2][j+1] != E_Bullet){
			buffer[i+2][j+1] = arbusto;
		}

		if(buffer[i+3][j] != P_Bullet && buffer[i+3][j] != E_Bullet){
			buffer[i+3][j] = caule;
		}
	}
}

void arvoreM3(char buffer[][MAX_WIDTH], int vel_j, int j){
	int arbustoCima = 219, arbusto = 220, galhoEsq = 185, galhoDir = 204, caule = 186, extCima = 202, ext = 205;
	int i=14;
	//magia da natureza. São 3h da manhã eu to viajando. Conversei com mercúrio que tá ali no céu. Muito bom o papo. Ele me ensinou isso
	if(j - vel_j <= MAX_WIDTH-10 && j-vel_j>=0){
		j = j - vel_j;

		if(buffer[i][j] != P_Bullet && buffer[i][j] != E_Bullet){
			buffer[i][j] = arbustoCima;
		}
		if(buffer[i+1][j] != P_Bullet && buffer[i+1][j] != E_Bullet){
			buffer[i+1][j] = arbustoCima;
		}
		if(buffer[i+1][j+1] != P_Bullet && buffer[i+1][j+1] != E_Bullet){
			buffer[i+1][j+1] = arbustoCima;
		}
		if(buffer[i+1][j-1] != P_Bullet && buffer[i+1][j-1] != E_Bullet){
			buffer[i+1][j-1] = arbustoCima;
		}
		if(buffer[i+2][j] != P_Bullet && buffer[i+2][j] != E_Bullet){
			buffer[i+2][j] = arbustoCima;
		}
		if(buffer[i+2][j-2] != P_Bullet && buffer[i+2][j-2] != E_Bullet){
			buffer[i+2][j-2] = arbustoCima;
		}
		if(buffer[i+2][j-1] != P_Bullet && buffer[i+2][j-1] != E_Bullet){
			buffer[i+2][j-1] = arbustoCima;
		}
		if(buffer[i+2][j+1] != P_Bullet && buffer[i+2][j+1] != E_Bullet){
			buffer[i+2][j+1] = arbustoCima;
		}
		if(buffer[i+2][j+2] != P_Bullet && buffer[i+2][j+2] != E_Bullet){
			buffer[i+2][j+2] = arbustoCima;
		}
		if(buffer[i+3][j] != P_Bullet && buffer[i+3][j] != E_Bullet){
			buffer[i+3][j] = galhoDir;
		}
		if(buffer[i+3][j+1] != P_Bullet && buffer[i+3][j+1] != E_Bullet){
			buffer[i+3][j+1] = ext;
		}
		if(buffer[i+4][j] != P_Bullet && buffer[i+4][j] != E_Bullet){
			buffer[i+4][j] = caule;
		}
		if(buffer[i+5][j] != P_Bullet && buffer[i+5][j] != E_Bullet){
			buffer[i+5][j] = caule;
		}
	}
}

void arvoreM4(char buffer[][MAX_WIDTH], int vel_j, int j){
	int arbustoCima = 219, arbusto = 220, galhoEsq = 185, galhoDir = 204, caule = 186, extCima = 202, ext = 205;
	int i=14;
	//magia da natureza. São 3h da manhã eu to viajando. Conversei com mercúrio que tá ali no céu. Muito bom o papo. Ele me ensinou isso
	if(j - vel_j <= MAX_WIDTH-10 && j-vel_j>=0){
		j = j - vel_j;

		if(buffer[i][j] != P_Bullet && buffer[i][j] != E_Bullet){
			buffer[i][j] = arbustoCima;
		}
		if(buffer[i+1][j] != P_Bullet && buffer[i+1][j] != E_Bullet){
			buffer[i+1][j] = arbustoCima;
		}
		if(buffer[i+1][j+1] != P_Bullet && buffer[i+1][j+1] != E_Bullet){
			buffer[i+1][j+1] = arbustoCima;
		}
		if(buffer[i+1][j-1] != P_Bullet && buffer[i+1][j-1] != E_Bullet){
			buffer[i+1][j-1] = arbustoCima;
		}
		if(buffer[i+2][j] != P_Bullet && buffer[i+2][j] != E_Bullet){
			buffer[i+2][j] = arbustoCima;
		}
		if(buffer[i+2][j-1] != P_Bullet && buffer[i+2][j-1] != E_Bullet){
			buffer[i+2][j-1] = arbustoCima;
		}
		if(buffer[i+2][j+1] != P_Bullet && buffer[i+2][j+1] != E_Bullet){
			buffer[i+2][j+1] = arbustoCima;
		}
		if(buffer[i+3][j] != P_Bullet && buffer[i+3][j] != E_Bullet){
			buffer[i+3][j] = arbustoCima;
		}
		if(buffer[i+4][j] != P_Bullet && buffer[i+4][j] != E_Bullet){
			buffer[i+4][j] = caule;
		}
		if(buffer[i+5][j] != P_Bullet && buffer[i+5][j] != E_Bullet){
			buffer[i+5][j] = caule;
		}
	}
}

void moita(char buffer[][MAX_WIDTH], int vel_j, int j){
	int arbustoCima = 219, arbusto = 220, galhoEsq = 185, galhoDir = 204, caule = 186, extCima = 202, ext = 205;
	int i=18;
	//magia da natureza. São 3h da manhã eu to viajando. Conversei com mercúrio que tá ali no céu. Muito bom o papo. Ele me ensinou isso
	if(j - vel_j <= MAX_WIDTH-10 && j-vel_j>=0){
		j = j - vel_j;
		if(buffer[i][j] != P_Bullet && buffer[i][j] != E_Bullet){
			buffer[i][j] = arbusto;
		}
		if(buffer[i+1][j] != P_Bullet && buffer[i+1][j] != E_Bullet){
			buffer[i+1][j] = arbustoCima;
  		}
		if(buffer[i+1][j-1] != P_Bullet && buffer[i+1][j-1] != E_Bullet){
			buffer[i+1][j-1] = arbusto;
		}
		if(buffer[i+1][j+1] != P_Bullet && buffer[i+1][j+1] != E_Bullet){
			buffer[i+1][j+1] = arbusto;
		}

	}
}

void moitaM2(char buffer[][MAX_WIDTH], int vel_j, int j){
	int arbustoCima = 219, arbusto = 220, galhoEsq = 185, galhoDir = 204, caule = 197, extCima = 202, ext = 205;
	int i=18;
	//magia da natureza. São 3h da manhã eu to viajando. Conversei com mercúrio que tá ali no céu. Muito bom o papo. Ele me ensinou isso
	if(j - vel_j <= MAX_WIDTH-10 && j-vel_j>=0){
		j = j - vel_j;
		if(buffer[i][j] != P_Bullet && buffer[i][j] != E_Bullet){
			buffer[i][j] = arbusto;
		}
		if(buffer[i+1][j] != P_Bullet && buffer[i+1][j] != E_Bullet){
			buffer[i+1][j] = caule;
  		}
	}
}

void floresta(char buffer[][MAX_WIDTH], int vel_x){
	moitaM2(buffer, vel_x, 21);
	arvore(buffer, vel_x, 25);
	arvoreM2(buffer, vel_x, 43);
	arvore(buffer, vel_x, 54);
	arvoreM2(buffer, vel_x, 66);
	arvore(buffer, vel_x, 70);
	arvore(buffer, vel_x, 76);
	arvoreM2(buffer, vel_x, 85);
	arvore(buffer, vel_x, 90);
	arvoreM2(buffer, vel_x, 94);
	moita(buffer, vel_x, 96);
	arvoreM2(buffer, vel_x, 99);
	arvore(buffer, vel_x, 102);
	arvore(buffer, vel_x, 111);
	moita(buffer, vel_x, 114);
	arvoreM2(buffer, vel_x, 120);
	arvore(buffer, vel_x, 125);
	arvore(buffer, vel_x, 130);
	arvore(buffer, vel_x, 134);
	arvoreM2(buffer, vel_x, 150);
	arvoreM2(buffer, vel_x, 166);
	arvore(buffer, vel_x, 170);
	moita(buffer, vel_x, 176);
	arvoreM2(buffer, vel_x, 185);
	arvore(buffer, vel_x, 190);
	arvoreM2(buffer, vel_x, 194);
	arvoreM2(buffer, vel_x, 196);
	arvoreM2(buffer, vel_x, 199);
	arvore(buffer, vel_x, 221);
	arvore(buffer, vel_x, 225);
	arvoreM2(buffer, vel_x, 240);
}

void florestaM2(char buffer[][MAX_WIDTH], int vel_x){
	arvoreM3(buffer, vel_x, 21);
	arvoreM3(buffer, vel_x, 25);
	arvoreM4(buffer, vel_x, 43);
	arvoreM3(buffer, vel_x, 54);
	arvoreM4(buffer, vel_x, 66);
	arvoreM3(buffer, vel_x, 70);
	arvoreM3(buffer, vel_x, 76);
	arvoreM4(buffer, vel_x, 85);
	arvoreM3(buffer, vel_x, 90);
	arvoreM4(buffer, vel_x, 94);
	arvoreM3(buffer, vel_x, 96);
	arvoreM4(buffer, vel_x, 99);
	arvoreM3(buffer, vel_x, 102);
	arvoreM4(buffer, vel_x, 111);
	arvoreM3(buffer, vel_x, 114);
	arvoreM4(buffer, vel_x, 120);
	arvoreM3(buffer, vel_x, 125);
	arvoreM3(buffer, vel_x, 130);
	arvoreM3(buffer, vel_x, 134);
	arvoreM4(buffer, vel_x, 150);
	arvoreM3(buffer, vel_x, 166);
	arvoreM3(buffer, vel_x, 170);
	arvoreM3(buffer, vel_x, 176);
	arvoreM4(buffer, vel_x, 185);
	arvoreM3(buffer, vel_x, 190);
	arvoreM4(buffer, vel_x, 194);
	arvoreM4(buffer, vel_x, 196);
	arvoreM4(buffer, vel_x, 199);
	arvoreM3(buffer, vel_x, 221);
	arvoreM3(buffer, vel_x, 225);
	arvoreM4(buffer, vel_x, 240);
}

void florestaM3(char buffer[][MAX_WIDTH], int vel_x){
	moitaM2(buffer, vel_x, 21);
	moita(buffer, vel_x, 25);
	moita(buffer, vel_x, 43);
	moitaM2(buffer, vel_x, 54);
	moita(buffer, vel_x, 66);
	moitaM2(buffer, vel_x, 76);
	moita(buffer, vel_x, 85);
	moitaM2(buffer, vel_x, 90);
	moita(buffer, vel_x, 94);
	moitaM2(buffer, vel_x, 96);
	moita(buffer, vel_x, 99);
	moitaM2(buffer, vel_x, 102);
	moita(buffer, vel_x, 111);
	moita(buffer, vel_x, 120);
	moita(buffer, vel_x, 130);
	moitaM2(buffer, vel_x, 134);
	moita(buffer, vel_x, 150);
	moitaM2(buffer, vel_x, 166);
	moita(buffer, vel_x, 185);
	moitaM2(buffer, vel_x, 190);
	moita(buffer, vel_x, 196);
	moita(buffer, vel_x, 199);
	moitaM2(buffer, vel_x, 240);
}

void montanha(char buffer[][MAX_WIDTH], int i, int j){
	int topo = 196, dobraEsq = 194, dobraDir = 191, ladoEsq = 47, ladoDir = 92, chao = 95;
	//int i=0, j=30;
	buffer[i][j]=topo;
	//lado direito da montanha
	buffer[i][j+1] = dobraDir;
	buffer[i+1][j+1] = ladoDir;
	buffer[i+2][j+2] = ladoDir;
	buffer[i+3][j+3] = ladoDir;
	buffer[i+4][j+4] = ladoDir;
	buffer[i+5][j+5] = ladoDir;
	buffer[i+5][j+6] = chao;
	buffer[i+5][j+7] = chao;
	buffer[i+5][j+8] = chao;
	buffer[i+5][j+9] = chao;
	buffer[i+5][j+10] = chao;
	buffer[i+6][j+11] = ladoDir;
	buffer[i+7][j+12] = ladoDir;
	buffer[i+8][j+13] = ladoDir;
	buffer[i+9][j+14] = ladoDir;
	buffer[i+10][j+15] = ladoDir;
	//lado esquerdo montanha
	buffer[i][j-1] = dobraEsq;
	buffer[i+1][j-1] = ladoEsq;
	buffer[i+2][j-2] = ladoEsq;
	buffer[i+3][j-3] = ladoEsq;
	buffer[i+4][j-4] = ladoEsq;
	buffer[i+5][j-5] = ladoEsq;
	buffer[i+5][j-6] = chao;
	buffer[i+5][j-7] = chao;
	buffer[i+5][j-8] = chao;
	buffer[i+5][j-9] = chao;
	buffer[i+5][j-10] = chao;
	buffer[i+6][j-11] = ladoEsq;
	buffer[i+7][j-12] = ladoEsq;
	buffer[i+8][j-13] = ladoEsq;
	buffer[i+9][j-14] = ladoEsq;
	buffer[i+10][j-15] = ladoEsq;
}

void montanhaM2(char buffer[][MAX_WIDTH], int i, int j){
	int topo = 196, dobraEsq = 194, dobraDir = 191, ladoEsq = 47, ladoDir = 92, chao = 95;
	buffer[i][j] = topo;
	//lado esquerdo
	buffer[i][j-1] = topo;
	buffer[i][j-2] = topo;
	buffer[i][j-3] = dobraEsq;
	buffer[i+1][j-4] = ladoEsq;
	buffer[i+2][j-5] = ladoEsq;
	buffer[i+3][j-6] = ladoEsq;
	buffer[i+4][j-7] = ladoEsq;
	buffer[i+5][j-8] = ladoEsq;
	//lado direito
	buffer[i][j+1] = topo;
	buffer[i][j+2] = topo;
	buffer[i][j+3] = dobraDir;
	buffer[i+1][j+4] = ladoDir;
	buffer[i+2][j+5] = ladoDir;
	buffer[i+3][j+6] = ladoDir;
	buffer[i+4][j+7] = ladoDir;
}

void cordilheira(char buffer[][MAX_WIDTH]){
	montanhaM2(buffer, 5, 8);
	montanha(buffer, 0, 30);
	montanhaM2(buffer, 5, 53);
}

void Enemy_Jump(char screen[][MAX_WIDTH]){
    int gravity = 1;
  //                Clearing Last Enemy Position
  for(int i=0;i<3;i++){
    for(int j=0;j<4;j++){
      screen[soldier.y+i][soldier.x+j] = ' ';
    }
  }

  //                Updating Enemy Position
soldier.y = soldier.y + soldier.vy;


  for (int i=0;i<3;i++){  //    Drawing Enemy Position
    for(int j=0;j<4;j++){
      if(screen[soldier.y+i][soldier.x+j]!= P_Bullet){
        screen[soldier.y+i][soldier.x+j] = soldier.img[i][j];
      }
    }
  }


    if(soldier.y< POSITION_ON_FLOOR){//If is jumping
      soldier.vy = soldier.vy + gravity;
    }else{
      soldier.vy = 0;
    }

}

void Enemy_Features_S1(char screen[][MAX_WIDTH]){

  soldier.v_shoot = 2;// Vel_shoot Enemy

    //Enemies Feature-------------------------------
  int Distance = 20;//Distance between enemy -------------------------att

  for(int i=0;i<N_ENEMY_1; i++){

    if(Steps == i*Distance && enemy_stage_1[i] == 1){

      Enemy = 1;
      Load_Sprite(&soldier, MAX_WIDTH-6, POSITION_ON_FLOOR, 20, 0, 2);//--------------------att
      for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
          screen[soldier.y+i][soldier.x+j] = soldier.img[i][j];
        }
      }
      enemy_stage_1[i] = 0;
    }    //vx Setting to V_Shoot
  }

  if(Enemy == 1){
    count++;
    E_Jump++;
    if(count == soldier.vx){
      Generate_Bullet(&soldier, screen, 2);
      count = 0;
    }

    if(E_Jump== 15){
      soldier.vy = -3;
      E_Jump=0;
    }
  }
}

void Enemy_Features_S2(char screen[][MAX_WIDTH]){

  soldier.v_shoot = 2;// Vel_shoot Enemy

    //Enemies Feature-------------------------------
  int Distance = 20;//Distance between enemy -------------------------att

  for(int i=0;i<N_ENEMY_1; i++){

    if(Steps == i*Distance && enemy_stage_2[i] == 1){

      Enemy = 1;
      Load_Sprite(&soldier, MAX_WIDTH-6, POSITION_ON_FLOOR, 15, 0, 2);//-----Cad_Shoot 20
      for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
          screen[soldier.y+i][soldier.x+j] = soldier.img[i][j];
        }
      }
      enemy_stage_2[i] = 0;
    }    //vx Setting to Cad_Shoot
  }

  if(Enemy == 1){
    count++;
    if(count == soldier.vx){
      Generate_Bullet(&soldier, screen, 2);
      count = 0;
    }

    if(screen[soldier.y+1][soldier.x-2]==P_Bullet&&E_Jump<2){
      soldier.vy = -3;
      E_Jump++;
    }else if(screen[soldier.y+1][soldier.x-3]==P_Bullet&&E_Jump<2){
      soldier.vy = -3;
      E_Jump++;
    }

  }

  if(Enemy==0&&E_Jump==2){
    E_Jump=0; //If Enemy Die, Reset E_Jump Count

  }
}

void Enemy_Features_S3(char screen[][MAX_WIDTH]){
  soldier.v_shoot = 2;// Vel_shoot Enemy

    //Enemies Feature-------------------------------
  int Distance = 20;//Distance between enemy -------------------------att
  if(Boss==0){
    for(int i=0;i<N_ENEMY_1; i++){

      if(Steps == i*Distance && enemy_stage_3[i] == 1){

        Enemy = 1;
        Load_Sprite(&soldier, MAX_WIDTH-6, POSITION_ON_FLOOR, 5, 0, 2);//------Cad Shoot--att
        for(int i=0;i<3;i++){
          for(int j=0;j<4;j++){
            screen[soldier.y+i][soldier.x+j] = soldier.img[i][j];
          }
        }
        enemy_stage_3[i] = 0;
      }    //vx Setting to Cad_Shoot
    }

  }else if(Boss==1){
    Boss_Spawn(screen);
  }

  if(Boss==0){
    if(Enemy == 1){
      count++;
      E_Jump++;
      if(count == soldier.vx){
        Generate_Bullet(&soldier, screen, 2);
        count = 0;
      }

      if(E_Jump== 15){      //Time Jump ---------------------------------------------------att
        soldier.vy = -3;
        E_Jump=0;
      }
    }

  }else if(Boss==1){
    Boss_Features(screen);
  }
}

void logo_end_game(){
  FILE *arch8;
  char text8[50];
  arch8=fopen("FIM.txt","r");
   while(fgets(text8,50,arch8)!=NULL){
     printf("%s",text8);
   }
  printf("\n\n\n");
  system("PAUSE");
  fclose(arch8);
  system("cls");

}

void game_over(){
  FILE *arch9;
  char text9[50];
  arch9=fopen("Game_Over.txt","r");
   while(fgets(text9,50,arch9)!=NULL){
     printf("%s",text9);
   }
  printf("\n\n\n");
  system("PAUSE");
  fclose(arch9);
  system("cls");
}

void Hist1(){
  FILE *arch3;
  char text5[50];
  arch3=fopen("Stage1_Ini.txt","r");
   while(fgets(text5,50,arch3)!=NULL){
     printf("%s",text5);
   }
  printf("\n\n\n");
  system("PAUSE");
  fclose(arch3);
  system("cls");

  arch3=fopen("Hist1.txt","r");
   while(fgets(text5,50,arch3)!=NULL){
     printf("%s",text5);
   }
  printf("\n\n\n");
  system("PAUSE");
  fclose(arch3);
  system("cls");
}

void Hist2(){
  FILE *arch5;
  char text6[50];

  arch5=fopen("Stage2_Ini.txt","r");
   while(fgets(text6,50,arch5)!=NULL){
     printf("%s",text6);
   }
  printf("\n\n\n");
  system("PAUSE");
  fclose(arch5);
  system("cls");

  arch5=fopen("Hist2.txt","r");
   while(fgets(text6,50,arch5)!=NULL){
     printf("%s",text6);
   }
  printf("\n\n\n");
  system("PAUSE");
  fclose(arch5);
  system("cls");
}

void Hist3(){

  FILE *arch6;
  char text7[50];
  arch6=fopen("Stage3_Ini.txt","r");
   while(fgets(text7,50,arch6)!=NULL){
     printf("%s",text7);
   }
  printf("\n\n\n");
  system("PAUSE");
  fclose(arch6);
  system("cls");

  arch6=fopen("Hist3.txt","r");
   while(fgets(text7,50,arch6)!=NULL){
     printf("%s",text7);
   }
  printf("\n\n\n");
  system("PAUSE");
  fclose(arch6);
  system("cls");

}

void airdropC(char buffer[][MAX_WIDTH], int vel_i, int vel_j, int i, int j){
    int airdrop = 219, ladoDir = 41, ladoEsq = 40, corpo = 203;
    if(caduntDrop==1){
        if(airdropFixo==1){
            buffer[MAX_HEIGHT-6][MAX_WIDTH-38] = airdrop;
            buffer[MAX_HEIGHT-7][MAX_WIDTH-38] = corpo;
            buffer[MAX_HEIGHT-7][MAX_WIDTH-40] = ladoEsq;
            buffer[MAX_HEIGHT-7][MAX_WIDTH-36] = ladoDir;
        }else if(i+vel_i<MAX_HEIGHT-6 && j - vel_j <= MAX_WIDTH && j-vel_j>=0){//j=-5 9x e i=-3 7x
            i = i+vel_i;
            j = j-vel_j;
            buffer[i][j] = airdrop;
            buffer[i-1][j] = corpo;
            buffer[i-1][j+1] = ladoEsq;
            buffer[i-1][j-1] = ladoEsq;
        }
        if(i==18){
            airdropFixo=1;
        }
    }
}

void Catch_airdrop(char screen[][MAX_WIDTH], int *Life, int mode){
  if(airdropFixo==1){
    if(player.x==MAX_WIDTH-38){
      airdropFixo = 0;
      caduntDrop = 0;
      if(mode==1){
        DEF_CAD_P_SHOOT = 5;
      }
      else if(mode==2){
        *Life += 50;
        if(*Life>100){
          *Life = 100;
        }
      }
    }
  }
}

void Boss_Spawn(char screen[][MAX_WIDTH]){

  Enemy = 1;
  Load_Sprite(&soldier, MAX_WIDTH-6, POSITION_ON_FLOOR, 10, 0, 3);//--------------------att
  for(int i=0;i<3;i++){
    for(int j=0;j<4;j++){
      screen[soldier.y+i][soldier.x+j] = soldier.img[i][j];
    }
  }
}

void Boss_Features(char screen[][MAX_WIDTH]){

  count++;// count of Bullets
  E_Jump++;//count of  Jump Enemy
  if(count == soldier.vx){
    Generate_Bullet(&soldier, screen, 2);
    count = 0;
  }

  if(screen[soldier.y+1][soldier.x-2]==P_Bullet&&E_Jump<3){
    soldier.vy = -3;
    E_Jump++;
  }else if(screen[soldier.y+1][soldier.x-3]==P_Bullet&&E_Jump<3){
    soldier.vy = -3;
    E_Jump++;
  }

  if(E_Jump>2&&E_Jump<5){//Time from Boss Jump Setting to 2 frames(-3-5)
    E_Jump++;
  }
  else if(E_Jump==5){
    E_Jump = 0;
  }

}
