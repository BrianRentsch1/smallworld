#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    int m;
    
    if(argc == 1)
    {
        cout << endl << "Usage: \t./project2 <M value>\n" << endl;
        return 1;
    }
    else if(argc > 2)
    {
        cout << "Error: too many arguments" << endl;
        return 1;
    }
    else
    {
        m = stoi(argv[1]);        
    }
    
    Graph *g = new Graph();

    g->populateGraph(g, m);
    g->printGraph(g);
    
    return 0;
}
