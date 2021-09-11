//---LIBRERÍAS:--------------------------------------------------------------------------------------------------------------------------
#include<iostream> //Libreria general, entradas y salidas
#include<locale.h>   //librería de configuración regional
#include<fstream>  // librería para el manejo de archivos y streams
#include<string.h>   // librería de manejo de cadenas
#include<string>  // librerías para más métodos de manejo de cadenas
#include<time.h>  //librería de manejo de tiempo y fechas
using namespace std;
//--ESTRUCUTURAS: ------------------------------------------------------------------------------------------------------------------------
const int ML = 30;
const int May = 5;
struct personal  // estructura de manejo de usuarios
{
    char nombre[ML]={' '};
    char contrasena[ML]={' '};
    char tipo = ' ';
    char cuenta = 'e';
    char fecha[ML]={' '};
};
struct productos  // estrucutura que almacena los productos
{
    char nombre[ML]={' '};
    char categoria={' '};
    int precio=0;
    int disponibilidad=0;
    int ventas=0;
    int codigo=0;
};
struct recibo
{
    char nombre[ML]={' '};
    int precio_ind=0;
    int cantidad_compra=0;
};
struct Factura
{
    char nombre[ML]={' '};
    recibo escogidos [May];
    int precio_total=0;
    int num_factu=0;
    bool estado_de_orden=false;
    bool estado_de_compra=false;
}Factu;

