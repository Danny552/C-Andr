#include <iostream>
#include <cstdio>
#include <cstring> // For strcmp
#include <iomanip> // For setw

using namespace std;

struct producto {
    char nombre[50];
    int precio;
    int cantidad;
};

int llenar() {
        FILE *archdisco = fopen("productos.txt", "ab");
    if (!archdisco) {
        cout << "Error: Could not create or open file.\n";
        return 1;
    }


    producto p;
    cin.ignore(); // Clear the leftover newline from the input buffer
    cout << "Ingresar nombre producto: ";
    cin.getline(p.nombre, 50);
    cout << "Ingresar precio del producto: ";
    cin >> p.precio;
    cout << "Ingresar cantidad producto: ";
    cin >> p.cantidad;

    if (fwrite(&p, sizeof(p), 1, archdisco) != 1) {
        cout << "Error: Could not write to file.\n";
        return 1;
    }
    fclose(archdisco);
    return 0;
}

void Visualizar() {
    FILE *archdisco = fopen("productos.txt", "rb");
    if (!archdisco) {
        cout << "Error: Could not open file.\n";
        return;
    }

    producto p;
    cout << "Productos en existencia:\n";
    cout << "----------------------------------------------------------\n";
    cout << "|      PRODUCTO       | PRECIO  | CANTIDAD |PRECIO  TOTAL|\n";
    cout << "----------------------------------------------------------\n";

    // Debugging: Check if the file is read
    bool hasData = false;
    while (fread(&p, sizeof(p), 1, archdisco) == 1) {
        hasData = true;
        cout << "| " << setw(20) << left << p.nombre
             << "| " << setw(8) << right << p.precio
             << "| " << setw(8) << right << p.cantidad
             << "| " << setw(12) << right << (p.precio * p.cantidad)
             << " |\n";
    }

    if (!hasData) {
        cout << "No products encontrado in the file.\n";
    }

    cout << "----------------------------------------------------------\n";
    fclose(archdisco);
}


void eliminarProducto() {
    cin.ignore(); // Clear the leftover newline
    cout << "Ingrese el nombre del producto a eliminar: ";
    string nombre_producto;
    getline(cin, nombre_producto);

    FILE *archdisco = fopen("productos.txt", "rb"); // Open the original file for reading
    if (!archdisco) {
        cout << "Error: Could not open productos.txt for reading.\n";
        return;
    }

    FILE *tempfile = fopen("temp.txt", "wb"); // Create a temporary file for writing
    if (!tempfile) {
        cout << "Error: Could not create temp.txt.\n";
        fclose(archdisco);
        return;
    }

    producto p;
    bool encontrado = false;

    // Copy products to the temporary file, skipping the one to delete
    while (fread(&p, sizeof(p), 1, archdisco) == 1) {
        if (strcmp(p.nombre, nombre_producto.c_str()) != 0) {
            if (fwrite(&p, sizeof(p), 1, tempfile) != 1) {
                cout << "Error: Could not write to temp.txt.\n";
                fclose(archdisco);
                fclose(tempfile);
                return;
            }
        } else {
            encontrado = true;
        }
    }

    fclose(archdisco);
    fclose(tempfile);

    if (!encontrado) {
        cout << "Producto '" << nombre_producto << "' no encontrado.\n";
        remove("temp.txt");
        return;
    }

    // Open the files again to manually copy data back
    archdisco = fopen("productos.txt", "wb"); // Reopen productos.txt for writing
    tempfile = fopen("temp.txt", "rb");      // Reopen temp.txt for reading

    if (!archdisco || !tempfile) {
        cout << "Error: Could not reopen files for copying.\n";
        if (archdisco) fclose(archdisco);
        if (tempfile) fclose(tempfile);
        return;
    }

    // Copy contents from temp.txt back to productos.txt
    while (fread(&p, sizeof(p), 1, tempfile) == 1) {
        if (fwrite(&p, sizeof(p), 1, archdisco) != 1) {
            cout << "Error: Could not write back to productos.txt.\n";
            fclose(archdisco);
            fclose(tempfile);
            return;
        }
    }

    fclose(archdisco);
    fclose(tempfile);

    // Remove the temporary file after copying
    if (remove("temp.txt") != 0) {
        cout << "Warning: Could not remove temp.txt.\n";
    }

    cout << "Producto '" << nombre_producto << "' eliminado correctamente.\n";
}


