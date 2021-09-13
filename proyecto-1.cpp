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
void menu_categorias();   //funcion muestra opciones de categorias en la listas de productos
void crear_producto(productos produc,string inventario);  // función para crear productos en inventario
void archivoproducto (string inventario, productos produc);  // función para...
string convertToString(char* arreglo, int size);  // función de manejo de cadenas, paso de vecotr char a string
productos buscar(string archivo, productos produc);  // imprimir un producto en archivo de inventario
productos ordenaralf (string archivo, productos produc); //funcion para ordenar la listas de producto por orden alfabetico
productos ordenar_precio_M_m (string archivo, productos produc);//funcion para ordenar precios de mayor a menor por precio
productos ordenar_precio_m_M (string archivo, productos produc);//funcion para ordenar precios de menor a mayor por precio
int buscarcodigo(productos produc,string inventario);  // buscar un producto en archivo mediante su código
void cambios_cuenta(string nombre,personal enlista[],char letra, long ubicaciones[],char cambio);  // función para el cambio de permisos de usuarios
void Realizar_una_compra(productos produc, string inventario, recibo compras[], string recibos, Factura Factu, long direccion, string necesario);
void Cancelar_una_compra(productos produc, string inventario, string recibos, Factura Factu, long direccion);  // función para cancelar una factura
void Valor_total_de_compra(string recibos, Factura Factu);  // función para el calculo de total a pagar por un cliente
void Cantidad_de_productos (string recibos, Factura Factu); //función para el mostrado y cantidad de productos
void Total_de_ventas(productos produc, string inventario);  //calcula el total de ventas de productos
void Producto_mas_vendido(string recibos, Factura Factu, recibo compras[]);  //función que itera opr las facturas para ver el producto más vendido
void lista_clientes(string archivo,int orden);  //retorna una lista de los clientes activos
void bloqueo(personal registro,string nombre,string aux);  //función para bloquear a un usuario que digita incorrectamente su contraseña
void cambio_factura(string factura);  //función para la validación y el despacho de facturas por parte del admin
//--DESARROLLO DEL MAIN----------------------------------------------------------------------------------------------------------------------
int main()
{
    setlocale(LC_ALL,"");  //configuración de región
    int var,*avar,lec,*alec,con=0, orden;  //punteros y variables de manejo de menu;
    char opt,letra,cambio, comp;  //auxiliares y apoyos en el manejo del menu;
    bool encontrado,correcta,permitido,borrada,acambiar; // booleanos del programa
    recibo compras[ML];   // estrucutura para recibos
    personal nuevo,registro,enlista[ML]; //estructura de personal para nuevos usuarios
    time_t actual;    //variable de tipo tiempo
    struct tm * timeinfo;  //estructura de tiempo que abarca desde segundo a mes--> tm_(type)
    time(&actual);    //función para obtener el tiempo actual
    char date[ML],asignar[ML]={' '}; //arreglo char para la fecha
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
                                                cout<<"Mostrando las categorías ya creadas..."<<endl;
                                                menu_categorias();
                                                break;
                                            case 4:
                                                cout<<"Abriendo función de administrar productos..."<<endl;
                                                cout<<"¿Qué desea hacer?\n1)Crear producto\n2)Abastecer producto\nPara salir un numero diferente"<<endl;
                                                cin>> *alec;
                                                switch (lec)
                                                {
                                                    case 1:
                                                        cout<<"Cargando formato de generación..."<<endl;
                                                        do{
                                                            crear_producto(produc,inventario);
                                                            buscar(inventario,produc);
                                                            cout<<"desea ingresar otro producto (s/n)"<<endl;
                                                            cin>>comp;
                                                            while (comp!='s' && comp!='n')
                                                            {
                                                                cout<<" Por favor digite una respuesta correcta, s (si) ó n (no) "<<endl;
                                                                cin>>comp;
                                                            }                                                        
                                                        }while(comp=='s');
                                                        break;
                                                    case 2:
                                                        cout<<"Cargando inventario..."<<endl;
                                                        abastecer.open(inventario,ios::binary | ios::in |ios::out);  // apertura del archivo en los tres modos
                                                        if(abastecer.is_open())
                                                        {
                                                            abastecer.read((char *)&produc,sizeof(produc));
                                                            encontrado = false;
                                                            cout<<"Digite el producto a abastecer: ";
                                                            cin>> aux;
                                                            strcpy(asignar,aux.c_str());
                                                            cout<<"Comparaciones..."<<endl;
                                                            aux = convertToString(asignar,ML);  // cuadre para comparación válida
                                                            while(!abastecer.eof())
                                                            {
                                                                seleccion = convertToString(produc.nombre,ML);
                                                                cout<<seleccion<<"-"<<aux<<endl;  
                                                                if(aux == seleccion)
                                                                {
                                                                    encontrado = true;
                                                                    cout<<"Producto encontrado...\nDigite la cantidad a abastecer: ";
                                                                    cin>> con; // lectura de cantidad
                                                                    produc.disponibilidad += con;
                                                                    cout<<"Cambio = "<<produc.disponibilidad<<endl;
                                                                    abastecer.seekp(ios::cur - (sizeof(produc.codigo)+sizeof(produc.ventas)+sizeof(produc.disponibilidad)));  // volver a posición de disponibilidad
                                                                    abastecer.write((char *)&produc.disponibilidad,sizeof(produc.disponibilidad));  // efectuar escritura
                                                                    break;
                                                                }
                                                                abastecer.read((char *)&produc,sizeof(produc));
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
                                                cout<<"Accediendo a la validación..."<<endl;
                                                cambio_factura(recibos);
                                                cout<<"Guardando cambios..."<<endl;
                                                break;
                                            case 6:
                                                cout<<"Saliendo de la sesión..."<<endl;
                                                break;
                                            default: 
                                                cout<<"Volviendo a mostrar el menu"<<endl;
                                                break;
                                        }
                                        system("pause");
                                        system("cls");
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
                                                cout<<" Hola querid@ "<<convertToString(registro.nombre,ML)<<endl;
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
                                        }
                                        system("pause");
                                        system("cls");
                                        menu_client();
                                        cout<<"Digite su opción, querido cliente: "<<endl;
                                        cin>> *avar;
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
                                                do{
                                                cout<<" por favor ingrese el tipo de ordenamiento que desea hacer "<<endl;
                                                cout<<" 1) imprimir por orden del codigo "<<endl;
                                                cout<<" 2) ordenar por orden alfabetico  "<<endl;
                                                cout<<" 3) ordenar por precio de mayor a menor "<<endl;
                                                cout<<" 4) ordenar por precio de menor a mayor "<<endl;
                                                cout<<" 5)salir "<<endl;
                                                cin>>orden;
                                                if(orden=1){
                                                    buscar(inventario,produc);
                                                }
                                                if(orden=2){
                                                    ordenaralf (inventario,produc);
                                                }
                                                if(orden=3){
                                                    ordenar_precio_M_m(inventario,produc);
                                                }
                                                if(orden=4){
                                                    ordenar_precio_m_M(inventario,produc);
                                                }
                                                if(orden=5){
                                                    cout<<"bye bb"<<endl;
                                                }
                                                }while(orden!=5);
                                                break;
                                            case 2:
                                                cout<<"Cargando regristros de los clientes existentes..."<<endl;
                                                cout<<"Si desea digitarlos del más antiguo al más nuevo, digite 1, sino digite 2"<<endl;
                                                cin>>*alec;
                                                if(*alec==1)
                                                    lista_clientes(nombre,1);
                                                else if(*alec==2)
                                                    lista_clientes(nombre,2);
                                                else
                                                    cout<<"El ordenamiento tiene un error... Volviendo al menu"<<endl;
                                                break;
                                            case 3:
                                                cout<<"Calculando el total de ventas del programa..."<<endl;
                                                Total_de_ventas(produc, inventario);
                                                break;
                                            case 4:
                                                cout<<"Buscando el producto más vendido..."<<endl;
                                                Producto_mas_vendido(recibos, Factu, compras);
                                                break;
                                            case 5:
                                                cout<<"Saliendo de la sesión..."<<endl;
                                                break;
                                            default: 
                                                cout<<"Volviendo a mostrar el menu"<<endl;
                                                break;
                                        }
                                        system("pause");
                                        system("cls");
                                        menu_consul();
                                        cout<<"Digite su opción, querido consultor: "<<endl;
                                        cin>> *avar;
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
                            //función de bloque de usuario
                            bloqueo(registro,nombre,aux);
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
                system("pause");
                system("cls");
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
                system("pause");
                system("cls");
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
                system("pause");
                system("cls");
            break;
            case 5:
                cout<<"Saliendo..."<<endl;
                system("pause");
                system("cls");
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
void menu_categorias()      //menu de categorias
{

    cout<<"*********************************"<<endl;
    cout<<"*     OPCIONES DE categorias    *"<<endl;
    cout<<"*********************************"<<endl;
    cout<<"*      L) Lacteos               *"<<endl;
    cout<<"*      A) Aceites               *"<<endl;
    cout<<"*      F) Frutas y Hortalizas   *"<<endl;
    cout<<"*      D) Confiteria            *"<<endl;
    cout<<"*      C) Cereales              *"<<endl;
    cout<<"*      P) Panaderia             *"<<endl;
    cout<<"*      B) Productos carnico     *"<<endl;
    cout<<"*      H) Huevos                *"<<endl;
    cout<<"*      S) Salsas                *"<<endl;
    cout<<"*      W) Bebidas               *"<<endl;
    cout<<"*      T) Aperitivos            *"<<endl;
    cout<<"*********************************"<<endl;
    return;  //return final

}
void crear_producto(productos produc,string inventario) //void para crear la lista de los productos
{
    int autoincremental=0;      //variables
    char respuesta2;
    fstream tem;
    char apoyo [ML]={' '};
    char tempo={' '};
    bool veri;
    int verificar=0;
    string auxiliar, seleccion;
    tem.open(inventario.c_str(), ios::binary | ios::in);
    if(tem.is_open())       
    {
        tem.read((char *)&produc,sizeof(produc)); //abrir archivos y leerlo, corroborar que no este el nombre repetido 
        cout<< "Digite el nombre a ingresar nuevo: "<<endl;
        getline(cin>>ws,auxiliar);
        cout<< "Se verificara que el producto no exista"<<endl;
        strcpy(apoyo, auxiliar.c_str());        
        auxiliar=convertToString(apoyo,ML);
        while (verificar==0)        
        {
            seleccion=convertToString(produc.nombre,ML);
            if(auxiliar!=seleccion)     
            {
                tem.seekg(0,ios::end);    
                strcpy(produc.nombre,auxiliar.c_str());
                do
                {
                    menu_categorias();//sale el menu de categorias
                    cout<<"Ingrese la categoria del producto: "<<endl;
                    cin>>tempo;
                    if(tempo=='L' || tempo=='A' || tempo=='F' || tempo=='D' || tempo=='C' || tempo=='P' || tempo=='B' || tempo=='H' || tempo=='S' || tempo=='W' || tempo=='T')
                    {
                        veri=true;
                        produc.categoria=tempo;     //ingreso de categorias dependiendo las especificaciones dadas
                    }
                    else
                    {
                        veri=false;
                        cout<<"categoria no encontrada, vuelva a escribirla: "<<endl;
                    }
                }while(veri==false);        //ingreso de los demas componentes en la listas de productos
                cout<<"Ingrese el precio: "<<endl;
                cin>>produc.precio;
                cout<<"Ingrese la disponibilidad del producto: "<<endl;
                cin>>produc.disponibilidad;
                autoincremental=buscarcodigo(produc,inventario);
                cout<<"El codigo del producto es: ";
                produc.codigo=autoincremental+1;        //autoincremental en el codigo
                cout<<produc.codigo<<endl;
                archivoproducto(inventario,produc);     //funcion para escribir los datos en el archivo
                verificar=1;
            }
            tem.read((char *)&produc,sizeof(produc));
        }
    }
    tem.close();
    return;
}
void archivoproducto(string inventario, productos produc)       //funcion para escribir los datos en el archivo
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
productos buscar (string archivo, productos produc)     //imprime el archivo en pantalla producto con sus datos
{
    productos ejemplo;  //variables
    int i=0;
    string nombre="";
    fstream tem;
    tem.open(archivo,ios::binary | ios::in);
    while(!tem.eof())
    {
        tem.seekg((i)*sizeof(produc));      //abre el archivo lo lee y lo imprime por pantalla
        tem.read((char *) &produc,sizeof(produc));
        if(tem.good())
        {
            cout<<" la posicion en el archivo es: "<<i+1<<endl;
            nombre=convertToString(produc.nombre,ML);
            cout<<"--------------------------------------"<<endl;
            cout<<"Nombre: "<< nombre<<"\nCategoria: "<< produc.categoria <<"\nPrecio: "<<produc.precio <<"\nDisponibilidad: "<<produc.disponibilidad<<endl;
            cout<<"Codigo "<<produc.codigo<<" "<<endl;
        }
        cout<<"--------------------------------------"<<endl;
        i=i+1;
    }
    tem.close();
    return ejemplo;
}
int buscarcodigo(productos produc,string inventario)        //funcion para incremental el codigo
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
productos ordenaralf (string archivo, productos produc)     //funcion que ordena alfabeticamente por nombre 
{
    productos ejemplo;  //variables
    int i=0, n=0, p=0, num;
    string nombre="";
    fstream tem;

    tem.open(archivo,ios::binary | ios::in);
    while(!tem.eof())       
    {
        tem.seekg((i)*sizeof(produc));      //leer el archivo para poder saber cuantas cantidades de productos hay
        tem.read((char *) &produc,sizeof(produc));
        if(tem.good())
        {

        }
        i=i+1;
    }
    num=i-1;    //numero para saber cuantos productos hay en el archivo y utilizarlo para el ordenamiento
    
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

        tempo[n]=produc;        //se copia en un temporal para poder ordenarlo
        codigo[n]=produc.codigo;
        tempo[n].codigo=codigo[n];
        }
        n=n+1;
    }
    tem.close();
    for (int j=0; j<num;j++)
    {
        for (int k=j+1;k<num;k++)
        {
            // strcoll() devuelve -1 si el 1º parametro es mayor que el 2º, 0 si el 1º es igual al 2º, o
            //1 si el 1º mayor que el 2º. Lo hace caracter a caracter hasta encontrar una diferencia o un nulo que es cuando retorna uno de los valores mensionados.
            if ( ( strcoll(/*1º*/ tempo[j].nombre, /*2º*/tempo[k].nombre))>0) {
                //esto va subiendo los nombres a la cabeza de la lista
                tep=tempo[j];       //se ordena para sacarlo al codigo
                tempo[j]=tempo[k];
                tempo[k]=tep;
            }
        }
    }
    cout << "los productor ordenados son: "<<endl;      //imprimir el ordenamiento por pantalla alfabeticamente
    for ( int m=0; m<num;m++)   
    {
        cout<<"--------------------------------------"<<endl;
        cout<<"Nombre "<< tempo[m].nombre<<"\nCategoria: "<< tempo[m].categoria <<"\nPrecio: "<<tempo[m].precio <<"\nDisponibilidad: "<<tempo[m].disponibilidad<<endl;
        cout<<" codigo "<<tempo[m].codigo<<" "<<endl;
        cout<<"--------------------------------------"<<endl;
    }
    tem.close();
    return ejemplo;
}
productos ordenar_precio_M_m (string archivo, productos produc)     //funcion de ordenar por precios de mayor a menor
{
    int i=0, n=0, p=0, num; //variables
    productos tep, terr,aux,ejemplo;
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
    num=i-1; //numero para saber cuantos productos hay en el archivo y utilizarlo para el ordenamiento
    
    tem.close();
    productos tempo[num];
    tem.open(archivo,ios::binary | ios::in);
    int codigo[num];
    while(!tem.eof())
    {
        tem.seekg((n)*sizeof(produc));
        tem.read((char *) &produc,sizeof(produc));
        if(tem.good())
        {
        tempo[n]=produc;    //se copia en un temporal para poder ordenarlo
        codigo[n]=produc.codigo;
        tempo[n].codigo=codigo[n];
        }
        n=n+1;
    }
    tem.close();        //ordenamiento burbuja para ordenar de mayor a menor el precio del producto
    for(int j=0; j<num-1; j++)
    {
        for(int k=0; k<num-j-1; k++)
        {
            if(tempo[k].precio>tempo[k+1].precio)
            {
                aux = tempo[k];
                tempo[k]=tempo[k+1];
                tempo[k+1]= aux;
            }
        }
    }
    cout << "los productor ordenados son: "<<endl;     //imprimir el ordenamiento por pantalla de mayor a menor
    for(int m=0; m<num;m++) 
    {
        cout<<"--------------------------------------"<<endl;
        cout<<"Nombre "<< tempo[m].nombre<<"\nCategoria: "<< tempo[m].categoria <<"\nPrecio "<<tempo[m].precio <<"\nDisponibilidad "<<tempo[m].disponibilidad<<endl;
        cout<<" codigo "<<tempo[m].codigo<<" "<<endl;
        cout<<endl;
        cout<<"--------------------------------------"<<endl;
    }
    tem.close();

    return ejemplo;
}
productos ordenar_precio_m_M (string archivo, productos produc)
{
    productos ejemplo, tep, terr,aux;  //borrar para después
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
    num=i-1;     //numero para saber cuantos productos hay en el archivo y utilizarlo para el ordenamiento
    
    tem.close();
    tem.open(archivo,ios::binary | ios::in);
    productos tempo[num];
    int codigo[num];
    while(!tem.eof())
    {
        tem.seekg((n)*sizeof(produc));
        tem.read((char *) &produc,sizeof(produc));
        if(tem.good())
        {
            tempo[n]=produc;        //se copia en un temporal para poder ordenarlo
            codigo[n]=produc.codigo;
            tempo[n].codigo=codigo[n];
        }
        n=n+1;
    }
    tem.close();
    for(int j=0; j<num-1; j++)      //ordenamiento burbuja para ordenar de menor a mayor el precio del producto
    {
        for(int k=0; k<num-j-1; k++)
        {
            if(tempo[k].precio<tempo[k+1].precio)
            {
                aux = tempo[k];
                tempo[k]=tempo[k+1];
                tempo[k+1]= aux;
            }
        }
    }
    cout << "los productor ordenados son: "<<endl;      //imprimir el ordenamiento por pantalla de menor a mayor
    for ( int m=0; m<num;m++){
        cout<<"--------------------------------------"<<endl;
        cout<<"Nombre: "<< tempo[m].nombre<<"\ncategoria: "<< tempo[m].categoria <<"\nprecio: "<<tempo[m].precio <<"\ndisponibilidad: "<<tempo[m].disponibilidad<<endl;
        cout<<" codigo "<<tempo[m].codigo<<" "<<endl;
        cout<<"--------------------------------------"<<endl;
    }


    tem.close();
    return ejemplo;
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
                con++;  // contador de coincidencias
        }
    }
    else
        cout<<"Ha ocurrido un problema con el archivo"<<endl;
    busqueda.close();
    cout<<"Lectura completada..."<<endl;
    //Segunda o n apertura del archivo para el cambio de permiso mediante el nombre 
    if(con>0)
    {
        for(int j=0;j<con-1;j++)
        {
            cout<<endl<<"Nombre: "<<enlista[j].nombre<<endl;
            cout<<"Contraseña: *******"<<endl; //No se despliega la contraseña puesto que es privada
            cout<<"Tipo: "<<enlista[j].tipo<<endl;
            cout<<"Cuenta: "<<enlista[j].cuenta<<endl;
            cout<<"Creación: "<<enlista[j].fecha<<endl;
            cout<<endl;
        }
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
void Realizar_una_compra (productos produc, string inventario, recibo compras[], string recibos, Factura Factu, long direccion, string necesario)//Función para realizar la compra
{
    long ayuda, actual;//Auxiliares para saber la posicion 
    char respuesta, respuesta2;//Auxiliares pra manejo de la funcion
    bool encontrado=false, aux2=true;//bool para verificar
    string auxiliar;//string para comprar los nombres de las personas
    char apoyo [ML]={' '};//Ayuda para convertir con las posiciones
    int contaux=0, aux=0,confirmar=0, cambiar=0,total, comprobado=0; //Auxiliares pra manejo de la funcion
    fstream guardar; //Variables de archivo para buscar
    productos temporal; //Variables de estructura de productos para modificar
    ifstream Leer; //Variables de archivo para leer
    fstream busca; //Variables de modificacion
    Leer.open(inventario.c_str(), ios::binary | ios::app);//Abrir el archivo de inventario
    cout<< "Digite porfavor el nombre de su usuario para cargar su factura en su cuenta: "<<endl;
    cin>> auxiliar;//Para la verificación y que se generen facturas a nombre de las personas
    cout<< "Primero se verificara que el usuario exista"<<endl;
    strcpy(apoyo, auxiliar.c_str());
    auxiliar=convertToString(apoyo,ML);//Lo convertimos a string
    if(necesario==auxiliar)  // comparación y validación para cambio
    {
        //cout<<"Encontrado"<<endl;
        cout<< "se encontro su usurario"<<endl;
            if(Leer.is_open())//Si se lee el archivo entonces podemos hacer nuestras operaciones
            {
                Leer.read((char *)&produc,sizeof(produc));//Leemos la estructura
                cout<< "Mira los respectivos productos: "<<endl;
                while(!Leer.eof())//Revisamos el archivo hasta el final
                {
                    do{//Mostramos los productos posibles a comprar
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
                        cin>>respuesta;//Preguntamos si quiere comprar el producto mostrado
                        while (respuesta!='s' && respuesta!='n')//Verificamos que sea posible
                        {
                            cout<<" Por favor digite una respuesta correcta, s (si) ó n (no) "<<endl;
                            cin>>respuesta;
                        }
                        if(respuesta=='s')//Si nuestro cliente dice que si empezamos  
                        {                        
                                confirmar=produc.codigo;
                                if (contaux<5)
                                {   //como solo pueden comprar 5 productos se deja el maximo en 5 para sacarlo si se pasa
                                    //guardar.open(recibos, ios::binary |ios::out |ios::app);//Para guardar la información 
                                    cout<< "Porfavor ingrese el numero de productos que desea obtener: "<<endl;
                                    cin>> aux;
                                    while (aux>produc.disponibilidad || aux<1) //Verificamos la cantidad de productos que sea posibles
                                    {
                                        cout<<" Esto no es posible debido a que no se puede o no hay tantos de este producto "<<endl;
                                        cout<<" Porfavor vuelva a ingrese el numero de productos que desea: "<<endl;
                                        cin>> aux;
                                    } //Seguimos 
                                    strcpy(Factu.escogidos[contaux].nombre,produc.nombre);//Igualamos el nombre
                                    cambiar=produc.disponibilidad-aux;
                                    produc.disponibilidad=cambiar;
                                    Factu.escogidos[contaux].precio_ind=produc.precio;//Igualamos el precio
                                    Factu.escogidos[contaux].cantidad_compra+=aux;//Igualamos la cantidad 
                                    total=aux*produc.precio;//Sacamos el precio
                                    total+=total;//Sacamos el total
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
                                                busca.seekp(ayuda-(sizeof(temporal.disponibilidad)-(sizeof(temporal.ventas)-(sizeof(temporal.codigo)))));//Miramos la posicion
                                                temporal.disponibilidad=cambiar;//Cambiamos la cantidad a una menor
                                            }
                                            busca.write((char *)&temporal.disponibilidad,sizeof(temporal.disponibilidad));//Miramos en donde y lo escribimos
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
                                            busca.write((char *)&temporal.disponibilidad,sizeof(temporal.disponibilidad));//Miramos en donde y lo escribimos
                                        }
                                        else
                                            cout<<"Ha ocurrido un problema con el archivo"<<endl;
                                        busca.close();
                                        contaux++;
                                }
                                cout<< "Te gustaria comprar otro articulo (s/n)"<<endl;
                                cin>>respuesta2;//Miramos la respuesta y de esto cambiamos en el do while para ver si sigue o no 
                                while (respuesta2!='s' && respuesta2!='n')
                                {
                                    cout<<" Por favor digite una respuesta correcta, s (si) ó n (no) "<<endl;
                                    cin>>respuesta2;
                                }
                                if(respuesta2=='n')
                                {
                                    aux2=false;
                                }
                                else if(respuesta2=='s')
                                {
                                    aux2=true;                                        
                                }
                                else if(contaux>=5)
                                {
                                    cout <<" Ya alcanzo los 5 productos "<<endl;
                                    aux2=false;
                                    break;
                                }
                        }
                        Leer.read((char *)&produc,sizeof(produc));
                    }while(aux2==true);
                }
                Factu.precio_total = total;//Igualamos todos los valores despues de terminar la 
                Factu.estado_de_orden=true;
                Factu.num_factu=+1;
                strcpy(Factu.nombre,auxiliar.c_str());
                guardar.open(recibos, ios::binary|ios::app);//Para guardar la información 
                if(guardar.is_open())
                    guardar.write((char *)&Factu,sizeof(Factu));//Y lo escribimos
                else
                    cout<<"Se ha generado un error en la escritura..."<<endl;
            }
            guardar.close();//Cerramos el archivo
    }
    else
        cout<< "No se encontro su nombre, porfavor verifique he intente mas tarde "<<endl;
    Leer.close();//Cerramos el archivo
    return;
}
void Cancelar_una_compra (productos produc, string inventario, string recibos, Factura Factu, long direccion)
{
    long ayuda;//Auxiliares para saber la posicion 
    bool change=false;//bool para verificar
    bool encontrado;//bool para verificar
    char apoyo [ML]={' '};//Ayuda para convertir con las posiciones
    string auxiliar, seleccion;//string para comprar los nombres de las personas
    productos temporal;//Variables de estructura de productos para modificar
    ifstream Leer;//Variables de archivo para leer
    fstream busca, busca1;//Variables de modificacion
    Factura temporal1;//Variables de estructura de facturas para modificar
    int confirmar, con;//Auxiliares para manejo de la funcion
    char respues, respuesta2;//Auxiliares pra manejo de la funcion
    Leer.open(recibos.c_str(), ios::binary | ios::in);//Abrir el archivo de recibo
    if(Leer.is_open())//Si se lee el archivo entonces podemos hacer nuestras operaciones
        {
            Leer.read((char *)&Factu,sizeof(Factu));//Leemos la estructura
            cout<< "Digite porfavor el nombre de su usuario para cargar su factura en su cuenta: "<<endl;
            cin>> auxiliar;//Para la verificación y que se generen facturas a nombre de las personas
            cout<< "Primero se verificara que el usuario exista"<<endl;
            strcpy(apoyo, auxiliar.c_str());
            auxiliar=convertToString(apoyo,ML);//Lo convertimos a string
                while(!Leer.eof())//Revisamos el archivo hasta el final
                {
                    seleccion=convertToString(Factu.nombre,ML);//Mientras el nombre que nos digitarion este en la estructura puede cancelarlo
                    if(seleccion==auxiliar)// comparación y validación para aceptar cambios
                    {
                        do
                        {   //Mostramos los recibo posibles a cancelar              
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
                            cin>>respues;//Preguntamos si quiere cancelar el producto mostrado
                            while (respues!='s' && respues!='n')//Verificamos que sea posible
                            {
                                cout<<" Por favor digite una respuesta correcta, s (si) ó n (no) "<<endl;
                                cin>>respues;
                            }
                            if(respues== 's')//Si nuestro cliente dice que si empezamos
                            {
                                busca.open(recibos,ios::binary | ios::out | ios::in);//Para abrir recibos
                                if(busca.is_open()) //verificación de apertura de archivo
                                    {              
                                        busca.read((char *)&Factu,sizeof(Factu));  // lectura comprimida mediante la estructura en lista
                                        direccion = busca.tellg(); // guardado de posición para cambio
                                        ayuda=busca.tellg();//Miramos la dirreción
                                        busca.seekp(ayuda-(sizeof(temporal1.estado_de_compra)));
                                        temporal1.estado_de_compra=change;//Cambiamos lo que toca cambiar en eso
                                        busca.write((char *)&temporal1.estado_de_compra,sizeof(temporal1.estado_de_compra));//Miramos la posicion
                                        busca1.open(inventario, ios::binary | ios::out | ios::in );//Lo abrimos
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
                                                    temporal.ventas=temporal.ventas-1;//Restamos una venta ya que fue cancelada
                                                }
                                                busca1.write((char *)&temporal.disponibilidad,sizeof(temporal.disponibilidad));//Miramos en donde y lo escribimos
                                            }
                                        }
                                        else
                                        cout<<"Ha ocurrido un problema con el archivo"<<endl;
                                        busca1.close();//Cerramos el archivo 
                                    }
                                    else
                                        cout<<"Ha ocurrido un problema con el archivo"<<endl;
                                        busca.close();//Cerramos el archivo 
                            }
                            cout<< "Te gustaria cancelar otro articulo (s/n)"<<endl;
                            cin>>respuesta2;
                            while (respuesta2!='s' && respuesta2!='n')
                                {
                                    cout<<" Por favor digite una respuesta correcta, s (si) ó n (no) "<<endl;
                                    cin>>respuesta2;
                                }
                        }while(respuesta2=='s');
                    }
                    Leer.read((char *)&Factu,sizeof(Factu));//Volvemos a leer
                }
        }
        Leer.close();//Cerramos el archivo 
        
    return;
}
void Valor_total_de_compra(string recibos, Factura Factu)
{
    ifstream Leer;// Variables de archivo para leer
    bool aux;// Auxiliar para el estado de cuenta
    char apoyo [ML]={' '};// Ayuda para convertir con las posiciones
    string auxiliar, seleccion;// Auxiliares para string de nombres
    Leer.open(recibos.c_str(), ios::binary | ios::in);// Apertura del archivo 

    if(Leer.is_open())//Verificamos que este abierto
    {
        Leer.read((char *)&Factu,sizeof(Factu));// Leemos la estructura
        cout<< "Digite porfavor el nombre de su usuario para cargar su factura en su cuenta: "<<endl;
        cin>> auxiliar;//Para mostrar los productos
        cout<< "Primero se verificara que el usuario tenga alguna compra"<<endl;
        strcpy(apoyo, auxiliar.c_str());
        auxiliar=convertToString(apoyo,ML);//Lo convertimos a string
        while(!Leer.eof())//Revisamos el archivo hasta el final
        {
            seleccion=convertToString(Factu.nombre,ML);//Ponemos el nombre que aparecen en la factu.nombre
            aux=Factu.estado_de_orden;//Miramos el orden de la factura
            if (seleccion==auxiliar&& aux==true)//Verificamos para mostrar la factura
            {
                cout<< "Mira el total de la compra con sus respectivos productos seleccionados: "<<endl;
                for(int i=0;i<5;i++){//Y empezamos a mostrar
                cout<<"----------------------------"<<endl;
                cout<<"Producto:        "<<i<<"  "<<Factu.escogidos[i].nombre <<endl;
                cout<<"Precio:                 "<<Factu.escogidos[i].precio_ind<<endl;
                cout<<"Cantidad de producto:   "<<Factu.escogidos[i].cantidad_compra <<endl;
                cout<<"----------------------------"<<endl;
                cout<<endl;
                }
                cout<< "El precio total es de: "<<Factu.precio_total;//Mostramos el precio total del recibo
                cout<< "El numero de factura es de: "<<Factu.num_factu;//Mostramos el numero del recibo 
            }
            else// Y si no no tiene ningun recibo
            {
            cout<< "Si no se mostrado ninguna factura es porque: "<<endl;
            cout<< "No hay ninguna factura a su nombre hasta el momento o estan canceladas sus facturas "<<endl;
            }
            Leer.read((char *)&Factu,sizeof(Factu));//Volvemos a leer
        }
    }
    Leer.close();//Cerramos el archivo
    return;
}
void Cantidad_de_productos (string recibos, Factura Factu)//Mostrar cantidad de productos por resivo
{
    ifstream Leer;// Variables de archivo para leer
    int cont=0;//Auxiliar contador
    char apoyo [ML]={' '};//Ayuda para convertir con las posiciones
    bool aux;//Auxiliar para el estado de cuenta
    string auxiliar, seleccion;// Auxiliares para string de nombres
    Leer.open(recibos.c_str(), ios::binary | ios::in);// Apertura del archivo 
    if(Leer.is_open())//Verificamos que este abierto 
    {
        Leer.read((char *)&Factu,sizeof(Factu));// Leemos la estructura
        cout<< "Digite porfavor el nombre de su usuario para cargar su factura en su cuenta: "<<endl;
        cin>> auxiliar;//Para mostrar los productos 
        cout<< "Primero se verificara que el usuario tenga alguna compra"<<endl;
        strcpy(apoyo, auxiliar.c_str());
        auxiliar=convertToString(apoyo,ML);//Lo convertimos a string
        while(!Leer.eof())//Revisamos el archivo hasta el final
        {
            seleccion=convertToString(Factu.nombre,ML);//Ponemos el nombre que aparecen en la factu.nombre
            aux=Factu.estado_de_orden;//Miramos el orden de la factura
            if(seleccion==auxiliar && aux==true)//Verificamos para mostrar la factura
            {
                cout<< "Mira tus productos que estan en facturas validas y a tu nombre: "<<endl;
                for(int i=0;i<5;i++)//Y empezamos a mostrar
                {
                cout<<"----------------------------"<<endl;
                cout<<"Producto:        "<<i<<"  "<<Factu.escogidos[i].nombre <<endl;
                cout<<"Precio:                  "<<Factu.escogidos[i].precio_ind<<endl;
                cout<<"Cantidad de producto:    "<<Factu.escogidos[i].cantidad_compra <<endl;
                cout<<"----------------------------"<<endl;
                cout<<endl;
                }
            }
            Leer.read((char *)&Factu,sizeof(Factu));//Volvemos a leer
        }
    }
    Leer.close();//Cerramos el archivo
    return;
}
void Total_de_ventas(productos produc, string inventario)//Funcion para conocer el total de ventas que hay en la tienda
{
    ifstream Leer;// Variables de archivo para leer
    string aux;// String para comparar los nombres
    Leer.open(inventario.c_str(), ios::binary | ios::in);  //apertura del archivo 
    if(Leer.is_open())//Verificamos que este abierto 
    {
        Leer.read((char *)&produc,sizeof(produc));// Leemos la estructura
        cout<< "Mira los respectivos productos: "<<endl;
        cout <<"(Maximo 5 productos)"<<endl;
        while(!Leer.eof())//Revisamos el archivo hasta el final
        {
            aux = convertToString(produc.nombre,ML);//Igualamos y mostramos
            cout<<"----------------------------"<<endl;
            cout<<"     El total de ventas     "<<endl;
            cout<<"----------------------------"<<endl;
            cout<<"Producto es: "<<aux<<endl;
            cout<<"   Es de:           "<<produc.ventas;//Y mostramos la cantidad de ventas hasta en el moemnto en la tienda
            cout<<" Aqui estan unicamente las ";
            cout<<"ventas vigentes a pagar     "<<endl;
            cout<<"----------------------------"<<endl;
            cout<<endl;
            Leer.read((char *)&produc,sizeof(produc));
        }
    }
    Leer.close();
    return;
}
void Producto_mas_vendido(string recibos, Factura Factu, recibo compras[])//Arreglar
{
    ifstream Leer; //Variables de archivo para leer
    Factura temporal1;//Variables de estructura de facturas para modificar
    bool aux;//Auxiliares para saber el estado de orden
    int mayor, imayor;//Auxiliares para manejo de la funcion
    string cad1,cad2, aux2;//string para comparar los nombres de las personas
    char vacio[ML]= {' '};//Ayuda para convertir con las posiciones
    Leer.open(recibos.c_str(), ios::binary | ios::in);//Abrir el archivo de recibo
    if(Leer.is_open())//Si se lee el archivo entonces podemos hacer nuestras operaciones
    {
        Leer.read((char *)&Factu,sizeof(Factu));//Leemos la estructura
        while (!Leer.eof())//Revisamos el archivo hasta el final
        {
            for(int i=0;i<5;i++)//como solo pueden comprar 5 productos se deja el maximo en 5 para sacarlo si se pasa
            {
                aux=Factu.estado_de_orden;//Igualamos
                cad1 = convertToString(Factu.escogidos[i].nombre,ML);
                cad2 = convertToString(vacio,ML);
                if(temporal1.escogidos[i].nombre==Factu.escogidos[i].nombre && aux==true && cad2 != cad1)//Hacemos las condiciones  como que el recibo no este cancelado, el nombre sea igual tras con el nombre
                {
                    temporal1.escogidos[i].cantidad_compra+=temporal1.escogidos[i].cantidad_compra;//Cantidad de compra de los productos sumandose si son iguales   
                }                               
            }
            Leer.read((char *)&Factu,sizeof(Factu));//Seguimos leyendo la estructura
        }    
    }
    Leer.close();//Lo cerramos
    Leer.open(recibos.c_str(), ios::binary | ios::in);//Volvemos a leer el recibo 
    if(Leer.is_open())//Verificamos
    {
        Leer.read((char *)&Factu,sizeof(Factu));//Leemos la estructura
        while (!Leer.eof())//Lemos al final 
        {
            for(int i=0;i<5;i++)//generamos el for de los productos
            {
                if(i==0)//Miramos que este n la primera posicion
                {
                    mayor=temporal1.escogidos[i].cantidad_compra;   
                }               
                else
                {//Asiganmos la posicion del mayor
                    if (temporal1.escogidos[i].cantidad_compra>mayor)
                    { 
                        mayor = temporal1.escogidos[i].cantidad_compra;
                        imayor=i;
                    }
                }              
            }
            Leer.read((char *)&Factu,sizeof(Factu));
        }
        aux2=convertToString(temporal1.escogidos[imayor].nombre,ML);//Lo imprimimos               
        cout<<"El prodcuto con mayor ventas es: "<<aux2<<endl<< "Mayor: "<<mayor<<endl;      
    }
    Leer.close();//Cerramos el archivo   
    return;
}
void lista_clientes(string archivo,int orden)
{
    fstream canal; // stream para el manejo del archivo
    personal clientes[ML];
    int con=0,ini,fin,proceso,i=0;
    char letra = 'c';
    string aux;
    canal.open(archivo,ios::binary | ios::in);  // apertura de archivo en modo binario y lectura
    if(canal.is_open())
    {
        while(!canal.eof() && canal.good())  //lectura mientras el archivo no se acabo
        {
            canal.read(clientes[con].nombre,sizeof(clientes[con].nombre));
            canal.read(clientes[con].contrasena,sizeof(clientes[con].contrasena));  //lectura de registros mediante estructuras
            canal.read((char *)&clientes[con].tipo,sizeof(clientes[con].tipo));
            canal.read((char *)&clientes[con].cuenta,sizeof(clientes[con].cuenta));
            canal.read(clientes[con].fecha,sizeof(clientes[con].fecha));
            if(letra == clientes[con].tipo && clientes[con].cuenta=='a')  // si la cuenta es clientes y existe, continua lectura
                con++;
        }
        cout<<"Contador: "<<con<<endl;
        if(orden==1)  // configuraciónde orden de más viejos a más nuevos
        {
            ini = 0;
            fin = con;
            proceso = 1;
        }
        else if(orden==2)  //configuración orden de más nuevo a más viejo
        {
            ini = con-1;
            fin = 0;
            proceso = -1;
        }
        do
        {
            i++;
            aux = convertToString(clientes[ini].nombre,ML);
            cout<<"Cliente"<<i<<":\nNombre: "<<aux<<endl;
            aux = convertToString(clientes[ini].fecha,ML);
            cout<<"Tipo: Cliente"<<endl<<"Fecha de creación: "<<aux<<endl; //mostrar resultados
            ini+=proceso;
        } while (ini!=fin);
    }
    else
        cout<<"Ha ocurrido un problema con la obtención del listado..."<<endl;
    return;
}
void bloqueo(personal registro,string nombre,string aux)
{
    fstream usuarios;
    string user;
    char buscado[ML]= {' '},letra; // auxiliares char
    bool encontrado = false;
    long direccion;
    cout<<"Contraseña digitada incorrectamente 3 veces, se bloqueo el usuario..."<<endl;
    user = convertToString(registro.nombre,ML);
    usuarios.open(nombre,ios::binary|ios::in);  // abrir archivo en los tres modos
    if(usuarios.is_open())
    {
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
                letra = 'b'; // cambio de letra para bloqueo de usuarios
                //direccion = usuarios.tellg()-(sizeof(registro.fecha)+sizeof(registro.cuenta));   //mover puntero al aspecto para cuenta
                registro.cuenta = letra; //actualización de permiso
                usuarios.seekp(ios::cur -(sizeof(registro.fecha)+sizeof(registro.cuenta)));
                usuarios.write((char *)&registro.cuenta,sizeof(registro.cuenta)); // reasignación de bloqueo
                cout<<"Su usuario ha sido bloqueado, contacte al admin en caso de requerir desbloqueo"<<endl;
                cout<<"Realizando cambios..."<<endl;
                break;
            }
        }
    }
    else
        cout<<"Ha ocurrido un problema la bloquear al usuario"<<endl;
    usuarios.close();
    /*usuarios.open(nombre,ios::binary | ios::out);
    if(usuarios.is_open())
    {
        registro.cuenta = letra; //actualización de permiso
        usuarios.seekp(direccion);
        usuarios.write((char *)&registro.cuenta,sizeof(registro.cuenta)); // reasignación de bloqueo
        cout<<"Su usuario ha sido bloqueado, contacte al admin en caso de requerir desbloqueo"<<endl;
    }  
    usuarios.close();*/
    return;
}
void cambio_factura(string factura)
{
    fstream despacho;
    Factura impresos[ML]; // estructura de factura para guardado de lecturas
    int con=0,el,cod;
    string aux1, aux2;
    despacho.open(factura,ios::binary | ios::in); // apertura en modo lectura
    if(despacho.is_open())
    {
        while(!despacho.eof())
        {
            despacho.read((char *)&impresos[con],sizeof(impresos[con]));  //lectura de registro
            if(impresos[con].estado_de_compra && !impresos[con].estado_de_orden)
                con++; // contador para la búsqueda de nuevos casos y coincidencias
        }
    }
    else
        cout<<"Se ha generado un problema al acceder al hisotiral de compras..."<<endl;
    despacho.close();
    for(int i=0;i<con-1;i++)
    {
        aux1 = convertToString(impresos[i].nombre,ML);
        cout<<"-------------------------------------------------------------------"<<endl;
        cout<<"Nombre: "<<aux1<<"\nCódigo de compra: "<<impresos[i].num_factu<<endl;
        cout<<"Total a pagar: "<<impresos[i].precio_total<<"Estado de despacho: En espera"<<endl;  //mostrado de facturas sin validar
    }
    cout<<"-------------------------------------------------------------------"<<endl;
    do  // ciclo de validación
    {
        con = 0;
        despacho.open(factura,ios::binary | ios::out | ios::in);  // apertura del archivo en los tres modos
        cout<<"Digite el código de la factura a validar: ";
        cin>>cod;
        if(despacho.is_open())
        {
            while(!despacho.eof()) //lectura mientras no se llegue al final del archivo
            {
                despacho.read((char *)&impresos[con],sizeof(impresos[con]));
                if(cod == impresos[con].num_factu)  //búsqueda del código a validar
                {
                    despacho.seekp(despacho.tellg()-sizeof(impresos[con].estado_de_compra));  // ubicar el puntero correctamente para el cambio
                    impresos[con].estado_de_compra = true;
                    despacho.write((char *)&impresos[con].estado_de_compra,sizeof(impresos[con].estado_de_compra));  // actualización del registro
                }
            }
        }
        else
            cout<<"Ha ocurrido un problema con la validación del pago"<<endl;
        despacho.close(); // cierre
        cout<<"Si desea validar otro, digite 1, para salir digite otra opción: "<<endl;
        cin>> el;  // lectura de opción
    }while(el==1);
    return;
}
