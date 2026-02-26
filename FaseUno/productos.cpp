#include <iostream>
#include <ctime>
#include <cstring> 
#include<iomanip>
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

    //Descripcion
    cout << "Ingrese la descripcion del producto: ";
    cin.getline(p.descripcion, 200);

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
    cin.ignore();

    //4 y 6. Asignacion automatica

    p.id = tienda -> siguienteIdProducto;
    obtenerFechaActual(p.fechaRegistro);

    cout << "\n--- Vista previa del registro ---" <<endl;
    mostrarTabla();
    imprimirFilaProducto(p);
    int anchos[] = {4, 12, 20, 12, 10, 8, 12};
    int col = 7;
    dibujarTabla(anchos, col);

    cout << "Descripcion: " << p.descripcion <<endl;

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

void buscarProducto(Tienda* tienda){
    if(tienda -> numProductos == 0){
        cout << "No hay productos registrados"<<endl;
        return;
    }

    int opcion;
    char criterio[100];
    cout << "\n--- Menu de Busqueda ---" << endl;
    cout << "1. Por Id\n2. Por codigo\n3. Por Nombre (Parcial)\n4. Por ID Proveedor\n0. Cancelar\nSeleccione: ";
    cin >> opcion;
    cin.ignore();

    if(opcion == 0){
        cout << "Busqueda cancelada. Volviendo al menu principal." << endl;
        return;
    }

    cout << "Ingrese el valor a buscar: ";
    cin.getline(criterio, 100);

    bool encontrado = false;
    bool tablaMostrada = false;
    int anchos[] = {4, 12, 20, 12, 10, 8, 12};
    int col = 7;

    for(int i = 0; i < tienda -> numProductos; i++){
        Producto& p = tienda -> productos[i];
        bool coincide = false;

        switch(opcion){
            case 1:
                if(p.id == atoi(criterio)){
                    coincide = true;
                }
                break;
            case 2:
                if(compararLetras(p.codigo, criterio)){
                    coincide = true;
                }
                break;
            case 3:
                if(compararLetras(p.nombre, criterio)){
                    coincide = true;
                }
                break;
            case 4:
                if(p.idProveedor == atoi(criterio)){
                    coincide = true;
                }
                break;
            default:
                cout << "Opcion no valida." << endl;
                return;
        }

        if(coincide){
            if(!tablaMostrada){
                mostrarTabla();
                tablaMostrada = true;
            }
            imprimirFilaProducto(p);
            dibujarTabla(anchos, col);
            encontrado = true;
        }
    }

    if(!encontrado){
        cout << "\nNo se encontraron coincidencias." << endl;
    }
}

//Mostrar Tabla
void mostrarTabla(){
    int anchos [] = {4, 12, 20, 12, 10, 8, 12};
    int col = 7;

    cout << "\n" << setfill('=') << setw(85) << "" <<endl;
    cout << " Listado de Productos" << endl; 
    cout << setw(85) << "" << setfill(' ') << endl;

    dibujarTabla(anchos, col);

    cout << "| " << left << setw(anchos[0]) << "ID"
         << "| " << setw(anchos[1]) << "Codigo"
         << "| " << setw(anchos[2]) << "Nombre"
         << "| " << setw(anchos[3]) << "Proveedor"
         << "| " << setw(anchos[4]) << "Precio"
         << "| " << setw(anchos[5]) << "Stock"
         << "| " << setw(anchos[6]) << "Fecha" << " |" <<endl;
         
    dibujarTabla(anchos, col);
}

//Imprimir los productos en tabla.
void imprimirFilaProducto(const Producto& p){
    int anchos[] = {4, 12, 20, 12, 10, 8, 12};

    cout << "| " << left << setw(anchos[0]) << p.id
         << "| " << setw(anchos[1]) << p.codigo
         << "| " << setw(anchos[2]) << p.nombre
         << "| " << setw(anchos[3]) << p.idProveedor
         << "| " << setw(anchos[4]) << fixed << setprecision(2) <<  p.precio
         << "| " << setw(anchos[5]) << p.stock
         << "| " << setw(anchos[6]) << p.fechaRegistro << " |" <<endl;
}

int obtenerIndice(Tienda * tienda, int idBuscar){
    for(int i = 0; i < tienda -> numProductos; i++){
        if(tienda -> productos[i].id == idBuscar){
            return i; 
        }
    }
    return -1;
}

void actualizarProducto(Tienda* tienda){
    if(tienda -> numProductos == 0){
        cout << "\nNo hay productos registrados" << endl;
        return;
    }

    int idBuscar;
    cout << "\n---Actualizar producto---" << endl;
    cout << "Ingrese el ID del producto: ";
    cin >> idBuscar;
    cin.ignore();

    int indice = obtenerIndice(tienda, idBuscar);

    if(indice == -1){
        cout << "Error: el producto con ID " << idBuscar << " no existe." << endl;
        return;
    }

    Producto pEdit = tienda -> productos[indice];
    int opcion;
    int anchos[] = {4, 12, 20, 12, 10, 8, 12};
    int col = 7;

    do{
        cout << "\nDatos actuales del producto" << endl;
        mostrarTabla();
        imprimirFilaProducto(pEdit);
        dibujarTabla(anchos, col);

        cout << "\nQue desea agregar/editar?" << endl;
        cout << "1. Codigo\n2. Nombre\n3. Descripcion\n4. Por ID Proveedor\n0. Guardar y volver\nSeleccione: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion){
            case 0:
                break;
            case 1: case 2: case 3: case 4:
                cout << "Opcion en desarrollo." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while(opcion != 0);

    tienda -> productos[indice] = pEdit;
    cout << "Producto actualizado correctamente." << endl;
}

