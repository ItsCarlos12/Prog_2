#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>
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

void redimensionarProveedores(Tienda* tienda){
    int nuevaCapacidad = tienda -> capacidadProveedores * 2;
    Proveedor* nuevoArray = new Proveedor[nuevaCapacidad];

    for(int i = 0; i < tienda -> numProveedores; i++){
        nuevoArray[i] = tienda -> proveedores[i];
    }

    delete[] tienda -> proveedores;
    tienda -> proveedores = nuevoArray;
    tienda -> capacidadProveedores = nuevaCapacidad;

    cout << "Redimensionado (proveedores)." << endl;
}

void crearProveedor(Tienda* tienda){
    char opcion;
    char buffer[200];

    cout << "\nDesea registrar un nuevo proveedor? (S/N): ";
    cin >> opcion;
    cin.ignore();

    if(opcion == 'n' || opcion == 'N'){
        cout << "Operacion cancelada." << endl;
        return;
    }

    if(tienda -> numProveedores == tienda -> capacidadProveedores){
        redimensionarProveedores(tienda);
    }

    Proveedor& p = tienda -> proveedores[tienda -> numProveedores];

    //Nombre
    cout << "Ingrese el nombre del proveedor (0 o CANCELAR para cancelar): ";
    cin.getline(buffer, 100);
    if(strcmp(buffer, "0") == 0 || strcasecmp(buffer, "CANCELAR") == 0){
        cout << "Registro cancelado." << endl;
        return;
    }
    strcpy(p.nombre, buffer);

    //RIF
    cout << "Ingrese el RIF del proveedor (0 o CANCELAR para cancelar): ";
    cin.getline(buffer, 20);
    if(strcmp(buffer, "0") == 0 || strcasecmp(buffer, "CANCELAR") == 0){
        cout << "Registro cancelado." << endl;
        return;
    }
    if(rifDuplicado(tienda, buffer)){
        cout << "ERROR: El RIF ya esta registrado." << endl;
        return;
    }
    strcpy(p.rif, buffer);

    //Telefono
    cout << "Ingrese el telefono: ";
    cin.getline(p.telefono, 20);

    //Email
    cout << "Ingrese el email: ";
    cin.getline(buffer, 100);
    if(!validarEmail(buffer)){
        cout << "ERROR: Formato de email invalido. Debe contener '@' y '.'" << endl;
        return;
    }
    strcpy(p.email, buffer);

    //Direccion
    cout << "Ingrese la direccion: ";
    cin.getline(p.direccion, 200);

    p.id = tienda -> siguienteIdProveedor;
    obtenerFechaActual(p.fechaRegistro);

    cout << "\n--- Vista previa ---" << endl;
    cout << "Nombre: " << p.nombre << endl;
    cout << "RIF: " << p.rif << endl;
    cout << "Telefono: " << p.telefono << endl;
    cout << "Email: " << p.email << endl;
    cout << "Direccion: " << p.direccion << endl;

    cout << "\n¿Guardar proveedor? (S/N): ";
    cin >> opcion;
    cin.ignore();

    if(opcion == 's' || opcion == 'S'){
        tienda -> numProveedores++;
        tienda -> siguienteIdProveedor++;
        cout << "Proveedor guardado exitosamente." << endl;
    } else {
        cout << "Registro descartado." << endl;
    }
}

