/*
	------------------- SNAIL MAZE SLICED -------------------
	|  Remake of the built-in game of SEGA Master System	|
	|				SEGA BIOS Snail Maze 					|
	|														|
	|   Game realised for ISEN Engineering - Challenge		|
	|														|
	|	  The Maze is now displayed from the side of the 	|
	|	snail as it should be regarding the snail's sprite  |
	|		Pressing the key S will show you the map 		|
	|			   from the top of the maze.				|
	|														|
	|						Enjoy !							|
	|												 By I.A.| (Sebastien SILVANO)
	---------------------------------------------------------

	In there is any issue executing the game, please report to i.a.sebsil83@gmail.com
*/



//===================== DEFINITION =========================

#define HEIGHT 7
#define LENGTH 40
#define END_X 39
#define END_Y 2



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



// ==================== IMPORTATIONS =======================

//standard files
#include <stdlib.h> //To use exit()
#include <stdio.h>  //To use printf()

//graphic files
#include "GfxLib.h" //graphics
#include "ESLib.h"  //To use valeurAleatoire()

//game files
#include "keys.c"
#include "click.c"
#include "display.c"



// ==================== DECLARATIONS =======================

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



// =================== MAIN EXECUTION ======================

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
			snailR = readRGBA2ARVB("SnailR.rgba",snailR);
			//snail seeing left
			snailL.width = 16;	snailL.height = 16;
			snailL.data = NULL;
			snailL = readRGBA2ARVB("SnailL.rgba",snailL);
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
