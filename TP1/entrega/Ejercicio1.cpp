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


int maxPintados1;

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

int backtrackSinPodar(vector<int> &a , vector<int> &b  , int k) 
{
    for (int c = 1 ; c <= 3 ; c++)    // El ciclo principal del algoritmo recorre las tres descisiones posible : 
    {                                 // c = 1 es ROJO, c = 2 es AZUL , c = 3 es NO lo pinto
        b[k] = c;
        if( (k+1) < a.size())
        {
            backtrackSinPodar(a,b,k+1);  // Si hay mas elementos por recorrer hago la llamada recursiva con el siguiente
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

int ejercicio1 (int n, vector<int> &a) 
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
        backtrackSinPodar(a,b,k); // Esta funcion toma el arreglo original, uno auxiliar y una posicion en el arreglo
        return (n - maxPintados1);
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
        fprintf(stderr, "Uso: %s path/entrada.txt \n", argv[0]);
        return 0;
    }

    ifstream myfile;
	int n = parsertam(myfile,argv[1]);
	vector<int> vec = parser(myfile,argv[1]);
	auto start = std::chrono::high_resolution_clock::now();
    ejercicio1(n,vec);
    auto finish = std::chrono::high_resolution_clock::now();
    cout << "Salida :" << endl;
    cout << n - maxPintados1 << endl;
    cout << "tiempo tomado : " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << " ms " << endl;
   
	return 0;

}