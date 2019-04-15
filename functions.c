// Copyright 2017 Brezeanu Dan-Eugen
#include "./functions.h"

void start_graphics()
{
	initscr();
	start_color();
	cbreak();
	keypad(stdscr,TRUE);
	noecho();
	curs_set(0);
	refresh();

	attron(A_BOLD);

	init_color(COLOR_4,750,750,900); 
	init_color(COLOR_8,694,230,0);
	init_color(COLOR_16,594,330,0); 
	init_color(COLOR_32,594,50,0); 
	init_color(COLOR_128,950,700,200); 
	init_color(COLOR_256,950,700,0); 
	init_color(COLOR_512,900,814,0); 
	init_color(COLOR_2048,846,998,0); 

	init_pair(COLOR_2, COLOR_BLACK, COLOR_WHITE); 
	init_pair(COLOR_4, COLOR_BLACK, COLOR_4); 
	init_pair(COLOR_8, COLOR_WHITE, COLOR_8);
	init_pair(COLOR_16, COLOR_WHITE, COLOR_16);
	init_pair(COLOR_32, COLOR_WHITE, COLOR_32);
	init_pair(COLOR_64, COLOR_WHITE, COLOR_RED);
	init_pair(COLOR_128, COLOR_WHITE, COLOR_128);
	init_pair(COLOR_256, COLOR_WHITE, COLOR_256); 
	init_pair(COLOR_512, COLOR_WHITE, COLOR_512); 
	init_pair(COLOR_1024, COLOR_WHITE, COLOR_YELLOW); 
	init_pair(COLOR_2048, COLOR_WHITE, COLOR_2048); 
	init_pair(COLOR_4096, COLOR_WHITE, COLOR_MAGENTA);

}

void end_graphics()
{
	clear_screen();
	//curs_set(1);
	attroff(A_BOLD);
	endwin();


}

void show_clock()
{
	int width,height;
    time_t rawtime;
    struct tm*  time_;

    time(&rawtime);
    time_ = localtime(&rawtime);

    getmaxyx(stdscr, width, height);

    if(time_->tm_hour < 10)
    {
    	if(time_->tm_min < 10)
    		mvprintw(width/4+2,height/2+20,"0%i:0%i	 ",time_->tm_hour,time_->tm_min);
    	else
    		mvprintw(width/4+2,height/2+20,"0%i:%i	 ",time_->tm_hour,time_->tm_min);
    }
    else
    {
    	if(time_->tm_min < 10)
    		mvprintw(width/4+2,height/2+20,"%i:0%i	 ",time_->tm_hour,time_->tm_min);
    	else
    		mvprintw(width/4+2,height/2+20,"%i:%i	 ",time_->tm_hour,time_->tm_min);
    }

    mvprintw(width/4+2,height/2+28,"%i/%i/%i",time_->tm_mday, time_->tm_mon+1,time_->tm_year+1900);

    move(width/4 + 6, height/2 + 20); addch(ACS_BULLET);printw(" Q ");addch(ACS_BULLET);printw(" TO QUIT");
    move(width/4 + 8, height/2 + 20); addch(ACS_BULLET);printw(" ");addch(ACS_UARROW);printw(" ");addch(ACS_BULLET);printw(" TO MOVE ALL NUMBERS UPWARDS");
    move(width/4 + 10, height/2 + 20); addch(ACS_BULLET);printw(" ");addch(ACS_RARROW);printw(" ");addch(ACS_BULLET);printw(" TO MOVE ALL NUMBERS RIGHTWARDS");
    move(width/4 + 12, height/2 + 20); addch(ACS_BULLET);printw(" v ");addch(ACS_BULLET);printw(" TO MOVE ALL NUMBERS DOWNWARDS");
    move(width/4 + 14, height/2 + 20); addch(ACS_BULLET);printw(" ");addch(ACS_LARROW);printw(" ");addch(ACS_BULLET);printw(" TO MOVE ALL NUMBERS LEFTWARDS");

}

void show_error_message(char* error_message)
{
	int height, width;


	getmaxyx(stdscr, width, height);
	mvprintw(width/4,height/2 - strlen(error_message)/2,"%s",error_message);
	refresh();
	usleep(30*DELAY);

}

