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
| Pressing key S will show you the map. (debug or cheat)  |
|                                                         |
| Enjoy !                                                 |
|                                                         |
| Contact     : i.a.sebsil83@gmail.com                    |
| Youtube     : https://www.youtube.com/user/IAsebsil83   |
| GitHub repo : https://github.com/iasebsil83             |
|                                                         |
| Let's Code !                                     By I.A.|
-----------------------------------------------------------
*/




















// ==================== IMPORTATIONS =======================

//standard files
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



//graphics
#include "S2DE.h"



//image utility
#include "img.c"




















//===================== DECLARATIONS =========================

//dimensions
#define MAXL 800
#define MAXH 400
#define HEIGHT 7
#define LENGTH 40
#define END_X 39
#define END_Y 2



//menus
#define MENU_START 's'
#define MENU_MAZE 'm'
#define MENU_END 'e'



//S2DE
extern int S2DE_keyState;
extern short S2DE_key;
extern int S2DE_mouseState;
extern int S2DE_mouseButton;
extern int S2DE_mouseX;
extern int S2DE_mouseY;



//game vars
static char menu = MENU_START;
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



//display vars
#define os_x 80 //offsets
#define os_y 200
#define bs 16 //boxsize (in pixel)



//textures
img snailR = { .width = 16, .height = 16, .data = NULL};
img snailL = { .width = 16, .height = 16, .data = NULL};




















// ===================== UTILITIES ========================

//mouse utility
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

void showCase(int dy, int dx){
	switch(map[dy][dx]){
		case ' ': //void
			S2DE_setColor(0,0,255);
			S2DE_rectangle(
				os_x+    dx*bs,	os_y+    dy*bs,
				os_x+(dx+1)*bs, os_y+(dy+1)*bs,
				true
			);
		break;
		case '#': //wall
			S2DE_setColor(50,100,255);
			S2DE_rectangle(
				os_x+    dx*bs,	os_y+    dy*bs,
				os_x+(dx+1)*bs, os_y+(dy+1)*bs,
				true
			);
		break;
		case '^': //upAccess
			S2DE_setColor(0,0,255);
			S2DE_rectangle(
				os_x+    dx*bs,	os_y+    dy*bs,
				os_x+(dx+1)*bs, os_y+(dy+1)*bs,
				true
			);
			S2DE_setColor(90,0,100);
			S2DE_rectangle(
				os_x+    dx*bs, os_y+       dy*bs,
				os_x+(dx+1)*bs, os_y+(dy+0.33)*bs,
				true
			);
		break;
		case 'v': //downAccess
			S2DE_setColor(0,0,255);
			S2DE_rectangle(
				os_x+    dx*bs,	os_y+    dy*bs,
				os_x+(dx+1)*bs, os_y+(dy+1)*bs,
				true
			);
			S2DE_setColor(90,0,100);
			S2DE_rectangle(
				os_x+    dx*bs, os_y+(dy+0.67)*bs,
				os_x+(dx+1)*bs, os_y+   (dy+1)*bs,
				true
			);
		break;
		case '{': //bothAccess
			S2DE_setColor(0,0,255);
			S2DE_rectangle(
				os_x+    dx*bs,	os_y+    dy*bs,
				os_x+(dx+1)*bs, os_y+(dy+1)*bs,
				true
			);
			S2DE_setColor(90,0,100);
			S2DE_rectangle(
				os_x+    dx*bs, os_y+       dy*bs,
				os_x+(dx+1)*bs, os_y+(dy+0.33)*bs,
				true
			);
			S2DE_rectangle(
				os_x+    dx*bs, os_y+(dy+0.67)*bs,
				os_x+(dx+1)*bs, os_y+   (dy+1)*bs,
				true
			);
		break;
		case 'G': //end
			S2DE_setColor(255,255,255);
			S2DE_rectangle(
				os_x+    dx*bs, os_y+    dy*bs,
				os_x+(dx+1)*bs, os_y+(dy+1)*bs,
				true
			);
		break;
	}
}




















// =================== MAIN EXECUTION ======================

