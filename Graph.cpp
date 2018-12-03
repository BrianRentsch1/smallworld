#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"
#include <stdio.h>
#include <queue>

using namespace std;

Graph::Graph()
{
    
}

//Initialize new graph
int Graph::initializeGraph(Graph *g, int m)
{
    srand(time(NULL));
    g->num_nodes = 0;
    g->num_edges = 0;
    g->incomplete_nodes = 0;
    if((4*m)/3 > MAX_NODES)
    {        
        return 1;
    }
    g->m = m;
    
    for(int i = 0; i < MAX_NODES; i++) //For all nodes, set random degree and initialize place in adjecency list as null
    {
        g->node_edges[i] = 0;   //Currently no edges in graph, so each node has 0 edges
        g->node_degree[i] = rand() % (((4*g->m)/3) - ((2*g->m)/3) + 1) + ((2*g->m)/3);  //generate random degree between 2/3m and and 4/3m for each node
        g->edges[i] = new node(i);
        num_nodes++;
    }
    return 0;
}

//Insert an edge into the graph
void Graph::insertEdge(Graph *g, int x, int y, bool duplicate)
{
    //cout << "Inserting an edge (" << x << "," <<y<< ")" <<endl;
    node *p = new node(y);  //Allocate new node
    p->next = g->edges[x]->next;  //Append list to end of new node
    g->edges[x]->next = p;  //Insert new node at head of list
    g->node_edges[x] += 1;  //Node x has one more edge 
    if(duplicate == false)
    {
        insertEdge(g,y,x,true);  //This is undirected graph, so insert an edge in y's list    
    }
    g->num_edges += 1;    
}

void Graph::populateGraph(Graph *g, int m)
{
    int y;
    int invalid_graph;
    invalid_graph = initializeGraph(g, m);
    if(invalid_graph == 1) //Make sure the M value chosen is realistic
    {
        cout << "Error:\tCould not populate graph.\n\tPlease select an M value such that 4m/3 is less than or equal to " << MAX_NODES << ".\n";
        cout << "\tCurrently, m = " << m << " and 4m/3 = " << (4*m)/3 << endl;
        return;
    }    
    cout << "\n\t*POPULATING GRAPH*" << endl;
    if(m > 150)
    {
        cout << "Large M value detected. This might take a while..." << endl;
    }
    graph_populated = 1;
    srand(time(NULL));
    
    for(int i = 0; i < MAX_NODES; i++)  //For each node...
    {
        node *p = g->edges[i];  //temporary node pointer

        //Variables used to prevent looping (used for small MAX_NODE values only
        bool unique_found;
        bool all_possibilities_tested = false;
        //       int past_ys[MAX_NODES];            
        int uniques_tested = 0;

        int loop_counter = 0;   //Value to prevent looping at large MAX_NODE values

        /*The purpose of this array is to hold all unique random y values we get. We do this in order to see if we have tested every possible y value, 
          in case it is impossible to completely populate a node due to limitations based on the M value. What I mean by this is, if all people only know a 
          small amount of people (M people on average), then those relationships get filled quickly while populating the graph. Each node has a respective 
          degree, meaning they should have DEGREE edges to other nodes, but this may not be possible if the other nodes have already filled their own 
          degrees, and if the remaining eligible nodes without their degrees filled are already edges connected to the node in question. Thus, incomplete 
          nodes are left in the graph. "Incomplete" meaning they have a degree higher than the number of unique edges that could be given to them.*/
        /* if(MAX_NODES < 1000)   //This operation becomes too expensive at large MAX_NODE values
        {        
            for(int p = 0; p < MAX_NODES; p++)
            {
                past_ys[p] = -1;   //Fill array of previously tested ys with -1s ("indicating blanks")
            }
            }*/
        for(int j = 0; g->node_edges[i] < g->node_degree[i]; j++) //Keep adding edges until the number of edges for node[i] == the degree of node[i]
        {
            //      cout << "ID: " << g->edges[i]->id << " Edges: "<< g->node_edges[i] << " Degree: " << g->node_degree[i] <<endl;
            bool edge_exists; //Indicate if we have found a duplicate edge
            do
            {
                p = g->edges[i]; //Point p to the top of the current node's linked list

                y = rand() % MAX_NODES;  //Generate a random node to make an edge with                

                /*   if(MAX_NODES < 1000)    //Complete this processing only if we are using the "past_ys" array previously declared
                {
                    unique_found = true;  //Start with unique_found being true
                    
                    for(int p = 0; p < MAX_NODES; p++)   //Search the array of past y's
                    {
                        if (past_ys[p] == y)   //If we find a duplicate
                        {
                            unique_found = false;   //...we won't add it to the array
                        }
                    }
                    if(unique_found == true)    //If we find a unique value
                    {
                        past_ys[uniques_tested] = y;   //...add it to the array
                        uniques_tested++;   //We found one more unique y value
                    }
                    if(uniques_tested >= MAX_NODES)   //If we have found all possible unique y values (and none of them were adequate to make a unique edge)
                    {
                        all_possibilities_tested = true;   //...we need to leave this loop, else we will loop forever
                        break;
                        }
                }*/

                //Traverse linked list of our current node to find if edge (x,y) already exists                
                while(p != nullptr)
                {
                    if(node_edges[y] == 0) //If there are no edges connected to this node...
                    {                        
                        edge_exists = false; //Currently no edges connected to this node -- OK to insert any edge (besides (x, x))  
                    }
                    else if(p->id == y)   //If a node (x, y) already exists... 
                    {
                        edge_exists = true;  //Edge will be a duplicate -- don't insert it and stop traversing this node's linked list
                        break;
                    }
                    else  //Otherwise, the edge (x, y) doesn't exist, and can be inserted
                    {
                        edge_exists = false;  //Edge will not be a duplicate -- OK to insert
                    }
                    
                    p = p->next;
                }
                
                if(loop_counter > 100000)  //Assume after 100000 loops, we've exhausted all possible y values, so break to prevent infinite looping
                {
                    all_possibilities_tested = true;
                    break;
                }
                
                loop_counter++;

            } while(y == i || node_edges[y] == node_degree[y] || edge_exists);  //Repeatedly pick a new y value if node y already has its full degree of edges or if (x,y) is an edge that already exits

            if(all_possibilities_tested == false)  //If this node did not exhaust all possible y values, we insert an edge
            {
                insertEdge(g,i,y,false);
            }
            else  //Otherwise, we break and proceed to the next node, as no other edges can be added to this node
            {
                break;
            }
        }
    }    
}

