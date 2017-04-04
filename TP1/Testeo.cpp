#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <chrono>
#include <bits/stdc++.h>
#include <fstream>
#define MAX 102

using namespace std;

//Variables globales 
int size;
vector<int> v;
int* arr;
int maxPintados1;
int maxPintados2;

//Funciones para el ejercicio 1
int cantPintados(vector<int> &b);
bool esSolucion(vector<int> &a , vector<int> &b ,  int k , int c);
int BacktrackSinPodar(vector<int> &a , vector<int> &b  , int k);
int Ejercicio1 (int n, vector<int> &a );

//Funciones para el ejercicio 2
bool PuedoPintar(vector<int> &a , vector<int> &b ,  int k , int c);
int BacktrackColoreo(vector<int> &a , vector<int> &b , int k);
int Ejercicio2 (int n, vector<int> &a);

//Funciones para el ejercicio 3
int Ejercicio3(int n, vector<int> &a);
int min_SinPintar(vector<int> &a , int dp[MAX][MAX][MAX], int n, int dec, int inc, int i);

//Funciones para generar tests
int populateArray();
int testGenerator();
vector<int> parser(ifstream &myfile);

int main(int argc, char** argv) {
    int menuOption;

    do

    {
        cout << "Selecciona un algoritmo para resolver el problema : " << endl  ;
        cout << "1. Fuerza Bruta" << endl ;
        cout << "2. Backtracking-Podando" << endl ;
        cout << "3. Dinamico" << endl  ;
        cout << "4. Usar el mismo arreglo para compararlo contra Fuerza Bruta" << endl;
        cout << "5. Usar el mismo arreglo para compararlo contra Backtracking-Podando" << endl;
        cout << "6. Usar el mismo arreglo para compararlo contra Dinamico" << endl;
        cout << "7. Salir " << endl ;
        cin >> menuOption ;

        auto start = std::chrono::high_resolution_clock::now();
        auto finish = std::chrono::high_resolution_clock::now();

        switch (menuOption)
        {
        case 1:

            size=populateArray();
            start = std::chrono::high_resolution_clock::now();
            Ejercicio1(size,v);
            finish = std::chrono::high_resolution_clock::now();
            
           /*size=testGenerator();
            v = parser(myfile);
            start = std::chrono::high_resolution_clock::now();
            Ejercicio1(size,v);
            finish = std::chrono::high_resolution_clock::now();
           */

            break;

        case 2:

            size=populateArray();
            start = std::chrono::high_resolution_clock::now();
            Ejercicio2(size,v);
            finish = std::chrono::high_resolution_clock::now();

            break;

        case 3:

            size=populateArray();
            start = std::chrono::high_resolution_clock::now();
            Ejercicio3(size,v);
            finish = std::chrono::high_resolution_clock::now();

        break;        

        case 4:

            start = std::chrono::high_resolution_clock::now();
            Ejercicio1(size,v);
            finish = std::chrono::high_resolution_clock::now();

        break;

        case 5:

            start = std::chrono::high_resolution_clock::now();
            Ejercicio2(size,v);
            finish = std::chrono::high_resolution_clock::now();

        break;

        case 6:

            start = std::chrono::high_resolution_clock::now();
            Ejercicio3(size,v);
            finish = std::chrono::high_resolution_clock::now();

        break;
        
        case 7:
            cout << endl << "Salir del programa" << endl  ;
            break;
            
        default:
            cout << endl << "Flasheaste con el numero de opcion" << endl  ;
        }// end switch

        cout <<"tiempo tomado = "<< std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() <<" nanosegundos" << endl;
        cout << "o en milisegundos : "<< (std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() / 1000000 ) << endl;
        cout << "o en segundos : "<< (std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() / 1000000000 ) << endl;
    }   while (menuOption !=7); // end do-while

}

int cantPintados(int k , vector<int> &b ) //Cuenta la cantidad de azules y rojos que hay en el arreglo
{
    int res = 0;
    for(int i = 0; i <= k ; i++)
    {
        if(b[i] == 1 || b[i] == 2)
        {
            res++;
        }
    }
    return res;
}