void modificaProducto() {
    cin.ignore(); // Clear the leftover newline
    cout << "Ingrese el nombre del producto a modificar: ";
    string nombre_producto;
    getline(cin, nombre_producto);

    FILE *archdisco = fopen("productos.txt", "rb"); // Open the original file for reading
    FILE *tempfile = fopen("temp.txt", "wb");      // Create a temporary file for writing

    if (!archdisco || !tempfile) {
        cout << "Error: Could not open files.\n";
        if (archdisco) fclose(archdisco);
        if (tempfile) fclose(tempfile);
        return;
    }

    producto p;
    bool encontrado = false;

    // Process each product
    while (fread(&p, sizeof(p), 1, archdisco) == 1) {
        if (strcmp(p.nombre, nombre_producto.c_str()) == 0) {
            encontrado = true;
            cout << "Producto encontrado: " << p.nombre << "\n";
            cout << "Precio actual: " << p.precio << ", Cantidad actual: " << p.cantidad << "\n";

            int opc;
            cout << "¿Desea modificar el precio (1), la cantidad (2) o ambos (3)? ";
            cin >> opc;

            switch (opc) {
                case 1:
                    cout << "Ingrese el nuevo precio: ";
                    cin >> p.precio;
                    break;
                case 2:
                    cout << "Ingrese la nueva cantidad: ";
                    cin >> p.cantidad;
                    break;
                case 3:
                    cout << "Ingrese el nuevo precio: ";
                    cin >> p.precio;
                    cout << "Ingrese la nueva cantidad: ";
                    cin >> p.cantidad;
                    break;
                default:
                    cout << "Opción no válida. No se realizaron cambios.\n";
                    break;
            }
        }

        if (fwrite(&p, sizeof(p), 1, tempfile) != 1) {
            cout << "Error: Could not write to temp.txt.\n";
            fclose(archdisco);
            fclose(tempfile);
            return;
        }
    }

    fclose(archdisco);
    fclose(tempfile);

    if (!encontrado) {
        cout << "Producto '" << nombre_producto << "' no encontrado.\n";
        remove("temp.txt");
        return;
    }

    if (remove("productos.txt") != 0) {
        cout << "Error: Could not remove productos.txt.\n";
        return;
    }

    if (rename("temp.txt", "productos.txt") != 0) {
        cout << "Error: Could not rename temp.txt to productos.txt.\n";
        return;
    }

    cout << "Producto '" << nombre_producto << "' modificado correctamente.\n";
}

void filtraProducto() {
    int limiteInf, limiteSup;

    // Asking the user for the price range
    cout << "Ingrese el límite inferior del precio: ";
    cin >> limiteInf;
    cout << "Ingrese el límite superior del precio: ";
    cin >> limiteSup;

    // Check if the limits are valid
    if (limiteInf > limiteSup) {
        cout << "El límite inferior no puede ser mayor que el límite superior.\n";
        return;
    }

    FILE *archdisco = fopen("productos.txt", "rb");
    if (!archdisco) {
        cout << "Error: Could not open productos.txt for reading.\n";
        return;
    }

    producto p;
    bool encontrado = false;

    cout << "Productos en el rango de precios (" << limiteInf << " - " << limiteSup << "):\n";
    cout << "----------------------------------------------------------\n";
    cout << "|      PRODUCTO       | PRECIO  | CANTIDAD |PRECIO  TOTAL|\n";
    cout << "----------------------------------------------------------\n";

    while (fread(&p, sizeof(p), 1, archdisco) == 1) {
        // Check if the product's price is within the range
        if (p.precio >= limiteInf && p.precio <= limiteSup) {
            encontrado = true;
            cout << "| " << setw(20) << left << p.nombre
                 << "| " << setw(8) << right << p.precio
                 << "| " << setw(8) << right << p.cantidad
                 << "| " << setw(12) << right << (p.precio * p.cantidad)
                 << " |\n";
        }
    }

    if (!encontrado) {
        cout << "No se encontraron productos en el rango de precios indicado.\n";
    }

    cout << "----------------------------------------------------------\n";
    fclose(archdisco);
}


int main() {

    int opc;
    bool exit = false;
    while (!exit) {
        cout << "Ingrese el comando que desee:\n1) Ingresar un producto\n2) Eliminar un producto\n3) Modificar un producto\n4) Filtrar productos por cantidad\n5) Visualizar tabla\n6) Salir\n";
        cin >> opc;

        switch (opc) {
            case 1:
                llenar();
                break;
            case 2:
                eliminarProducto();
                break;
            case 3:
                modificaProducto();
                break;
            case 4:
                filtraProducto();
                break;
            case 5:
                Visualizar();
                break;
            case 6:
                exit = true;
                break;
            default:
                cout << "Comando no existente, volviendo...\n";
                break;
        }
    }
    return 0;
}
