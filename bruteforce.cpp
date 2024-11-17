#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

vector<int> cost_insert(26), cost_delete(26);
vector<vector<int>> cost_replace(26, vector<int>(26)), cost_transpose(26, vector<int>(26));

int costo_sub(char a, char b)
{
    return cost_replace[int(a) - 97][int(b) - 97];
}

int costo_ins(char b)
{
    return cost_insert[int(b) - 97];
}

int costo_del(char a)
{
    return cost_delete[int(a) - 97];
}

int costo_trans(char a, char b)
{
    return cost_transpose[int(a) - 97][int(b) - 97];
}

int distanciaEdicionBruteForce(const string &S1, const string &S2){
    
}

int main()
{
    string S1, S2;
    int num, i, j;

    ifstream archivo("cost_insert.txt");

    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    i = 0;
    while (archivo >> num)
        cost_insert[i++] = num;

    ifstream archivo2("cost_delete.txt");

    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    i = 0;
    while (archivo2 >> num)
        cost_delete[i++] = num;

    ifstream archivo3("cost_replace.txt");

    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    i = 0, j = 0;
    while (archivo3 >> num)
    {
        cost_replace[i][j++] = num;
        if (j == 26)
        {
            j = 0;
            i++;
        }
    }

    ifstream archivo4("cost_transpose.txt");

    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    i = 0, j = 0;
    while (archivo4 >> num)
    {
        cost_transpose[i][j++] = num;
        if (j == 26)
        {
            j = 0;
            i++;
        }
    }

    cin >> S1 >> S2;

    int resultado = distanciaEdicionBruteForce(S1, S2);
    cout << "La distancia mínima de edición es: " << resultado << endl;

    return 0;
}