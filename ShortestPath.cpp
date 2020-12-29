//Author: Zachary Gay  Date: 09/17/19 
//Purpose: This program implements Dijkstra's Algorithm in finding the shortest path in a graph whose vertices and edges are defined in the file 'GraphData.txt'

//INCLUDES
#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <limits.h> 
#include <stdio.h> 

//NAMESPACES
using namespace std;
  
//Constants
#define VERTEXES 14
#define INTMAX 999999

//Global Variables
int graph[VERTEXES][VERTEXES];
int dist[VERTEXES];

//Pick next vertex to visted base don which has the shortest path from unvisted vertexes
int shorestDistance(int distance[], bool Set[]) { 
    int minimum = INT_MAX, min_index; 

    for (int i = 0; i < VERTEXES; i++) 
    {
        if (Set[i] == false && distance[i] <= minimum) 
        {
            minimum = distance[i]; 
            min_index = i; 
        }  
    }
    return min_index; 
} 
  
//Calculates the shortest path of all vertexes from the start vertex. Uses matrix to track vertexs and edges of graph.
void shortestPath(int graph[VERTEXES][VERTEXES], int start) {   
    
    bool Visted[VERTEXES];  
    // Give all distance a default value of Max integer value(infinity) 
    for (int i = 0; i < VERTEXES; i++) 
    {
        dist[i] = INTMAX;
        Visted[i] = false; 
    } 
    // Set Distance of start node to 0 
    dist[start] = 0; 
    // Find shortest path for all vertices 
    for (int vertexNum = 0; vertexNum < VERTEXES - 1; vertexNum++) { 

        int min_index = shorestDistance(dist, Visted); 
        // Mark the picked vertex as processed 
        Visted[min_index] = true; 
        // Update the new distance value from adjancent vertexes
        for (int i = 0; i < VERTEXES; i++)   
        {
            //Check if vertex has been visted, & that the new distance is shorter than a previously set distance.
            if (!Visted[i] && graph[min_index][i] && dist[min_index] != INTMAX && dist[min_index] + graph[min_index][i] < dist[i]) 
            {
                dist[i] = dist[min_index] + graph[min_index][i]; 
            }
        }
    } 
} 

void formGraph(){
    //create stream
    std::ifstream inFile;
    //open file
    inFile.open("GraphData.txt");
    //check if file opened succesfully. if not end program.
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); 
    }
    int start, end, weight;
    //while there is still input create matrix
    while (inFile >> start >> end >> weight) {
        graph[start][end] = weight;
    }
    //close file
    inFile.close();
}

int main() 
{   //create graph from input file and form 3d array
    formGraph();
    //create variabels to hold user input information
    int start,end;
    printf("\nEnter Start Vertex:"); 
    std::cin >> start;
    printf("Enter End Vertex:"); 
    std::cin >> end;

    //Calculate the shortest path for each vertex from the start vertex
    shortestPath(graph, start); 
    //Display the amount of weight for the shortest path from start vertex toe nd vertex
    printf("Total Weight: %d",dist[end]); 
    printf("\n"); 
    return 0; 
}
