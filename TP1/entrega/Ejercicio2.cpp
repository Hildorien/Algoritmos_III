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

using namespace std;

//ACLARACION : Para resolver los ejercicios opte por devolver la MAXIMA cantidad de elementos pintados en las funciones recursivas.
// Luego la funcion principal, que devuelve el resultado final, simplemente le resta a la longitud del arreglo la MAXIMA 
//cantidad de numero pintados , es decir , la MINIMA cantidad de elementos que deje sin pintar en el arreglo.



int maxPintados2;

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

bool puedoPintar(vector<int> &a , vector<int> &b ,  int k , int c)
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

int backtrackConPoda(vector<int> &a , vector<int> &b , int k) 
{
    for (int c = 1 ; c <= 3 ; c++)    // El ciclo principal del algoritmo recorre las tres descisiones posible : 
    {                                 // c = 1 es ROJO, c = 2 es AZUL , c = 3 es NO lo pinto
        if(puedoPintar(a,b,k,c)) 
        {
            b[k] = c;                 // b es un arreglos paralelo al original que lo uso para ir construyendo las posibles soluciones
            
            if( (k+1) < a.size())            // Si hay mas elementos por pintar llamo devuelta a la funcion pero en el siguiente elemento
            {
                backtrackConPoda(a,b,k+1);    
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

int ejercicio2 (int n, vector<int> &a) 
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
        backtrackConPoda(a,b,k); // Esta funcion toma el arreglo original, uno auxiliar y una posicion en el arreglo
        return (n - maxPintados2);
    }

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
        fprintf(stderr, "Uso: %s path/entrada.txt\n", argv[0]);
        return 0;
    }

    ifstream myfile;
    int n = parsertam(myfile,argv[1]);
    vector<int> vec = parser(myfile,argv[1]);
    auto start = std::chrono::high_resolution_clock::now();
    ejercicio2(n,vec);
    auto finish = std::chrono::high_resolution_clock::now();
    cout << "Salida :" << endl;
    cout << n - maxPintados2 << endl;
    cout << "tiempo tomado : " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << " ms " << endl;

    return 0;

}