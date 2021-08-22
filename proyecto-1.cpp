//---LIBRERÍAS:------------------------------------------------------------------------------------
#include<iostream>
#include<locale.h>   //librería de configuración regional
#include<fstream>
#include<string.h>  
#include<time.h>  //librería de manejo de tiempo y fechas
using namespace std;
//--ESTRUCUTURAS: ---------------------------------------------------------------------------------
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
//--PROTOTIPOS DE FUNCIONES:-----------------------------------------------------------------------
void menu_general();
void menu_admin();
void menu_client();
void menu_consul();
void compra_producto();
void archivoproducto ();
string convertToString(char* arreglo, int size);
productos buscar ();
//--DESARROLLO DEL MAIN---------------------------------------------------------------------------
int main()
{
    setlocale(LC_ALL,"");  //configuración de región
    int var,*avar,lec,*alec;
    char opt,*aopt,letra;
    listado compras[ML];   // estrucutura para recibos
    personal nuevo; //estructura de personal para nuevos usuarios
    time_t actual;    //variable de tipo tiempo
    struct tm * timeinfo;  //estructura de tiempo que abarca desde segundo a mes--> tm_(type)
    time(&actual);    //función para obtener el tiempo actual
    char date[ML]; //arreglo char para la fecha
    timeinfo = localtime(&actual);  //cambiar el formato a la zona configurada
    string nombre = "perfiles.txt"; //nombre del archivo de usario
    string aux;
    fstream usuarios;
    //para imprimeir el tiempo usar el comando asctime(timeinfo);
    alec = &lec;  // variable y puntero del menu general
    aopt = &opt;  //variable y puntero de logueo y usuarios
    avar = &var;  // variable y puntero de menus privados
    do
    {
        menu_general();
        cout<<"Digite su opción: ";
        cin>> *alec;
        switch(lec)  //---switch del menu inicial
        {
            case 1:
                cout<<"Siga los pasos para inicio de sesión: "<<endl;
                do
                {
                    switch(opt)   //--switch de roles
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
            break;
            case 2:
                cout<<"Preparandose para crear un nuevo usuario..."<<endl;
                usuarios.open(nombre,ios::app);
                if(usuarios.is_open())
                {
                    timeinfo = localtime( &actual); //cambio de formato de tiempo
                    strcpy(date,ctime(&actual)); //cambio a char para ser copiado en date
                    date[10]= date[13] = '_';
                    date[3]=date[7]=date[16]=date[19]='-';
                    cout<<"Digite su nuevo nombre usuario :";
                    getline(cin>>ws,aux);
                    strcpy(nuevo.nombre,aux.c_str());
                    cout<<"Digite una nueva contraseña: ";
                    getline(cin>>ws,aux);
                    strcpy(nuevo.contrasena,aux.c_str());
                    cout<<"Digite el rol inicial (a--> admin, c-->cliente, o--> consultor)"<<endl;
                    do
                    {
                        cin>>letra;
                    } while (letra!='a' || letra!='c' || letra!='o');
                    nuevo.tipo = letra;
                    nuevo.cuenta = 'e';
                    strcpy(nuevo.fecha,date);
                    usuarios.open(nombre,ios::app);
                        usuarios.write(nuevo.nombre,sizeof(nuevo.nombre));
                        usuarios.write(nuevo.contrasena,sizeof(nuevo.contrasena));
                        usuarios.write((char *)&nuevo.tipo,sizeof(nuevo.tipo));
                        usuarios.write((char *)&nuevo.cuenta,sizeof(nuevo.cuenta));
                        usuarios.write(nuevo.fecha,sizeof(nuevo.fecha));
                    usuarios.close();
                    cout<<"Usuario creado correctamente, para estar activo requiere validación de un admin...Este pendiente de esto"<<endl;
                }
                else
                    cout<<"Ha ocurrido un error, no archivo ni master detectado...\nVolviendo al menu"<<endl;
            break;
            case 3:
                cout<<"Desplegando plantilla informativa..."<<endl;
            break;
            case 4:
                cout<<"Mostrando créditos..."<<endl;
                cout<<"Gracias por venir...\nCréditos:\n\tPrograma de:\n\tJuan Rodriguez\n\tDavid Medrano\n\tDaniel López"<<endl;
            break;
            case 5:
                cout<<"Saliendo..."<<endl;
            break;
            default:
                cout<<"Volviendo a despleguar el menú: "<<endl;
        }
    } while (true);
    cout<<"Vuelva pronto : )"<<endl;
    return 0;   
}
//--DEFINICIÓN DE FUNCIONES------------------------------------------------------------------------
void menu_general()   // menu inicial
{
    cout<<"*********************************"<<endl;
    cout<<"*   OPCIONES DEL PROGRAMA       *"<<endl;
    cout<<"*********************************"<<endl;
    cout<<"*   1) Log in (Entrada)         *"<<endl;
    cout<<"*   2) Crear un usuario         *"<<endl;
    cout<<"*   3) Ayuda e info             *"<<endl;
    cout<<"*   4) Ver créditos             *"<<endl;
    cout<<"*   5) Salir                    *"<<endl;
    cout<<"*********************************"<<endl;
    return;
}
void menu_admin()   //menu del administrador
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
void menu_client()   // menu del cliente
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
void menu_consul()   // menu del consultor
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