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
productos buscar();
void cambios_cuenta(string nombre,personal enlista[],char letra, long ubicaciones[],char cambio);
//--DESARROLLO DEL MAIN---------------------------------------------------------------------------
int main()
{
    setlocale(LC_ALL,"");  //configuración de región
    int var,*avar,lec,*alec,con=0;  //punteros y variables de manejo de menu;
    char opt,letra,cambio;  //auxiliares y apoyos en el manejo del menu;
    bool encontrado,correcta,permitido,borrada; // booleanos del programa
    listado compras[ML];   // estrucutura para recibos
    personal nuevo,registro,enlista[ML]; //estructura de personal para nuevos usuarios
    time_t actual;    //variable de tipo tiempo
    struct tm * timeinfo;  //estructura de tiempo que abarca desde segundo a mes--> tm_(type)
    time(&actual);    //función para obtener el tiempo actual
    char date[ML]; //arreglo char para la fecha
    timeinfo = localtime(&actual);  //cambiar el formato a la zona configurada
    string nombre = "perfiles.txt"; //nombre del archivo de usario
    string aux,*apaux,user,password,persona; //cadenas para la lectura de teclado y asignaciones
    fstream usuarios,generar;   // stream para el manejo de archivos
    //para imprimeir el tiempo usar el comando asctime(timeinfo);
    alec = &lec;  // variable y puntero del menu general
    avar = &var;  // variable y puntero de menus privados
    apaux = &aux; // auxiliar para nombres
    char buscado[ML]={' '};  // vector auxiliar para compatibilidad con registros
    long direccion,ubicaciones[ML];  // arreglo de direcciones para cambio
    do
    {
        menu_general();
        cout<<"Digite su opción: ";
        cin>> *alec;
        switch(lec)  //---switch del menu inicial
        {
            case 1:
                cout<<"Siga los pasos para inicio de sesión: "<<endl;
                cout<<"Digite su nombre:";
                getline(cin>>ws,*apaux);  //lectura de nombre
                permitido = true;
                usuarios.open(nombre,ios::in | ios::binary);  // apertura de archivo en modo binario
                if(usuarios.is_open())
                {
                    encontrado= borrada = false;
                    while(!usuarios.eof())
                    {
                        usuarios.read(registro.nombre,sizeof(registro.nombre));
                        usuarios.read(registro.contrasena,sizeof(registro.contrasena));  //lectura de registros mediante estructuras
                        usuarios.read((char *)&registro.tipo,sizeof(registro.tipo));
                        usuarios.read((char *)&registro.cuenta,sizeof(registro.cuenta));
                        usuarios.read(registro.fecha,sizeof(registro.fecha));
                        user = convertToString(registro.nombre,ML);
                        strcpy(buscado,aux.c_str());  // paso a arreglo para igualar tamanios
                        aux = convertToString(buscado,ML);  // convertir a string para permitir comparación
                        if (user==aux)
                        {
                            encontrado = true;  // se ha encontrado coincidencia de nombre
                            break;
                        }
                    }
                    usuarios.close();
                    if(registro.cuenta == 'b' || registro.cuenta=='d'  || registro.cuenta == 'e')
                        permitido = false;
                    if(encontrado && permitido)  //verificación de encontrado del usuario
                    {
                        password = convertToString(registro.contrasena,ML);
                        correcta = false;
                        do
                        {
                            cout<<"Digite la contraseña del usuario "<<user<<"\nContraseña: ";
                            cin>> aux;
                            strcpy(buscado,aux.c_str());  // conversión para mantener tamanios
                            aux = convertToString(buscado,ML);  // convertir a string para facilidad de comparacion
                            if(password == aux)
                            {
                                correcta = true;  // añadir que se ha encontrado coincidencia
                                break;
                            }
                            con++;
                        } while (con<=3); // si excede los tres intentos se sabra
                        if(correcta)  // verificación de la contraseña correcta
                        {
                            opt =registro.tipo;
                            switch(opt)   //--switch de roles
                            {
                                case 'a':   //----------------------------Funcionalidades del admin--------------------------------------
                                    menu_admin();
                                    persona = convertToString(registro.nombre,ML);
                                    cout<<"Bienvenido :"<< persona<<endl;
                                    cout<<"Querido admin,digite su opcion: ";
                                    cin>>*avar;
                                    do
                                    {
                                        switch(var) 
                                        {
                                            case 1:
                                                cout<<"Abriendo la funcionalidad de registros..."<<endl;
                                                letra = 'e'; // e--> en espera
                                                cambio = 'a';
                                                cambios_cuenta(nombre,enlista,letra,ubicaciones,cambio); // cambio para activación de cuenta
                                                break;
                                            case 2:
                                                cout<<"Abriendo la funcionalidad de desbloques..."<<endl;
                                                letra = 'b'; // b--> bloqueado
                                                cambio = 'a';
                                                cambios_cuenta(nombre,enlista,letra,ubicaciones,cambio);  // cambio para desbloqueo de cuenta 
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
                                                break;
                                            default: 
                                                cout<<"Volviendo a mostrar el menu"<<endl;
                                                break;
                                        }
                                        menu_admin();
                                        cout<<"Digite su opción, admin: "<<endl;
                                        cin>> *avar;
                                    }while (var!=6);
                                break;
                                case 'c':   //---------------------------------Funcionalidades del cliente----------------------------------
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
                                                break;
                                                default: 
                                                cout<<"Volviendo a mostrar el menu"<<endl;
                                                break;
                                            menu_client();
                                            cout<<"Digite su opción, querido cliente: "<<endl;
                                            cin>> *avar;
                                        }
                                    } while (var!=5);
                                break;
                                case 'o':   //----------------------------------Funcionalidades del consultor-------------------------------
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
                                                break;
                                            default: 
                                                cout<<"Volviendo a mostrar el menu"<<endl;
                                                break;
                                            menu_consul();
                                            cout<<"Digite su opción, querido cliente: "<<endl;
                                            cin>> *avar;
                                        }
                                    } while (var!=5);
                                break;
                                default:
                                    cout<<"Opcion no valida volviendo al loggueo"<<endl;
                                    break;
                            }
                        }
                        else  // else en caso de bloque de usuario
                        {
                            cout<<"Contraseña digitada incorrectamente 3 veces, se bloqueo el usuario..."<<endl;
                            usuarios.open(nombre,ios::binary | ios::out |ios::in);  // abrir archivo en los tres modods
                            encontrado = false;
                            while(!usuarios.eof())
                            {
                                usuarios.read(registro.nombre,sizeof(registro.nombre));
                                usuarios.read(registro.contrasena,sizeof(registro.contrasena));  //lectura de registros mediante estructuras
                                usuarios.read((char *)&registro.tipo,sizeof(registro.tipo));
                                usuarios.read((char *)&registro.tipo,sizeof(registro.tipo));
                                usuarios.read(registro.fecha,sizeof(registro.fecha));
                                aux = convertToString(registro.nombre,ML);
                                strcpy(buscado,aux.c_str());  // conversión de apoyo
                                aux = convertToString(buscado,ML);  // paso a string para mejor comparación
                                if(user == aux)  // buscar nuevamente la concidencia
                                {
                                    encontrado=true;
                                    direccion = usuarios.tellp();  //asignar la dirección actual en registros
                                    letra = 'b'; // cambio de letra para bloqueo de usuarios
                                    usuarios.seekp(direccion-(sizeof(registro.fecha)+sizeof(registro.cuenta)));   //mover puntero al aspecto para cuenta
                                    registro.cuenta = letra; 
                                    usuarios.write((char *)&registro.cuenta,sizeof(registro.cuenta)); // reasignación de bloqueo
                                    break;
                                }
                            }
                            cout<<"Su usuario ha sido bloqueado, contacte al admin en caso de requerir desbloque"<<endl;
                            usuarios.close();
                        }
                    }
                    else
                    {
                        if(registro.cuenta == 'b')  // en caso de cuenta bloqueada
                            cout<<"Su cuenta se encuentra aun bloqueada, contacte al admin para el desbloque"<<endl;
                        if(registro.cuenta== 'e') // en caso de cuenta en espera
                            cout<<"Su cuenta aún está en espera, vuelva pronto para verificar si ha sido activada por el admin"<<endl;
                        else
                            cout<<"Usuario no encontrado, posiblemente no se ha creado o fue borrado...\nVolviendo al menu"<<endl;
                    }
                }
                else
                    cout<<"Volviendo al menú...nHa ocurrido un error con el archivo de registrados..."<<endl;
                if(usuarios.is_open())
                    usuarios.close();
                break;
            case 2:
                cout<<"Preparandose para crear un nuevo usuario..."<<endl;
                generar.open(nombre,ios::out | ios::app);
                if(generar.is_open())
                {
                    timeinfo = localtime( &actual); //cambio de formato de tiempo
                    strcpy(date,ctime(&actual)); //cambio a char para ser copiado en date
                    date[10]= date[13] = '_';
                    date[3]=date[7]=date[16]=date[19]='-';  // corrección de formato de fecha
                    cout<<"Digite su nuevo nombre usuario :";
                    getline(cin>>ws,aux); 
                    strcpy(nuevo.nombre,aux.c_str());  // copiado de nombre
                    cout<<"Digite una nueva contraseña: ";
                    getline(cin>>ws,aux);   // copiado de contraseña
                    strcpy(nuevo.contrasena,aux.c_str());
                    cout<<"Digite el rol inicial (a--> admin, c-->cliente, o--> consultor)"<<endl;
                    do
                    {
                        cin>>letra;
                    } while (letra!='a' && letra!='c' && letra!='o');  // lectura de rol permitido
                    nuevo.tipo = letra;
                    nuevo.cuenta = 'e';
                    strcpy(nuevo.fecha,date);
                    generar.write(nuevo.nombre,sizeof(nuevo.nombre));
                    generar.write(nuevo.contrasena,sizeof(nuevo.contrasena));
                    generar.write((char *)&nuevo.tipo,sizeof(nuevo.tipo));
                    generar.write((char *)&nuevo.cuenta,sizeof(nuevo.cuenta));
                    generar.write(nuevo.fecha,sizeof(nuevo.fecha)); //escritura de datos en archivo
                    cout<<"Usuario creado correctamente, para estar activo requiere validación de un admin...Este pendiente de esto"<<endl;
                }
                else
                    cout<<"Ha ocurrido un error, no archivo ni master detectado...\nVolviendo al menu"<<endl;
                generar.close();
            break;
            case 3:
                cout<<"Desplegando plantilla informativa..."<<endl;
                cout<<"--------------------------------------------\nSOBRE PERFILES...\n--------------------------------------------"<<endl;
                cout<<"Este es un perfil de una tienda con 3 roles \ndefinidos que corresponden a admin, cliente y consultor"<<endl;
                cout<<"El admin tiene funciones relacionadas a\n validación de usuarios, administrar objetos, entre otros"<<endl;
                cout<<"El cliente puede realizar compras, cancelarlas\n o pagarlas, así como ver su total"<<endl;
                cout<<"El consultor puede buscar y listar diferentes\n productos y categorías, así como acceso a\n estadísticas de la tienda"<<endl;
                cout<<"--------------------------------------------\nSOBRE EL LOGUEO...\n--------------------------------------------"<<endl;
                cout<<"Para usar el programa se requiere de una cuenta\n previamente creada y validada por un admin"<<endl;
                cout<<"Una vez creados y validados no se cambiaran\n los roles ya definidos"<<endl;
                cout<<"Si se digita tres veces la contraseña incorrecta\n se bloqueará el usuaria hasta el desbloque \n por parte de un admin"<<endl;
                cout<<"Solo el admin tiene los permisos para el bloque\n de cuentas y su eliminación"<<endl;
                cout<<"--------------------------------------------"<<endl;
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
                break;
        }
    }while (lec!=5);
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
    productos ejemplo;  //borrar para después
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
    return ejemplo;
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
void cambios_cuenta(string nombre,personal enlista[],char letra, long ubicaciones[],char cambio)
{
    int elec,con = 0;
    string nom,fecha;
    long dir;
    char conversor[ML];
    fstream busqueda;
    busqueda.open(nombre, ios::binary | ios::in | ios::out);  // abrir el archivo en modo lectura
    if(busqueda.is_open()) //verificación de apertura de archivo
    {
        while(!busqueda.eof())  // mientras el archivo no termine
        {
            busqueda.read(enlista[con].nombre,sizeof(enlista[con].nombre));
            busqueda.read(enlista[con].contrasena,sizeof(enlista[con].contrasena));  //lectura de registros mediante estructuras
            busqueda.read((char *)&enlista[con].tipo,sizeof(enlista[con].tipo));
            busqueda.read((char *)&enlista[con].cuenta,sizeof(enlista[con].cuenta));
            busqueda.read(enlista[con].fecha,sizeof(enlista[con].fecha));
            ubicaciones[con] = busqueda.tellp(); // guardado de posición para cambio
            dir = busqueda.tellp();  // guardado de dirección especifica
            if(enlista[con].cuenta==letra)  // si hay coincidencia de permiso, se va a la siguiente posición
            {
                nom = convertToString(enlista[con].nombre,ML);
                cout<<"Usuario: "<<nom<<"\nEstado actual: "<<enlista[con].cuenta<<endl;
                cout<<"Que desea relizar?\n1)Aceptar cambio\n2)Ignorar cambio\n3)Pedir cambio de rol\n4)Continuar"<<endl;
                cin>>elec;  //lectura de opción
                switch(elec)
                {
                    case 1:
                        busqueda.seekp(dir-(sizeof(enlista[con].fecha)+sizeof(enlista[con].cuenta)));
                        enlista[con].cuenta = letra;
                        busqueda.write((char *)&enlista[con].cuenta,sizeof(enlista[con].cuenta));
                        break;
                    case 2:
                        cout<<"Se ha ignorado el cambio, volverá a aparecer en posteriores ocasiones"<<endl;
                        break;
                    case 3:
                        busqueda.seekp(dir-(sizeof(enlista[con].fecha)+sizeof(enlista[con].cuenta)));
                        enlista[con].cuenta = 'c';
                        busqueda.write((char *)&enlista[con].cuenta,sizeof(enlista[con].cuenta));
                        cout<<"Se ha solicitado el cambio de rol al usuario..."<<endl;
                        break;
                    default:
                        cout<<"Continuando frente a omisión..."<<endl;
                        break;
                }
                con++;
                busqueda.seekg(dir); // volver al punto de lectura correcto
                //--PENDIENTE CORREGIR SISTEMA DE DESBLOQUEO
            }
        }
        cout<<"A continuación se despliegan los cambios y aspectos realizados: "<<endl;
        for(int a=0;a<con;a++)
        {
            nom = convertToString(enlista[con].nombre,ML);
            fecha = convertToString(enlista[con].fecha,ML);  // conversión a formato válido
            cout<<"Nombre: "<<nom<<"\nContraseña:**********\nTipo"<<(char *)&enlista[con].tipo<<"\nCuenta"<<(char *)&enlista[con].cuenta<<"\nFecha: "<<fecha<<endl;
        }
    }
    else
        cout<<"Ha ocurrido un problema con el archivo"<<endl;
    busqueda.close();
    return;
}