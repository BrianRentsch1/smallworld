#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"

using namespace std;

int main(void)
{
    Graph *g = new Graph();

    g->populateGraph(g, 100);
    g->printGraph(g);
    
    return 0;
}
