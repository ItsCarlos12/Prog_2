#include <iostream>
#include "structs.h"

using namespace std;

int main(){
    Tienda miTienda;

    inicializarTienda(&miTienda, "Mi TiendaTech", "J-112233445");

    int opcion;

    do{
        cout << "\n===== Sistema de Gestion de " << miTienda.nombre << " =====" << endl;
        cout << "1. Registrar producto" << endl;
        cout << "2. Buscar producto" << endl;
        cout << "3. Actualizar producto" << endl;
        cout << "4. Listar productos" << endl;
        cout << "5. Registrar proveedor" << endl;
        cout << "6. Listar proveedores" << endl;
        cout << "7. Buscar proveedor" << endl;
        cout << "8. Actualizar proveedor" << endl;
        cout << "9. Eliminar proveedor" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada.

        switch(opcion){
            case 1: 
                crearProducto(&miTienda);
                break;

            case 2: 
                buscarProducto(&miTienda);
                break;

            case 3:
                actualizarProducto(&miTienda);
                break;

            case 4:
                listarProductos(&miTienda);
                break;

            case 5:
                crearProveedor(&miTienda);
                break;

            case 6:
                listarProveedores(&miTienda);
                break;

            case 7:
                buscarProveedor(&miTienda);
                break;

            case 8:
                actualizarProveedor(&miTienda);
                break;

            case 9:
                eliminarProveedor(&miTienda);
                break;

            case 0:
                cout << "Saliendo del sistema. Hasta luego!" << endl;
                break;

            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);

    liberarTienda(&miTienda);

    return 0;
}
