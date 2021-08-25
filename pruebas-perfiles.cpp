//--LIBRERÍAS DEL PROGRAMA:
#include<iostream>
#include<fstream>
using namespace std;
//--CONSTANTES DEL PROGRAMA:
const int ML = 30;
//--ESTRUCTURAS DEL PROGRAMA:
struct personal
{
    char nombre[ML]={' '};
    char contrasena[ML]={' '};
    char tipo = ' ';
    char cuenta = 'e';
    char fecha[ML]={' '};
};
//--DESARROLLO DEL MAIN:
int main()
{
    fstream archivo;
    personal revision;
    return 0;
}
