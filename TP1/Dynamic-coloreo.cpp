#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <bits/stdc++.h>
#define MAX 102

using namespace std;

int min_SinPintar(int arr[], int dp[MAX][MAX][MAX], int n, int dec, int inc, int i)
{
    // Si ya lo calcule devolver
    if (dp[dec][inc][i] != -1)
        return dp[dec][inc][i];
 
    // Si ya revise todo
    if (i == n)
        return 0;
 
    // en a[i] tomo la decision de pintarlo de rojo (ser parte de una cadena creciente)
    if (arr[i] > arr[inc])
        // Voy al siguiente elemento tomando la decision de que en la pos i lo pinte de rojo
        dp[dec][inc][i] = min_SinPintar(arr, dp, n, dec, i, i + 1);
 
    // en a[i] tomo la decision de pintarlo de azul (ser parte de una cadena decreciente)
    if (arr[i] < arr[dec])
    {
        // Si es la primera vez que lo voy a pintar de azul
        if (dp[dec][inc][i] == -1)
            // Voy al siguiente elemento tomando la decision de que en la pos i lo pinte de azul
            dp[dec][inc][i] = min_SinPintar(arr, dp, n, i, inc, i + 1);
 
        // Si ya habia tomado una decision sobre i (como siempre pregunto primero si puedo pintarlo de rojo 
        // quiere decir que i ya fue considerado como rojo). Ahora debo ver si la decision es optima 
        // , es decir , si tengo la minima cantidad de elementos no pintados
        else
            //Tengo que decidir el minimo entre dejarlo como estaba o pintarlo de azul y seguir avanzando recursivamente
            dp[dec][inc][i] = min(min_SinPintar(arr, dp, n, i, inc, i + 1),
                                                  dp[dec][inc][i]);
    }
 
    // Si el elemento no puede ser pintado de algun color y es la primera vez que paso por esta decision
    if (dp[dec][inc][i] == -1)
       // Ya tengo uno que no puedo pintar asique sumo uno y sigo avanzando con recursion
        dp[dec][inc][i] = 1 + min_SinPintar(arr, dp, n, dec, inc, i + 1); 
 
    // Si ya se habia tomado una decision para el elemento en la pos i , y ahora se considera no pintarlo
    else
    // Tengo que tomar la decision optima, es decir, el minimo entre dejarlo como estaba antes o dejarlo como no pintado y seguir avanzando
        dp[dec][inc][i] = min(1 + min_SinPintar(arr, dp, n, dec, inc, i + 1),
                                                    dp[dec][inc][i]);
 
    return dp[dec][inc][i];
}
 

int Ejercicio3(int arr[], int n)
{
    // Agrego dos elementos al arreglo
    // para que se puedan armar las subsecuencias de rojos y azules
    // en la pos MAX - 2  es asignado INT_MAX para los azules (cadena decreciente)
    // ya que el siguiente numero debe ser mas chico. De esta manera siempre un elem va a ser mas chico que INT_MAX
    //Igualmente para los rojos (cadena creciente) INT_MIN es asignado a la pos MAX - 1
    arr[MAX - 2] = INT_MAX;
    arr[MAX - 1] = INT_MIN;
 
    int dp[MAX][MAX][MAX];
    memset(dp, -1, sizeof dp);
 
    return min_SinPintar(arr, dp, n, MAX - 2, MAX - 1, 0);
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
	int arr[n];
	copy(vec.begin(),vec.end(),arr);
	cout << Ejercicio3(arr,n) << endl;

	return 0;

}