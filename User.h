//
// Created by gery on 09/11/17.
//

#ifndef BATTLEFOROLYMPIA_USER_H
#define BATTLEFOROLYMPIA_USER_H

#include "Unit.h"
#include "Map.h"

#define STARTING_GOLD 100
#define STARTING_INCOME 100

typedef struct {
    int gold, income, upkeep, color;
    lcList units;
} Player;

void addUnit(int playerID, int unitID);
	//terima player ID

void removeUnit(int playerID, int unitID);

Player* getPlayer(int ID);

int createPlayer(const Map* map);

#endif //BATTLEFOROLYMPIA_USER_H