void Graph::printGraph(Graph *g)
{
    if(graph_populated == 0)  //Handle being called when graph has yet to be populated
    {
        cout << "Error:\tCould not print graph.\n\tPlease populate a graph with a valid M value first." << endl;
        return;
    }
    
    node *p;   //temporary pointer

    for(int i = 0; i < g->num_nodes; i++)
    {
        int first = 1;  //Keep track of whether or not this is the head of the current linked list, for special formatting
        
        printf("%d: ", i);
        p = g->edges[i];
        
        while (p != NULL)
        {
            if(first == 1)  //Skip first entry in list (which is the current node itself)
            {
                p = p->next;
                first = !first;
            }
            
            if(p != NULL)
            {
                printf(" %d", p->id);
                p = p->next;       
            }            
        }
        if(g->node_degree[i] != g->node_edges[i])
        {
            printf(" // expected: %d actual: %d\n", g->node_degree[i], g->node_edges[i]);
            g->incomplete_nodes += 1;
        }
        else cout << endl;
    }
    cout <<endl<< "Total nodes: " << g->num_nodes << endl;
    cout << "Total edges: " << g->num_edges << endl;
    cout << "Total nodes left incomplete: " << g->incomplete_nodes << endl;
}

void Graph::simplePrint(Graph *g)
{
    if(graph_populated == 0)  //Handle being called when graph has yet to be populated
    {
        cout << "Error:\tCould not print graph.\n\tPlease populate a graph with a valid M value first." << endl;
        return;
    }
    
    for(int i = 0; i < g->num_nodes; i++)
    {        
        if(g->node_degree[i] != g->node_edges[i])
        {
            g->incomplete_nodes += 1;
        }
    }
    cout <<endl<< "Total nodes: " << g->num_nodes << endl;
    cout << "Total edges: " << g->num_edges << endl;
    cout << "Total nodes left incomplete: " << g->incomplete_nodes << endl;
}

int Graph::bfs(Graph *g, int start, int destination)
{
    if(start >= MAX_NODES || destination >= MAX_NODES)
    {
        cout << "\nError:\tBFS could not be performed.\n\tInvalid start or destination node.\n\n";
        return -1;  //Error
    }
    node *s = g->edges[start];
    node *dst = g->edges[destination];
    
    if(s->id == dst->id)
    {    
        return 0;  //s = dst
    }

    bool visited[MAX_NODES];  //Keep track of which nodes have been visited
    for(int i = 0; i < MAX_NODES; i++) //Initialize all entries of visited to false
    {
        visited[i] = false;
    }
    
    node *parent[MAX_NODES];  //Keep track of parent nodes
    node *curr_node;  //current node
    node *curr_neighbor;
    int id;
          
    
    queue <node* > q;
    q.push(s);
    //cout <<"\n\t*STARTING BFS*\n"<< endl;
    while(!q.empty())
    {
        curr_node = q.front();
        if(curr_node->id == dst->id)  //If we have found our destination...
        {
            return backtrack(g,parent,s,dst);
        }
        q.pop();
        visited[curr_node->id] = true;
        curr_neighbor = g->edges[curr_node->id]->next;  //curr_neighbor = first edge of curr_node
        
        while(curr_neighbor != nullptr)
        {
            id = curr_neighbor->id;
            if(visited[id] == false)  //If neighbor hasn't been visited...
            {
                q.push(curr_neighbor);  //push it to queue
                visited[id] = true;   //mark as visited
                parent[id] = curr_node;            //record parent    
            }
            curr_neighbor = curr_neighbor->next;  //advance along list
        }
    }
    return -1;  //DST not found in graph containing s    
}

int Graph::backtrack(Graph *g, node *parents[MAX_NODES], node *s, node *dst)
{
    node *p = dst; //temp node pointer
    int distance = 0;

    // cout << endl;
    
    while(p->id != s->id)
    {
        distance++;
        //    cout << p->id << endl;
        p = parents[p->id];  //go back one edge
    }
    // cout << p->id <<endl;
    return distance;
}
