#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

/*
*   Maze solver
*
*   Solve a simple 5 * 5 maze comprising of walls (#), spaces ( ) and
*   a starting point (X).
*
*   Author: Douglas Groves
*   Date: 03/04/2018
*/

int main(int argc, char **argv){
    char **maze;
    Start *start;
    if(argc != NO_OF_ARGS){
        fprintf(stderr, ERR_INVALID_ARGS_MSG);
        exit(ERR_INVALID_ARGS_CODE);
    }
    maze = load_maze(argv[1]);
    initialise_start(&start, maze);
    solve_maze(start->start_x, start->start_y, maze);
    print_maze(maze);
    delete_maze(maze);
    free(start);
}

char **load_maze(const char *filename){
    FILE *maze_file;
    char *ch;
    char **maze;
    int i;
    maze_file = fopen(filename, READONLY);
    if(maze_file == NULL){
        fprintf(stderr, ERR_FILE_HANDLE_MSG, filename);
        exit(ERR_FILE_HANDLE_CODE);
    }
    maze = (char **)malloc(HEIGHT * sizeof(char *));
    if(maze == NULL){
        fprintf(stderr, ERR_OOM_MSG, sizeof(char *));
        exit(ERR_OOM_CODE);
    }
    ch = (char *)malloc((WIDTH + NEWLINE_NULLCHAR_LEN) * sizeof(char));
    if(ch == NULL){
        fprintf(stderr, ERR_OOM_MSG, sizeof(char));
        exit(ERR_OOM_CODE);
    }
    i = 0;
    while(fgets(ch, WIDTH + NEWLINE_NULLCHAR_LEN, maze_file) != NULL){
        maze[i] = (char *)malloc((WIDTH + NULLCHAR_LEN) * sizeof(char));
        if(maze[i] == NULL){
            fprintf(stderr, ERR_OOM_MSG, sizeof(char));
            exit(ERR_OOM_CODE);
        }
        memcpy(maze[i], ch, WIDTH * sizeof(char));
        maze[i][WIDTH] = NULLCHAR;
        i++;
        free(ch);
        ch = (char *)malloc(WIDTH + NEWLINE_NULLCHAR_LEN * sizeof(char));
        if(ch == NULL){
            fprintf(stderr, ERR_OOM_MSG, sizeof(char));
            exit(ERR_OOM_CODE);
        }
    }
    free(ch);
    fclose(maze_file);
    return maze;
}

void initialise_start(Start **start, char **maze){
    int y, x;
    *start = (Start *)malloc(sizeof(Start));
    if(*start == NULL){
        fprintf(stderr, ERR_OOM_MSG, sizeof(Start));
        exit(ERR_OOM_CODE);
    }
    for(y = 0; y < HEIGHT; y++){
        for(x = 0; x < WIDTH; x++){
            if(maze[y][x] == START){
                (*start)->start_x = x;
                (*start)->start_y = y;
                break;
            }
        }
    }
}

int solve_maze(int x, int y, char **maze){
    //return false if we have exceeded the bounds of the maze or we have hit a wall
    if((x < 0 || x >= WIDTH) || (y < 0 || y >= HEIGHT) || maze[y][x] == WALL || maze[y][x] == VISITED){
        return FALSE;
    }
    //return true if we have reached the exit
    else if((x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) && maze[y][x] == UNVISITED){
        maze[y][x] = VISITED;
        return TRUE;
    }
    //mark the current position (except for the starting square)
    if(maze[y][x] != START){
        maze[y][x] = VISITED;
    }
    if(solve_maze(x, y + 1, maze) == TRUE){
        return TRUE;
    }
    if(solve_maze(x + 1, y, maze) == TRUE){
        return TRUE;
    }
    if(solve_maze(x, y - 1, maze) == TRUE){
        return TRUE;
    }
    if(solve_maze(x - 1, y, maze) == TRUE){
        return TRUE;
    }
    //unmark the current position and return false if it does not contribute to the solution
    if(maze[y][x] != START){
        maze[y][x] = UNVISITED;
    }
    return FALSE;
}


void print_maze(char **maze){
    int y;
    for(y = 0; y < HEIGHT; y++){
        printf(MAZE_LINE, maze[y]);
    }
}

void delete_maze(char **maze){
    int i;
    for(i = 0; i < WIDTH; i++){
        free(maze[i]);
    }
    free(maze);
}
