#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>


using namespace std;

struct Tupla {
	int x,y;
	Tupla();
};
Tupla::Tupla() {
	x = 0;
	y = 0;
}

vector<int> Extraer (vector<int> v1 , vector<int> v2)
{
	vector<int> res;
	vector< Tupla > marcados;
	for ( int i = 0 ; i < v1.size() ; i++) 
	{
		marcados[i].x = 0;
		marcados[i].y = 0;
	}

	for(int i = 0; i < v1.size() ; i ++)
	{
		for(int j = 0 ; j < v2.size() ; j++)
		{
			if( v1[i] != v2[j] )
			{
				res.push_back(v1[i]);
			}
		}
	}
}




vector<int> Longest_sub(vector< vector <int> > s)
{
	int max = 0;
	vector<int> res;
	for( int i = 0; i < s.size() ; i++)
	{
		
		if( s[i].size() > max)
		{
			max = s[i].size();
			res = s[i];
		}
	}

	return res;
}

vector<int> max_Rojos(vector<int>& v)
{
	vector< vector<int> > s(v.size()); // La subsecuencia mas larga de rojos termina en v[i]
	
	s[0].push_back(v[0]);  // Claramente s[0] = {v[0]} pues la subsecuencia mas larga que termina en v[0] es la que tiene solo al v[0];
	
	for(int i=1 ; i<v.size() ; i++)
	{
		for(int j=0 ; j<i ; j++)
		{
			if( (v[j] < v[i]) && (s[i].size() < s[j].size() +1 ))
			{
				s[i] = s[j]; // s[i] = [v[j] | j < i & v[j] < v[i]] ++ [v[i]]
			}
		}	
		s[i].push_back(v[i]);
	}
	return Longest_sub(s); // Deberia devolver tmb en los indices que estan usados
}

vector<int> max_Azules(vector<int>& v)
{
	vector< vector<int> > s(v.size()); // La subsecuencia mas larga de rojos termina en v[i]
	
	s[0].push_back(v[0]);  // Claramente s[0] = {v[0]} pues la subsecuencia mas larga que termina en v[0] es la que tiene solo al v[0];
	
	for(int i=1 ; i<v.size() ; i++)
	{
		for(int j=0 ; j<i ; j++)
		{
			if( (v[j] > v[i]) && (s[i].size() < s[j].size() +1 ))
			{
				s[i] = s[j];
			}
		}	
		s[i].push_back(v[i]);
	}
	return Longest_sub(s);
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
	vector<int> r = max_Rojos(vec);
	return 0;

}