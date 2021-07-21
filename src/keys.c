// ======================== KEYS ==========================

void keyEvent(char k, char* menu, char map[HEIGHT][LENGTH], int* px, int* py, bool* upViewPoint, bool* right){
	switch(*menu){
		case 's': //start_menu
			if(k == 'q' || k == 'Q'){
				termineBoucleEvenements();
				exit(1);
			}
		break;
		case 'm': //maze
			switch(k){
				case 'Z':
				case 'z': //go up
					if(map[*py][*px] == 'v' || map[*py][*px] == '{')
						*py = *(py)+1;
				break;
				case 'S':
				case 's': //go down
					if(map[*py][*px] == '^' || map[*py][*px] == '{')
						*py = *(py)-1;
				break;
				case 'Q':
				case 'q':
					if(*px != 0){
						if(map[*py][*px-1] == ' ' || map[*py][*px-1] == '^'
						|| map[*py][*px-1] == 'v' || map[*py][*px-1] == '{'){
							*px = *(px)-1;
							*right = false;
						}
					}
				break;
				case 'D':
				case 'd':
					if(*px != LENGTH-1){
						if(map[*py][*px+1] == ' ' || map[*py][*px+1] == '^'
						|| map[*py][*px+1] == 'v' || map[*py][*px+1] == '{'
						|| map[*py][*px+1] == 'G'){
							*px = *(px)+1;
							*right = true;
						}
					}
				break;
				case 'M':
				case 'm':
					*upViewPoint = !*upViewPoint;
				break;
			}
			if(*px == END_X && *py == END_Y)
				*menu = 'e';
		break;
		case 'e': //end_menu
			if(k == 'q' || k == 'Q'){
				termineBoucleEvenements();
				exit(1);
			}
		break;
	}
}
