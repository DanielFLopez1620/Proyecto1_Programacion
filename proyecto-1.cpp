//---LIBRERÍAS:
#include<iostream>
#include<locale.h>   //librería de configuración regional
#include<fstream>
#include<string.h>  
#include<time.h>  //librería de manejo de tiempo y fechas
using namespace std;
//--PROTOTIPOS DE FUNCIONES:

//--DESARROLLO DEL MAIN:
int main()
{
    int var;
    setlocale(LC_ALL,"");  //configuración de región
    time_t rawtime;    //variable de tipo tiempo
    struct tm * timeinfo;  //estructura de tiempo que abarca desde segundo a mes--> tm_(type)
    time(&rawtime);    //función para obtener el tiempo actual
    timeinfo = localtime(&rawtime);  //cambiar el formato a la zona configurada
    //para imprimeir el tiempo usar el comando asctime(timeinfo);
    return 0;   
}
//--DEFINICIÓN DE FUNCIONES
