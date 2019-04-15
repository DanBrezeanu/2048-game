// Copyright 2017 Brezeanu Dan-Eugen
#include "./functions.h"


int main()
{
	POINT *poz;
	int selection, game_over_output = 0;
	bool quit = FALSE;

	poz = calloc(N_CELLS + 3, sizeof(POINT));

	start_graphics();	

	while(!quit)
	{
		selection = navigate_menu(poz);

		switch(selection)
		{
			case 1 : 
				label3 :
				clear_screen();
				game_over_output = start_new_game(poz);
				break;

			case 2 :
				game_over_output = resume_game(poz);
				break;

			case 3 : 
				clear_screen();
				quit = 1;
				break;		

		}
		if(game_over_output == 1)
			goto label3;
			else if(game_over_output == 2)
			quit = 1;

	}

	end_graphics();

	free(poz);

	return 0;
}
