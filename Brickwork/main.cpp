#include "Brickwork.h"
#include <iostream>


void read_input(std::istream& istream = std::cin)
{
    int n, m;
    int **matrix;
    istream >> n >> m;
    matrix = new int* [n];
    for(int j = 0; j < n; ++j)
    {
        matrix[j] = new int [m];
    }
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            istream >> matrix[i][j];
        }
    }

    Brickwork bw(n, m, matrix);
    bw.generate_second_layer();
    bw.print_second_layer();
}

int main()
{
    read_input();
    return 0;
}


/*
2 4
1 1 2 2
3 3 4 4

2 8
1 1 2 2 6 5 5 8
3 3 4 4 6 7 7 8
*/