int something_has_happened(POINT *poz, POINT *aux)
{
	for(int i = 0; i < N_CELLS ; ++i)
		if(poz[i].free  != aux[i].free )
			return 1;

	return 0;

}
void clear_screen()
{
	for(int i = 0; i < WIDTH_TABLE*3; ++i)
		for(int j = 0; j < HEIGHT_TABLE*3 ; ++j)
				mvprintw(j,i,"%c",32);

}

void print_game_over_menu(POINT *poz, int selection)
{
	mvprintw(HEIGHT_TABLE/2,WIDTH_TABLE+3,"GAME OVER");
	mvprintw(HEIGHT_TABLE/2 + 2,WIDTH_TABLE,"FINAL SCORE : %d", poz[N_CELLS].value);

	mvprintw(HEIGHT_TABLE/2 + 9,WIDTH_TABLE,"START A NEW GAME?");
	init_pair(6,COLOR_BLACK,COLOR_WHITE);


	switch(selection)
	{
		case 1 :
			attron(COLOR_PAIR(6));
			mvprintw(HEIGHT_TABLE/2 + 12,WIDTH_TABLE - 15,">  YES");
			attroff(COLOR_PAIR(6));

			mvprintw(HEIGHT_TABLE/2 + 12,WIDTH_TABLE + 15, "   NO, I'M BORED");
			break;

		case 2 :
			mvprintw(HEIGHT_TABLE/2 + 12,WIDTH_TABLE - 15,"   YES");
			
			attron(COLOR_PAIR(6));
			mvprintw(HEIGHT_TABLE/2 + 12,WIDTH_TABLE + 15, ">  NO, I'M BORED");
			attroff(COLOR_PAIR(6));
			break;


	}


}
void print_menu(int selection)
{
	int height, width;

	getmaxyx(stdscr, height, width);
	clear_screen();
	init_pair(5,COLOR_BLACK,COLOR_WHITE);

	switch(selection)
	{
		case 1 :

			attron(COLOR_PAIR(5));
			mvprintw(height/2 -5,width/2 - 5,">  New game");
			attroff(COLOR_PAIR(5));

			mvprintw(height/2 ,width/2 - 5,"   Resume");

			mvprintw(height/2 + 5,width/2 - 5,"   Quit");
			break;


		case 2 :

			mvprintw(height/2 -5,width/2 - 5,"   New game");

			attron(COLOR_PAIR(5));
			mvprintw(height/2 ,width/2 - 5,">  Resume");
			attroff(COLOR_PAIR(5));

			mvprintw(height/2 + 5,width/2 - 5,"   Quit");
			break;


		case 3 : 

			mvprintw(height/2 -5,width/2 - 5,"   New game");

			
			mvprintw(height/2 ,width/2 - 5,"   Resume");
			
			attron(COLOR_PAIR(5));
			mvprintw(height/2 + 5,width/2 - 5,">  Quit");
			attroff(COLOR_PAIR(5));
			break;


	}
	


}

void init(POINT *poz)
{
	POINT zero;
	int width,height;


	zero.x = 0; zero.y = 0; zero.free = 1 ; zero.modified = 0, zero.value = 0;

	for(int i = 0; i <= N_CELLS; ++i)
		poz[i] = zero;

	getmaxyx(stdscr, height, width);
	poz[N_CELLS].y = height - 35 ; poz[N_CELLS].x = width - 50;
	poz[N_CELLS].free = 0;

}


