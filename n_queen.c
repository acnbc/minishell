#include <stdio.h>
#include <stdlib.h>

int     ft_abs(int n)
{
    if (n < 0)
        return (-n);
    return (n);
}

int     is_safe(int *board, int col, int row)
{
    int i;

    i = 0;
    while (i < col)
    {
        if (board[i] == row || ft_abs(board[i] - row) == col - i)
            return (0);
        i++;
    }
    return (1);
}

void    display_solution(int *board, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        fprintf(stdout, "%d", board[i]);
        if (i < n - 1)
            fprintf(stdout, " ");
        i++;
    }
    fprintf(stdout, "\n");
}

void    place_queens(int *board, int col, int n)
{
    int row;

    if (col == n)
    {
        display_solution(board, n);
        return ;
    }
    row = 0;
    while (row < n)
    {
        if (is_safe(board, col, row))
        {
            board[col] = row;
            place_queens(board, col + 1, n);
        }
        row++;
    }
}

int     main(int argc, char **argv)
{
    int n;
    int *board;

    if (argc != 2)
        return (1);
    n = atoi(argv[1]);
    if (n <= 0)
        return (1);
    board = malloc(sizeof(int) * n);
    if (!board)
        return (1);
    place_queens(board, 0, n);
    free(board);
    return (0);
}
