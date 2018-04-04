#ifndef MAZE
#define MAZE

#define FALSE 0
#define TRUE 1
#define NO_OF_ARGS 2
#define NULLCHAR_LEN 1
#define NEWLINE_NULLCHAR_LEN 2
#define READONLY "r"
#define WIDTH 5
#define HEIGHT 5
#define NULLCHAR '\0'
#define MAZE_LINE "%s\n"
#define START 'X'
#define WALL '#'
#define VISITED '.'
#define UNVISITED ' '
#define ERR_INVALID_ARGS_MSG "Usage: maze FILENAME\n"
#define ERR_INVALID_ARGS_CODE 1
#define ERR_FILE_HANDLE_MSG "Unable to open file: %s\n"
#define ERR_FILE_HANDLE_CODE 2
#define ERR_OOM_MSG "Failed to allocate %zu bytes of memory\n"
#define ERR_OOM_CODE 3

typedef struct start {
    int start_x;
    int start_y;
} Start;

void initialise_start(Start **start, char **maze);
char **load_maze(const char *filename);
int solve_maze(int x, int y, char **maze);
void print_maze(char **maze);
void delete_maze(char **maze);

#endif