void assign_attr_cell(TYPE* cell, int cell_type)
{
	(cell->ls) = ACS_VLINE; (cell->rs) = ACS_VLINE; (cell->ts) = ACS_HLINE; (cell->bs) = ACS_HLINE;

	switch(cell_type)
	{
		case 0 :
			(cell->tl) = ACS_ULCORNER; (cell->tr) = ACS_URCORNER; (cell->bl) = ACS_LLCORNER; (cell->br) = ACS_LLCORNER;
			break;

		case 1 :
			(cell->tl) = ACS_ULCORNER; (cell->tr) = ACS_TTEE; (cell->bl) = ACS_LTEE; (cell->br) = ACS_PLUS;
			break;

		case 2 :
			(cell->tl) = ACS_TTEE; (cell->tr) = ACS_TTEE; (cell->bl) = ACS_PLUS; (cell->br) = ACS_PLUS;
			break;

		case 3 :
			(cell->tl) = ACS_TTEE; (cell->tr) = ACS_URCORNER; (cell->bl) = ACS_PLUS; (cell->br) = ACS_RTEE;
			break;

		case 4 :
			(cell->tl) = ACS_LTEE; (cell->tr) = ACS_PLUS; (cell->bl) = ACS_LTEE; (cell->br) = ACS_PLUS;
			break;

		case 5 :
			(cell->tl) = ACS_PLUS; (cell->tr) = ACS_PLUS; (cell->bl) = ACS_PLUS; (cell->br) = ACS_PLUS;
			break;

		case 6 :
			(cell->tl) = ACS_PLUS; (cell->tr) = ACS_RTEE; (cell->bl) = ACS_PLUS; (cell->br) = ACS_RTEE;
			break;

		case 7 :
			(cell->tl) = ACS_LTEE; (cell->tr) = ACS_PLUS; (cell->bl) = ACS_LLCORNER; (cell->br) = ACS_BTEE;
			break;

		case 8 :
			(cell->tl) = ACS_PLUS; (cell->tr) = ACS_PLUS; (cell->bl) = ACS_BTEE; (cell->br) = ACS_BTEE;
			break;

		case 9 :
			(cell->tl) = ACS_PLUS; (cell->tr) = ACS_RTEE; (cell->bl) = ACS_BTEE; (cell->br) = ACS_LRCORNER;
			break;

		default : break;
	}
}

void cell_print(int startY, int startX, int width, int height, TYPE cell)
{

	mvaddch(startY, startX, cell.tl);

	for(int i = 0; i < width; ++i)
		mvaddch(startY, ++startX, cell.ts);

	mvaddch (startY, ++startX, cell.tr);

	for(int i = 0; i < height; ++i)
		mvaddch(++startY, startX, cell.rs);

	mvaddch(++startY, startX, cell.br);

	for(int i = 0; i < width; ++i)
		mvaddch(startY, --startX, cell.bs);

	mvaddch(startY, --startX, cell.bl);

	for(int i = 0; i < height; ++i)
		mvaddch(--startY, startX, cell.ls);

}

void cell_create(int startY, int startX, int width, int height, int cell_type)
{
	TYPE cell;

		assign_attr_cell(&cell, cell_type);
		cell_print(startY, startX, width, height, cell);
}

void cell_colour(POINT *poz, int startY, int startX, int width, int height, int colour_to_print)
{
	attron(COLOR_PAIR(colour_to_print));
	
		for(int i = startX + 1; i < WIDTH_CELL + startX + 1; ++i)
			for(int j = startY + 1; j < HEIGHT_CELL+ startY + 1; ++j)
				mvprintw(j, i, "%c", 32);

}

void free_cell(POINT *poz, int startY, int startX, int width, int height, int cell_number)
{
	init_pair(0,COLOR_BLACK, COLOR_BLACK);

	attron(COLOR_PAIR(0));

	for(int i = startX + 1; i < WIDTH_CELL + startX + 1; ++i)
			for(int j = startY + 1; j < HEIGHT_CELL+ startY + 1; ++j)
				mvprintw(j, i, "%c", 32);

	poz[cell_number].free = 1;

	attroff(COLOR_PAIR(0));


}

void number_print(POINT *poz, int startY, int startX, int width, int height, int cell_number, int value_to_print)
{
	int copy, digits_no = 0, color_pair_no;

	copy = value_to_print;

	while(copy)
	{
		copy /= 10;
		digits_no++;
	}

	switch(value_to_print)
	{
		case 2 :
			cell_colour(poz, startY, startX, width, height,COLOR_2);
			color_pair_no = COLOR_2;
			break;

		case 4 :
			cell_colour(poz, startY, startX, width, height,COLOR_4);
			color_pair_no = COLOR_4;
			break;

		case 8 :
			cell_colour(poz, startY, startX, width, height, COLOR_8);
			color_pair_no = COLOR_8;
			break;

		case 16 :
			cell_colour(poz, startY, startX, width, height, COLOR_16);
			color_pair_no = COLOR_16;
			break;

		case 32 :
			cell_colour(poz, startY, startX, width, height, COLOR_32);
			color_pair_no = COLOR_32;
			break;

		case 64 :
			cell_colour(poz, startY, startX, width, height, COLOR_64);
			color_pair_no = COLOR_64;
			break;

		case 128 :
			cell_colour(poz, startY, startX, width, height, COLOR_128);
			color_pair_no = COLOR_128;
			break;

		case 256 :
			cell_colour(poz, startY, startX, width, height, COLOR_256);
			color_pair_no = COLOR_256;
			break;

		case 512 : 
			cell_colour(poz, startY, startX, width, height, COLOR_512);
			color_pair_no = COLOR_512;
			break;

		case 1024 :
			cell_colour(poz, startY, startX, width, height, COLOR_1024);
			color_pair_no = COLOR_1024;
			break;

		case 2048 :
			cell_colour(poz, startY, startX, width, height, COLOR_2048);
			color_pair_no = COLOR_2048;
			break;

		case 4096 ... 1048576 :
			cell_colour(poz, startY, startX, width, height, COLOR_4096);
			color_pair_no = COLOR_4096;
			break;

	}

	switch(digits_no)
	{
		case 0 ... 3 : 
			mvprintw(startY + height/2 + 1, startX + width/2, "%d", value_to_print);
			poz[cell_number].value = value_to_print;
			break;

		case 4 ... 7:
			mvprintw(startY + height/2 + 1, startX + width/2 - 1 , "%d", value_to_print);
			poz[cell_number].value = value_to_print;
			break;

	}

	poz[cell_number].free = 0;
	attroff(COLOR_PAIR(color_pair_no));

	

}

