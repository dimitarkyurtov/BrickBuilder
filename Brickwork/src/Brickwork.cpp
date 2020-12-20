#include "Brickwork.h"
#include <iostream>

void Brickwork::initialize(const int& n, const int& m)
{
    this->n = n;
    this->m = m;
    first_layer = new int* [n];
    second_layer = new int* [n];
    for(int i = 0; i < n; ++i)
    {
        first_layer[i] = new int [m];
        second_layer[i] = new int [m];
    }
}

void Brickwork::assign(int **matrix)
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            this->first_layer[i][j] = matrix[i][j];
            this->second_layer[i][j] = 0;
        }
    }
}

Brickwork::Brickwork()
{
   initialize(0, 0);
}

Brickwork::Brickwork(const int& n, const int& m, int **_first_layer)
{
    initialize(n, m);
    assign(_first_layer);
}

Brickwork::Brickwork(const Brickwork& bw)
{
    initialize(bw.n, bw.m);
    assign(bw.first_layer);
}

const Brickwork& Brickwork::operator=(const Brickwork& bw)
{
    int **cpy_layer;
    for(int i = 0; i < n; ++i)
    {
        cpy_layer[i] = new int [m];
        cpy_layer[i] = first_layer[i];
    }
    cpy_layer = first_layer;
    if(this != &bw)
    {
        initialize(bw.n, bw.m);
        assign(bw.first_layer);
    }
    for(int i = 0; i < n; ++i)
    {
        delete []cpy_layer[i];
    }
    delete []cpy_layer;
    return *this;
}

void Brickwork::print_layer(int **layer, std::ostream& stream = std::cout)
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            stream << layer[i][j] << " ";
        }
        stream << std::endl;
    }
}

void Brickwork::print_second_layer(std::ostream& stream = std::cout)
{
    print_layer(second_layer, stream);
}


void Brickwork::print_first_layer(std::ostream& stream = std::cout)
{
    print_layer(first_layer, stream);
}

void Brickwork::generate_second_layer()
{
    int** cpy_layer = new int* [n];
    int** cpy_layer_2 = new int* [n];
    for(int i = 0; i < n; ++i)
    {
        cpy_layer[i] = new int [m];
        cpy_layer_2[i] = new int [m];
    }
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            cpy_layer[i][j] = first_layer[i][j];
            cpy_layer_2[i][j] = 0;
        }
    }
    recursion(cpy_layer, 1, cpy_layer_2);
    for(int i = 0; i < n; ++i)
    {
        delete [] cpy_layer[i];
        delete [] cpy_layer_2[i];
    }

    delete []cpy_layer;
    delete []cpy_layer_2;
}

void Brickwork::recursion(int **layer_1, int ctr, int **layer_2)
{
    int** cpy_layer_2 = new int* [n];
    int** layer = new int* [n];
    for(int i = 0; i < n; ++i)
    {
        layer[i] = new int[m];
        cpy_layer_2[i] = new int [m];
    }
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            layer[i][j] = layer_1[i][j];
            cpy_layer_2[i][j] = layer_2[i][j];
        }
    }
    int first = -1, second = -1;
    bool isCompleted = true;
    for(int i = 0; i < n && isCompleted; ++i)
    {
        for(int j = 0; j < m && isCompleted; ++j)
        {
            if(layer[i][j] != -1)
            {
                isCompleted = false;
                first = layer[i][j];
                cpy_layer_2[i][j] = ctr;
                layer[i][j] = -1;
                if(i+1 < n && layer[i+1][j] != -1 && layer[i+1][j] != first)
                {
                    second = layer[i+1][j];
                    layer[i+1][j] = -1;
                    cpy_layer_2[i+1][j] = ctr;
                    ctr++;
                    if(i+2 < n && layer[i+2][j] == second)
                    {
                         recursion(layer, i+2, j, ctr, first, cpy_layer_2);
                    }
                     if(j+1 < m && layer[i+1][j+1] == second)
                    {
                         recursion(layer, i+1, j+1, ctr, first, cpy_layer_2);
                    }
                     if(j-1 >= 0 && layer[i+1][j-1] == second)
                    {
                         recursion(layer, i+1, j-1, ctr, first, cpy_layer_2);
                    }
                    layer[i+1][j] = second;
                    cpy_layer_2[i+1][j] = 0;
                    ctr--;
                }
                 if(j+1 < m && layer[i][j+1] != -1 && layer[i][j+1] != first)
                {
                    second = layer[i][j+1];
                    layer[i][j+1] = -1;
                    cpy_layer_2[i][j+1] = ctr;
                    ctr++;
                    if(j+2 < m && layer[i][j+2] == second)
                    {
                         recursion(layer, i, j+2, ctr, first, cpy_layer_2);
                    }
                     if(i+1 < n && layer[i+1][j+1] == second)
                    {
                         recursion(layer, i+1, j+1, ctr, first, cpy_layer_2);
                    }
                     if(i-1 >= 0 && layer[i-1][j+1] == second)
                    {
                         recursion(layer, i-1, j+1, ctr, first, cpy_layer_2);
                    }
                    ctr--;
                }
            }
        }
    }
    if(isCompleted)
    {
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                second_layer[i][j] = cpy_layer_2[i][j];
            }
        }
    }
    for(int i = 0; i < n; ++i)
    {
        delete [] layer[i];
        delete [] cpy_layer_2[i];
    }

    delete []layer;
    delete []cpy_layer_2;
}