//S2DE events
void S2DE_event(int event){
	switch(event){

		case S2DE_DISPLAY:
			switch(menu){

				case MENU_START:
					S2DE_setColor(0,0,0);
					S2DE_rectangle(0,0, MAXL,MAXH, true);

					//button zones
					S2DE_setColor(0,0,255);
					S2DE_rectangle(250,170,530,230, true); //play
					S2DE_rectangle(250,40,530,100, true);  //exit

					//text : MAZE (red on yellow)
					S2DE_setColor(255,255,0);
					S2DE_setThickness(7);
					S2DE_text("MAZE",0.46,298,275);
					S2DE_setColor(255,0,0);
					S2DE_setThickness(5);
					S2DE_text("MAZE",0.46,298,275);

					//text : other
					S2DE_setColor(255,255,255);
					S2DE_setThickness(4);
					S2DE_text("Snail      Sliced",0.417,40,270);
					S2DE_setThickness(3);
					S2DE_text("Play",0.33,320,185);
					S2DE_text("Exit",0.33,320,55);
				break;

				case MENU_MAZE:
					S2DE_setColor(0,0,0);
					S2DE_rectangle(0,0, MAXL,MAXH, true);

					//display the whole maze
					for(unsigned int dx=0; dx < LENGTH; dx++){

						//whole terrain selected
						for(unsigned int dy=0; dy < HEIGHT; dy++)
							showCase(dy,dx);

						//only the concerned line
						showCase(py,dx);
					}

					//player
					S2DE_setColor(0,255,0);
					if(right)
						S2DE_imageRGBA(
							os_x+px*bs, os_y+py*bs,
							snailL.width, snailL.height,
							snailR.data
						);
					else
						S2DE_imageRGBA(
							os_x+px*bs, os_y+py*bs,
							snailL.width, snailL.height,
							snailL.data
						);
				break;

				case MENU_END:
					S2DE_setColor(0,0,0);
					S2DE_rectangle(0,0, MAXL,MAXH, true);

					//button zone
					S2DE_setColor(0,0,255);
					S2DE_rectangle(250,190,530,250, true);

					//text : exit
					S2DE_setColor(255,255,255);
					S2DE_setThickness(3);
					S2DE_text("Exit",0.33,320,200);
				break;
			}
		break;

		case S2DE_KEYBOARD:
			if(S2DE_keyState == S2DE_KEY_RELEASED) //keep only "key pressed" events
				break;
			switch(menu){

				case MENU_START:
					if(S2DE_key == S2DE_KEY_Q || S2DE_key == S2DE_KEY_q){
						S2DE_stop();
						exit(EXIT_SUCCESS);
					}
				break;

				case MENU_MAZE:
					switch(S2DE_key){
						case S2DE_KEY_Z:
						case S2DE_KEY_z: //go up
							if(map[py][px] == 'v' || map[py][px] == '{')
								py++;
						break;
						case S2DE_KEY_S:
						case S2DE_KEY_s: //go down
							if(map[py][px] == '^' || map[py][px] == '{')
								py--;
						break;
						case S2DE_KEY_Q:
						case S2DE_KEY_q:
							if(px){
								if(
									map[py][px-1] == ' ' || map[py][px-1] == '^' ||
									map[py][px-1] == 'v' || map[py][px-1] == '{'
								){
									px--;
									right = false;
								}
							}
						break;
						case S2DE_KEY_D:
						case S2DE_KEY_d:
							if(px != LENGTH-1){
								if(
									map[py][px+1] == ' ' || map[py][px+1] == '^' ||
									map[py][px+1] == 'v' || map[py][px+1] == '{' ||
									map[py][px+1] == 'G'
								){
									px++;
									right = true;
								}
							}
						break;
						case S2DE_KEY_m:
						case S2DE_KEY_M:
							upViewPoint = !upViewPoint;
						break;
					}
					if(px == END_X && py == END_Y)
						menu = MENU_END;
				break;

				case MENU_END:
					if(S2DE_key == S2DE_KEY_q){
						S2DE_stop();
						exit(EXIT_SUCCESS);
					}
				break;
			}
			S2DE_refresh();
		break;

		case S2DE_MOUSECLICK:
			if(S2DE_mouseState == S2DE_MOUSE_PRESSED && S2DE_mouseButton == S2DE_LEFT_BUTTON){
				switch(menu){
					case MENU_START:
						//play button
						if(inZone(S2DE_mouseX,S2DE_mouseY, 250,170,530,230)){
							menu = MENU_MAZE;

						//exit button
						}else if(inZone(S2DE_mouseX,S2DE_mouseY, 250,40,530,100)){
							S2DE_stop();
							exit(EXIT_SUCCESS);
						}
					break;

					case MENU_MAZE:
					break;

					case MENU_END:
						//exit button
						if(inZone(S2DE_mouseX,S2DE_mouseY, 250,190,530,250)){
							S2DE_stop();
							exit(EXIT_SUCCESS);
						}
					break;
				}
				S2DE_refresh();
			}
		break;
	}
}

//main
int main(int argc, char **argv){

	//set textures
	snailR = readRGBA2ARVB("SnailR.rgba",snailR);
	snailL = readRGBA2ARVB("SnailL.rgba",snailL);

	//init graphics
	S2DE_init(argc,argv, "Snail Maze Slice", MAXL,MAXH);

	//launch S2DE
	S2DE_start();

	return EXIT_SUCCESS;
}
