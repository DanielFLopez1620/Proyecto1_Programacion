//--LIBRERÍAS DEL PROGRAMA:
#include<iostream>
#include<fstream>
#include<locale.h>
#include<string.h>
using namespace std;
//--CONSTANTES DEL PROGRAMA:
const int ML = 30;
const int lec = 5;
//--ESTRUCTURAS DEL PROGRAMA:
struct personal
{
    char nombre[ML]={' '};
    char contrasena[ML]={' '};
    char tipo = ' ';
    char cuenta = 'e';
    char fecha[ML]={' '};
};
//--PROTOTIPOS DE FUNCIONES:
string convertToString(char* arreglo, int size); //conversión de string a caracter mediante concatenación
//--DESARROLLO DEL MAIN:
int main()
{
    setlocale(LC_ALL,"");
    int opt,con;
    fstream archivo;
    personal revision, lectura[lec];
    string nombre = "perfiles.txt";
    string aux,convertido;
    char buscado[ML]={' '};
    char letra;
    long direccion;
    do
    {
        cout<<"1)Cambio permiso\n2)Leer archivo\n3)Salir\nDigite una opcion:";
        cin>> opt;
        switch (opt)
        {
        case 1:
            cout<<"Habilitando opción de cambio..."<<endl;
            cout<<"Digite el nombre a cambiar: ";
            getline(cin>>ws,aux);
            archivo.open(nombre,ios::binary | ios::in | ios::out);
            if(archivo.is_open())
            {
                cout<<"Abriendo..."<<endl;
                while(!archivo.eof())
                {
                    archivo.read(lectura[con].nombre,sizeof(lectura[con].nombre));
                    archivo.read(lectura[con].contrasena,sizeof(lectura[con].contrasena));
                    archivo.read((char *)&lectura[con].tipo,sizeof(lectura[con].tipo));
                    archivo.read((char *)&lectura[con].cuenta,sizeof(lectura[con].cuenta));
                    archivo.read(lectura[con].fecha,sizeof(lectura[con].fecha));
                    convertido = convertToString(lectura[con].nombre,ML);
                    cout<<aux<<" "<<convertido<<"-"<<endl;   
                    strcpy(buscado,aux.c_str());
                    aux = convertToString(buscado,ML);
                    if(aux == convertido)
                    {
                        cout<<"Encontrado..."<<endl; 
                        direccion = archivo.tellp();
                        cout<<"Digite el cambio en cuenta: ";
                        cin>> letra;
                        archivo.seekp(direccion-(sizeof(lectura[con].fecha)+sizeof(lectura[con].cuenta)));
                        lectura[con].cuenta = letra;
                        archivo.write((char *)&lectura[con].cuenta,sizeof(lectura[con].cuenta));
                        cout<<"Asignación completada..."<<endl;
                        break;
                    }
                }
            }
            else
                cout<<"Ha ocurrido un problema accediendo al archivo"<<endl;
            system("pause");
            archivo.close();
            break;
        case 2:
            cout<<"Leyendo archivo..."<<endl;
            archivo.open(nombre,ios::binary|ios::in);
            if(archivo.is_open())
            {
                con = 0;
                while(!archivo.eof())
                {
                    archivo.read(lectura[con].nombre,sizeof(lectura[con].nombre));
                    archivo.read(lectura[con].contrasena,sizeof(lectura[con].contrasena));
                    archivo.read((char *)&lectura[con].tipo,sizeof(lectura[con].tipo));
                    archivo.read((char *)&lectura[con].cuenta,sizeof(lectura[con].cuenta));
                    archivo.read(lectura[con].fecha,sizeof(lectura[con].fecha));
                    con++;
                }
                for(int i=0;i<con-1;i++)
                {
                    cout<<"Nombre: "<<lectura[i].nombre<<endl;
                    cout<<"Contraseña: "<<lectura[i].contrasena<<endl;
                    cout<<"Tipo: "<<lectura[i].tipo<<endl;
                    cout<<"Cuenta: "<<lectura[i].cuenta<<endl;
                    cout<<"Creación: "<<lectura[i].fecha<<"-"<<endl;
                    cout<<endl;
                }
            }
            else
                cout<<"Ha ocurrido un problema accediendo al archivo"<<endl;
            archivo.close();
            break;
        case 3:
            cout<<"Saliendo..."<<endl;
            break;
        default:
            cout<<"Volviendo a mostrar menu:"<<endl;
            break;
        }
    } while (opt!=3);
    return 0;
}
string convertToString(char* arreglo, int size) //conversión de string a caracter mediante concatenación
{
    string s = "";
    for (int i = 0; i < size; i++)
    {
        s = s + arreglo[i];
    }
    return s;
}