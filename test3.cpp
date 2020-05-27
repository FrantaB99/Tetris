#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

class Hulk
{
    public:
        int legs = 2;
};

class Thanos
{
    int glove;
    public:
        void print_glove();
        Thanos(Hulk& mulk);
};

void Thanos::print_glove()
{
    std::cout << glove << std::endl;
}

Thanos::Thanos(Hulk& mulk)
{
    glove = mulk.legs;
}

int main()
{
    Hulk hulk;
    Thanos thanos(hulk);
    thanos.print_glove();
    return 0;
}