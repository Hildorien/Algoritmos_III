#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>


using namespace std;

int parsertam(ifstream &myfile)  // Devuelve el tamanio del arreglo
{
	int tam;
	string n;
	myfile.open("/home/toni-acer-ubuntu/Documents/Algoritmos_y estructura_de_datos_III/Algoritmos_III/listas.txt");
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
myfile.open("/home/toni-acer-ubuntu/Documents/Algoritmos_y estructura_de_datos_III/listas.txt");
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
	else cout << "No se pudo encontrar el archivo";
}

int main() {
	
	ifstream myfile;
	int n = parsertam(myfile);
	vector<int> vec = parser(myfile);
	cout << "Lista extraida del archivo : " << endl; 
	for (int i = 0; i < n ; i++) 
	{
		cout << vec[i] << ",";
	}
	cout << endl;
	
return 0;

}