void get_random(POINT *poz)
{
	int random_out, number_to_print;
	unsigned int seed = 0 ;
	int board_full = 1;

	for(int i = 0; i < N_CELLS; ++i)
		if(poz[i].free)
		{
			seed += poz[i].x * poz[i].y;
			board_full = 0;
		}

	

	srand(seed);

	random_out = rand() % 5;

	switch(random_out)
	{
		case 0 ... 3 :
			number_to_print = 2;
			break;

		case 4 :
			number_to_print = 4;
			break;

	}

	srand(time(NULL));
	
	while(!board_full)
	{
		
		random_out = rand() % N_CELLS;


		if( poz[random_out].free )
		{
			number_print(poz, poz[random_out].y, poz[random_out].x, WIDTH_CELL, HEIGHT_CELL, random_out, number_to_print);

			mvprintw(poz[N_CELLS].y, poz[N_CELLS].x, "SCORE : %d", poz[N_CELLS].value);

			break;
		}


	}

}

void move_cells(POINT *poz, int input, int print)
{
	int current_position;
	int something_happened = 0;

	switch(input)
	{
		case 1 :  // KEY_LEFT
			for(int i = 0; i < N_CELLS; ++i)
			{
				if(i == 0 || i == 4 || i == 8 || i == 12 || poz[i].free )
					continue;

				current_position = i;
				for(int j = i-1; ; --j)
				{	

					if(poz[j].free)
					{
						if(print)
							free_cell(poz, poz[current_position].y, poz[current_position].x, WIDTH_CELL, HEIGHT_CELL, current_position);
						else
							poz[current_position].free = 1;

						if(print)
						{
							number_print(poz, poz[j].y, poz[j].x, WIDTH_CELL, HEIGHT_CELL, j, poz[current_position].value);
							refresh();
							usleep(DELAY);
						}
						else
							poz[j].free = 0;
						

						current_position = j;
						something_happened = 1;

					}
					else if( current_position - j == 1)
							if(poz[j].value == poz[current_position].value && !poz[current_position].modified && !poz[j].modified)
						   	{	
								poz[j].value *= 2;

								if(print)
								{
									poz[N_CELLS].value += poz[j].value;

									free_cell(poz, poz[current_position].y, poz[current_position].x, WIDTH_CELL, HEIGHT_CELL, current_position);
							     	free_cell(poz, poz[j].y, poz[j].x, WIDTH_CELL, HEIGHT_CELL, j);

						    		refresh();
						    		usleep(DELAY);
						    	}
						    	else
						    	{
						    		poz[j].free = 1;
									poz[current_position].free = 1;
						    	}

						    	if(print)
						    		number_print(poz, poz[j].y, poz[j].x, WIDTH_CELL, HEIGHT_CELL, j, poz[j].value);
						    	else
									poz[j].free = 0;


						    	current_position = j;

								poz[j].modified = 1;	poz[current_position].modified = 1;
								something_happened = 1;

							}

					if(j == 0 || j == 4 || j == 8 || j == 12 )
						break;
				}



			}

			for(int i = 0; i < N_CELLS; ++i)
				poz[i].modified = 0 ;

			break; 


		case 2 :  // KEY_UP
			for(int i = 0; i < N_CELLS; i+=4 )
			{
				if(i == 0 || i == 1 || i == 2 || i == 3 )
					continue;

				if( poz[i].free )
					goto label1;

				current_position = i;
				for(int j = i-4; ; j -= 4)
				{	

					if(poz[j].free)
					{
						if(print)
							free_cell(poz, poz[current_position].y, poz[current_position].x, WIDTH_CELL, HEIGHT_CELL, current_position);
						else
							poz[current_position].free = 1;

						if(print)
						{
							number_print(poz, poz[j].y, poz[j].x, WIDTH_CELL, HEIGHT_CELL, j, poz[current_position].value);
							refresh();
							usleep(DELAY);
						}
						else
							poz[j].free = 0;

							

						current_position = j;
						something_happened = 1;
					}
					else if( current_position - j == 4) 
						if(poz[j].value == poz[current_position].value && !poz[current_position].modified && !poz[j].modified)
						{
							poz[j].value *= 2;

							if(print)
							{
								poz[N_CELLS].value += poz[j].value;
								free_cell(poz, poz[current_position].y, poz[current_position].x, WIDTH_CELL, HEIGHT_CELL, current_position);
								free_cell(poz, poz[j].y, poz[j].x, WIDTH_CELL, HEIGHT_CELL, j);
							
								refresh();
								usleep(DELAY);
							}
							else
							{
								poz[j].free = 1;
								poz[current_position].free = 1;
							}	


							if(print)
								number_print(poz, poz[j].y, poz[j].x, WIDTH_CELL, HEIGHT_CELL, j, poz[j].value);
							else
								poz[j].free = 0;

							current_position = j;
							
							poz[j].modified = 1;	poz[current_position].modified = 1;
							something_happened = 1;

						}


					if(j == 0 || j == 1 || j == 2 || j == 3 )
						break;
				}

				label1 :
				if(i == 12 || i == 13 || i == 14)
					i = i%4 - 3;
			}

			for(int i = 0; i < N_CELLS; ++i)
				poz[i].modified = 0 ;

			break;	

		case 3 :  // KEY_RIGHT
			for(int i = N_CELLS - 1; i >= 0; --i)
			{
				if(i == 3 || i == 7 || i == 11 || i == 15 || poz[i].free )
					continue;

				current_position = i;
				for(int j = i+1; ; ++j)
				{	

					if(poz[j].free)
					{
						if(print)
							free_cell(poz, poz[current_position].y, poz[current_position].x, WIDTH_CELL, HEIGHT_CELL, current_position);
						else
							poz[current_position].free = 1;

						if(print)
						{
							number_print(poz, poz[j].y, poz[j].x, WIDTH_CELL, HEIGHT_CELL, j, poz[current_position].value);
							refresh();
							usleep(DELAY);

						}
						else
							poz[j].free = 0;

						
						current_position = j;
						something_happened = 1;
					}
					else if( current_position - j == -1)
						if(poz[j].value == poz[current_position].value && !poz[current_position].modified && !poz[j].modified)
						{
							poz[j].value *= 2;
							if(print)
							{
								poz[N_CELLS].value += poz[j].value;
								free_cell(poz, poz[current_position].y, poz[current_position].x, WIDTH_CELL, HEIGHT_CELL, current_position);
								free_cell(poz, poz[j].y, poz[j].x, WIDTH_CELL, HEIGHT_CELL, j);

								refresh();
								usleep(DELAY);
							}
							else
							{
								poz[current_position].free = 1;
								poz[j].free = 1;
							}

							if(print)
								number_print(poz, poz[j].y, poz[j].x, WIDTH_CELL, HEIGHT_CELL, j, poz[j].value);
							else
								poz[j].free = 0;

							current_position = j;
							
							poz[j].modified = 1;	poz[current_position].modified = 1;
							something_happened = 1;

						}

					if(j == 3 || j == 7 || j == 11 || j == 15 )
						break;
				}



			}

			for(int i = 0; i < N_CELLS; ++i)
				poz[i].modified = 0 ;
			break;


		case 4 :  // KEY_DOWN
			for(int i = N_CELLS-1; i >= 0; i -= 4)
			{
				if(i == 12 || i == 13 || i == 14 || i == 15 ) 
					continue;

				if(poz[i].free)
					goto label2;

				current_position = i;
				for(int j = i + 4; ; j += 4)
				{	

					if(poz[j].free)
					{
						if(print)
							free_cell(poz, poz[current_position].y, poz[current_position].x, WIDTH_CELL, HEIGHT_CELL, current_position);
						else
							poz[current_position].free = 1;


						if(print)
						{
							number_print(poz, poz[j].y, poz[j].x, WIDTH_CELL, HEIGHT_CELL, j, poz[current_position].value);
							refresh();
							usleep(DELAY);
						}
						else
							poz[j].free = 0;
						

						current_position = j;
						something_happened = 1;
					}
					else if( current_position - j == -4)
						if(poz[j].value == poz[current_position].value && !poz[current_position].modified && !poz[j].modified)
						{
							poz[j].value *= 2;
							if(print)
							{
								poz[N_CELLS].value += poz[j].value;
								free_cell(poz, poz[current_position].y, poz[current_position].x, WIDTH_CELL, HEIGHT_CELL, current_position);
								free_cell(poz, poz[j].y, poz[j].x, WIDTH_CELL, HEIGHT_CELL, j);

								refresh();
								usleep(DELAY);
							}
							else
							{
								poz[current_position].free = 1;
								poz[j].free = 1;
							}

							if(print)
								number_print(poz, poz[j].y, poz[j].x, WIDTH_CELL, HEIGHT_CELL, j, poz[j].value);
							else
								poz[j].free = 0;

							current_position = j;

							poz[j].modified = 1;	poz[current_position].modified = 1;
							something_happened = 1;

						}

					if(j == 12 || j == 13 || j == 14 || j == 15 )
						break;
				}

				label2 :
					if( i == 3 )
						i = 18;
					else if(i == 2)
							i = 17;
						else if(i == 1)
								i = 16;
			}

			for(int i = 0; i < N_CELLS; ++i)
				poz[i].modified = 0 ;

			break;
			
	}

	refresh();
	usleep(DELAY);

	if(something_happened && print)
	{
		mvprintw(poz[N_CELLS].y, poz[N_CELLS].x, "SCORE : %d", poz[N_CELLS].value);
		refresh();
		usleep(5*DELAY);
		get_random(poz);

	}



}