void listarProveedores(Tienda* tienda){
    if(tienda -> numProveedores == 0){
        cout << "\nNo hay proveedores registrados." << endl;
        return;
    }

    int anchos[] = {4, 20, 15, 25, 12};
    int col = 5;

    cout << "\n" << setfill('=') << setw(85) << "" << endl;
    cout << " LISTADO DE PROVEEDORES" << endl;
    cout << setw(85) << "" << setfill(' ') << endl;
    dibujarTabla(anchos, col);
    cout << "| " << left << setw(anchos[0]) << "ID"
         << "| " << setw(anchos[1]) << "Nombre"
         << "| " << setw(anchos[2]) << "RIF"
         << "| " << setw(anchos[3]) << "Email"
         << "| " << setw(anchos[4]) << "Telefono" << " |" << endl;
    dibujarTabla(anchos, col);

    for(int i = 0; i < tienda -> numProveedores; i++){
        Proveedor& p = tienda -> proveedores[i];
        cout << "| " << left << setw(anchos[0]) << p.id
             << "| " << setw(anchos[1]) << p.nombre
             << "| " << setw(anchos[2]) << p.rif
             << "| " << setw(anchos[3]) << p.email
             << "| " << setw(anchos[4]) << p.telefono << " |" << endl;
    }
    dibujarTabla(anchos, col);
    cout << "Total de proveedores: " << tienda -> numProveedores << endl;
}

void buscarProveedor(Tienda* tienda){
    if(tienda -> numProveedores == 0){
        cout << "\nNo hay proveedores registrados." << endl;
        return;
    }

    int opcion;
    char criterio[100];
    cout << "\n--- Menu de Busqueda ---" << endl;
    cout << "1. Por ID\n2. Por nombre (parcial)\n3. Por RIF\n0. Cancelar\nSeleccione: ";
    cin >> opcion;
    cin.ignore();

    if(opcion == 0){
        cout << "Busqueda cancelada." << endl;
        return;
    }

    cout << "Ingrese el valor a buscar: ";
    cin.getline(criterio, 100);

    bool encontrado = false;
    int anchos[] = {4, 20, 15, 25, 12};
    int col = 5;

    for(int i = 0; i < tienda -> numProveedores; i++){
        Proveedor& p = tienda -> proveedores[i];
        bool coincide = false;

        switch(opcion){
            case 1:
                if(p.id == atoi(criterio)) coincide = true;
                break;
            case 2:
                if(compararLetras(p.nombre, criterio)) coincide = true;
                break;
            case 3:
                if(compararLetras(p.rif, criterio)) coincide = true;
                break;
            default:
                cout << "Opcion no valida." << endl;
                return;
        }

        if(coincide){
            if(!encontrado){
                cout << "\n| ID | Nombre | RIF | Email | Telefono |" << endl;
                dibujarTabla(anchos, col);
            }
            cout << "| " << left << setw(4) << p.id
                 << "| " << setw(20) << p.nombre
                 << "| " << setw(15) << p.rif
                 << "| " << setw(25) << p.email
                 << "| " << setw(12) << p.telefono << " |" << endl;
            encontrado = true;
        }
    }

    if(!encontrado){
        cout << "\nNo se encontraron coincidencias." << endl;
    }
}

int obtenerIndiceProveedor(Tienda* tienda, int idBuscar){
    for(int i = 0; i < tienda -> numProveedores; i++){
        if(tienda -> proveedores[i].id == idBuscar){
            return i;
        }
    }
    return -1;
}

int contarProductosDeProveedor(Tienda* tienda, int idProveedor){
    int count = 0;
    for(int i = 0; i < tienda -> numProductos; i++){
        if(tienda -> productos[i].idProveedor == idProveedor){
            count++;
        }
    }
    return count;
}

