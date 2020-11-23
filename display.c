// ======================= DISPLAY ========================

void display(char menu, char map[HEIGHT][LENGTH], unsigned short int px, unsigned short int py, bool upViewPoint, img snailL, img snailR, bool right){
	unsigned short int os_x = 80; //offsets
	unsigned short int os_y = 200;
	unsigned short int bs = 16; //boxsize (in pixel)
	switch(menu){
		case 's': //start_menu
			effaceFenetre(0,0,0);
			//button zones
			couleurCourante(0,0,255);
			rectangle(250,170,530,230); //play
			rectangle(250,40,530,100);  //exit
			//text : MAZE (red on yellow)
			couleurCourante(255,255,0);
			epaisseurDeTrait(7);
			afficheChaine("MAZE",55,298,275);
			couleurCourante(255,0,0);
			epaisseurDeTrait(5);
			afficheChaine("MAZE",55,298,275);
			//text : other
			couleurCourante(255,255,255);
			epaisseurDeTrait(4);
			afficheChaine("Snail      Sliced",50,40,270);
			epaisseurDeTrait(3);
			afficheChaine("Play",40,320,185);
			afficheChaine("Exit",40,320,55);
		break;
		case 'm': //maze
			effaceFenetre(0,0,0);
			if(upViewPoint){
				for(unsigned int dy=0; dy < HEIGHT; dy++){
					for(unsigned int dx=0; dx < LENGTH; dx++){
						switch(map[dy][dx]){
							case ' ': //void
								couleurCourante(0,0,255);
								rectangle(
									os_x+    dx*bs,	os_y+    dy*bs,
									os_x+(dx+1)*bs, os_y+(dy+1)*bs
								);
							break;
							case '#': //wall
								couleurCourante(50,100,255);
								rectangle(
									os_x+    dx*bs,	os_y+    dy*bs,
									os_x+(dx+1)*bs, os_y+(dy+1)*bs
								);
							break;
							case '^': //upAccess
								couleurCourante(0,0,255);
								rectangle(
									os_x+    dx*bs,	os_y+    dy*bs,
									os_x+(dx+1)*bs, os_y+(dy+1)*bs
								);
								couleurCourante(90,0,100);
								rectangle(
									os_x+    dx*bs, os_y+       dy*bs,
									os_x+(dx+1)*bs, os_y+(dy+0.33)*bs
								);
							break;
							case 'v': //downAccess
								couleurCourante(0,0,255);
								rectangle(
									os_x+    dx*bs,	os_y+    dy*bs,
									os_x+(dx+1)*bs, os_y+(dy+1)*bs
								);
								couleurCourante(90,0,100);
								rectangle(
									os_x+    dx*bs, os_y+(dy+0.67)*bs,
									os_x+(dx+1)*bs, os_y+   (dy+1)*bs
								);
							break;
							case '{': //bothAccess
								couleurCourante(0,0,255);
								rectangle(
									os_x+    dx*bs,	os_y+    dy*bs,
									os_x+(dx+1)*bs, os_y+(dy+1)*bs
								);
								couleurCourante(90,0,100);
								rectangle(
									os_x+    dx*bs, os_y+       dy*bs,
									os_x+(dx+1)*bs, os_y+(dy+0.33)*bs
								);
								rectangle(
									os_x+    dx*bs, os_y+(dy+0.67)*bs,
									os_x+(dx+1)*bs, os_y+   (dy+1)*bs
								);
							break;
							case 'G': //end
								couleurCourante(255,255,255);
								rectangle(
									os_x+    dx*bs, os_y+    dy*bs,
									os_x+(dx+1)*bs, os_y+(dy+1)*bs
								);
							break;
						}
					}
				}
			}else{
				for(unsigned int dx=0; dx < LENGTH; dx++){
					switch(map[py][dx]){
						case ' ': //void
							couleurCourante(0,0,255);
							rectangle(
								os_x+    dx*bs,	os_y+    py*bs,
								os_x+(dx+1)*bs, os_y+(py+1)*bs
							);
						break;
						case '#': //wall
							couleurCourante(50,100,255);
							rectangle(
								os_x+    dx*bs,	os_y+    py*bs,
								os_x+(dx+1)*bs, os_y+(py+1)*bs
							);
						break;
						case '^': //upAccess
							couleurCourante(0,0,255);
							rectangle(
								os_x+    dx*bs,	os_y+    py*bs,
								os_x+(dx+1)*bs, os_y+(py+1)*bs
							);
							couleurCourante(90,0,100);
							rectangle(
								os_x+    dx*bs, os_y+       py*bs,
								os_x+(dx+1)*bs, os_y+(py+0.33)*bs
							);
						break;
						case 'v': //downAccess
							couleurCourante(0,0,255);
							rectangle(
								os_x+    dx*bs,	os_y+    py*bs,
								os_x+(dx+1)*bs, os_y+(py+1)*bs
							);
							couleurCourante(90,0,100);
							rectangle(
								os_x+    dx*bs, os_y+(py+0.67)*bs,
								os_x+(dx+1)*bs, os_y+   (py+1)*bs
							);
						break;
						case '{': //bothAccess
							couleurCourante(0,0,255);
							rectangle(
								os_x+    dx*bs,	os_y+    py*bs,
								os_x+(dx+1)*bs, os_y+(py+1)*bs
							);
							couleurCourante(90,0,100);
							rectangle(
								os_x+    dx*bs, os_y+       py*bs,
								os_x+(dx+1)*bs, os_y+(py+0.33)*bs
							);
							rectangle(
								os_x+    dx*bs, os_y+(py+0.67)*bs,
								os_x+(dx+1)*bs, os_y+   (py+1)*bs
							);
						break;
						case 'G': //end
							couleurCourante(255,255,255);
							rectangle(
								os_x+    dx*bs, os_y+    py*bs,
								os_x+(dx+1)*bs, os_y+(py+1)*bs
							);
						break;
					}
				}
			}
			//player
			couleurCourante(0,255,0);
			if(right)
				ecrisImageIMG(os_x+px*bs, os_y+py*bs, snailR);
			else
				ecrisImageIMG(os_x+px*bs, os_y+py*bs, snailL);
		break;
		case 'e': //end_menu
			effaceFenetre(0,0,0);
			//button zone
			couleurCourante(0,0,255);
			rectangle(250,190,530,250);
			//text : exit
			couleurCourante(255,255,255);
			epaisseurDeTrait(3);
			afficheChaine("Exit",40,320,200);
		break;
	}
}