bool esSolucion(vector<int> &a , vector<int> &b ,  int k , int c)
{
    if(k==0){return true;}  // Si estoy en el primero siempre es solucion

    for ( int i = 0 ; i < k ; i++)  // Me paro en un indice i comenzando desde el principio
    {
        for ( int j = i+1 ; j <= k ; j++)  // Me paro en j = i+1. Voy comparando si aquellos que sean del mismo color respetan su orden
        {
            if ( b[i] == 1 && b[j] == 1)    // Si son rojos deben ser crecientes
            {
                if ( a[i] >= a[j]){return false;}
            }
            if( b[i] == 2 && b[j] == 2)     //Si son azules deben ser decrecientes.
            {
                if( a[i] <= a[j]){return false;}
            }
        }
    }
    return true;
}

int BacktrackSinPodar(vector<int> &a , vector<int> &b  , int k) 
{
    for (int c = 1 ; c <= 3 ; c++)    // El ciclo principal del algoritmo recorre las tres descisiones posible : 
    {                                 // c = 1 es ROJO, c = 2 es AZUL , c = 3 es NO lo pinto
        b[k] = c;
        if( (k+1) < a.size())
        {
            BacktrackSinPodar(a,b,k+1);  // Si hay mas elementos por recorrer hago la llamada recursiva con el siguiente
        }
        else
        {               
            if(esSolucion(a,b,k,c))   // Si llegue al final del arreglo me fijo si esta rama dentro del arbol de decisiones
            {                           // es una solucion correcta.
                                        // Porque hasta k ? Bueno porque como voy a estar pisando el arreglo b , cuando vuelva de la recursion
                                        // no me interesa ver los valores despues del k actual ya que no deberian estar pintados.
                int p = cantPintados(k,b);   // Si es solucion me fijos cuantos pinte y comparo con el maximo que venia pintando
                if(p >= maxPintados1){maxPintados1=p;}
            }
        }                   
    }
    return true; // Si sali del ciclo es porque ya probe los tres colores;
}

int Ejercicio1 (int n, vector<int> &a) 
{
    a.resize(n);
    if (n == 0)  // Si el arreglo es vacio no pinto nada;
    {
        return 0;
    }
    else 
    {
        vector<int> b(n);
        int k = 0;  // Posicion en el arreglo
        maxPintados1 = 0; // Inicializo una variable global
        for (int i = 0; i < n ; i++) 
        {
            b[i] = 0;   // Inicializo el arreglo auxiliar con 0
        }
        BacktrackSinPodar(a,b,k); // Esta funcion toma el arreglo original, uno auxiliar y una posicion en el arreglo

        cout << "Salida :" << endl;
        cout << n - maxPintados1 << endl;
        return (n - maxPintados1);
    }

}

bool PuedoPintar(vector<int> &a , vector<int> &b ,  int k , int c)
{

    if (k == 0) {return true;} //Siempre puedo pintar el primer elemento del arreglo
    if (c == 3) {return true;} //Siempre puedo "no-pintarlo"
    
    int i = k-1;               //Me ubico en el anterior al que estoy mirando
    
    while ( i >= 0 )           //Avanzo hacia atras hasta encontrar otro del mismo color con el que quiero pintar la k-esima posicion
    {
        if (b[i] != c) 
        {
            i--;
        }
        else
        {
            break;
        }

    }
    if (i == -1)           // Si llegue aca es porque no encontre ningun numero pintado del color actual
    {
        return true;       // Entonces seguro que lo puedo pintar
    }
    else                   // Si sali antes del ciclo es porque si encontre uno.
    {
        if (c == 1)        // Si es rojo tengo que verificar que el que quiero pintar mantenga la propiedad de creciente.  
        {
            if (a[i] < a[k]) 
            {
                return true;
            }
            else 
            {
                return false;
            }
        }

        if (c == 2)       // Si es azul tengo que verificar que el que quiero pintar mantenga la propiedad de creciente.
        {
            if (a[i] > a[k]) 
            {
                return true;
            }
            else 
            {
                return false;
            }
        }
    }

}

