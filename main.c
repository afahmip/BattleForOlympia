#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "GameController.h"
#include "Undo.h"
#include "User.h"
#include "Unit.h"
#include "boolean.h"
#include "Point/Point.h"


/* Var Global */
int i; //Iterating variable
int width, height, x, y;
int idxEnemy, idxUnit;
int number_of_player, playerID, currUnitID;
Unit *unitEnemy, *myUnit;
Map map;
char command[20];
Player currPlayer;
boolean IsOneKing, validCommand, IsExit;


void initializeMap(Map* map) {
    scanf("%d %d", &height, &width);
    createMap(height, width, map);
    generateMap(4, width, height, map);
    printMap(*map);
}

int main() {
    srand(time(NULL));
    printf("Start a New Game!\n");

	/* Create map */
	printf("Insert map size :\n");
	printf("Width : ");
	scanf("%d", &width);
	printf("Height : ");
	scanf("%d", &height);
	createMap(height, width, &map);

	/* Create players */
	printf("How many players do you want : ");
	scanf("%d", &number_of_player);
	createPlayers(&map, number_of_player);
	printMap(map);

	/* Initialize */
	IsOneKing = false;
	IsExit = false;

	while(!IsOneKing && !IsExit){
		for(i = 1; i <= number_of_player; i++){
			/* Initialize */
			playerID = i;
			currUnitID = 0;
			currPlayer = *getPlayer(playerID);
			myUnit = getUnit(currUnitID);

			printf("Player %d's Turn\n", playerID);

			printf("Cash : %dG | Income : %dG | Upkeep : %dG\n", currPlayer.gold, currPlayer.income, currPlayer.upkeep);
			printf("Unit : | Movement Point : %d\n");
			printf("--------------------------------------------\n");

			/* Input command game */
			printf("Insert your command : ");
			scanf("%s", command);
			validCommand = false;
			/* Choose action */
			while(!validCommand){
				if (strcmp(command, "MOVE")==0){

					boolean IsCanMove;
					Point From, To;
					validCommand = true;

					printf("\n");
					printMap(map);
					printf("\n");
					printf("Please​ ​enter​ ​cell’s​ ​coordinate​ ​x​ ​y :​ ");
					scanf("%d %d",&x,&y);
					To = MakePoint(x, y);
					IsCanMove = moveUnit(&map, currUnitID, absis(To), ordinat(To));
					while(!IsCanMove){
						printf("You​ ​can’t​ ​move​ ​there\n");
						printf("Please​ ​enter​ ​cell’s​ ​coordinate​ ​x​ ​y :​ ");
						scanf("%d %d",&x,&y);
						To = MakePoint(x, y);
						IsCanMove = moveUnit(&map, currUnitID, absis(To), ordinat(To));
					}
					//registerMove(currUnitID, &map, );
					printf("You​ ​have​ ​successfully​ ​moved​ ​to​ (%d, %d)\n", x, y);

				}else if (strcmp(command, "UNDO")==0){

					validCommand = true;
					
					undo(&map);
					printMap(map);

				}else if (strcmp(command, "CHANGE_UNIT")==0){

					int *listOfUnit;
					int numberOrUnit;
					validCommand = true;
					
					printf("=== List of Units ===\n");
					//

				}else if (strcmp(command, "RECRUIT")==0){

					boolean castleOccupied=true;
					int RecruitID;
					Point From, To;
					validCommand = true;
					
					printf("Enter coordinate of empty castle : ");
					scanf("%d %d",&x,&y);
					To = MakePoint(x, y);
					//Occupy_castle
					while(castleOccupied){
						printf("That​ ​castle​ ​is​ ​occupied!\n");
						printf("Enter coordinate of empty castle : ");
						scanf("%d %d",&x,&y);
						To = MakePoint(x, y);
						//Occupy_castle
					}
					printf("\n=== List of Recruits ===\n");
					printf("Enter​ ​no.​ ​of​ ​unit​ ​you​ ​want​ ​to​ ​recruit : ");
					scanf("%d", &RecruitID);
					printf("You​ ​have​ ​recruited​ ​an​ !\n");

				}else if (strcmp(command, "ATTACK")==0){

					int* listOfTarget;
					int numberOfTarget, idEnemy;
					char enemyName[20], charName[20];
					boolean battleDone=false;
					BattleResult battleResult;
					validCommand = true;
					
					initUndo();
					printf("Enemies that ​you​ ​can ​attack :\n");
					getTargetID(&map, currUnitID, listOfTarget, &numberOfTarget);

					/* Print enemy list */
					for (int j = 0; j < numberOfTarget; j++) {
						Unit *unit = getUnit(listOfTarget[i]);
						switch (unitTypes[unit->type].mapSymbol){
							case 'K' :
								strcpy(enemyName, "King");
								break;
							case 'A' :
								strcpy(enemyName, "Archer");
								break;
							case 'S' :
								strcpy(enemyName, "Swordsman");
								break;
							case 'W' :
								strcpy(enemyName, "White Mage");
								break;
						}
						printf("%d. %s (%d, %d) | Health %d/%d ", j+1, enemyName,
							unit->location.X, unit->location.Y, unit->health, unitTypes[unit->type].maxHealth);
						
						/* Check if enemy can retaliate */
						if(unitTypes[unit->type].atkType == unitTypes[myUnit->type].atkType)
							printf("(Retaliates)\n");
						else printf("\n");
					}

					/* Battle process */
					while(!battleDone){
						/* Choose enemy */
						printf("Select enemy you want to attack : ");
						scanf("%d", &idxEnemy);

						idEnemy = listOfTarget[idxEnemy - 1];

						/* Battle started */
						battleResult = procBattle(&map, idxUnit, idEnemy);

						unitEnemy = getUnit(idEnemy);

						if(battleResult.battleFlag == ATTACK_SUCCEED){
							//printf("Enemy’s​ %s ​is​ ​damaged​ ​by​, %d",battleResult.atkDamageDone);
							if(unitTypes[unitEnemy->type].atkType == unitTypes[myUnit->type].atkType){
								printf("Enemy’s​ retaliates.\n");
							}
							battleDone = true;
						}else if(battleResult.battleFlag == ATTACK_MISSED){
							printf("Attack missed! Poor you...\n");
							battleDone = true;
						}else if(battleResult.battleFlag == ATTACK_NOT_PERFORMED){
							printf("You can't attack this unit!\n");
						}
					}

				}else if (strcmp(command, "MAP")==0){ //UDAH JADI

					validCommand = true;
					
					printf("\n");
					printMap(map);
					printf("\n");

				}else if (strcmp(command, "INFO")==0){ //UDAH JADI

					validCommand = true;
					
					printf("Enter​ ​the​ ​coordinate​ ​of​ ​the​ ​cell : ");
					scanf("%d %d",&x,&y);
					printInfoSquare(x, y, map);

				}else if (strcmp(command, "END_TURN")==0){ //UDAH JADI

					validCommand = true;

					printf("Your turn has ended.\n");
					break;

				}else if (strcmp(command, "SAVE")==0){

					validCommand = true;
					

				}else if (strcmp(command, "EXIT")==0){ //UDAH JADI

					validCommand = true;
					char Exit;
					
					printf("Are you sure want to exit? (y/n) : ");
					scanf("%c", &Exit);
					if(Exit == 'n')break;
					else IsExit = true;

				}else{ //UDAH JADI

					printf("Invalid command!\n");
					printf("Insert your command : ");
					scanf("%s", command);

				}
			}
		}
	}
    return 0;
}
