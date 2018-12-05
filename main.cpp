/**************************
CSC 335 Project 2
Brian Rentsch, Matt Kilcher
Fall 2018
***************************/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    int m;    

    //Parse command line input
    if(argc == 1)  //No arguments
    {
        cout << "\nUsage: \t" << argv[0] << " <M value>\n\n";
        return 1;
    }
    else if(argc > 2)  //Too many arguments
    {
        cout << "\nError: too many arguments\n";
        cout << "\nUsage: \t" << argv[0] << " <M value>\n\n";           
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
            cout << "\nUsage: \t" << argv[0] << " <M value>\n\n";
            return 1;
        }
    }

    cout << "\nM value: " << m << endl;  //Display m value to user
    
    Graph *g = new Graph();  //Initialize graph
    bool connected;        
    
    g->populateGraph(g, m);    //Populate graph with avg degree M
    //g->printGraph(g);        //Print entire contents of graph
    g->simplePrint(g);         //Print stats of graph
    g->estimateDiameter(g);    //Estimate diameter of graph
    connected = g->connected(g);    
    cout << "Graph connected: " << connected << endl;   //If connected = 1, graph is connected;  if connected = 0, graph is disconnected   

    return 0;
}
