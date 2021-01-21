#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 1
#define MAX 45000

typedef int candidates[10];

typedef struct cell {
	int has_value, value;

	candidates *row_candidates;
	candidates *col_candidates;
	candidates *square_candidates;
} cell;

typedef struct board {
	int unset_cells;

	cell cells[10][10];

	candidates rows[10];
	candidates columns[10];
	candidates squares[10];
} board;

void init_candidates(candidates *c)
{
	for(int i = 1; i <= 9; ++i)
		(*c)[i] = 0;
}

void use_candidate(candidates *cp, int num)
{
	if(!(cp))
        return;

	(*cp)[num] = 1;
}

void restore_candidate(candidates *cp, int num)
{
	if(!(cp && num >= 1 && num <= 9))
        return;

	(*cp)[num] = 0;
}

int square(int row, int col)
{
	return (((row - 1) / 3) * 3) + ((col - 1) / 3) + 1;
}

void init_board(board *b)
{
	if(!(b))
        return;

	b->unset_cells = 9 * 9;

	for (int i = 1; i <= 9; ++i) {
		init_candidates(b->rows + i);
		init_candidates(b->columns + i);
		init_candidates(b->squares + i);

		for (int j = 1; j <= 9; ++j) {
			b->cells[i][j].has_value = 0;
			b->cells[i][j].value = 0;
			b->cells[i][j].row_candidates = b->rows + i;
			b->cells[i][j].col_candidates = b->columns + j;
			b->cells[i][j].square_candidates = b->squares + square(i, j);
		}
	}
}

int find_common_free(candidates *r, candidates *c, candidates *s, int atleast)
{
	for (int i = atleast; i <= 9; ++i)
		if ((!(*r)[i]) && (!(*c)[i]) && (!(*s)[i]))
			return i;
	return (-1);
}

void set_cell(board *b, int r, int c, int val)
{
	if(!(b && r >= 1 && r <= 9 && c >= 1 && c <= 9))
        return;

	if(!((!(*(b->cells[r][c].row_candidates))[val]) && (!(*(b->cells[r][c].col_candidates))[val]) && (!(*(b->cells[r][c].square_candidates))[val])))
        return;

	b->unset_cells--;
	b->cells[r][c].has_value = 1;
	b->cells[r][c].value = val;
	use_candidate(b->cells[r][c].row_candidates, val);
	use_candidate(b->cells[r][c].col_candidates, val);
	use_candidate(b->cells[r][c].square_candidates, val);
}

void unset_cell(board *b, int r, int c, int val)
{
	if(!(b && r >= 1 && r <= 9 && c >= 1 && c <= 9 && val >= 1 && val <= 9))
        return;

	if(!((*(b->cells[r][c].row_candidates))[val] && (*(b->cells[r][c].col_candidates))[val] && (*(b->cells[r][c].square_candidates))[val]))
        return;

	b->unset_cells++;
	b->cells[r][c].has_value = 0;
	b->cells[r][c].value = 0;
	restore_candidate(b->cells[r][c].row_candidates, val);
	restore_candidate(b->cells[r][c].col_candidates, val);
	restore_candidate(b->cells[r][c].square_candidates, val);
}

int is_set(board *b, int r, int c)
{
	if(!(b && r >= 1 && r <= 9 && c >= 1 && c <= 9))
        return 0;

	return (b->cells[r][c].has_value);
}

int following(int num)
{
	return ((num) % 9 + 1);
}

int next_cell(int *r, int *c)
{
	if((*r) == 9 && (*c) == 9)
		return 0;

	*c = following(*c);

	if ((*c) == 1)
		(*r) = following(*r);

	return 1;
}

void print_board(board *b)
{
	if(!b)
        return;

	for(int i = 1; i <= 9; ++i){
		for (int j = 1; j <= 9; ++j)
			printf(" %d", b->cells[i][j].value);
		printf("\n");
	}
}

int solve_board(board *b, int r, int c)
{
	int prev, val;

	if(!(b && r >= 1 && r <= 9 && c >= 1 && c <= 9))
        return 0;

	if (b->unset_cells == 0) {
        printf("Solved board:\n");
		print_board(b);
		return 1;
	}

	while (is_set(b, r, c) && next_cell(&r, &c))
        ;

	prev = 1;

	while (1) {
		val = find_common_free(b->cells[r][c].row_candidates, b->cells[r][c].col_candidates, b->cells[r][c].square_candidates, prev);

		if (val == -1)
			break;

		set_cell(b, r, c, val);

		if (solve_board(b, r, c))
			return 1;

		unset_cell(b, r, c, val);

		prev = val + 1;
	}

	return 0;
}

int Rand(void)
{
	int randBr = 0;
	randBr = (MIN + (rand() / (RAND_MAX / (MAX - MIN + 1) + 1)));
	return randBr;
}

void read_board(board *b, int i)
{
    FILE *file = fopen("datoteke/sem_puz.txt", "r");
	int row, col, ran, c = 0;

	if(!(file && b))
        return; 

    ran = Rand() * 81;

	row = col = 1;

    fseek(file, ran, SEEK_SET);

    for(int i = 0; i < 81; ++i){
        fscanf(file, "%1d", &c);
        if(c <= 9 && c >= 1)
            set_cell(b, row, col, c);
        if(!next_cell(&row, &col))
            break;

    }

    printf("\n%d.Board\n\ninitial board:\n", ++i);
    print_board(b);
    printf("\n");

    rewind(file);
    fclose(file);
}

int main(void)
{
    srand((unsigned int)time(NULL));
    int i = 0;

    printf("Number of puzzles: ");
    scanf("%d", &i);

    if(i < 1)
        return 0;

    board b;

    for (int j = 0; j < i; j++) {
        init_board(&b);
        read_board(&b,j);
        solve_board(&b, 1, 1);
    }

    return 0;
}