void auto_move(POINT *poz)
{
	int max_free = 0, max_move, curr_free = 0;
	POINT *aux;

	aux = calloc(N_CELLS + 3, sizeof(POINT));

	for(int i = 0; i <= N_CELLS; ++i)
		aux[i] = poz[i];

	move_cells(aux,1,0);

	for( int i = 0; i < N_CELLS; ++i )
		if(aux[i].free)
			++curr_free;
			
	if( (curr_free > max_free) && something_has_happened(poz,aux))
	{
		max_free = curr_free;
		max_move = 1;
	}




	curr_free = 0;

	for(int i = 0; i <= N_CELLS; ++i)
		aux[i] = poz[i];

	move_cells(aux,2,0);

	for( int i = 0; i < N_CELLS; ++i )
		if(aux[i].free)
			++curr_free;
			
	if( (curr_free > max_free) && something_has_happened(poz,aux))
	{
		max_free = curr_free;
		max_move = 2;
	}




	curr_free = 0;

	for(int i = 0; i <= N_CELLS; ++i)
		aux[i] = poz[i];
		

	move_cells(aux,3,0);

	for( int i = 0; i < N_CELLS; ++i )
		if(aux[i].free)
			++curr_free;
			
	if( (curr_free > max_free) && something_has_happened(poz,aux))
	{
		max_free = curr_free;
		max_move = 3;
	}




	curr_free = 0;
	
	for(int i = 0; i <= N_CELLS; ++i)
		aux[i] = poz[i];


	move_cells(aux,4,0);

	for( int i = 0; i < N_CELLS; ++i )
		if(aux[i].free)
			++curr_free;
			
	if( (curr_free > max_free) && something_has_happened(poz,aux))
	{
		max_free = curr_free;
		max_move = 4;
	}

	free(aux);

	move_cells(poz,max_move,1);
}