int BacktrackColoreo(vector<int> &a , vector<int> &b , int k) 
{
    for (int c = 1 ; c <= 3 ; c++)    // El ciclo principal del algoritmo recorre las tres descisiones posible : 
    {                                 // c = 1 es ROJO, c = 2 es AZUL , c = 3 es NO lo pinto
        if(PuedoPintar(a,b,k,c)) 
        {
            b[k] = c;                 // b es un arreglos paralelo al original que lo uso para ir construyendo las posibles soluciones
            
            if( (k+1) < a.size())            // Si hay mas elementos por pintar llamo devuelta a la funcion pero en el siguiente elemento
            {
                BacktrackColoreo(a,b,k+1);    
            }
            else                      // Si llegue a una hoja en el arbol de decisiones. Termine con una posible solucion en b.
            {
                int p = cantPintados(k,b);     // Cuento cuantos elementos pinte hasta k
                if(p >= maxPintados2){maxPintados2 = p;}  // Si supere los que habia pintado en una solucion anterior guardada en
                                                        // variable global, actualizo el maximo 
            }
            
        }                   
    }
    return true; // Si sali del ciclo es porque ya probe los tres colores;
}

int Ejercicio2 (int n, vector<int> &a) 
{
    a.resize(n);
    if (n == 0)  // Si el arreglo es vacio no pinto nada;
    {
        return 0;
    }
    else 
    {
        vector<int> b(n);
        int k = 0;  // Posicion en el arreglo
        maxPintados2 = 0; // Inicializo una variable global
        for (int i = 0; i < n ; i++) 
        {
            b[i] = 0;   // Inicializo el arreglo auxiliar con 0
        }
        BacktrackColoreo(a,b,k); // Esta funcion toma el arreglo original, uno auxiliar y una posicion en el arreglo
       
        cout << "Salida :" << endl;
        cout << n - maxPintados2 << endl;
        return (n - maxPintados2);
    }

}

int min_SinPintar(vector<int> &a , int dp[MAX][MAX][MAX], int n, int dec, int inc, int i)
{
    // Si ya lo calcule devolver
    if (dp[dec][inc][i] != -1)
        return dp[dec][inc][i];
 
    // Si ya revise todo
    if (i == n)
        return 0;
 
    // en a[i] tomo la decision de pintarlo de rojo (ser parte de una cadena creciente)
    if (a[i] > a[inc])
        // Voy al siguiente elemento tomando la decision de que en la pos i lo pinte de rojo
        dp[dec][inc][i] = min_SinPintar(a, dp, n, dec, i, i + 1);
 
    // en a[i] tomo la decision de pintarlo de azul (ser parte de una cadena decreciente)
    if (a[i] < a[dec])
    {
        // Si es la primera vez que lo voy a pintar de azul
        if (dp[dec][inc][i] == -1)
            // Voy al siguiente elemento tomando la decision de que en la pos i lo pinte de azul
            dp[dec][inc][i] = min_SinPintar(a, dp, n, i, inc, i + 1);
 
        // Si ya habia tomado una decision sobre i (como siempre pregunto primero si puedo pintarlo de rojo 
        // quiere decir que i ya fue considerado como rojo). Ahora debo ver si la decision es optima 
        // , es decir , si tengo la minima cantidad de elementos no pintados
        else
            //Tengo que decidir el minimo entre dejarlo como estaba o pintarlo de azul y seguir avanzando recursivamente
            dp[dec][inc][i] = min(min_SinPintar(a, dp, n, i, inc, i + 1),
                                                  dp[dec][inc][i]);
    }
 
    // Si el elemento no puede ser pintado de algun color y es la primera vez que paso por esta decision
    if (dp[dec][inc][i] == -1)
       // Ya tengo uno que no puedo pintar asique sumo uno y sigo avanzando con recursion
        dp[dec][inc][i] = 1 + min_SinPintar(a, dp, n, dec, inc, i + 1); 
 
    // Si ya se habia tomado una decision para el elemento en la pos i , y ahora se considera no pintarlo
    else
    // Tengo que tomar la decision optima, es decir, el minimo entre dejarlo como estaba antes o dejarlo como no pintado y seguir avanzando
        dp[dec][inc][i] = min(1 + min_SinPintar(a, dp, n, dec, inc, i + 1),
                                                    dp[dec][inc][i]);
 
    return dp[dec][inc][i];
}
 

