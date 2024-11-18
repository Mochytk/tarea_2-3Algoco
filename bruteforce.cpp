#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>

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
    int n = S1.size();
    int m = S2.size();
    int costo = 0;
    if (S1 == S2)
    {
        return costo;
    }

    else if (S1.empty())
    {
        for (size_t i = 0; i < m; i++)
        {
            costo += costo_ins(S2[i]);
        }
        return costo;
    }

    else if (S2.empty())
    {
        for (size_t i = 0; i < n; i++)
        {
            costo += costo_del(S1[i]);
        }
        return costo;
    }

    else if (S1[0] == S2[0])
    {
        return distanciaEdicionBruteForce(S1.substr(1),S2.substr(1));
    }

    else{
        // Buscamos el minimo de manera recursiva
        costo = min({
            (distanciaEdicionBruteForce(S1.substr(1), S2.substr(1)) + costo_sub(S1[0], S2[0])),
            (distanciaEdicionBruteForce(S1, S2.substr(1)) + costo_ins(S2[0])),
            (distanciaEdicionBruteForce(S1.substr(1), S2) + costo_del(S1[0]))
        });
        
        // Chequeamos si la transposición es posible
        if (S1[0] == S2[1] && S1[1] == S2[0]){
            costo = min(costo, 
            ((distanciaEdicionBruteForce(S1.substr(2), S2.substr(2)) + costo_trans(S1[0], S1[1])))
            );
        }

        return costo;
    }
}

int main()
{
    string S1, S2;
    int num, i, j;

    ifstream archivo("costos/cost_insert.txt");

    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    i = 0;
    while (archivo >> num)
        cost_insert[i++] = num;

    ifstream archivo2("costos/cost_delete.txt");

    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    i = 0;
    while (archivo2 >> num)
        cost_delete[i++] = num;

    ifstream archivo3("costos/cost_replace.txt");

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

    ifstream archivo4("costos/cost_transpose.txt");

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

    string carpetas[] = {"testcases/test2", "testcases/test3", "testcases/test5"};
    string archivos[] = {"testcase_2.txt", "testcase_4.txt", "testcase_6.txt", "testcase_8.txt", "testcase_10.txt"};
    for(const string& carpeta : carpetas){
        for (const string& archivo : archivos) {
            string rutaTestcase = carpeta + "/" + archivo;
            ifstream archivoTest(rutaTestcase);
            if (!archivoTest.is_open()) {
                cerr << "No se pudo abrir el archivo de prueba: " << rutaTestcase << endl;
                continue; // Salta a la siguiente iteración
            }

            string S1, S2;
            archivoTest >> S1 >> S2;
            archivoTest.close();

            // Calcular la distancia de edición
            auto inicio = chrono::high_resolution_clock::now();
            int resultado = distanciaEdicionBruteForce(S1, S2);
            auto fin = chrono::high_resolution_clock::now();

            // Mostrar resultados
            cout << "Carpeta: " << carpeta << ", Archivo: " << archivo << endl;
            cout << "S1: " << S1 << ", S2: " << S2 << endl;
            cout << "La distancia mínima de edición es: " << resultado << endl;

            auto duracion = chrono::duration_cast<chrono::nanoseconds>(fin - inicio);
            cout << "Tiempo de ejecución: " << duracion.count() << " ns" << endl;
            cout << "--------------------------------------------" << endl;
        }
    }
    
    return 0;
}