#include <iostream>
#include <ctime>
#include <cstring> 
#include<iomanip>
#include "structs.h"

using namespace std;

bool rifDuplicado(Tienda* tienda, const char* rif){
    for(int i = 0; i < tienda -> numProveedores; i++){
        if(strcmp(tienda -> proveedores[i].rif, rif) == 0){
            return true;
        }
    }
    return false;
}

bool emailValido(const char* email){
    return strchr(email, '@') != nullptr;
}

void redimensionarProveedores(Tienda* tienda){
    int nuevaCapacidad = tienda -> capacidadProveedores * 2;

    //crear nuevo arreglo con la nueva capacidad.
    Proveedor* newArray = new Proveedor[nuevaCapacidad];

    //copiar todos los proveedores.
    for(int i=0; i<tienda -> numProveedores; i++){
        newArray[i] = tienda -> proveedores[i];
    }

    delete [] tienda -> proveedores;
    tienda -> proveedores = nullptr;

    tienda -> proveedores = newArray;
    tienda -> capacidadProveedores = nuevaCapacidad;

    cout<<"Redimensionado"<<endl;
}

void crearProveedor(Tienda* tienda){
    char buffer[200];
    char opcion;

    mostrarBanner("Registrar Nuevo Proveedor");

    if(tienda -> numProveedores == tienda -> capacidadProveedores){
        redimensionarProveedores(tienda);
    }

    Proveedor& prov = tienda -> proveedores[tienda -> numProveedores];

    cout << "Ingrese el RIF (o '0' para cancelar): ";
    cin.getline(buffer, 20);

    if(strcmp(buffer, 0) == 0){
        cout << "Registro cancelado" << endl;
        return;
    }

    if(rifDuplicado(tienda, buffer)){
        cout << "Error: el rif " << buffer << " ya existe en el sistema" << endl;
        return;
    }

    strcpy(prov.rif, buffer);

    //Datos basicos

    cout << "Nombre del proveedor: ";
    cin.getline(prov.nombre, 100);

    bool correoVer = false;


}