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

    g->populateGraph(g, m);
    g->printGraph(g);
    
    return 0;
}
