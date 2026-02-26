#include <iostream>
#include <ctime>
#include <cstring> 
#include "structs.h"

using namespace std;

//5. Redimensionar el array.
void redimensionarProductos(Tienda* tienda){
    //calcular nueva capacidad (doble de la actual).
    int nuevaCapacidad = tienda -> capacidadProductos * 2;

    //crear nuevo arreglo con la nueva capacidad.
    Producto* newArray = new Producto[nuevaCapacidad];

    //copiar todos los productos.
    for(int i=0; i<tienda -> numProductos; i++){
        newArray[i] = tienda -> productos[i];
    }

    delete [] tienda -> productos;
    tienda -> productos = nullptr;

    tienda -> productos = newArray;
    tienda -> capacidadProductos = nuevaCapacidad;

    cout<<"Redimensionado"<<endl;

}

bool codigoDuplicado(Tienda* tienda, const char* codigo){
    for(int i=0; i<tienda -> numProductos; i++){
        if(strcmp(tienda -> productos[i].codigo, codigo) == 0){
            return true;
        }
    }
    return false;
}

bool existeProveedor(Tienda* tienda, int idProveedor){
    for(int i=0; i<tienda -> numProveedores; i++){
        if(tienda -> proveedores[i].id == idProveedor){
            return true;
        }
    }
    return false;
}

void obtenerFechaActual(char* fecha){
    time_t t = time(0);
    tm* now = localtime(&t);

    strftime(fecha, 11, "%d/%m/%Y", now);
}

void crearProducto(Tienda* tienda){
    char opcion;
    char buffer[200];

    //1. Preguntar si desea registrar un nuevo producto.
    cout<<"\n Desea registrar un nuevo producto? (S/N): ";
    cin>>opcion;
    cin.ignore(); //Para limpiar el buffer.

    //2. Confirmacion antes de guardar.
    if(opcion == 'n' || opcion == 'N'){
        cout<<"Gracias por usar nuestro sistema de inventario. ¡Hasta luego!"<<endl;
        return;
    }

    //Si la tienda ya tiene el maximo de productos, se redimensiona el arreglo.
    if(tienda -> numProductos == tienda -> capacidadProductos){
        redimensionarProductos(tienda);
    }
    Producto& p = tienda -> productos[tienda -> numProductos];

    //3. Solicitar los datos.

    //Codigo
    cout<<"Ingrese el codigo del producto: (o 0 para cancelar): ";
    cin.getline(buffer, 20);
    if(strcmp(buffer, "0") == 0 || strcasecmp(buffer, "Cancelar")== 0 ){
        cout<<"Registro de producto cancelado."<<endl;
        return;
    }

    if(codigoDuplicado(tienda, buffer)){
        cout << "Error: el codigo " << buffer << "ya existe" <<endl;
        return;
    }
    strcpy(p.codigo, buffer);

    //Nombre
    cout << "Ingrese el nombre del producto: ";
    cin.getline(p.nombre, 100);

    //ID proveedor
    int temp;
    cout << "Ingrese el ID del proveedor: ";
    cin >> temp;

    if(!existeProveedor(tienda, temp)){
        cout << "Error: el proveedor con ID " << temp << " no existe." << endl;
        return;
    }

    p.idProveedor = temp;

    //Precio
    cout << "Ingrese el precio del producto: ";
    cin >> p.precio;
    if(p.precio <= 0){
        cout << "Error: el precio debe ser mayor a 0." << endl;
        return;
    }

    //Stock
    cout <<"Ingrese el stock del producto: ";
    cin >> p.stock;
    if(p.stock < 0){
        cout << "Error: el stock debe ser mayor o igual a 0." << endl;
        return;
    }

    //4 y 6. Asignacion automatica

    p.id = tienda -> siguienteIdProducto;
    obtenerFechaActual(p.fechaRegistro);

    cout << "---Producto Registrado---" << endl;
    cout << "ID: " << p.id << " | Codigo: " << p.codigo <<" | Nombre: " << p.nombre << " | Fecha de Registro: " << p.fechaRegistro << endl;
    cout << "Precio: " <<p.precio << " | Stock: " << p.stock <<endl;

    //Confirmacion final de si se quiere agregar el producto.
    cout <<" Confirmar guardado? (S/N): ";
    cin >> opcion;

    if(opcion == 's' || opcion == 'S'){
        tienda -> numProductos++;
        tienda -> siguienteIdProducto++;
        cout<<"Producto guardado exitosamente."<<endl;
    }
    else{
        cout<<"Registro descartado."<<endl;
    }

}