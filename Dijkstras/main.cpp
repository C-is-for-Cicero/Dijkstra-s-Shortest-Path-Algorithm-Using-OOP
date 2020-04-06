#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;
// total number of vertices in the graph
#define vert 6
#define INF 9999

struct Vertex {
};

struct Arc {
  const Vertex *source;
  const Vertex *target;
  double weight;
  Arc() {
    this->source = nullptr;
    this->target = nullptr;
  }
  double get_adjacent_weight(const Vertex & s) {
    return &s == this->source ? this->weight : 0.0;
  }
  ~Arc() {
    //delete this->source;
    //delete this->target;
  }
};


struct Graph {
  Arc * arcs;
  Vertex * vertices;
  unsigned int cardA = 0;
  unsigned int cardV = 0;

  void dijkstra(int graph[vert][vert],int src, int dest) {

      //variables
      int i, r, c, V,
          tmpC,
          min,
          currVertex,
          edgeWt = 0,
          destValue = 0,
          markedValue = 0,
          wtTableR = 0,
          markedVerticesIdx = 0;
      V = this->cardV;

      /**
       * array containing vertices in the shortest path
       */
      int shortestPathVertices[V];
      memset(shortestPathVertices, 0, V*sizeof(int));
      int shortestPathVerticesIdx = 0;

      /**
       * this table will hold the weight
       */
      int weightTable[V][V];
      memset(weightTable, 0, V*V*sizeof(int));
      for (r = 0; r < V; r++) {
          for (c = 0; c < V; c++) {
              weightTable[r][c] = 9999;;
          }
      }
      weightTable[wtTableR++][src] = 0;

      /**
       * vertices that are marked
       */
      int markedVertices[V];
      memset(markedVertices, 0, V*sizeof(int));
      markedVertices[markedVerticesIdx++] = src;
      currVertex = src;

      /**
       * find shortest path
       */
      while(currVertex != dest) {

          /**
           * copy marked values to the next row of weightTable
           */
          for (i = 0; i < markedVerticesIdx; i++) {

              c = markedVertices[i];
              weightTable[wtTableR][c] = weightTable[wtTableR - 1][c];
          }

          /**
           * find the weight from the current vertex to all the other
           * vertices that are directly connected and not yet marked
           */
          for (c = 0; c < V; c++) {

              if (c != currVertex && !isMarked(c, markedVertices, markedVerticesIdx)) {

                  edgeWt = graph[currVertex][c];
                  destValue = weightTable[wtTableR - 1][c];
                  markedValue = weightTable[wtTableR][currVertex];

                  min = findMin(destValue, markedValue + edgeWt);

                  weightTable[wtTableR][c] = min;

              }

          }

          /**
           * find minimum unmarked vertices in current row
           */
          min = 99999;
          for (c = 0; c < V; c++) {

              if (!isMarked(c, markedVertices, markedVerticesIdx)) {
                  if (weightTable[wtTableR][c] < min) {
                      min = weightTable[wtTableR][c];
                      tmpC = c;
                  }
              }

          }

          /**
           * found a new vertex for marking
           */
          markedVertices[markedVerticesIdx++] = tmpC;
          currVertex = tmpC;

          /**
           * variables update
           */
          wtTableR++;

      }

      /**
       * compute shortest path vertices
       */
      c = dest;
      shortestPathVertices[shortestPathVerticesIdx++] = c;
      markedValue = weightTable[wtTableR - 1][dest];
      for (r = wtTableR - 2; r >= 0; r--) {

          if (weightTable[r][c] != markedValue) {
              c = markedVertices[r];
              markedValue = weightTable[r][c];
              shortestPathVertices[shortestPathVerticesIdx++] = c;
          }

      }

      /**
       * display the weight and shortest path
       * print adj
       */
      printf("Shortest Path between %d and %d\n", src, dest);
      for (i = shortestPathVerticesIdx-1; i >= 0; i--) {
          printf("%d", shortestPathVertices[i]);
          if (i > 0) {
              printf(" --> ");
          }
      }
      printf("\n");
      printf("Weight of the path: %d\n", weightTable[wtTableR-1][dest]);

  }