int check_for_game_over(POINT *poz)
{
	POINT *aux;

	for( int i = 0; i < N_CELLS; ++i )
		if(poz[i].free)
			return 0;


	aux = calloc(N_CELLS + 3, sizeof(POINT));


	for(int i = 0; i < N_CELLS; ++i)
		aux[i] = poz[i];

	move_cells(aux,1,0);

	for( int i = 0; i < N_CELLS; ++i )
		if(aux[i].free)
		{
			return 0;
			free(aux);
		}



	for(int i = 0; i <= N_CELLS; ++i)
		aux[i] = poz[i];

	move_cells(aux,2,0);

	for( int i = 0; i < N_CELLS; ++i )
		if(aux[i].free)
		{
			return 0;
			free(aux);
		}
			
	

	for(int i = 0; i <= N_CELLS; ++i)
		aux[i] = poz[i];	

	move_cells(aux,3,0);

	for( int i = 0; i < N_CELLS; ++i )
		if(aux[i].free)
		{
			return 0;
			free(aux);
		}


	
	for(int i = 0; i <= N_CELLS; ++i)
		aux[i] = poz[i];


	move_cells(aux,4,0);

	for( int i = 0; i < N_CELLS; ++i )
		if(aux[i].free)
		{
			return 0;
			free(aux);
		}
			
	free(aux);
	return 1;

}

