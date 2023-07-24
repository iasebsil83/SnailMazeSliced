/*
-------------------- SNAIL MAZE SLICED --------------------
|      Remake of the built-in game of SEGA Master System  |
|  BIOS Snail Maze.                                       |
|                                                         |
|   Game realised for ISEN Engineering - Challenge        |
|                                                         |
|     The Maze is now displayed from the side of the      |
| snail only.                                             |
|                                                         |
| Pressing key M will show you the map. (debug or cheat)  |
|                                                         |
| Enjoy !                                                 |
|                                                         |
| Contact     : i.a.sebsil83@gmail.com                    |
| Youtube     : https://www.youtube.com/user/IAsebsil83   |
| GitHub repo : https://github.com/iasebsil83             |
|                                                         |
| Let's Code !                                     By I.A.|
**************************************************************************
|    LICENSE :                                                           |
|                                                                        |
|   SnailMazeSliced_GfxLib                                               |
|   Copyright (C) 2020 Sebastien SILVANO                                 |
|                                                                        |
|   This program is free software: you can redistribute it and/or modify |
|   it under the terms of the GNU General Public License as published by |
|   the Free Software Foundation, either version 3 of the License, or    |
|   (at your option) any later version.                                  |
|                                                                        |
|   This program is distributed in the hope that it will be useful,      |
|   but WITHOUT ANY WARRANTY; without even the implied warranty of       |
|   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        |
|   GNU General Public License for more details.                         |
|                                                                        |
|   You should have received a copy of the GNU General Public License    |
|   along with this program.                                             |
|                                                                        |
|   If not, see <https://www.gnu.org/licenses/>.                         |
--------------------------------------------------------------------------
*/












// ==================== IMPORTATIONS =======================

//standard files
#include <stdlib.h>
#include <stdio.h>

//graphic files
#include "../lib/GfxLib.h" //graphics
#include "../lib/ESLib.h"












//===================== DECLARATIONS =========================

#define HEIGHT 7
#define LENGTH 40
#define END_X 39
#define END_Y 2

//game vars
static char menu = 's'; //s:start_menu, m:maze, e:end_menu
static int px = 0;
static int py = 2;
static char map[HEIGHT][LENGTH] = { // :space, #:wall, ^:upAccess, v:downAccess, {:bothAccess, G:end
    "######################v   ##############",
//   #####################| |################
    "##     v#v     v####v ^#################",
//   ######| | |###| |##| |##################
    "       ^ ^ ### ^    {  ##########v     G",
//   ###################| |##########| |#####
    "##  v ####v         ^            ^ #####",
//   ###| |###| |############################
    "####^  v  ^######################### v #",
//   ######| |###########################| |#
    "#######^                             ^##",
};
static bool upViewPoint = false;
static bool right = true;

//textures
img snailR;
img snailL;












// ===================== FUNCTIONS ========================

//Usefull functions
int inZone(int x,int y, int xmin,int ymin, int xmax,int ymax){
	if(xmax < xmin){
		int temp = xmin;
		xmin = xmax;
		xmax = temp;
	}
	if(ymax < ymin){
		int temp = ymin;
		ymin = ymax;
		ymax = temp;
	}
	return (x <= xmax && x >= xmin && y <= ymax && y >= ymin);
}












// =================== MAIN EXECUTION ======================

//game files
#include "keys.c"
#include "click.c"
#include "display.c"

//main
int main(int argc, char **argv){
	//init graphics
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("Snail Maze Slice", 800,400);
	lanceBoucleEvenements();
	return 0;
}

void gestionEvenement(EvenementGfx evenement){
	switch(evenement){
		case Initialisation:
			epaisseurDeTrait(3);
			//snail seeing right
			snailR.width = 16;	snailR.height = 16;
			snailR.data = NULL;
			snailR = readRGBA2ARVB("sprites/SnailR.rgba",snailR);
			//snail seeing left
			snailL.width = 16;	snailL.height = 16;
			snailL.data = NULL;
			snailL = readRGBA2ARVB("sprites/SnailL.rgba",snailL);
		break;
		case Temporisation:
		break;
		case Affichage:
			display(
				menu,map,px,py,upViewPoint,snailL,snailR,right
			);
		break;
		case Clavier:
			keyEvent(
				caractereClavier(),
				&menu,map,&px,&py,&upViewPoint,&right
			);
			rafraichisFenetre();
		break;
		case ClavierSpecial:
		break;
		case BoutonSouris:
			if(etatBoutonSouris() == GaucheAppuye){
				clickEvent(
					abscisseSouris(),ordonneeSouris(),
					&menu,map
				);
				rafraichisFenetre();
			}
		break;
		case Souris:
		break;
		case Inactivite:
		break;
		case Redimensionnement:
		break;
	}
}
