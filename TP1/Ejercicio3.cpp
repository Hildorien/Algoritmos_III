#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <bits/stdc++.h>
#define MAX 102

using namespace std;

//ACLARACION : Para resolver los ejercicios opte por devolver la MAXIMA cantidad de elementos pintados en las funciones recursivas.
// Luego la funcion principal, que devuelve el resultado final, simplemente le resta a la longitud del arreglo lo que devuelven las
// funciones recursivas, es decir , la MINIMA cantidad de elementos que deje sin pintar en el arreglo.

int max_Pintados(vector<int> &a , int dp[MAX][MAX][MAX], int n, int dec, int inc, int i)
{
    // Si ya lo calcule devolver
    if (dp[dec][inc][i] != -1)
        return dp[dec][inc][i];
 
    // Si ya revise todo
    if (i == n)
        return 0;
 
    // en a[i] tomo la decision de pintarlo de rojo (ser parte de una cadena creciente)
    if (a[i] > a[inc])
        // Sumo 1 y voy al siguiente elemento tomando la decision de que en la pos i lo pinte de rojo
        dp[dec][inc][i] = 1 + max_Pintados(a, dp, n, dec, i, i + 1);
 
    // en a[i] tomo la decision de pintarlo de azul (ser parte de una cadena decreciente)
    if (a[i] < a[dec])
    {
        // Si es la primera vez que lo voy a pintar de azul
        if (dp[dec][inc][i] == -1)
            // Sumo 1 y voy al siguiente elemento tomando la decision de que en la pos i lo pinte de azul
            dp[dec][inc][i] = 1 + max_Pintados(a, dp, n, i, inc, i + 1);
 
        // Si ya se habia calculado los pintados hasta i (como siempre pregunto primero si puedo pintarlo de rojo 
        // quiere decir que i ya fue considerado como rojo). Ahora debo ver si la decision es optima 
        // , es decir , si tengo la maxima cantidad de elementos pintados
        else
            //Tengo que decidir el maximo entre pintarlo de azul (por eso le sumo 1) y seguir avanzando recursivamente
            // o el valor previamente calculado (es el mejor hasta ahora).
            dp[dec][inc][i] = max( 1 + max_Pintados(a, dp, n, i, inc, i + 1),
                                                  dp[dec][inc][i]);
    }
 
    // Si el elemento no puede ser pintado de algun color y es la primera vez que paso por esta decision
    if (dp[dec][inc][i] == -1)
       // Ya tengo uno que no puedo pintar asique no le sumo nada y sigo avanzando con recursion
        dp[dec][inc][i] = max_Pintados(a, dp, n, dec, inc, i + 1); 
 
    // Si ya se habia calculado los pintados hasta la pos i , y ahora se considera no pintarlo
    else
    // Tengo que tomar la decision optima, es decir, el maximo entre dejarlo como no pintado 
    // (por eso no le sumo nada) y seguir avanzando recursivamente tomando la decision de que no pinte el i 
    // o el valor previamente calculado (es el mejor hasta ahora).
        dp[dec][inc][i] = max( max_Pintados(a, dp, n, dec, inc, i + 1),
                                                    dp[dec][inc][i]);
 
    return dp[dec][inc][i];
}
 

int Ejercicio3(int n, vector<int> &a)
{
    // Agrego dos elementos al vector
    // para que se puedan armar las subsecuencias de rojos y azules
    // en la pos MAX - 2  es asignado INT_MAX para los azules (cadena decreciente)
    // ya que el siguiente numero debe ser mas chico. De esta manera siempre un elem va a ser mas chico que INT_MAX
    //Igualmente para los rojos (cadena creciente) INT_MIN es asignado a la pos MAX - 1. Esto sirve para los casos donde
    // se comienza a pintar de un color que no use y la comparacion a[i] < a[dec] con dec = INT_MAX siempre es true para el caso
    // de querer usar el color azul por primera vez en el arreglo.
    // Para el resto de los casos a[dec] y a[inc] guardan los ultimos elementos pintados del de azul y rojo respectivamente.
    a[MAX - 2] = INT_MAX;
    a[MAX - 1] = INT_MIN;
 
    int dp[MAX][MAX][MAX]; // En el caso de que el arreglo original tenga una longitud mayor a 100 esto no puede resolverse
    // Sin embargo para comparar con los otros dos algoritmos voy a estar probando con longitudes menores a 100
    memset(dp, -1, sizeof dp);
    // Como max_Pintados devuelve la maxima cantidad de elementos que puedo pintar en el arreglo
    // restarle a n esta funcion me devuelve el minimo de elementos que NO pinte en el arreglo.
    return  n - max_Pintados(a, dp, n, MAX - 2, MAX - 1, 0);
}

int parsertam(ifstream &myfile)  // Devuelve el tamanio del arreglo
{
	int tam;
	string n;
	myfile.open("listas.txt");
	if (myfile.is_open())
	{
		getline(myfile,n); // n esta el primer arguemento
		myfile.close();
		tam = atoi(n.c_str());
		return tam;
	}
	else cout << "No se pudo encontrar el archivo";
}

vector<int> parser(ifstream &myfile) { // Devuelve un arreglo con los numeros;
	int tam;
	string n;
	string str;
	char cNum[10];
	int i = 0;
	myfile.open("listas.txt");
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

int main() {
	
	ifstream myfile;
	int n = parsertam(myfile);
	vector<int> vec = parser(myfile);
	cout << Ejercicio3(n,vec) << endl;

	return 0;

}