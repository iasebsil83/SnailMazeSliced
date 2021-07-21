// ======================== CLICK =========================

void clickEvent(int x, int y, char* menu, char map[HEIGHT][LENGTH]){
	switch(*menu){
		case 's': //start_menu
			//play button
			if(inZone(x,y,250,170,530,230)){
				*menu = 'm'; //maze
			//exit button
			}else if(inZone(x,y,250,40,530,100)){
				termineBoucleEvenements();
				exit(1);
			}
		break;
		case 'm': //maze
		break;
		case 'e': //end_menu
			//exit button
			if(inZone(x,y,250,190,530,250)){
				termineBoucleEvenements();
				exit(1);
			}
		break;
	}
}
