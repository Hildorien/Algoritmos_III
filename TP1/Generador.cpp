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

int main()
{
	
	cout << "Cuantos archivos queres generar? ";
    int n;
    cin >> n;

    //cout << "Cuantos digitos queres mostrar? ";
    //int n_digits;
    //cin >> n_digits;   // i.e. zeroes == 3  ->  001.txt

    //cout << "Introduzca un prefijo para todos los archivos: ";
    //string prefix;
    //cin.ignore();
    //getline(cin, prefix);  // i.e. prefix == "file"  -> file001.txt

    int size;
    cout <<  endl << "Introduzca la longitud del arreglo :" << endl ;
    cin >> size;

    string prefix = "_caso_";
    cout << "El prefijo de los archivos sera: " << size << prefix << endl;
    
    string ext(".txt");

    int c1, n1;

    for ( int i = 1; i <= n; ++i )
    {   // use a stringstream to create a file names like: prefix001.txt
        stringstream ss;
        //ss << prefix << setfill('0') << setw(n_digits) << i << ext;
        ss << size << prefix << i << ext;

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
            n1 = rand()%100;
            if(c1 < size){file << n1 << " ";} // Si no es el final hacer un espacio
            else{ file  << n1 << endl;}        // Si voy a imprimir el ultimo no poner un espacio despues
        }

        if ( !file )
        {
            cerr << "Error: failed to write to file " << ss.str() << '\n';
            break;
        }
    }
	return 0;
}