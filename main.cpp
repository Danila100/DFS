#include <iostream>
#include <fstream>
using namespace std;

void DFS(int n, int v, int prev, bool *used_vertices,int ** adjacency_Matrix )
{
    if ( v != prev )
        cout << prev+1 << "->" << v+1 <<endl;
    prev = v;     // запоминаем вершину из которой пришли
    used_vertices[v]=true;   // ставим метку о прохождении
    for (int r=0; r<n; r++) {
        if ((adjacency_Matrix[v][r] != 0) && (!used_vertices[r]))    // если в след вершине еще не были и если в нее есть ребро из текущей вершины
            DFS(n, r,v, used_vertices, adjacency_Matrix);
    }

}


int main() {

    ifstream fin( "input.txt" );

    //// поменяй названия всего сама
    //// она еще просила сделать ввод с клавы или както еще,но не с файла,думаю тоже сама справишься :)
    //// так как я начало проги скопиповал своей,то коменатрии у меня такие же,посмотри,мб их тоже поменяешь или уберешь
    //// комменты к функции DFS уникальны))

    int n = 0, v = 0;
    cout << "Enter the amount of vertices : " << endl;  // Вводим количество вершин графа
    fin >> n;

    int ** adjacency_Matrix = new int * [n]; // Матрица смежности для вершин графа
    for ( int j = 0; j < n ; ++j )
        adjacency_Matrix[j] = new int [n];

    bool used_vertices [n] ; // вектор тегов,указывающий пройдена ли вершина ( добавлена в остов )
    for (int k = 0; k < n; ++k) // изначально 0,все вершины не пройдены
        used_vertices[k] = 0;

    for ( int i = 0; i <n; ++i )
    {
        for ( int j = 0; j < n ; ++j )
            fin >> adjacency_Matrix [i][j];    // ввод матрицы
    }
    //// далее комменты можешь не менять,это я для тебя написал,чтобы понятннее было
    // проверка на связность, так как граф может быть ориентированым,то нужно пройтись по столбцам и строчкам
    for (int i = n-1; i >= 0; --i) {
        bool check1 = 0;
        bool check2 = 0;
        for (int j = n-1; j >= 0; --j) {
            check1 += adjacency_Matrix [i][j]; //проходим по строчке
            check2 += adjacency_Matrix [j][i]; // проходим по столбцу
        }
        if ( check1 + check2 == 0) {    //если нули и в строке и в столбце
            cout << "The graph is not weighted! Algorithm can not be applied! " << endl;  // если граф не связный, программа вылетает
            system("pause");
            return 0;
        }
        if ( check1 != 0)
            v = i;           // если в строке не нули,то запоминаем это вершину,потому что если нули,то из нее нет ребра(только в нее) и с нее нельзя начинать алгоритм
    }

    DFS(n, v,v, used_vertices,adjacency_Matrix);    //начинаем алгоритм с вершины,которую запомнили,из которой выходит хотя бы одно реберо

    system("pause");
    return 0;
}