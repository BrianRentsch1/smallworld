#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"

#define BFS_SAMPLES 100

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
    //g->printGraph(g);
    g->simplePrint(g);

    srand(time(NULL));

    int s; 
    int d;
    int dist;
    int greatest_distance = 0;
    int greatest_s;
    int greatest_d;

    //Run BFS a certain number of times and take the largest result as the likely diameter of the graph
    for(int i = 0; i < BFS_SAMPLES; i++)  
    {
        s = rand()%MAX_NODES;
        d = rand()%MAX_NODES;   
        
        dist = g->bfs(g, s, d);
        if(dist > greatest_distance && dist != -1)
        {
            greatest_distance = dist;
            greatest_s = s;
            greatest_d = d;
        }
    }
    
    cout << "distance between "<< s << " and " << d << ": " << greatest_distance << endl;
    return 0;
}
