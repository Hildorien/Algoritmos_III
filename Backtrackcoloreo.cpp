#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

int maxPintados; 
int aux;


using namespace std;

bool PuedoPintar(int n , int a[] , int b[] ,  int k , int c)
{
	//	cout << "Veo si puedo pintar el " << a[k] << "de color " << c << endl;
	//	cout << "k es " << k << endl;
	//	cout << "c es " << c << endl;
	//	cout << "a[k] es " << a[k] << endl;
	//	cout << " b[k] es " << b[k] << "porque todavia no lo pinte" << endl;
	//	if ( k >=1 ) {cout << " b[k-1] es " << b[k-1] << "que es el anterior que pinte" << endl;}

	if (k == 0) {
	//cout << " Como k es 0 lo puedo pintar" << endl;
	 return true;} //
	if (c == 3) {return true;}
	int i = k-1;
	//cout << "i vale " << i << endl;
	//cout << "Reviso los anteriores a partir de la pos : " << i << " para atras " << endl;
	while ( i >= 0 ) 
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
	//cout << " i vale " << i  << "al salir del cilco " << endl;
	if (i == -1)
	{
	//	cout << "Salgo por i == -1 , es decir no hay otro pintado del mismo color todavia " << endl;
		return true;
	}
	else 
	{
		if (c == 1)
		{
		//	cout << "Me fijo si voy a colorear de rojo" << endl;
		//	cout << "a[i] es : " << a[i] << "a[k] es: " << a[k] << endl;
			if (a[i] < a[k]) 
			{
		//		cout << " Voy a colorear : " << a[k] << "de rojo" << endl;
				return true;
			}
			else 
			{
		//		cout << " No puedo colorearlo de rojo" << endl;
				return false;
			}
		}

		if (c == 2) 
		{
	//		cout << "Me fijo si voy a colorear de azul" << endl;
			if (a[i] > a[k]) 
			{
	//			cout << " Voy a colorear : " << a[k] << "de azul" << endl;
				return true;
			}
			else 
			{
	//			cout << " No puedo colorearlo de azul" << endl;
				return false;
			}
		}
	}

}



int BacktrackColoreo(int n , int a[] , int b[] , int k, int pintados) 
{
	for (int c = 1 ; c <= 3 ; c++) 
	{		
		if(PuedoPintar(n,a,b,k,c)) 
		{
			b[k] = c;
 			if ( c!= 3) {pintados++;}

 			cout << " b queda : " << endl;
 			for(int i = 0 ; i < n ; i++)
 			{
 				cout << b[i] << " , ";
 			}
 			cout << endl;
 			cout << " Pintados vale : " << pintados << endl;

 			if( (k+1) < n) 
			{
				BacktrackColoreo(n,a,b,k+1,pintados);
				
				for (int i = k + 1; i < n ; i++) // Subo un nivel, despinto todo lo que venia pintando hasta el nivel que subi para probar otro camino
				{
					b[i] = 0;

				}
			}
			
		}					
	}
	return true; // Si sali del ciclo es porque ya probe los tres colores;
}


int Coloreo (int n, int a[]) 
{
	if (n == 0) 
	{
		return 0;
	}
	else 
	{
		int b[n];
		int pintados = 0;
		int k = 0;
		for (int i = 0; i < n ; i++) 
		{
			b[i] = 0;
		}
		maxPintados = 0;
		pintados = 0;
		BacktrackColoreo(n,a,b,k,pintados);
		return n - maxPintados;
	}

}


int main() 
{
	int n = 4;
	int a[n] = {0,7,1,2};
	int res = Coloreo(n,a);
	cout << maxPintados << endl;


}