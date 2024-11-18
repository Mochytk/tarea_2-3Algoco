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

int distanciaEdicionDP(const string &S1, const string &S2)
{
    int n = S1.size();
    int m = S2.size();

    // Se define la matriz de DP llamada dp de tamaño (n+1)x(m+1) inicialmente conformada por ceros.
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Se inicializan los casos base de nuestra matriz.
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = i * costo_del(S1[i - 1]); // Costo de eliminar todos los caracteres de S1.
    }
    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = j * costo_ins(S2[j - 1]); // Costo de insertar todos los caracteres de S2.
    }

    // Llenamos los coeficientes restantes de nuestra matriz.
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            
            // Ahora se calculan los costos de operaciones en las casillas adyacentes (menos la transpocisión).
            int costoSustitucion = dp[i - 1][j - 1] + costo_sub(S1[i - 1], S2[j - 1]);
            int costoInsercion = dp[i][j - 1] + costo_ins(S2[j - 1]);
            int costoEliminacion = dp[i - 1][j] + costo_del(S1[i - 1]);

            // Se estudia cual es el mejor caso a elegir.
            dp[i][j] = min({costoSustitucion, costoInsercion, costoEliminacion});
            
            // Finalmente, y en caso de que sea posible, comparamos este valor con el coste de transponer los carácteres.
            if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1])
            {
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + costo_trans(S1[i - 1], S1[i - 2]));
            }
            
        }
    }

    // Por último, la solución a nuestro problema está contenido en la esquina inferior derecha de nuestra matriz, en dp[n][m].
    return dp[n][m];
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
    
    bool unico = true;
    cout << "Probar los casos arbitrarios o los unicos (Palabra Vacía y Palabras Invertidas)" << endl;
    cout << "0: Arbitrarios" << endl;
    cout << "1: Únicos" << endl;
    cin >> unico;
    if (!unico)
    {
        string carpetas[] = {"testcases/test2", "testcases/test3", "testcases/test5"};
        string archivos[] = {"testcase_2.txt", "testcase_4.txt", "testcase_6.txt", "testcase_8.txt", "testcase_10.txt"};
        for(const string& carpeta : carpetas){
            cout << "--------------------------------------------" << endl;
            cout << "--------------------------------------------" << endl;
            cout << "--------------------------------------------" << endl;
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
                int resultado = distanciaEdicionDP(S1, S2);
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
    } else {
        cout << "Copie y pegue las palabras del testcase que quiera probar" << endl;
        // Aquí haremos los casos unicos como el vacio y las palabras invertidas
        cin >> S1 >> S2;
        // Calcular la distancia de edición
        auto inicio = chrono::high_resolution_clock::now();
        int resultado = distanciaEdicionDP(S1, S2);
        auto fin = chrono::high_resolution_clock::now();
        auto duracion = chrono::duration_cast<chrono::nanoseconds>(fin - inicio);
        cout << "La distancia mínima de edición es: " << resultado << endl;
        cout << "Tiempo de ejecución: " << duracion.count() << " ns" << endl;
        cout << "--------------------------------------------" << endl;
    }
    
    return 0;
}