void Brickwork::recursion(int **layer_1, const int& ind, const int& ind2, int ctr, const int& last, int **layer_2)
{
    int** cpy_layer_2 = new int* [n];
    int** layer = new int* [n];
    for(int i = 0; i < n; ++i)
    {
        layer[i] = new int[m];
        cpy_layer_2[i] = new int [m];
    }
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            layer[i][j] = layer_1[i][j];
            cpy_layer_2[i][j] = layer_2[i][j];
        }
    }
    int first = layer[ind][ind2], second;
    layer[ind][ind2] = -1;
    cpy_layer_2[ind][ind2] = ctr;
    if(ind-1 >= 0 && layer[ind-1][ind2] != -1 && layer[ind-1][ind2] != first && layer[ind-1][ind2] != last)
    {
        second = layer[ind-1][ind2];
        layer[ind-1][ind2] = -1;
        cpy_layer_2[ind-1][ind2] = ctr;
        ctr++;
        if(ind-2 >= 0 && layer[ind-2][ind2] == second)
        {
             recursion(layer, ind-2, ind2, ctr, first, cpy_layer_2);
        }

         if(ind2-1 >= 0 && layer[ind-1][ind2-1] == second)
        {
             recursion(layer, ind-1, ind2-1, ctr, first, cpy_layer_2);
        }
         if(ind2+1 < m && layer[ind-1][ind2+1] == second)
        {
             recursion(layer, ind-1, ind2+1, ctr, first, cpy_layer_2);
        }

        {
             recursion(layer, ctr, cpy_layer_2);
        }
        layer[ind-1][ind2] = second;
        cpy_layer_2[ind-1][ind2] = 0;
        ctr--;
    }
     if(ind+1 < n && layer[ind+1][ind2] != -1 && layer[ind+1][ind2] != first && layer[ind+1][ind2] != last)
    {
        second = layer[ind+1][ind2];
        layer[ind+1][ind2] = -1;
        cpy_layer_2[ind+1][ind2] = ctr;
        ctr++;
        if(ind+2 < n && layer[ind+2][ind2] == second)
        {
             recursion(layer, ind+2, ind2, ctr, first, cpy_layer_2);
        }
         if(ind2-1 >= 0 && layer[ind+1][ind2-1] == second)
        {
             recursion(layer, ind+1, ind2-1, ctr, first, cpy_layer_2);
        }
         if(ind2+1 < m && layer[ind+1][ind2+1] == second)
        {
             recursion(layer, ind+1, ind2+1, ctr, first, cpy_layer_2);
        }

        {
             recursion(layer, ctr, cpy_layer_2);
        }
        layer[ind+1][ind2] = second;
        cpy_layer_2[ind+1][ind2] = 0;
        ctr--;
    }
     if(ind2-1 >= 0 && layer[ind][ind2-1] != -1 && layer[ind][ind2-1] != first && layer[ind][ind2-1] != last)
    {
        second = layer[ind][ind2-1];
        layer[ind][ind2-1] = -1;
        cpy_layer_2[ind][ind2-1] = ctr;
        ctr++;
        if(ind-1 >= 0 && layer[ind-1][ind2-1] == second)
        {
             recursion(layer, ind-1, ind2-1, ctr, first, cpy_layer_2);
        }
         if(ind+1 < n && layer[ind+1][ind2-1] == second)
        {
             recursion(layer, ind+1, ind2-1, ctr, first, cpy_layer_2);
        }
         if(ind2-2 >= 0 && layer[ind][ind2-2] == second)
        {
             recursion(layer, ind, ind2-2, ctr, first, cpy_layer_2);
        }

        {
             recursion(layer, ctr, cpy_layer_2);
        }
        layer[ind][ind2-1] = second;
        cpy_layer_2[ind][ind2-1] = 0;
        ctr--;
    }
     if(ind2+1 < m && layer[ind][ind2+1] != -1 && layer[ind][ind2+1] != first && layer[ind][ind2+1] != last)
    {
        second = layer[ind][ind2+1];
        layer[ind][ind2+1] = -1;
        cpy_layer_2[ind][ind2+1] = ctr;
        ctr++;
        if(ind-1 >= 0 && layer[ind-1][ind2+1] == second)
        {
             recursion(layer, ind-1, ind2+1, ctr, first, cpy_layer_2);
        }
        if(ind+1 < n && layer[ind+1][ind2+1] == second)
        {
             recursion(layer, ind+1, ind2+1, ctr, first, cpy_layer_2);
        }
        if(ind2+2 < m && layer[ind][ind2+2] == second)
        {
             recursion(layer, ind, ind2+2, ctr, first, cpy_layer_2);
        }

        {
             recursion(layer, ctr, cpy_layer_2);
        }
        layer[ind][ind2+1] = second;
        cpy_layer_2[ind][ind2+1] = 0;
        ctr--;
    }
    else
    {
        //error
    }
    for(int i = 0; i < n; ++i)
    {
        delete [] cpy_layer_2[i];
        delete [] layer[i];
    }

    delete []layer;
    delete []cpy_layer_2;
}

Brickwork::~Brickwork()
{
    for(int i = 0; i < n; ++i)
    {
        delete [] first_layer[i];
        delete [] second_layer[i];
    }

    delete []first_layer;
    delete []second_layer;
}
