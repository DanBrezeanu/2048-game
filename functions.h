// Copyright 2017 Brezeanu Dan-Eugen
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define HEIGHT_TABLE 33
#define WIDTH_TABLE  61
#define HEIGHT_CELL  5
#define WIDTH_CELL   12	

#define N_CELLS 16
#define N_LINES 4

#define DELAY 20000

#define ENTER 10

#define COLOR_2    1
#define COLOR_4    30
#define COLOR_8    32
#define COLOR_16   33
#define COLOR_32   31
#define COLOR_64   2
#define COLOR_128  34
#define COLOR_256  35
#define COLOR_512  3
#define COLOR_1024 36
#define COLOR_2048 38
#define COLOR_4096 4


typedef struct
{
	chtype ls, rs, ts, bs;
	chtype tl, tr, bl, br;

}TYPE;

typedef struct
{
	int x,y;
	int free,modified;
	int value;

}POINT;


void start_graphics(); 
void end_graphics(); 
void show_clock(); 
void show_error_message(char *error_message); 
void clear_screen(); 

void init(POINT *poz); 
int something_has_happened(POINT *poz, POINT *aux); 

void assign_attr_cell(TYPE* cell, int cell_type); 
void cell_print(int startY, int startX, int width, int height, TYPE cell); 
void cell_create(int startY, int startX, int width, int height, int cell_type); 
void cell_colour(POINT *poz, int startY, int startX, int width, int height, int colour_to_print); 
void free_cell(POINT *poz, int startY, int startX, int width, int height, int cell_number); 

void number_print(POINT *poz, int startY, int startX, int width, int height, int cell_number, int value_to_print); 
void get_random(POINT *poz); 
void move_cells(POINT *poz, int input, int print); 

int check_for_game_over(POINT *poz);
int game_over_screen(POINT *poz); 
void print_game_over_menu(POINT *poz, int selection); 

int check_for_game_won(POINT *poz); 
int game_won_screen(POINT *poz); 
void print_game_won_menu(POINT *poz, int selection); 

int start_new_game(POINT *poz); 
void create_game(POINT *poz); 
void show_cells(POINT *poz);

void save_game_state(POINT *poz); 
int resume_game(POINT *poz); 

int run_game(POINT *poz); 
void print_menu(int selection); 
void auto_move(POINT *poz); 
int navigate_menu(POINT *poz); 

#endif
