/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
             double heuristic(Loc start, Loc end, Grid<double>& world)) {
    
    /* Implementation of Dijkstra's Algorithm */

    // Color all nodes initially gray and set parent of each node initially to NULL
    Grid<NodeStatus> worldStatus(world.numRows(), world.numCols());
  
    for (int i = 0; i < world.numRows(); i++)
        for (int j = 0; j < world.numCols(); j++)
            worldStatus[i][j].col = GRAY;
    
    // Initialize priority queue
    TrailblazerPQueue<Loc>  pQueue;
    
    // Setup start node
    worldStatus[start.row][start.col].col = YELLOW;
    worldStatus[start.row][start.col].dist = 0;
    pQueue.enqueue(start, heuristic(start, end, world));
    colorCell(world, start, YELLOW);

    Loc curr;
    while (!pQueue.isEmpty())   {
        curr = pQueue.dequeueMin();
        worldStatus[curr.row][curr.col].col = GREEN;
        colorCell(world, curr, GREEN);
        
        if (curr.row == end.row && curr.col == end.col) {
            Vector<Loc> finalPath;
            while (curr != start)   {
                finalPath.add(curr);
                curr = worldStatus[curr.row][curr.col].parent;
            }
            finalPath.add(start);
            Vector<Loc> finalPathRev;
            for (int i = finalPath.size()-1; i >= 0; i--)
                finalPathRev.add(finalPath.get(i));
            return finalPathRev;
        }
        
        for (Direction dir = NORTH; dir <= NORTHWEST; dir++)    {
            Loc v = adjacentPoint(curr, dir);

            if (v.row >= 0 && v.row < world.numRows() && v.col >= 0 && v.col < world.numCols()) {
                double distFromCurr = worldStatus[curr.row][curr.col].dist + costFn(curr, v, world);
                
                if (worldStatus[v.row][v.col].col == GRAY)  {
                    worldStatus[v.row][v.col].col = YELLOW;
                    worldStatus[v.row][v.col].dist = distFromCurr;
                    worldStatus[v.row][v.col].parent = curr;
                    pQueue.enqueue(v, distFromCurr + heuristic(v, end, world));
                    colorCell(world, v, YELLOW);
                }
                else if (worldStatus[v.row][v.col].col == YELLOW && worldStatus[v.row][v.col].dist >distFromCurr)     {
                    worldStatus[v.row][v.col].dist = distFromCurr;
                    worldStatus[v.row][v.col].parent = curr;
                    pQueue.decreaseKey(v, distFromCurr + heuristic(v, end, world));
                }
            }
        }
    }
}

Set<Edge> createMaze(int numRows, int numCols) {
    int clusterID = 0;
    Map<int, Set<Loc> > clusterMap;
    TrailblazerPQueue<Edge> edges;
    Set<Edge> spanningTree;
    Loc start, end;
    Edge e;
    for (int r = 0; r < numRows; r++)
        for (int c = 0; c < numCols; c++)   {
            Set<Loc> cluster;
            cluster.add(makeLoc(r, c));
            clusterMap.put(clusterID++, cluster);
        }
    
    for (int r = 0; r < numRows; r++)
        for (int c = 0; c < numCols; c++)  {
            // Horizontal edges
            if(c < numCols - 1) {
                start = clusterMap.get(r * numRows + c).first();
                end = clusterMap.get(r * numRows + c + 1).first();
                edges.enqueue(makeEdge(start, end), randomInteger(0, 9));
            }
            
            // Vertical edges
            if(r < numRows - 1) {
                start = clusterMap.get(r * numRows + c).first();
                end = clusterMap.get((r + 1) * numRows + c).first();
                edges.enqueue(makeEdge(start, end), randomInteger(0, 9));
            }
        }
    
    while (clusterMap.size() > 1)   {
        e = edges.dequeueMin();
        start = e.start;
        end = e.end;
        
        int startCl = -1;
        int endCl = -1;
        
        for (int cl : clusterMap)   {
            if (clusterMap[cl].contains(start)) {
                startCl = cl;
                if(endCl != - 1)
                    break;
            }
            
            if (clusterMap[cl].contains(end)) {
                endCl = cl;
                if(startCl != - 1)
                    break;
            }

        }
        
        if (startCl != endCl)   {
            clusterMap[startCl] = clusterMap[startCl] + clusterMap[endCl];
            clusterMap.remove(endCl);
            spanningTree.add(e);
        }
        
    }
    return spanningTree;
}

/*
 * Function: operator++(Direction & dir, int)
 * Usage: for(Direction dir = NORTH; dir <= NORTHWEST; dir++)    { ...}
 * --------------------------
 * Functionality: Overloads the ++ operator for usage with the data type Direction
 */
Direction operator++(Direction & dir, int) {
    Direction old = dir;
    dir = Direction(dir + 1);
    return old;
}

/*
 * Function: adjacentPoint(Point start, Direction dir)
 * Usage: Point nextPoint = adjacentPoint(currentPoint, NORTH)
 * --------------------------
 * Functionality: Moves a point on a 2D integer grid towards the specified direction, whereas each
 * dimension is incremented or decremented at most by 1
 */
Loc adjacentPoint(Loc loc, Direction dir) {
    Loc next;
    switch(dir) {
        case NORTH:
            next.row = loc.row - 1;
            next.col = loc.col;
            return next;
        case NORTHEAST:
            next.row = loc.row - 1;
            next.col = loc.col + 1;
            return next;
        case EAST:
            next.row = loc.row;
            next.col = loc.col + 1;
            return next;
        case SOUTHEAST:
            next.row = loc.row + 1;
            next.col = loc.col + 1;
            return next;
        case SOUTH:
            next.row = loc.row + 1;
            next.col = loc.col;
            return next;
        case SOUTHWEST:
            next.row = loc.row + 1;
            next.col = loc.col - 1;
            return next;
        case WEST:
            next.row = loc.row;
            next.col = loc.col - 1;
            return next;
        case NORTHWEST:
            next.row = loc.row - 1;
            next.col = loc.col - 1;
            return next;
    }
}

