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

#define MAX 202

using namespace std;

//ACLARACION : Para resolver los ejercicios opte por devolver la MAXIMA cantidad de elementos pintados en las funciones recursivas.
// Luego la funcion principal, que devuelve el resultado final, simplemente le resta a la longitud del arreglo la MAXIMA 
//cantidad de numero pintados , es decir , la MINIMA cantidad de elementos que deje sin pintar en el arreglo.

int max_Pintados(vector<int> &a , vector<vector<vector<int> > > &cubo , int n, int dec, int inc, int i)
{
 
   // Si ya lo calcule devolver
    if (cubo[dec][inc][i] != -1){
        return cubo[dec][inc][i];}
 
    // Si ya revise todo
    if (i == n){
        return 0;}
 
    // en a[i] tomo la decision de pintarlo de rojo (ser parte de una cadena creciente)
    if (a[i] > a[inc]) 
    {
        // Tengo que guardar el valor optimo es decir la maxima cant. de numero pintados a partir de i.
        // Voy a guardar el maximo entre pintarlo de rojo y seguir con la recursion tomando esa decision 
        // (por eso le sumo uno) o quedarme con el valor que calcule antes
        cubo[dec][inc][i] = max ( 1 + max_Pintados(a, cubo, n, dec, i, i + 1),cubo[dec][inc][i]);
    }
  
    // en a[i] tomo la decision de pintarlo de azul (ser parte de una cadena decreciente)
    if (a[i] < a[dec])
    {
        // Tengo que guardar el valor optimo es decir la maxima cant. de numero pintados a partir de i.
        // Voy a guardar el maximo entre pintarlo de azul y seguir con la recursion tomando esa decision 
        // (por eso le sumo uno) o quedarme con el valor que calcule antes
        cubo[dec][inc][i] = max( 1 + max_Pintados(a, cubo, n, i, inc, i + 1), cubo[dec][inc][i]);
    }
   
   // Siempre puedo no pintarlo , asique tambien debo guardar el valor optimo. En este caso 
   // tomo el maximo entre no pintarlo (por eso no le sumo uno) y el valor que tenia antes calculado.
    cubo[dec][inc][i] = max( max_Pintados(a, cubo, n, dec, inc, i + 1), cubo[dec][inc][i]);
 
    return cubo[dec][inc][i];

}
 

int ejercicio3(int n, vector<int> &a)
{
    vector<vector<vector<int> > > cubo (MAX,vector<vector<int> >(MAX,vector <int>(MAX,-1))); //Estructura auxiliar que sirve como diccionario
     // Le agrego dos valores al arreglo para formar las cadenas de rojos y azules. Esto es para que
    // cuando pinte por primera vez un color siempre va a poder hacerlo ya que para el caso de querer
    // pintar el a[i] de rojo , el ultimo de ese color es INT_MIN y siempre el a[i] > INT_MIN. 
    // El caso azul es analogo.
    // Notar que para arreglos con longitud mayor a 200 esto no funciona pero no voy a usar 
    // mas que eso para hacer pruebas.
    a[MAX - 1] = INT_MAX; 
    a[MAX - 2] = INT_MIN;
    int r = n - max_Pintados(a, cubo, n, MAX - 1, MAX - 2,0);
   // cout << "Salida :" << endl;
   // cout << r << endl;
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
    /*cout << "Entrada :" << endl;
    for(int i = 0 ; i < vec.size(); i++) 
    {
        cout << vec[i] << " , ";
    }
    cout << endl;*/
    auto start = std::chrono::high_resolution_clock::now();
    ejercicio3(n,vec);
    auto finish = std::chrono::high_resolution_clock::now();
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << " ";
   /* cout <<"tiempo tomado = "<< std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() <<" nanosegundos" << endl;
    cout << "o en milisegundos : "<< std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << endl;
    cout << "o en segundos : "<< std::chrono::duration_cast<std::chrono::seconds>(finish-start).count()  << endl;
    */
    return 0;

}