#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    int m;
    
    if(argc == 1)  //No arguments
    {
        cout << "\nUsage: \t./project2 <M value>\n\n";
        return 1;
    }
    else if(argc > 2)  //Too many arguments
    {
        cout << "\nError: too many arguments\n";
        cout << "\nUsage: \t./project2 <M value>\n\n";           
        return 1;
    }
    else    //Correct number of arguments
    {
        try
        {
            m = stoi(argv[1]);   //Try converting arg to int
        }
        catch(...)  //If conversion fails, handle exception
        {           
            cout << "\nError: your M value should be an integer\n";
            cout << "\nUsage: \t./project2 <M value>\n\n";
            return 1;
        }
    }

    
    Graph *g = new Graph();
    bool connected;
    
    g->populateGraph(g, m);    //Populate graph with avg degree M
    //g->printGraph(g);
    g->simplePrint(g);         //Print stats of graph
    g->estimateDiameter(g, 10000);    //Estimate diameter of graph
    connected = g->connected(g);
    cout << "Graph connected: " << connected << endl;
    
    return 0;
}
