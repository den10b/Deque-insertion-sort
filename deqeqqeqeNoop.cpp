#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <locale.h>
#define N 6
using namespace std;
class graph {
public:
    int matrixSM[N][N];
    int matrixDS[N][N];
    int matrixSV[N][N];
    bool nodes[N];
    void DFS(int u)
    {
        nodes[u] = 1;
        for (int w = 0; w < N; w++) { if (matrixSM[u][w] == 1) if (nodes[w] == 0) DFS(w); }
    }
};

int main()
{
    graph GR;
    int Count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            GR.matrixSM[i][j] = 0;
            GR.matrixDS[i][j] = 0;
            GR.matrixSV[i][j] = 0;
        }

    GR.matrixSM[0][1] = 1;
    GR.matrixSM[1][2] = 1;
    GR.matrixSM[2][0] = 1;
    GR.matrixSM[3][4] = 1;
    GR.matrixSM[4][3] = 1;

    cout << endl << endl << "Matrix of connection " << endl;
    for (int i = 0; i < N; i++) {
        cout << endl;
        for (int j = 0; j < N; j++)
            cout << GR.matrixSM[i][j] << " ";
    }

    for (int i = 0; i < N; i++) GR.nodes[i] = 0;

    for (int v = 0; v < N; v++)
    {
        for (int i = 0; i < N; i++)
            GR.nodes[i] = 0;
        GR.DFS(v);
        for (int f = 0; f < N; f++)
            GR.matrixDS[v][f] = GR.nodes[f];
    }

    for (int i = 0; i < N; i++)  GR.nodes[i] = 0;

    cout << endl;
    cout << endl << endl << "Matrix of reaching " << endl;
    for (int i = 0; i < N; i++) {
        cout << endl;
        for (int j = 0; j < N; j++)
            cout << GR.matrixDS[i][j] << " ";
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if ((GR.matrixDS[i][j] == 1) && (GR.matrixDS[j][i] == 1) && (i != j)) GR.matrixSV[i][j] = 1;

    }
    cout << endl;
    cout << endl << endl << "Matrix of double reaching " << endl;
    for (int i = 0; i < N; i++) {
        cout << endl;
        for (int j = 0; j < N; j++)
            cout << GR.matrixSV[i][j] << " ";
    }
    for (int i = 0; i < N; i++)
    {
        if (GR.nodes[i] == 0) {
            for (int j = 0; j < N; j++)
                if ((GR.matrixSV[i][j] == 1)) {
                    if ((GR.nodes[j] == 0) && (GR.nodes[i] == 0)) Count++;
                    GR.nodes[i] = 1;
                    GR.nodes[j] = 1;
                }
        }
    }


    cout << endl << endl << "number of Nice connected knots is " << Count << endl;


}