int check_for_game_won(POINT *poz)
{
	int game_won_output = 0;

	for (int i = 0; i < N_CELLS; ++i)
		if(!poz[i].free && poz[i].value == 2048)
		{
			game_won_output = game_won_screen(poz);
			break;
		}

	return game_won_output;
}

int game_over_screen(POINT *poz)
{	
	int selection = 1, quit = 0, input, game_over_output = 0;

	clear_screen();

	FILE *pFile;
 
   	pFile = fopen("file.dump", "w");
  
	for(int i = 0; i <= N_CELLS; ++i)
		 fprintf (pFile,"0 0 0 0 0");
	
	 fclose (pFile);


	print_game_over_menu(poz,selection);

	while(!quit)
	{
		input = getch();

		switch(input)
		{
			case KEY_LEFT :

				if(selection == 1)
					selection = 2;
				else
					selection--;

				print_game_over_menu(poz,selection);
				break;

			case KEY_RIGHT :

				if(selection == 2)
					selection = 1;
				else
					selection++;

				print_game_over_menu(poz,selection);
				break;

			case ENTER :

				switch(selection)
				{
					case 1 :
						clear_screen();
						quit = 1;
						game_over_output = 1;
						break;

					case 2 :
						game_over_output = 2;
						quit = 1;
						break;
				}		

				break;
					

		}
	}

	return game_over_output;
}

int game_won_screen(POINT *poz)
{
	int selection = 1, quit = 0, input, game_won_output = 0;

	clear_screen();

	print_game_won_menu(poz,selection);

	while(!quit)
	{
		input = getch();

		switch(input)
		{
			case KEY_LEFT :

				if(selection == 1)
					selection = 2;
				else
					selection--;

				print_game_won_menu(poz,selection);
				break;

			case KEY_RIGHT :

				if(selection == 2)
					selection = 1;
				else
					selection++;

				print_game_won_menu(poz,selection);
				break;

			case ENTER :

				switch(selection)
				{
					case 1 :
						clear_screen();
						quit = 1;
						game_won_output = 2;
						break;

					case 2 :
						game_won_output = 1;
						quit = 1;
						break;
				}		

				break;
					

		}
	}

	return game_won_output;
}

void print_game_won_menu(POINT *poz, int selection)
{
	mvprintw(HEIGHT_TABLE/2,WIDTH_TABLE+3,"GAME WON!!!");
	mvprintw(HEIGHT_TABLE/2 + 2,WIDTH_TABLE,"TOTAL SCORE : %d", poz[N_CELLS].value);

	mvprintw(HEIGHT_TABLE/2 + 9,WIDTH_TABLE,"CONTINUE PLAYING?");
	init_pair(6,COLOR_BLACK,COLOR_WHITE);


	switch(selection)
	{
		case 1 :
			attron(COLOR_PAIR(6));
			mvprintw(HEIGHT_TABLE/2 + 12,WIDTH_TABLE - 15,">  YES");
			attroff(COLOR_PAIR(6));

			mvprintw(HEIGHT_TABLE/2 + 12,WIDTH_TABLE + 15, "   NO, I'M BORED");
			break;

		case 2 :
			mvprintw(HEIGHT_TABLE/2 + 12,WIDTH_TABLE - 15,"   YES");
			
			attron(COLOR_PAIR(6));
			mvprintw(HEIGHT_TABLE/2 + 12,WIDTH_TABLE + 15, ">  NO, I'M BORED");
			attroff(COLOR_PAIR(6));
			break;


	}
}

