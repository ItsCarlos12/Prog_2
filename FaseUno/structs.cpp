struct General{
    int id;
    char nombre[100];
    char fechaRegistro[11];
    char email[100];
    char direccion[200];
};



struct Producto : General{
    char codigo[20];
    char descripcion[200];
    int idProveedor;
    float precio;
    int stock;
};

struct Proveedor : General{
    char rif[20];
    char telefono[20];
    char email[100];
};

struct Cliente : General{
    char cedula[20];
    char telefono[20];
    char email[100];
};

struct Transaccion : General{
    char tipo[10];
    int idProducto;
    int idRelacionado;

    int cantidad;
    float precioUnitario;

    float total;
    char fecha[11];
    char descripcion[200];
};

struct Tienda : General{
    char rif[20];
    
    //Arrays dinamicos de entidades.

    Producto* productos;
    int numProductos;
    int capacidadProductos;

    Proveedor* proveedores;
    int numProveedores;
    int capacidadProveedores;

    Cliente* clientes;
    int numClientes;
    int capacidadClientes;

    Transaccion* transacciones;
    int numTransacciones;
    int capacidadTransacciones;

    //Contadores para IDs autoincrementales.

    int siguienteIdProducto;
    int siguienteIdProveedor;
    int siguienteIdCliente;
    int siguienteIdTransaccion;
};
