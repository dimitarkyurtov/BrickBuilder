#ifndef BRICKWORK_H
#define BRICKWORK_H

#include <iostream>

class Brickwork
{
    public:
        Brickwork();
        Brickwork(const int& _n, const int& _m, int** _first_layer);
        Brickwork(const Brickwork& bw);
        const Brickwork& operator=(const Brickwork& bw);
        void generate_second_layer();
        void print_first_layer(std::ostream&);
        void print_second_layer(std::ostream&);
        ~Brickwork();

    private:
        int n, m;
        int **first_layer;
        int **second_layer;
        void initialize(const int& n, const int& m);
        void assign(int **matrix);
        void print_layer(int **layer, std::ostream&);
        void recursion(int **layer, int ctr,int **layer_2);
        void recursion(int **layer, const int& ind, const int& ind2, int ctr, const int& last, int **layer_2);
};

#endif // BRICKWORK_H