  Graph(const unsigned int &A, const unsigned int &V) {
    this->arcs = new Arc[A]();
    this->vertices = new Vertex[V]();
    this->cardV = V;
    this->cardA = A;
  }

  void define_arc(const unsigned int & i,
                  const Vertex * s,
                  const Vertex * t,
                  const double & w) {
    if (i >= cardA || (s == nullptr) || (t == nullptr)) {
      cout << "Error cannot define arc on " << i << endl;
      return;
    }
    this->arcs[i].source = s;
    this->arcs[i].target = t;
    this->arcs[i].weight = w;

  }
  const Vertex * get_vertex(const unsigned int & i) const {
    return i >= cardV ? nullptr : &this->vertices[i];
  }

  void print_matrix() {


    for (unsigned int i = 0; i < this->cardV; ++i) {
      cout << i << " : ";
      for (unsigned int j = 0; j < this->cardA; ++j) {
        cout << this->arcs[j].get_adjacent_weight(this->vertices[i]) << " ";
      }
      cout << endl;
    }
  }

  ~Graph() {
    delete [] arcs;
    delete [] vertices;
  }

  int findMin(int x, int y) {
      if (x < y) {
          return x;
      }
      return y;
  }

  /**
   * this function will check if the vertex is marked
   */
  int isMarked(int v, int markedVertices[], int markedVerticesIdx) {

      int i = 0;
      for (i = 0; i < markedVerticesIdx; i++) {
          if (v == markedVertices[i]) {
              return 1;
          }
      }

      return 0;
  }











};

int main() {
   /*instructions:
   */


  Graph * graph = new Graph(9, 6);
  int weightedtable[6][6];
  graph->define_arc(0, graph->get_vertex(0), graph->get_vertex(1), 2.0);
  graph->define_arc(0, graph->get_vertex(0), graph->get_vertex(2), 4.0);
  graph->define_arc(1, graph->get_vertex(1), graph->get_vertex(2), 1.0);
  graph->define_arc(1, graph->get_vertex(1), graph->get_vertex(3), 4.0);
  graph->define_arc(1, graph->get_vertex(1), graph->get_vertex(4), 2.0);
  graph->define_arc(2, graph->get_vertex(2), graph->get_vertex(4), 3.0);
  graph->define_arc(3, graph->get_vertex(3), graph->get_vertex(4), 3.0);
  graph->define_arc(3, graph->get_vertex(3), graph->get_vertex(5), 2.0);
  graph->define_arc(4, graph->get_vertex(4), graph->get_vertex(5), 2.0);


  weightedtable[0][1]=2;
  weightedtable[0][2]=4;
  weightedtable[0][3]=INF;
  weightedtable[0][4]=INF;
  weightedtable[0][5]=INF;
  weightedtable[0][0]=0;

  weightedtable[1][0]=2;
  weightedtable[1][1]=0;
  weightedtable[1][2]=1;
  weightedtable[1][3]=4;
  weightedtable[1][4]=2;
  weightedtable[1][5]=9999;

  weightedtable[2][0]=4;
  weightedtable[2][1]=1;
  weightedtable[2][2]=0;
  weightedtable[2][3]=INF;
  weightedtable[2][4]=3;
  weightedtable[2][5]=INF;

  weightedtable[4][0]=INF;
  weightedtable[4][1]=2;
  weightedtable[4][2]=3;
  weightedtable[4][3]=3;
  weightedtable[4][4]=0;
  weightedtable[4][5]=2;

  weightedtable[3][0]=INF;
  weightedtable[3][1]=4;
  weightedtable[3][2]=INF;
  weightedtable[3][3]=0;
  weightedtable[3][4]=3;
  weightedtable[3][5]=2;

  weightedtable[5][0]=INF;
  weightedtable[5][1]=INF;
  weightedtable[5][2]=INF;
  weightedtable[5][3]=2;
  weightedtable[5][4]=2;
  weightedtable[5][5]=0;


  graph->print_matrix();
  graph->dijkstra(weightedtable,0,5);

  delete graph;
  return 0;
}