void show_cells(POINT *poz)
{
	for(int i = 0; i < N_CELLS; ++i)
	 	if(!poz[i].free)
	 		number_print(poz, poz[i].y, poz[i].x, WIDTH_CELL, HEIGHT_CELL, i, poz[i].value);


}

void create_game(POINT *poz)
{
	int cell_line = 0, startX = 1, startY = 1;

	show_clock();
	mvprintw(poz[N_CELLS].y, poz[N_CELLS].x, "SCORE : %d", poz[N_CELLS].value);

	for(int i = 0; i < N_LINES; ++i, startY += HEIGHT_CELL+1, startX = 1, (i!=2) ? cell_line += 3 : cell_line)
		for(int j = 0; j < N_LINES; ++j, startX += WIDTH_CELL+1)
		{
			
			poz[i * N_LINES + j].x = startX;	poz[i * N_LINES + j].y = startY;

			switch(j)
			{
				case 0 ... 1 : 
					cell_create(startY, startX, WIDTH_CELL, HEIGHT_CELL, cell_line + j + 1);
					break;

				case 2 ... 3 :
					cell_create(startY, startX, WIDTH_CELL, HEIGHT_CELL, cell_line + j);
					break;

			}	

				
		}

}

int start_new_game(POINT *poz)
{
	int game_over_output = 0;

	init(poz);

	create_game(poz);


	get_random(poz);
	get_random(poz);
	
	game_over_output = run_game(poz);

	return game_over_output;


}

void save_game_state(POINT *poz)
{
	FILE *pFile;
 
   	pFile = fopen("file.dump", "w");
  
	for(int i = 0; i <= N_CELLS; ++i)
		 fprintf (pFile,"%d %d %d %d %d\n",poz[i].x, poz[i].y, poz[i].free, poz[i].modified, poz[i].value);
	
	 fclose (pFile);

}

int resume_game(POINT *poz)
{
	int game_over_output = 0;

	FILE *pFile;

	pFile = fopen("file.dump", "r");

	if(pFile == NULL)
	{
		show_error_message("No previous game recorded");
		return 0;
	}

	for(int i = 0; i <= N_CELLS; ++i)
		 fscanf (pFile,"%d %d %d %d %d\n",&poz[i].x, &poz[i].y, &poz[i].free, &poz[i].modified, &poz[i].value);

	if(poz[0].x == 0)
	{
		show_error_message("No previous game recorded");
		fclose(pFile);
		return 0;
	}
	
	 fclose (pFile);

	 clear_screen();
	 create_game(poz);
	 show_cells(poz);
	 game_over_output = run_game(poz);

	 return game_over_output;

}

int run_game(POINT *poz)
{
	halfdelay(50);

	int quit = 0, game_over = 0, input, game_over_output = 0, game_won = 1, game_already_won = 0;

	while(!quit && !game_over)
	{
		input = getch();
		show_clock();
		game_already_won = poz[N_CELLS].modified;

		switch(input)
		{
			case KEY_LEFT :
				move_cells(poz,1,1);
				break;

			case KEY_UP :
				move_cells(poz,2,1);
				break;

			case KEY_RIGHT :
				move_cells(poz,3,1);
				break;

			case KEY_DOWN :
				move_cells(poz,4,1);
				break;

			case ERR :
				auto_move(poz);
				break;

			case 'Q' :
			case 'q' :
				save_game_state(poz);
				clear_screen();
				cbreak();
				quit = 1;
				break;

		}

		if(!game_already_won)
		{
			game_won = check_for_game_won(poz); // 0 == continue & !won ; 1 == stop & won ; 2 == continue & won 
			
			if(game_won == 1)
				quit = 1;

			if(game_won == 2)
			{
				poz[N_CELLS].modified = 1;
				create_game(poz);
				show_cells(poz);
			}
		}

		game_over = check_for_game_over(poz);

	}

	if(game_over)
		game_over_output = game_over_screen(poz);

	return game_over_output;
	

}

int navigate_menu(POINT *poz)
{
	int input;
	int selection = 1, quit = 0;

	print_menu(selection);

	while(!quit)
	{
		input = getch();

		switch(input)
		{
			case KEY_UP :

				if(selection == 1)
					selection = 3;
				else
					selection--;

				print_menu(selection);
				break;

			case KEY_DOWN :

				if(selection == 3)
					selection = 1;
				else
					selection++;

				print_menu(selection);
				break;

			case ENTER :

				return selection;		
				break;
					

		}
	}
	return 0;
}


