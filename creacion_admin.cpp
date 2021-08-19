#include<iostream>
#include<fstream>
#include<string.h>
#include<locale.h>
using namespace std;
//--Estructuras del programa
const int ML = 30;
struct personal
{
    char nombre[ML]={' '};
    char contraseña[ML]={' '};
    char tipo = ' ';
    char cuenta = 'e';
    char fecha[ML]={' '};
};
//--DESARROLLO DEL MAIN
int main()
{
    fstream archivo;
    personal admin;
    string nombre = "perfiles.txt";
    string aux;
    cout<<"Bienvenido al programa de creación de admin o masters"<<endl;
    cout<<"Digite el nombre del admin :";
    getline(cin>>ws,aux);
    strcpy(admin.nombre,aux.c_str());
    cout<<"Digite una nueva contraseña: ";
    
    archivo.open(nombre,ios::app);
    
    archivo.close();
    return 0;
}