void actualizarProveedor(Tienda* tienda){
    if(tienda -> numProveedores == 0){
        cout << "\nNo hay proveedores registrados." << endl;
        return;
    }

    int idBuscar;
    cout << "\n--- Actualizar proveedor ---" << endl;
    cout << "Ingrese el ID del proveedor: ";
    cin >> idBuscar;
    cin.ignore();

    int indice = obtenerIndiceProveedor(tienda, idBuscar);
    if(indice == -1){
        cout << "ERROR: El proveedor con ID " << idBuscar << " no existe." << endl;
        return;
    }

    Proveedor& p = tienda -> proveedores[indice];
    int opcion;
    char buffer[200];

    do{
        cout << "\nDatos actuales:" << endl;
        cout << "Nombre: " << p.nombre << " | RIF: " << p.rif << endl;
        cout << "Telefono: " << p.telefono << " | Email: " << p.email << endl;
        cout << "\nQue desea editar?" << endl;
        cout << "1. Nombre\n2. RIF\n3. Telefono\n4. Email\n5. Direccion\n6. Guardar cambios\n0. Cancelar sin guardar\nSeleccione: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion){
            case 0:{
                cout << "Cambios descartados." << endl;
                return;
            }
            case 6:{
                char confirmar;
                cout << "¿Guardar cambios? (S/N): ";
                cin >> confirmar;
                cin.ignore();
                if(confirmar == 's' || confirmar == 'S'){
                    cout << "Proveedor actualizado correctamente." << endl;
                    return;
                }
                break;
            }
            case 1:{
                cout << "Nuevo nombre (actual: " << p.nombre << "): ";
                cin.getline(buffer, 100);
                if(strcmp(buffer, "0") != 0 && strcasecmp(buffer, "CANCELAR") != 0){
                    strcpy(p.nombre, buffer);
                    cout << "Nombre actualizado." << endl;
                }
                break;
            }
            case 2:{
                cout << "Nuevo RIF (actual: " << p.rif << "): ";
                cin.getline(buffer, 20);
                if(strcmp(buffer, "0") != 0 && strcasecmp(buffer, "CANCELAR") != 0){
                    if(rifDuplicado(tienda, buffer) && strcmp(buffer, p.rif) != 0){
                        cout << "ERROR: El RIF ya esta registrado." << endl;
                    } else {
                        strcpy(p.rif, buffer);
                        cout << "RIF actualizado." << endl;
                    }
                }
                break;
            }
            case 3:{
                cout << "Nuevo telefono (actual: " << p.telefono << "): ";
                cin.getline(p.telefono, 20);
                cout << "Telefono actualizado." << endl;
                break;
            }
            case 4:{
                cout << "Nuevo email (actual: " << p.email << "): ";
                cin.getline(buffer, 100);
                if(validarEmail(buffer)){
                    strcpy(p.email, buffer);
                    cout << "Email actualizado." << endl;
                } else {
                    cout << "ERROR: Formato de email invalido." << endl;
                }
                break;
            }
            case 5:{
                cout << "Nueva direccion (actual: " << p.direccion << "): ";
                cin.getline(p.direccion, 200);
                cout << "Direccion actualizada." << endl;
                break;
            }
            default:
                cout << "Opcion no valida." << endl;
        }
    } while(true);
}

void eliminarProveedor(Tienda* tienda){
    if(tienda -> numProveedores == 0){
        cout << "\nNo hay proveedores registrados." << endl;
        return;
    }

    int idBuscar;
    cout << "\n--- Eliminar proveedor ---" << endl;
    cout << "Ingrese el ID del proveedor: ";
    cin >> idBuscar;
    cin.ignore();

    int indice = obtenerIndiceProveedor(tienda, idBuscar);
    if(indice == -1){
        cout << "ERROR: El proveedor con ID " << idBuscar << " no existe." << endl;
        return;
    }

    Proveedor& p = tienda -> proveedores[indice];
    int productosAsociados = contarProductosDeProveedor(tienda, idBuscar);

    if(productosAsociados > 0){
        cout << "ADVERTENCIA: Este proveedor tiene " << productosAsociados << " productos asociados." << endl;
        cout << "No se puede eliminar hasta reasignar los productos a otro proveedor." << endl;
        return;
    }

    cout << "\nProveedor a eliminar: " << p.nombre << " (ID: " << p.id << ")" << endl;
    char confirmar;
    cout << "¿Confirmar eliminacion? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if(confirmar == 's' || confirmar == 'S'){
        for(int i = indice; i < tienda -> numProveedores - 1; i++){
            tienda -> proveedores[i] = tienda -> proveedores[i + 1];
        }
        tienda -> numProveedores--;
        cout << "Proveedor eliminado correctamente." << endl;
    } else {
        cout << "Eliminacion cancelada." << endl;
    }
}
