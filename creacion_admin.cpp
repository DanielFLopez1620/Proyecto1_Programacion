#include<iostream>
#include<fstream>
#include<string.h>
#include<locale.h>
#include<time.h>
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
    char date[ML]; //arreglo char para la fecha
    time_t actual; //variable requerida para manejo de tiempo
    struct tm * timeinfo; //estructura requerida para el manejo de tiempo
    time(&actual); //lectura de tiempo
    timeinfo = localtime( &actual); //cambio de formato de tiempo
    strcpy(date,ctime(&actual)); //cambio a char para ser copiado en date
    date[10]= date[13] = '_';
    date[3]=date[7]=date[16]=date[19]='-';
    cout<<"Bienvenido al programa de creación de admin o masters"<<endl;
    cout<<"Digite el nombre del admin :";
    getline(cin>>ws,aux);
    strcpy(admin.nombre,aux.c_str());
    cout<<"Digite una nueva contraseña: ";
    getline(cin>>ws,aux);
    strcpy(admin.contraseña,aux.c_str());
    admin.tipo = 'a';
    admin.cuenta = 'a';
    strcpy(admin.fecha,date);
    archivo.open(nombre,ios::app | ios::binary);
    archivo.write(admin.nombre,sizeof(admin.nombre));
    archivo.close();
    return 0;
}