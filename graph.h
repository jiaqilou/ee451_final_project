class Graph {
public:
      int** adjacencyMatrix;
      int vertexCount;
public:
      Graph(int vertexCount) {
            this->vertexCount = vertexCount;
            adjacencyMatrix = new int*[vertexCount];
            for (int i = 0; i < vertexCount; i++) {
                  adjacencyMatrix[i] = new int[vertexCount];
                  for (int j = 0; j < vertexCount; j++)
                        adjacencyMatrix[i][j] = 0;
            }
      }
 
      void addEdge(int i, int j,int weight) {
            if (i >= 0 && i < vertexCount && j > 0 && j < vertexCount) {
                  adjacencyMatrix[i][j] = weight;
                  adjacencyMatrix[j][i] = -(weight);
            }
      }
 
      void removeEdge(int i, int j) {
            if (i >= 0 && i < vertexCount && j > 0 && j < vertexCount) {
                  adjacencyMatrix[i][j] = 0;
                  adjacencyMatrix[j][i] = 0;
            }
      }
 
      int EdgeWeight(int i, int j) {
            if (i >= 0 && i < vertexCount && j > 0 && j < vertexCount)
                  return adjacencyMatrix[i][j];
            else
                  return 0;
      }
 
      ~Graph() {
            for (int i = 0; i < vertexCount; i++)
                  delete[] adjacencyMatrix[i];
            delete[] adjacencyMatrix;
      }
};