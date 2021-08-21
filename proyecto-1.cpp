//---LIBRERÍAS:
#include<iostream>
#include<locale.h>   //librería de configuración regional
#include<fstream>
#include<string.h>  
#include<time.h>  //librería de manejo de tiempo y fechas
using namespace std;
//--ESTRUCUTURAS: 
const int ML = 30;
struct personal
{
    char nombre[ML]={' '};
    char contrasena[ML]={' '};
    char tipo = ' ';
    char cuenta = 'e';
    char fecha[ML]={' '};
};
struct productos{
    char nombre[ML]={' '};
    char categoria={' '};
    int precio=0;
    int disponibilidad=0;
    int ventas=0;
    int codigo=0;
};
struct listado
{
    char nombre[ML]={' '};
    int precio_ind=0;
    int cantidad_compra=0;
};
//--PROTOTIPOS DE FUNCIONES:
void menu_admin();
void menu_client();
void menu_consul();
void compra_producto();
void archivoproducto ();
string convertToString(char* arreglo, int size);
productos buscar ();
//--DESARROLLO DEL MAIN:
int main()
{
    int var,*avar;
    char opt,*aopt;
    listado compras[ML];   // estrucutura para recibos
    setlocale(LC_ALL,"");  //configuración de región
    time_t rawtime;    //variable de tipo tiempo
    struct tm * timeinfo;  //estructura de tiempo que abarca desde segundo a mes--> tm_(type)
    time(&rawtime);    //función para obtener el tiempo actual
    timeinfo = localtime(&rawtime);  //cambiar el formato a la zona configurada
    //para imprimeir el tiempo usar el comando asctime(timeinfo);
    aopt = &opt;
    avar = &var;
    cout<<"Logueo: "<<endl;
    do
    {
        switch(opt)
        {
            case 'a':   //---Funcionalidades del admin---
                menu_admin();
                cout<<"Querido admin,digite su opcion: ";
                cin>>*avar;
                do
                {
                    switch(var)
                    {
                        case 1:
                            cout<<"Abriendo la funcionalidad de registros..."<<endl;
                        break;
                        case 2:
                            cout<<"Abriendo la funcionalidad de desbloques..."<<endl;
                        break;
                        case 3:
                            cout<<"Abriendo función de administrar categorías..."<<endl;
                        break;
                        case 4:
                            cout<<"Abriendo función de administrar productos..."<<endl;
                        break;
                        case 5:
                            cout<<"Abriendo la función de despacho de compras..."<<endl;
                        break;
                        case 6:
                            cout<<"Saliendo de la sesión..."<<endl;
                        default: 
                            cout<<"Volviendo a mostrar el menu"<<endl;
                    }
                } while (var!=6);
            break;
            case 'c':   //---Funcionalidades del cliente---
                menu_client();
                cout<<"Querido cliente,digite su opcion: ";
                cin>>*avar;
                do
                {
                    switch(var)
                    {
                        case 1:
                            cout<<"Eligio realizar una compra..."<<endl;
                        break;
                        case 2:
                            cout<<"Eligio la opción de cancelar compra..."<<endl;
                        break;
                        case 3:
                            cout<<"Calculando el total de la compra..."<<endl;
                        break;
                        case 4:
                            cout<<"Mostrando la cantidad de productos comprados..."<<endl;
                        break;
                        case 5:
                            cout<<"Saliendo de la sesión..."<<endl;
                        default: 
                            cout<<"Volviendo a mostrar el menu"<<endl;
                    }
                } while (var!=5);
            break;
            case 'o':   //---Funcionalidades del consultor---
                menu_consul();
                cout<<"Querido consultor,digite su opcion: ";
                cin>>*avar;
                do
                {
                    switch(var)
                    {
                        case 1:
                            cout<<"Cargando registros para listar productos..."<<endl;
                        break;
                        case 2:
                            cout<<"Cargando regristros de los clientes existentes..."<<endl;
                        break;
                        case 3:
                            cout<<"Calculando el total de ventas del programa..."<<endl;
                        break;
                        case 4:
                            cout<<"Buscando el producto más vendido..."<<endl;
                        break;
                        case 5:
                            cout<<"Saliendo de la sesión..."<<endl;
                        default: 
                            cout<<"Volviendo a mostrar el menu"<<endl;
                    }
                } while (var!=5);
            break;
            default:
                cout<<"Opcion no valida volviendo al loggueo"<<endl;
        }
    } while (opt!='s');
    cout<<"Gracias por venir...\nCréditos:\n\tPrograma de:\n\tJuan Rodriguez\n\tDavid Medrano\n\tDaniel López"<<endl;
    cout<<"Vuelva pronto : )"<<endl;
    return 0;   
}
//--DEFINICIÓN DE FUNCIONES
void menu_admin()
{
    cout<<"*********************************"<<endl;
    cout<<"*   OPCIONES DE ADMINISTRADOR   *"<<endl;
    cout<<"*********************************"<<endl;
    cout<<"*   1) Habilitar registros      *"<<endl;
    cout<<"*   2) Desbloquear usuarios     *"<<endl;
    cout<<"*   3) Administrar categorías   *"<<endl;
    cout<<"*   4) Administrar productos    *"<<endl;
    cout<<"*   5) Despacha compras         *"<<endl;
    cout<<"*   6) Cerrar sesión            *"<<endl;
    cout<<"*********************************"<<endl;
    return;
}
void menu_client()
{
    cout<<"*********************************"<<endl;
    cout<<"*      OPCIONES DE CLIENTE      *"<<endl;
    cout<<"*********************************"<<endl;
    cout<<"*   1) Realizar una compra      *"<<endl;
    cout<<"*   2) Cancelar una compra      *"<<endl;
    cout<<"*   3) Valor total de compra    *"<<endl;
    cout<<"*   4) Cantidad de productos    *"<<endl;
    cout<<"*   5) Cerrar Sesión            *"<<endl;
    cout<<"*********************************"<<endl;
    return;
}
void menu_consul()
{
    cout<<"*********************************"<<endl;
    cout<<"*     OPCIONES DE CONSULTOR     *"<<endl;
    cout<<"*********************************"<<endl;
    cout<<"*   1) Listado de productos     *"<<endl;
    cout<<"*   2) Listado de clientes      *"<<endl;
    cout<<"*   3) Total de ventas          *"<<endl;
    cout<<"*   4) Producto más vendido     *"<<endl;
    cout<<"*   5) Cerrar sesión            *"<<endl;
    cout<<"*********************************"<<endl;
    return;  //return final
}
void compra_producto()
{
    /*cout<<"Ingrese el nombre del producto: "<<endl;
    cin>>produc.nombre;
    cout<<"Ingrese la categoria del producto: "<<endl;
    cin>>produc.categoria;
    cout<<"Ingrese el precio: "<<endl;
    cin>>produc.precio;
    cout<<"Ingrese la disponibilidad del producto: "<<endl;
    cin>>produc.disponibilidad;
    cout<<"Ingrese la venta del producto: "<<endl;
    cin>>produc.ventas;
    */
    return;
}

void archivoproducto()
{
    /*string archivo = "archivobinario.txt";
    fstream tem;
    tem.open(archivo.c_str(), ios::binary | ios::app);
    if(!tem.eof())
    {
        tem.write((char *) &produc,sizeof(produc));
    }
    else 
    {
        cout<<"Error em la apertura de archivo"<<endl;   
    }
    tem.close();
    return;*/
}
productos buscar (string archivo)
{
    /*int autoincremental,i=0;
    fstream tem;
    tem.open(archivo,ios::binary | ios::in);
    while(!tem.eof())
    {
        tem.seekg((i)*sizeof(produc));
        tem.read((char *) &produc,sizeof(produc));
        if(tem.good())
        {
            cout<<" la posicion en el archivo es: "<<i+1<<endl;
            cout<<"nombre "<< convertToString(produc.nombre,ML)<<" categoria: "<< produc.categoria <<" precio "<<produc.precio <<" disponibilidad "<<produc.disponibilidad;
            cout<<" ventas "<< produc.ventas <<" codigo "<<produc.codigo<<" "<<endl;
            autoincremental=produc.codigo;
        }
        i=i+1;
    }  */
    return;
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