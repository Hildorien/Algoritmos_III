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

//ACLARACION : Para resolver los ejercicios opte por devolver la MAXIMA cantidad de elementos pintados en las funciones recursivas.
// Luego la funcion principal, que devuelve el resultado final, simplemente le resta a la longitud del arreglo la MAXIMA 
//cantidad de numero pintados , es decir , la MINIMA cantidad de elementos que deje sin pintar en el arreglo.

int max_Pintados(vector<int> &a , int cubo[MAX][MAX][MAX], int n, int dec, int inc, int i)
{
    // Si ya lo calcule devolver
    if (cubo[dec][inc][i] != -1)
        return cubo[dec][inc][i];
 
    // Si ya revise todo
    if (i == n)
        return 0;
 
    // en a[i] tomo la decision de pintarlo de rojo (ser parte de una cadena creciente)
    if (a[i] > a[inc])
        // Sumo 1 y voy al siguiente elemento tomando la decision de que en la pos i lo pinte de rojo
        cubo[dec][inc][i] = 1 + max_Pintados(a, cubo, n, dec, i, i + 1);
 
    // en a[i] tomo la decision de pintarlo de azul (ser parte de una cadena decreciente)
    if (a[i] < a[dec])
    {
        // Si es la primera vez que lo voy a pintar de azul
        if (cubo[dec][inc][i] == -1)
            // Sumo 1 y voy al siguiente elemento tomando la decision de que en la pos i lo pinte de azul
            cubo[dec][inc][i] = 1 + max_Pintados(a, cubo, n, i, inc, i + 1);
 
        // Si ya se habia calculado los pintados hasta i (como siempre pregunto primero si puedo pintarlo de rojo 
        // quiere decir que i ya fue considerado como rojo). Ahora debo ver si la decision es optima 
        // , es decir , si tengo la maxima cantidad de elementos pintados
        else
            //Tengo que decidir el maximo entre pintarlo de azul (por eso le sumo 1) y seguir avanzando recursivamente
            // o el valor previamente calculado (es el mejor hasta ahora).
            cubo[dec][inc][i] = max( 1 + max_Pintados(a, cubo, n, i, inc, i + 1),
                                                  cubo[dec][inc][i]);
    }
 
    // Si el elemento no puede ser pintado de algun color y es la primera vez que paso por esta decision
    if (cubo[dec][inc][i] == -1)
       // Ya tengo uno que no puedo pintar asique no le sumo nada y sigo avanzando con recursion
        cubo[dec][inc][i] = max_Pintados(a, cubo, n, dec, inc, i + 1); 
 
    // Si ya se habia calculado los pintados hasta la pos i , y ahora se considera no pintarlo
    else
    // Tengo que tomar la decision optima, es decir, el maximo entre dejarlo como no pintado 
    // (por eso no le sumo nada) y seguir avanzando recursivamente tomando la decision de que no pinte el i 
    // o el valor previamente calculado (es el mejor hasta ahora).
        cubo[dec][inc][i] = max( max_Pintados(a, cubo, n, dec, inc, i + 1),
                                                    cubo[dec][inc][i]);
 
    return cubo[dec][inc][i];
}
 

int Ejercicio3(int n, vector<int> &a)
{
    // Agrego dos elementos al vector para que se puedan armar las subsecuencias de rojos y azules.
    // En la pos MAX - 2  es asignado INT_MAX para los azules (cadena decreciente)
    // ya que el siguiente numero debe ser mas chico. De esta manera siempre un elem va a ser mas chico que INT_MAX.
    // Igualmente para los rojos (cadena creciente), INT_MIN es asignado a la pos MAX - 1. 
    // Esto sirve para los casos donde se comienza a pintar de un color que no use. Por ejemplo la comparacion a[i] < a[dec] 
    // con a[dec] = INT_MAX siempre es true para el caso de querer pintar el a[i] de azul cuando todavia no pinte ninguno.
    // En el caso para pintarlo de rojo es analogo.
    // Para el resto de los casos a[dec] y a[inc] guardan los ultimos elementos pintados del de azul y rojo respectivamente.
    // En conclusion para indicar que el ultimo pintado de un color todavia no ocurrio se pone un indice fuera del rango donde
    // se guarda una condicion que siempre sea verdadera al comparar el caso. 
    a[MAX - 2] = INT_MAX;
    a[MAX - 1] = INT_MIN;
 
    int cubo[MAX][MAX][MAX]; // En el caso de que el arreglo original tenga una longitud mayor a 100 esto no puede resolverse
    // Sin embargo para comparar con los otros dos algoritmos voy a estar probando con longitudes menores a 100
    memset(cubo, -1, sizeof cubo);
    // Como max_Pintados devuelve la maxima cantidad de elementos que puedo pintar en el arreglo
    // restarle a n esta funcion me devuelve el minimo de elementos que NO pinte en el arreglo.
    int r = n - max_Pintados(a, cubo, n, MAX - 2, MAX - 1, 0);
    cout << "Salida :" << endl;
    cout << r << endl;
    return  r;
}

int parsertam(ifstream &myfile, char* argv)  // Devuelve el tamanio del arreglo
{
    int tam;
    string n;
    myfile.open(argv);
    if (myfile.is_open())
    {
        getline(myfile,n); // n esta el primer arguemento
        myfile.close();
        tam = atoi(n.c_str());
        return tam;
    }
    else cout << "No se pudo encontrar el archivo" << endl;
}

vector<int> parser(ifstream &myfile, char* argv) { // Devuelve un arreglo con los numeros;
    int tam;
    string n;
    string str;
    char cNum[10];
    int i = 0;
    myfile.open(argv);
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
        cout << "No se pudo encontrar el archivo" << endl;
    }
}

int main(int argc , char* argv[]) {
    
    if (argc <= 1) {
        fprintf(stderr, "Uso: %s commando [argumentos ...]\n", argv[0]);
        return 0;
    }

    ifstream myfile;
    int n = parsertam(myfile,argv[1]);
    vector<int> vec = parser(myfile,argv[1]);
    cout << "Entrada :" << endl;
    for(int i = 0 ; i < vec.size() ; i++) 
    {
        cout << vec[i] << " , ";
    }
    cout << endl;
    auto start = std::chrono::high_resolution_clock::now();
    Ejercicio3(n,vec);
    auto finish = std::chrono::high_resolution_clock::now();
    cout <<"tiempo tomado = "<< std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() <<" nanosegundos" << endl;
    cout << "o en milisegundos : "<< (std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() / 1000000 ) << endl;
    cout << "o en segundos : "<< (std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() / 1000000000 ) << endl;

    return 0;

}