int Ejercicio3(int n, vector<int> &a)
{
    // Agrego dos elementos al arreglo
    // para que se puedan armar las subsecuencias de rojos y azules
    // en la pos MAX - 2  es asignado INT_MAX para los azules (cadena decreciente)
    // ya que el siguiente numero debe ser mas chico. De esta manera siempre un elem va a ser mas chico que INT_MAX
    //Igualmente para los rojos (cadena creciente) INT_MIN es asignado a la pos MAX - 1
    a[MAX - 2] = INT_MAX;
    a[MAX - 1] = INT_MIN;
 
    int dp[MAX][MAX][MAX];
    memset(dp, -1, sizeof dp);
 
    cout << "Salida :" << endl;
    cout << min_SinPintar(a, dp, n, MAX - 2, MAX - 1, 0) << endl;
    return min_SinPintar(a, dp, n, MAX - 2, MAX - 1, 0);
}

int populateArray()
{
    int size;
    cout <<  endl << "Longitud del arreglo :" << endl ;
    cin >> size;


    int randomnum, c1, n1;

    randomnum=size;
    v.resize(size);
    cout<< endl <<"La lista de numeros al azar es :" << endl;

    for (c1 = 1; c1 <= size; c1++) 
    {
        n1 = rand()%size + 1;
        cout << n1 << " , ";
        v[c1] = n1;
    }
    cout << endl;
    return size;    

}

int testGenerator()
{
    cout << "Cuantos archivos queres generar? ";
    int n;
    cin >> n;

    cout << "Cuantos digitos queres mostrar? ";
    int n_digits;
    cin >> n_digits;   // i.e. zeroes == 3  ->  001.txt

    cout << "Introduzca un prefijo para todos los archivos: ";
    string prefix;
    cin.ignore();
    getline(cin, prefix);  // i.e. prefix == "file"  -> file001.txt

    string ext(".txt");
    
    int size;
    cout <<  endl << "Introduzca la longitud del arreglo :" << endl ;
    cin >> size;

    int c1, n1;

    for ( int i = 1; i <= n; ++i )
    {   // use a stringstream to create a file names like: prefix001.txt
        stringstream ss;
        ss << prefix << setfill('0') << setw(n_digits) << i << ext;

        // open the file. If not c++11 use  ss.str().c_str()  instead
        ofstream file( ss.str() );
        if ( !file )
        {
            cerr << "Error: failed to create file " << ss.str() << '\n';
            break;
        }

        // write something to the newly created file
        file << size << endl;
        for (c1 = 1; c1 <= size; c1++) 
        {
            n1 = rand()%size + 1;
            if(c1 < size){file << n1 << " ";} // Si no es el final hacer un espacio
            else{ file  << n1 << endl;}        // Si voy a imprimir el ultimo no poner un espacio despues
        }

        if ( !file )
        {
            cerr << "Error: failed to write to file " << ss.str() << '\n';
            break;
        }
    }
    return size;
}

vector<int> parser(ifstream &myfile) { // Devuelve un arreglo con los numeros;
    int tam;
    string n;
    string str;
    char cNum[10];
    int i = 0;
    myfile.open("test01.txt");
    if (myfile.is_open())
    {
        getline(myfile,n); // n esta el primer arguemento
        tam = atoi(n.c_str());
        vector<int> list;
        list.reserve(tam);
        while(myfile.good()) 
        {
            myfile.getline(cNum,256, ' ');
            list.push_back(atoi(cNum)); 
            i++;
        }
        myfile.close();
        return list;            
    }   
    else 
    {
        cout << "No se pudo encontrar el archivo";
    }
}
