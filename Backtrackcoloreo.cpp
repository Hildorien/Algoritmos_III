#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

int max; // variable global NO ME FUNCIONA, NO PUEDO USARLA EN NINGUNA OTRA FUNCION , NI EN MAIN

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



int BacktrackColoreo(int n , int a[] , int b[] , int k , int pintados) 
{
	//cout << " k en esta llamada vale " << k << endl;;
	for (int c = 1 ; c <= 3 ; c++) 
	{
		if (k == 0) 
		{
	//		cout << " Si vuelvo al primero comenzar a pintar devuelta" << endl;
			pintados = 0;
			for (int i = 0; i < n ; i++)
			{
				b[i] = 0;
			}
		}

		if(PuedoPintar(n,a,b,k,c)) 
		{
			b[k] = c;
	//		cout << "Pinte en la pos " << k << " el " << a[k] << "de color " << c << " y en b[k] quedo : " << b[k] << endl;
			if (c!= 3) {
				pintados++;
	//			cout << "Si pinte un Rojo o Azul incremente pintados y vale: "  << pintados << endl;
			}
			//if (pintados >= max){max = pintados;}
 			if( (k+1) < n) 
			{
	//			cout << " Valor de k antes de la llamada recursiva : " << k << endl;
	//			cout << " Valor de pintados antes de la llamada recursiva : " << pintados << endl;
				BacktrackColoreo(n,a,b,k+1,pintados);
	//			cout << " Valor de k despues de la llamada recursiva : " << k << endl;
	//			cout << " Valor de pintados despues de la llamada recursiva : " << pintados << endl;

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
		BacktrackColoreo(n,a,b,k,pintados);
	}

}


int main() 
{
	int n = 2;
	int a[n] = {9,8};
	//max = 0;
	int res = Coloreo(n,a);


}