//--PROTOTIPOS DE FUNCIONES:---------------------------------------------------------------------------------------------------------------
void menu_general();  // función para desplegar el menú inicial
void menu_admin();   // función para desplegar el menú específico del administrador
void menu_client();  // función que muestra el menú del cliente
void menu_consul();  // fucnión que muestra las opciones para el consultor
void crear_producto(productos produc,string inventario);  // función para crear productos en inventario
void archivoproducto (string inventario, productos produc);  // función para...
string convertToString(char* arreglo, int size);  // función de manejo de cadenas, paso de vecotr char a string
productos buscar(string archivo, productos produc);  // buscar un producto en archivo de inventario
int buscarcodigo(productos produc,string inventario);  // buscar un producto en archivo mediante su código
void cambios_cuenta(string nombre,personal enlista[],char letra, long ubicaciones[],char cambio);  // función para el cambio de permisos de usuarios
void Realizar_una_compra(productos produc, string inventario, recibo compras[], string recibos, Factura Factu, long direccion, string necesario);
void Cancelar_una_compra(productos produc, string inventario, string recibos, Factura Factu, long direccion);
void Valor_total_de_compra(string recibos, Factura Factu);
void Cantidad_de_productos (string recibos, Factura Factu);
void Total_de_ventas(productos produc, string inventario);
void Producto_mas_vendido(recibo compras[]);
//--DESARROLLO DEL MAIN----------------------------------------------------------------------------------------------------------------------
int main()
{
    setlocale(LC_ALL,"");  //configuración de región
    int var,*avar,lec,*alec,con=0;  //punteros y variables de manejo de menu;
    char opt,letra,cambio;  //auxiliares y apoyos en el manejo del menu;
    bool encontrado,correcta,permitido,borrada,acambiar; // booleanos del programa
    recibo compras[ML];   // estrucutura para recibos
    personal nuevo,registro,enlista[ML]; //estructura de personal para nuevos usuarios
    time_t actual;    //variable de tipo tiempo
    struct tm * timeinfo;  //estructura de tiempo que abarca desde segundo a mes--> tm_(type)
    time(&actual);    //función para obtener el tiempo actual
    char date[ML]; //arreglo char para la fecha
    timeinfo = localtime(&actual);  //cambiar el formato a la zona configurada
    string nombre = "perfiles.txt"; //nombre del archivo de usario
    string inventario = "inventario.txt";  // nombre del archivo de los productos
    string recibos = "historial.txt";  //nombre de archivo para recibos y facturas
    string aux,*apaux,user,password,persona,seleccion, necesario; //cadenas para la lectura de teclado y asignaciones
    fstream usuarios,generar,abastecer;   // stream para el manejo de archivos
    //para imprimeir el tiempo usar el comando asctime(timeinfo);
    alec = &lec;  // variable y puntero del menu general
    avar = &var;  // variable y puntero de menus privados
    apaux = &aux; // auxiliar para nombres
    char buscado[ML]={' '};  // vector auxiliar para compatibilidad con registros
    long direccion,ubicaciones[ML];  // arreglo de direcciones para cambio
    productos produc;//variable para inicializar el listado del producto;
    do// Inicio     
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
                acambiar = false;
                usuarios.open(nombre,ios::in | ios::binary);  // apertura de archivo en modo binario
                con = 0;
                if(usuarios.is_open())
                {
                    encontrado= borrada = false;
                    while(!usuarios.eof())
                    {
                        //usuarios.read((char *)&registro,sizeof(registro));  //lectura del registro mediante estructura
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
                    else if(registro.cuenta == 'c')
                        acambiar = true;
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
                        } while (con<3); // si excede los tres intentos se sabra
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
                                                cout<<"¿Qué desea hacer?\n1)Crear producto\n2)Abastecer producto\nPara salir un numero diferente"<<endl;
                                                switch (lec)
                                                {
                                                case 1:
                                                    cout<<"Cargando formato de generación..."<<endl;
                                                    crear_producto(produc,inventario);
                                                    buscar(inventario,produc);
                                                    break;
                                                case 2:
                                                    cout<<"Cargando inventario..."<<endl;
                                                    abastecer.open(inventario,ios::binary | ios::in |ios::out);  // apertura del archivo en los tres modos
                                                    if(abastecer.is_open())
                                                    {
                                                        encontrado = false;
                                                        cout<<"Digite el producto a abastecer: ";
                                                        cin>> aux;
                                                        strcpy(date,aux.c_str());
                                                        convertToString(date,ML);  // cuadre para comparación válida
                                                        while(!abastecer.eof())
                                                        {
                                                            abastecer.read((char *)&produc,sizeof(produc));  //lectura de registro
                                                            seleccion = convertToString(produc.nombre,ML);  
                                                            if(aux == seleccion)
                                                            {
                                                                encontrado = true;
                                                                cout<<"Producto encontrado...\nDigite la cantidad a abastecer: ";
                                                                cin>> con; // lectura de cantidad
                                                                produc.disponibilidad += con;
                                                                cout<<"Cambio = "<<produc.disponibilidad<<endl;
                                                                //abastecer.seekp(abastecer.tellg() - (sizeof(produc.codigo)+sizeof(produc.ventas)+sizeof(produc.disponibilidad)));  // volver a posición de disponibilidad
                                                                abastecer.write((char *)&produc.disponibilidad,sizeof(produc.disponibilidad));  // efectuar escritura
                                                                break;
                                                            }
                                                        }
                                                        if(encontrado)
                                                            cout<<"Cambios realizadso correctamente..."<<endl;
                                                        else
                                                            cout<<"No se ha encontrado el producto...\n Volviendo al menú"<<endl;
                                                    }
                                                    else
                                                        cout<<"No se ha podido acceder al inventario..."<<endl;
                                                    break;
                                                default:
                                                    cout<<"Volviendo al menú del admin"<<endl;
                                                    break;
                                                }
                                                
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
                                                necesario=convertToString(registro.nombre,ML);
                                                cout<<" Hola querido "<<convertToString(registro.nombre,ML)<<endl;
                                                cout<< "A continuacion se le mostrara todos los productos en los que podra realizar su compra: "<<endl;
                                                Realizar_una_compra (produc, inventario, compras, recibos, Factu, direccion, necesario);         
                                                break;
                                            case 2:
                                                cout<<"Eligio la opción de cancelar compra..."<<endl;
                                                Cancelar_una_compra (produc, inventario, recibos,Factu,direccion);
                                                break;
                                            case 3:
                                                cout<<"Calculando el total de la compra..."<<endl;
                                                Valor_total_de_compra(recibos,Factu);
                                                break;
                                            case 4:
                                                cout<<"Mostrando la cantidad de productos comprados..."<<endl;
                                                Cantidad_de_productos (recibos,Factu);
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
                                                Total_de_ventas(produc, inventario);
                                                break;
                                            case 4:
                                                cout<<"Buscando el producto más vendido..."<<endl;
                                                Producto_mas_vendido(compras);
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
                        else if(acambiar) // else para cambio de rol de usuario
                        {
                            cout<<"El admin a pedido cambio de rol de su cuenta, seleccione un nuevo rol: "<<endl;
                            usuarios.open(nombre, ios::binary | ios::in | ios::out); 
                            if(usuarios.is_open())
                            {
                                encontrado = false;
                                while(!usuarios.eof())
                                {
                                    usuarios.read((char *)&registro,sizeof(registro));  //lectura del registro mediante estructura
                                    aux = convertToString(registro.nombre,ML);
                                    if(user == aux)  // buscar nuevamente la concidencia
                                    {
                                        encontrado=true;
                                        direccion = usuarios.tellg();  //asignar la dirección actual en registros
                                        cin>>letra; // cambio de letra para bloqueo de usuarios
                                        usuarios.seekp(direccion-(sizeof(registro.fecha)+sizeof(registro.cuenta)+sizeof(registro.cuenta)));   //mover puntero al aspecto para cuenta
                                        do
                                        {
                                            cin>>letra;
                                        } while (letra!='a' && letra!='c' && letra!='o');  // lectura de rol permitido
                                        registro.tipo = letra;
                                        usuarios.write((char *)&registro.tipo,sizeof(registro.tipo)); // reasignación de bloqueo
                                        break;
                                    }
                                }
                            }
                            else
                                cout<<"Ha ocurrido un problema con el cambio..."<<endl;
                            usuarios.close();
                        }
                        else  // else en caso de bloque de usuario
                        {
                            cout<<"Contraseña digitada incorrectamente 3 veces, se bloqueo el usuario..."<<endl;
                            user = convertToString(registro.nombre,ML);
                            usuarios.open(nombre,ios::binary | ios::out | ios::in);  // abrir archivo en los tres modos
                            if(usuarios.is_open())
                            {
                                encontrado = false;
                                while(!usuarios.eof())
                                {
                                    usuarios.read(registro.nombre,sizeof(registro.nombre));
                                    usuarios.read(registro.contrasena,sizeof(registro.contrasena));  //lectura de registros mediante estructuras
                                    usuarios.read((char *)&registro.tipo,sizeof(registro.tipo));
                                    usuarios.read((char *)&registro.cuenta,sizeof(registro.cuenta));
                                    usuarios.read(registro.fecha,sizeof(registro.fecha));
                                    strcpy(buscado,aux.c_str());  // conversión de apoyo
                                    aux = convertToString(buscado,ML);  // paso a string para mejor comparación
                                    if(user==aux)  // buscar nuevamente la concidencia
                                    {
                                        encontrado=true;
                                        direccion = usuarios.tellg();  //asignar la dirección actual en registros
                                        letra = 'b'; // cambio de letra para bloqueo de usuarios
                                        usuarios.seekp(direccion-(sizeof(registro.fecha)+sizeof(registro.cuenta)));   //mover puntero al aspecto para cuenta
                                        registro.cuenta = letra; 
                                        usuarios.write((char *)&registro.cuenta,sizeof(registro.cuenta)); // reasignación de bloqueo
                                        break;
                                    }
                                }
                            }
                            else
                                cout<<"Ha ocurrido un problema la bloquear al usuario"<<endl;
                            cout<<"Su usuario ha sido bloqueado, contacte al admin en caso de requerir desbloque"<<endl;
                            usuarios.close();
                        }
                    }
                    else
                    {
                        if(registro.cuenta == 'b')  // en caso de cuenta bloqueada
                            cout<<"Su cuenta se encuentra aun bloqueada, contacte al admin para el desbloque"<<endl;
                        else if(registro.cuenta== 'e') // en caso de cuenta en espera
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
                generar.open(nombre,ios::out | ios::binary | ios::app);
                if(generar.is_open())
                {
                    timeinfo = localtime( &actual); //cambio de formato de tiempo
                    strcpy(date,ctime(&actual)); //cambio a char para ser copiado en date
                    date[10]= date[13] = '_';
                    date[3]=date[7]=date[16]=date[19]='-';  // corrección de formato de fecha
                    cout<<"Digite su nuevo nombre usuario: ";
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
                    //generar.write((char *)&nuevo,sizeof(nuevo)); //escritura de datos en archivo mediante estructura
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
    cout<<"Vuelva pronto : "<<endl;
    return 0;   
}
//--DEFINICIÓN DE FUNCIONES--------------------------------------------------------------------------------------------------------------------
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
void crear_producto(productos produc,string inventario)
{
    int autoincremental=0;
    char respuesta2;
    fstream tem;
    char apoyo [ML]={' '};
    string auxiliar, seleccion;
    do
    {
        tem.open(inventario.c_str(), ios::binary | ios::in);
            if(tem.is_open())
            {
                tem.read((char *)&produc,sizeof(produc));
                cout<< "Digite el nombre a ingresar nuevo: "<<endl;
                getline(cin>>ws,auxiliar);
                cout<< "Se verificara que el producto no exista"<<endl;
                strcpy(apoyo, auxiliar.c_str());
                auxiliar=convertToString(apoyo,ML);
                while (!tem.eof())
                {
                    seleccion=convertToString(produc.nombre,ML);
                    if(auxiliar!=seleccion)
                    {
                        tem.seekg(0,ios::end);
                        strcpy(produc.nombre,auxiliar.c_str());
                        cout<<"Ingrese la categoria del producto: "<<endl;
                        cin>>produc.categoria;
                        cout<<"Ingrese el precio: "<<endl;
                        cin>>produc.precio;
                        cout<<"Ingrese la disponibilidad del producto: "<<endl;
                        cin>>produc.disponibilidad;
                        autoincremental=buscarcodigo(produc,inventario);
                        cout<<"El codigo del producto es: ";
                        produc.codigo=autoincremental+1;
                        cout<<produc.codigo<<endl;
                        archivoproducto(inventario,produc);
                    }
                    else
                        cout<< " Por favor este producto ya existe "<<endl;
                }
            }
            cout<<" Te gustaria añadir otro producto (s/n) "<<endl;
            cin>>respuesta2;
            while (respuesta2!='s' && respuesta2!='n')
            {
                    cout<<" Por favor digite una respuesta correcta, s (si) ó n (no) "<<endl;
                    cin>>respuesta2;
            }
    }while (respuesta2=='s');
    
    tem.close();
    return;
}
void archivoproducto(string inventario, productos produc)
{
    fstream tem;
    tem.open(inventario.c_str(), ios::binary | ios::app);
    if(!tem.eof())
        tem.write((char *) &produc,sizeof(produc));
    else
        cout<<"Error en la apertura de archivo"<<endl;
    tem.close();
    return;
}
productos buscar (string archivo, productos produc)
{
   productos ejemplo;  //borrar para después
    int i=0;
    string nombre="";
    fstream tem;
    tem.open(archivo,ios::binary | ios::in);
    while(!tem.eof())
    {
        tem.seekg((i)*sizeof(produc));
        tem.read((char *) &produc,sizeof(produc));
        if(tem.good())
        {
            cout<<" la posicion en el archivo es: "<<i+1<<endl;
            nombre=convertToString(produc.nombre,ML);
            cout<<"Nombre "<< nombre<<"\nCategoria: "<< produc.categoria <<"\nPrecio "<<produc.precio <<"\nDisponibilidad "<<produc.disponibilidad<<endl;
            cout<<"\nCodigo "<<produc.codigo<<" "<<endl;
        }
        i=i+1;
    }
    tem.close();
    return ejemplo;
}
int buscarcodigo(productos produc,string inventario)
{
    int tamyo, autoincremental;
    fstream tem;
    tem.open(inventario,ios::binary | ios::in);
    tamyo=sizeof(produc);
    tem.seekg(-tamyo,ios::end);
    tem.read((char *) &produc,sizeof(produc));
    autoincremental=produc.codigo;
    tem.close();
    return autoincremental;
}
string convertToString(char* arreglo, int size) //conversión de string a caracter mediante concatenación
{
    string s = "";
    for (int i = 0; i < size; i++)
        s = s + arreglo[i];  // concatenación de char o letras a un string
    return s;
}
void cambios_cuenta(string nombre,personal enlista[],char letra, long ubicaciones[],char cambio)
{
    int elec,con = 0;
    string nom,fecha,hallar;
    bool hallado; // booleano para verificar el usuario
    long dir;
    char conversor[ML]={' '};  // conversor de char de apoyo
    personal temporal;
    fstream busqueda;  // stream para el manejo de archivo
    //Primera apertura para búsqueda de usuarios con la condiicion "letra":
    busqueda.open(nombre, ios::binary | ios::in | ios::out);  // abrir el archivo en los tres modos
    if(busqueda.is_open()) //verificación de apertura de archivo
    {
        con = 0;
        while(!busqueda.eof())  // mientras el archivo no termine
        {
            busqueda.read(enlista[con].nombre,sizeof(enlista[con].nombre));
            busqueda.read(enlista[con].contrasena,sizeof(enlista[con].contrasena));  //lectura de registros mediante estructuras
            busqueda.read((char *)&enlista[con].tipo,sizeof(enlista[con].tipo));
            busqueda.read((char *)&enlista[con].cuenta,sizeof(enlista[con].cuenta));
            busqueda.read(enlista[con].fecha,sizeof(enlista[con].fecha));
            ubicaciones[con] = busqueda.tellg(); // guardado de posición para cambio
            if(enlista[con].cuenta==letra)  // si hay coincidencia de permiso, se va a la siguiente posición
            {
                cout<<endl<<"Nombre: "<<enlista[con].nombre<<endl;
                cout<<"Contraseña: *******"<<endl; //No se despliega la contraseña puesto que es privada
                cout<<"Tipo: "<<enlista[con].tipo<<endl;
                cout<<"Cuenta: "<<enlista[con].cuenta<<endl;
                cout<<"Creación: "<<enlista[con].fecha<<endl;
                cout<<endl;
                con++;  // contador de coincidencias
            }
        }
    }
    else
        cout<<"Ha ocurrido un problema con el archivo"<<endl;
    busqueda.close();
    cout<<"Lectura completada..."<<endl;
    //Segunda o n apertura del archivo para el cambio de permiso mediante el nombre 
    if(con>0)
    {
        do
        {
            busqueda.open(nombre,ios::binary | ios::out | ios::in);
            if(busqueda.is_open())
            {
                cout<<"Digite un caso:\n1)Aceptar por nombre\n2)Pedir cambio por nombre\n3)Ignorar todo\n4)Salir"<<endl;
                cin>>elec;
                if(elec == 1 || elec == 2) // opcion de modificación
                {
                    cout<<"Digite el nombre a buscar: ";
                    cin>> hallar;  // nombre a buscar
                    hallado = false;
                    strcpy(conversor,hallar.c_str());
                    hallar = convertToString(conversor,ML);  // conversión a un arreglo de tamaño equivalente a la propiedad nombre de la estructura
                    while (!busqueda.eof())  // mientras el archivo no termine
                    {
                        busqueda.read(temporal.nombre,sizeof(temporal.nombre));
                        busqueda.read(temporal.contrasena,sizeof(temporal.contrasena));  //lectura de registros mediante estructuras
                        busqueda.read((char *)&temporal.tipo,sizeof(temporal.tipo));
                        busqueda.read((char *)&temporal.cuenta,sizeof(temporal.cuenta));
                        busqueda.read(temporal.fecha,sizeof(temporal.fecha));
                        nom = convertToString(temporal.nombre,ML); // conversión de nombre a string
                        if(nom==hallar)  // comparación y validación para cambio
                        {
                            cout<<"Encontrado"<<endl;
                            hallado = true;
                            dir = busqueda.tellg(); // guardado de posición para cambio
                            busqueda.seekp(dir-(sizeof(temporal.fecha)+sizeof(temporal.cuenta)));  // ir a la posición para modificar el caracter de cuenta
                            if(elec == 1)
                            {
                                temporal.cuenta = cambio;  // cambio dependendiendo de la ocasión ya sea desbloqueo o activación
                                cout<<"Se ha valido el usuario: "<<nom<<endl;
                            }
                            else
                            {
                                temporal.cuenta = 'c';  // petición de cambio de tipo
                                cout<<"Se ha pedido un cambio al usuario: "<<nom<<endl;
                            }
                            busqueda.write((char *)&temporal.cuenta,sizeof(temporal.cuenta));  // actualización del permiso
                        }
                    }
                }
                else if (elec==3)
                    cout<<"Se han ignorado todos los usuarios, se preguntará por ellos despues, saliendo..."<<endl;
                else if(elec== 4)
                    cout<<"Saliendo con los cambios realizados..."<<endl;
                else
                    cout<<"Volviendo a desplegar el menu..."<<endl;
            }
            else
                cout<<"Ha ocurrido un problmea con las asignación..."<<endl; // mensaje de error en caso de apertura del archivo
            busqueda.close();
        } while (elec!=3 && elec!=4);  // hacer mientras no se indique lo contrario
    }
    else
        cout<<"No hay usuarios que cumplan la condición en la lista de espera..."<<endl;
    return;
}
void Realizar_una_compra (productos produc, string inventario, recibo compras[], string recibos, Factura Factu, long direccion, string necesario)
{
    long ayuda, actual;
    char respuesta, respuesta2;
    bool encontrado=false;
    string auxiliar;
    char apoyo [ML]={' '};
    int contaux=0, aux=0,confirmar=0, cambiar=0,total, comprobado=0;
    ofstream guardar;
    productos temporal;
    ifstream Leer;
    fstream busca;
    Leer.open(inventario.c_str(), ios::binary | ios::app);
        cout<< "Digite porfavor el nombre de su usuario para cargar su factura en su cuenta: "<<endl;
        cin>> auxiliar;
        cout<< "Primero se verificara que el usuario exista"<<endl;
        strcpy(apoyo, auxiliar.c_str());
        auxiliar=convertToString(apoyo,ML);
        if(necesario==auxiliar)  // comparación y validación para cambio
        {
            //cout<<"Encontrado"<<endl;
            cout<< "se encontro su usurario"<<endl;
                if(Leer.is_open())
                {
                    Leer.read((char *)&produc,sizeof(produc));
                        cout<< "Mira los respectivos productos: "<<endl;
                        while(!Leer.eof())//Revisamos el archivo hasta el final
                        {
                            do{
                                cout <<"(Maximo 5 productos)"<<endl;
                                aux=0;
                                cout<<"----------------------------"<<endl;
                                cout<<"Producto:               "<<produc.nombre <<endl;
                                cout<<"Categoria:              "<<produc.categoria<<endl;
                                cout<<"Precio:                 "<<produc.precio <<endl;
                                cout<<"Disponibilidad:         "<<produc.disponibilidad <<endl;
                                cout<<"Codigo del producto:    "<<produc.codigo <<endl;
                                cout<<"----------------------------"<<endl;
                                cout<<endl;
                                cout<<"Desea comprar este producto (s/n)"<<endl;
                                cin>>respuesta;
                                while (respuesta!='s' && respuesta!='n')
                                {
                                    cout<<" Por favor digite una respuesta correcta, s (si) ó n (no) "<<endl;
                                    cin>>respuesta;
                                }
                                if(respuesta=='s')
                                {                        
                                        confirmar=produc.codigo;
                                        if (contaux<5)
                                        {
                                            guardar.open(recibos, ios :: binary);
                                            /*if(guardar.fail())
                                            {
                                                cout<< "No se puede abrir el archivo"<<endl;
                                            }*/
                                            cout<< "Porfavor ingrese el numero de productos que desea obtener: "<<endl;
                                            cin>> aux;
                                            while (aux>produc.disponibilidad || aux<1)
                                            {
                                                cout<<" Esto no es posible debido a que no se puede o no hay tantos de este producto "<<endl;
                                                cout<<" Porfavor vuelva a ingrese el numero de productos que desea: "<<endl;
                                                cin>> aux;
                                            }
                                            strcpy(Factu.escogidos[contaux].nombre,produc.nombre);
                                            cambiar=produc.disponibilidad-aux;
                                            produc.disponibilidad=cambiar;
                                            Factu.escogidos[contaux].precio_ind=produc.precio;
                                            Factu.escogidos[contaux].cantidad_compra+=aux;
                                            total=aux*produc.precio;
                                            total+=total;
                                            busca.open(inventario, ios::binary | ios::out | ios::in );  // abrir el archivo en los tres modos
                                            if(busca.is_open()) //verificación de apertura de archivo
                                            {
                                                encontrado=false;
                                                while(!busca.eof())  // mientras el archivo no termine
                                                {
                                                    busca.read((char *)&produc,sizeof(produc));  // lectura comprimida mediante la estructura en lista
                                                    direccion = busca.tellg(); // guardado de posición para cambio
                                                    if(produc.codigo==confirmar)  // si hay coincidencia de permiso, se va a la siguiente posición
                                                    {
                                                        cout<<"Encontrado"<<endl;
                                                        encontrado=true;
                                                        ayuda=busca.tellg();
                                                        busca.seekp(ayuda-(sizeof(temporal.disponibilidad)-(sizeof(temporal.ventas)-(sizeof(temporal.codigo)))));
                                                        temporal.disponibilidad=cambiar;
                                                    }
                                                    busca.write((char *)&temporal.disponibilidad,sizeof(temporal.disponibilidad));
                                                }
                                            }
                                            else
                                            cout<<"Ha ocurrido un problema con el archivo"<<endl;
                                            busca.close();
                                            busca.open(inventario, ios::binary | ios::out | ios::in );  // abrir el archivo en los tres modos
                                                if(busca.is_open()) //verificación de apertura de archivo
                                                {
                                                    encontrado=false;
                                                    while(!busca.eof())  // mientras el archivo no termine
                                                    {
                                                        busca.read((char *)&produc,sizeof(produc));  // lectura comprimida mediante la estructura en lista
                                                        direccion = busca.tellg(); // guardado de posición para cambio
                                                        if(produc.codigo==confirmar)  // si hay coincidencia de permiso, se va a la siguiente posición
                                                        {
                                                            cout<<"Encontrado"<<endl;
                                                            encontrado=true;
                                                            ayuda=busca.tellg();
                                                            busca.seekp(ayuda-(sizeof(temporal.ventas)-(sizeof(temporal.codigo))));
                                                            temporal.ventas=temporal.ventas+1;
                                                        }
                                                    }
                                                    busca.write((char *)&temporal.disponibilidad,sizeof(temporal.disponibilidad));
                                                }
                                                else
                                                    cout<<"Ha ocurrido un problema con el archivo"<<endl;
                                                busca.close();
                                                contaux++;
                                        }
                                        cout<< "Te gustaria comprar otro articulo (s/n)"<<endl;
                                        cin>>respuesta2;
                                        while (respuesta2!='s' && respuesta2!='n')
                                        {
                                            cout<<" Por favor digite una respuesta correcta, s (si) ó n (no) "<<endl;
                                            cin>>respuesta2;
                                        }
                                        
                                        if(contaux>=5)
                                        {
                                            cout <<" Ya alcanzo los 5 productos "<<endl;
                                            break;
                                        }
                                }
                                Leer.read((char *)&produc,sizeof(produc));
                            }while(respuesta2=='s'||contaux<=5);
                        }
                        Factu.precio_total = total;
                        Factu.estado_de_orden=true;
                        Factu.num_factu=+1;
                        strcpy(Factu.nombre,auxiliar.c_str());
                        guardar.write((char *)&Factu,sizeof(Factu));
                }
                guardar.close();
        }
        else
            cout<< "No se encontro su nombre, porfavor verifique he intente mas tarde "<<endl;
    Leer.close();
    return;
}
void Cancelar_una_compra (productos produc, string inventario, string recibos, Factura Factu, long direccion)
{
    long ayuda;
    bool change=false;
    bool encontrado;
    char apoyo [ML]={' '};
    string auxiliar, seleccion;
    productos temporal;
    ifstream Leer;
    fstream busca, busca1;
    Factura temporal1;
    int confirmar, con;
    char respues, respuesta2;
    Leer.open(recibos.c_str(), ios::binary | ios::in);
    if(Leer.is_open())
        {
            Leer.read((char *)&Factu,sizeof(Factu));
            cout<< "Digite porfavor el nombre de su usuario para cargar su factura en su cuenta: "<<endl;
            cin>> auxiliar;
            cout<< "Primero se verificara que el usuario exista"<<endl;
            strcpy(apoyo, auxiliar.c_str());
            auxiliar=convertToString(apoyo,ML);
                while(!Leer.eof())//Revisamos el archivo hasta el final
                {
                    seleccion=convertToString(Factu.nombre,ML);
                    if(seleccion==auxiliar)
                    {
                        do
                        {                      
                            cout<< "Mira los respectivos productos comprados: "<<endl;
                            for(int i=0;i<5;i++){
                            cout<<"----------------------------"<<endl;
                            cout<<"Producto:        "<<i+1<<"  "<<Factu.escogidos[i].nombre <<endl;
                            cout<<"Precio:                 "<<Factu.escogidos[i].precio_ind<<endl;
                            cout<<"Cantidad de producto:   "<<Factu.escogidos[i].cantidad_compra <<endl;
                            cout<<"----------------------------"<<endl;
                            cout<<endl;
                            }
                            cout<< "El precio total es de: "<<Factu.precio_total;
                            cout<< "El numero de factura es de: "<<Factu.num_factu;
                            cout<< "Desea cancelar esta factura (s/n)"<<endl;
                            cin>>respues;
                            do
                            {
                                cout<<" Por favor digite una respuesta correcta, s (si) ó n (no) "<<endl;
                                cin>>respues;
                            }while (respues!='s' && respues!='n');
                            if(respues== 's')
                            {
                                busca.open(recibos,ios::binary | ios::out | ios::in);
                                if(busca.is_open()) //verificación de apertura de archivo
                                    {              
                                        busca.read((char *)&Factu,sizeof(Factu));  // lectura comprimida mediante la estructura en lista
                                        direccion = busca.tellg(); // guardado de posición para cambio
                                        ayuda=busca.tellg();
                                        busca.seekp(ayuda-(sizeof(temporal1.estado_de_compra)));
                                        temporal1.estado_de_compra=change;
                                        busca.write((char *)&temporal1.estado_de_compra,sizeof(temporal1.estado_de_compra));
                                        busca1.open(inventario, ios::binary | ios::out | ios::in );
                                          // abrir el archivo en los tres modos
                                        if(busca1.is_open()) //verificación de apertura de archivo
                                        {
                                            encontrado=false;
                                            while(!busca1.eof())  // mientras el archivo no termine
                                            {
                                                busca1.read((char *)&produc,sizeof(produc));  // lectura comprimida mediante la estructura en lista
                                                direccion = busca.tellg(); // guardado de posición para cambio
                                                if(produc.codigo==confirmar)  // si hay coincidencia de permiso, se va a la siguiente posición
                                                {
                                                    cout<<"Encontrado"<<endl;
                                                    encontrado=true;
                                                    ayuda=busca.tellg();
                                                    busca.seekp(ayuda-(sizeof(temporal.ventas)-(sizeof(temporal.codigo))));
                                                    temporal.ventas=temporal.ventas-1;
                                                }
                                                busca1.write((char *)&temporal.disponibilidad,sizeof(temporal.disponibilidad));
                                            }
                                        }
                                        else
                                        cout<<"Ha ocurrido un problema con el archivo"<<endl;
                                        busca1.close();
                                    }
                                    else
                                        cout<<"Ha ocurrido un problema con el archivo"<<endl;
                                        busca.close();
                            }
                            cout<< "Te gustaria comprar otro articulo (s/n)"<<endl;
                            cin>>respuesta2;
                            while (respuesta2!='s' && respuesta2!='n')
                                {
                                    cout<<" Por favor digite una respuesta correcta, s (si) ó n (no) "<<endl;
                                    cin>>respuesta2;
                                }
                        }while(respuesta2=='s');
                        
                    }
                    
                }
        }
        Leer.close();
        
  return;
}
void Valor_total_de_compra(string recibos, Factura Factu)
{
    ifstream Leer;
    bool aux;
    char apoyo [ML]={' '};
    string auxiliar, seleccion;
    Leer.open(recibos.c_str(), ios::binary | ios::in);

    if(Leer.is_open())
    {
        Leer.read((char *)&Factu,sizeof(Factu));
        cout<< "Digite porfavor el nombre de su usuario para cargar su factura en su cuenta: "<<endl;
        cin>> auxiliar;
        cout<< "Primero se verificara que el usuario tenga alguna compra"<<endl;
        strcpy(apoyo, auxiliar.c_str());
        auxiliar=convertToString(apoyo,ML);
        while(!Leer.eof())//Revisamos el archivo hasta el final
        {
            seleccion=convertToString(Factu.nombre,ML);
            aux=Factu.estado_de_orden;
            if (seleccion==auxiliar&& aux==true)
            {
                cout<< "Mira el total de la compra con sus respectivos productos seleccionados: "<<endl;
                for(int i=0;i<5;i++){
                cout<<"----------------------------"<<endl;
                cout<<"Producto:        "<<i<<"  "<<Factu.escogidos[i].nombre <<endl;
                cout<<"Precio:                 "<<Factu.escogidos[i].precio_ind<<endl;
                cout<<"Cantidad de producto:   "<<Factu.escogidos[i].cantidad_compra <<endl;
                cout<<"----------------------------"<<endl;
                cout<<endl;
                }
                cout<< "El precio total es de: "<<Factu.precio_total;
                cout<< "El numero de factura es de: "<<Factu.num_factu;
            }
            else
            {
            cout<< "Si no se mostrado ninguna factura es porque: "<<endl;
            cout<< "No hay ninguna factura a su nombre hasta el momento o estan canceladas sus facturas "<<endl;
            }
        }
    }
    Leer.close();
 return;
}
void Cantidad_de_productos (string recibos, Factura Factu)
{
    ifstream Leer;
    int cont=0;
    char apoyo [ML]={' '};
    bool aux;
    string auxiliar, seleccion;//Auxiliar
    Leer.open(recibos.c_str(), ios::binary | ios::in);
    if(Leer.is_open())
    {
        Leer.read((char *)&Factu,sizeof(Factu));
        cout<< "Digite porfavor el nombre de su usuario para cargar su factura en su cuenta: "<<endl;
        cin>> auxiliar;
        cout<< "Primero se verificara que el usuario tenga alguna compra"<<endl;
        strcpy(apoyo, auxiliar.c_str());
        auxiliar=convertToString(apoyo,ML);
        while(!Leer.eof())//Revisamos el archivo hasta el final
        {
            seleccion=convertToString(Factu.nombre,ML);
            aux=Factu.estado_de_orden;
            if(seleccion==auxiliar&& aux==true)
            {
                cout<< "Mira tus productos que estan en facturas validas y a tu nombre: "<<endl;
                for(int i=0;i<5;i++)
                {
                cout<<"----------------------------"<<endl;
                cout<<"Producto:        "<<i<<"  "<<Factu.escogidos[i].nombre <<endl;
                cout<<"Precio:                  "<<Factu.escogidos[i].precio_ind<<endl;
                cout<<"Cantidad de producto:    "<<Factu.escogidos[i].cantidad_compra <<endl;
                cout<<"----------------------------"<<endl;
                cout<<endl;
                }
            }
        }
    }
    Leer.close();
    return;
}
void Total_de_ventas(productos produc, string inventario)
{
    ifstream Leer;
    Leer.open(inventario.c_str(), ios::binary | ios::app);
    if(Leer.is_open())
                {
                    Leer.read((char *)&produc,sizeof(produc));
                    cout<< "Mira los respectivos productos: "<<endl;
                    cout <<"(Maximo 5 productos)"<<endl;
                    while(!Leer.eof())//Revisamos el archivo hasta el final
                    {
                        cout<<"----------------------------"<<endl;
                        cout<<"     El total de ventas     "<<endl;
                        cout<<"----------------------------"<<endl;
                        cout<<"   Es de:           "<<produc.ventas;
                        cout<<" Aqui estan unicamente las ";
                        cout<<"ventas vigentes a pagar     "<<endl;
                        cout<<"----------------------------"<<endl;
                        cout<<endl;
                    }
                }
                Leer.close();
    return;
}
void Producto_mas_vendido(recibo compras[])//Arreglar
{
    int contador[100]= {0};
    int mayor=0, aux=0;
    for(int i=0;i<ML;i++)
    {
            if(compras[i].cantidad_compra>=0)
            {
                mayor=compras[i].cantidad_compra;
            }
            aux=compras[i].cantidad_compra;
            if(mayor<aux)
                {
                    mayor=aux;
                }
    }
    cout<<" El producto con mayor ventas " <<mayor<<endl;
    return;
}
productos ordenaralf (string archivo, productos produc)
{
    productos ejemplo;  //borrar para después
    int i=0, n=0, p=0, num;
    string nombre="";
    fstream tem;

    tem.open(archivo,ios::binary | ios::in);
    while(!tem.eof())
    {
        tem.seekg((i)*sizeof(produc));
        tem.read((char *) &produc,sizeof(produc));
        if(tem.good())
        {

        }
        i=i+1;
    }
    num=i-1;
    cout<<num;
    tem.close();

    tem.open(archivo,ios::binary | ios::in);
    productos tempo[num], tep, terr;
    int codigo[num];
    while(!tem.eof())
    {
        tem.seekg((n)*sizeof(produc));
        tem.read((char *) &produc,sizeof(produc));
        if(tem.good())
        {

        tempo[n]=produc;
        codigo[n]=produc.codigo;
        tempo[n].codigo=codigo[n];
        }
        n=n+1;
    }
    tem.close();


    for (int j=0; j<num;j++){
        for (int k=j+1;k<num;k++){

            // strcoll() devuelve -1 si el 1º parametro es mayor que el 2º, 0 si el 1º es igual al 2º, o
            //1 si el 1º mayor que el 2º. Lo hace caracter a caracter hasta encontrar una diferencia o un nulo que es cuando retorna uno de los valores mensionados.
            /*if ( ( strcoll(/1º/ tempo[j].nombre, /2º/tempo[k].nombre))>0) 
            {
                //esto va subiendo los nombres a la cabeza de la lista
                strcpy ( tep.nombre, tempo[j].nombre );
                strcpy ( tempo[j].nombre, tempo[k].nombre );
                strcpy ( tempo[k].nombre, tep.nombre );
            }*/
        }
    }
    cout << "los productor ordenados son: "<<endl;
    for ( int m=0; m<num;m++){

        cout<<"nombre "<< tempo[m].nombre<<" categoria: "<< tempo[m].categoria <<" precio "<<tempo[m].precio <<" disponibilidad "<<tempo[m].disponibilidad<<endl;
        cout<<" codigo "<<tempo[m].codigo<<" "<<endl;
    }


    tem.close();
    return ejemplo;
}
productos ordenar_precio_M_m (string archivo, productos produc)
{
    productos ejemplo;  //borrar para después
    int i=0, n=0, p=0, num;
    string nombre="";
    fstream tem;
    tem.open(archivo,ios::binary | ios::in);
    while(!tem.eof())
    {
        tem.seekg((i)*sizeof(produc));
        tem.read((char *) &produc,sizeof(produc));
        if(tem.good())
        {
            //¿QUE FALTA...?
        }
        i=i+1;
    }
    num=i-1;
    cout<<num;
    tem.close();
    tem.open(archivo,ios::binary | ios::in);
    productos tempo[num], tep, terr;
    int codigo[num];
    while(!tem.eof())
    {
        tem.seekg((n)*sizeof(produc));
        tem.read((char *) &produc,sizeof(produc));
        if(tem.good())
        {
            tempo[n]=produc;
            codigo[n]=produc.codigo;
            tempo[n].codigo=codigo[n];
        }
        n=n+1;
    }
    tem.close();
    int aux;
    for(int j=0; j<num-1; j++)
    {
        for(int k=0; k<num-j-1; k++)
        {
            if(tempo[k].precio>tempo[k+1].precio)
            {
                aux = tempo[k].precio;
                tempo[k].precio=tempo[k+1].precio;
                tempo[k+1].precio= aux;
            }
        }
    }
    cout << "los productor ordenados son: "<<endl;
    for ( int m=0; m<num;m++){

        cout<<"nombre "<< tempo[m].nombre<<" categoria: "<< tempo[m].categoria <<" precio "<<tempo[m].precio <<" disponibilidad "<<tempo[m].disponibilidad<<endl;
        cout<<" codigo "<<tempo[m].codigo<<" "<<endl;
    }
    tem.close();
    return ejemplo;
}
productos ordenar_precio_m_M (string archivo, productos produc)
{
    productos ejemplo;  //borrar para después
    int i=0, n=0, p=0, num;
    string nombre="";
    fstream tem;
    tem.open(archivo,ios::binary | ios::in);
    while(!tem.eof())
    {
        tem.seekg((i)*sizeof(produc));
        tem.read((char *) &produc,sizeof(produc));
        if(tem.good())
        {
            //¿QUÉ FALTA AQUÍ?
        }
        i=i+1;
    }
    num=i-1;
    cout<<num;
    tem.close();

    tem.open(archivo,ios::binary | ios::in);
    productos tempo[num], tep, terr;
    int codigo[num];
    while(!tem.eof())
    {
        tem.seekg((n)*sizeof(produc));
        tem.read((char *) &produc,sizeof(produc));
        if(tem.good())
        {
        tempo[n]=produc;
        codigo[n]=produc.codigo;
        tempo[n].codigo=codigo[n];
        }
        n=n+1;
    }
    tem.close();
    int aux;
    for(int j=0; j<num-1; j++)
    {
        for(int k=0; k<num-j-1; k++)
        {
            if(tempo[k].precio<tempo[k+1].precio)
            {
                aux = tempo[k].precio;
                tempo[k].precio=tempo[k+1].precio;
                tempo[k+1].precio= aux;
            }

        }
    }

    cout << "los productor ordenados son: "<<endl;
    for ( int m=0; m<num;m++){

        cout<<"nombre "<< tempo[m].nombre<<" categoria: "<< tempo[m].categoria <<" precio "<<tempo[m].precio <<" disponibilidad "<<tempo[m].disponibilidad<<endl;
        cout<<" codigo "<<tempo[m].codigo<<" "<<endl;
    }
    tem.close();
    return ejemplo;
}
/*void menu_categorias();
{
    cout<<"Ingrese la categoria del producto: "<<endl;
    cin>>tempo;

    if(tempo=='L' || tempo=='A' || tempo=='F' || tempo=='D' || tempo=='C' || tempo=='P' || tempo=='B' || tempo=='H' || tempo=='S' || tempo=='W' || tempo=='T')
    {
        veri=true;
        produc.categoria=tempo;
    }
    else
    {
        veri=false;
        cout<<"categoria no encontrada, vuelva a escribirla: "<<endl;
    }
    }while(veri==false);
    cout<<"Ingrese el precio: "<<endl;
    cin>>produc.precio;
    cout<<"Ingrese la disponibilidad del producto: "<<endl;
    cin>>produc.disponibilidad;
    autoincremental=buscarcodigo(produc,inventario);
    cout<<"El codigo del producto es: ";
    produc.codigo=autoincremental+1;
    cout<<produc.codigo<<endl;
    archivoproducto(inventario,produc);

    tem.close();
}*/