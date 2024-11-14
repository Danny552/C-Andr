#include <iostream>
#include <cstdio>
#include <string.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct producto {
    char nombre[50];  // Use array for storing string
    int precio;
    int cantidad;
};

int llenar(FILE *archdisco) {
    system("CLS");
    struct producto producto;

    if (archdisco == nullptr) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    printf("Ingresar nombre producto: ");
    fgets(producto.nombre);  // No & needed for arrays
    printf("Ingresar precio del producto: ");
    scanf("%d", &producto.precio);
    printf("Ingresar cantidad producto: ");
    scanf("%d", &producto.cantidad);

    // Use sizeof(producto) to correctly write the entire struct
    fwrite(&producto, sizeof(producto), 1, archdisco);

    return 0;
}

void Visualizar() {
    system("CLS");
    FILE *archdisco;
    struct producto producto;

    // Use "rb" mode to open the file for reading in binary mode
    archdisco = fopen("productos.txt", "rb");
    
    if (archdisco == NULL) {
        printf("Error abriendo el Archivo\n");
        return;
    }

    printf("productos en existencias:\n");
    printf("-----------------------------------------------------------\n");
    printf("|      PRODUCTO       |  PRECIO  | CANTIDAD |PRECIO  TOTAL|\n");
    while (fread(&producto, sizeof(producto), 1, archdisco) == 1) {
        printf("-----------------------------------------------------------\n");
        printf("|%18.18s   |%6d    |%6d    |%10d   |\n", producto.nombre, producto.precio, producto.cantidad, (producto.precio * producto.cantidad));
    }
    printf("-----------------------------------------------------------\n");

    fclose(archdisco);
}

void EliminarProducto(const char* nombre_producto) {
    FILE *archdisco, *tempfile;
    struct producto producto;
    bool found = false;

    // Open in binary mode
    archdisco = fopen("productos.txt", "rb");
    tempfile = fopen("temp.txt", "wb");

    if (archdisco == NULL || tempfile == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Read from file
    while (fread(&producto, sizeof(producto), 1, archdisco)) {
        // If product does not match the name, write it to temp file
        if (strcmp(producto.nombre, nombre_producto) != 0) {
            if (fwrite(&producto, sizeof(producto), 1, tempfile) != 1) {
                printf("Error al escribir en el archivo temporal.\n");
                break;
            }
        } else {
            found = true;  // Mark product as found
        }
    }

    fclose(archdisco);
    fclose(tempfile);

    // If found, replace original file with the updated one
    if (found) {
        rename("temp.txt", "productos.txt");
        printf("Producto '%s' eliminado correctamente.\n", nombre_producto);
    } else {
        printf("Producto '%s' no encontrado.\n", nombre_producto);
        remove("temp.txt");  // Clean up temp file if product not found
    }
}

int main() {
    // Open a file in append mode to add products
    FILE *file = fopen("productos.txt", "ab");

    if (file == nullptr) {
        printf("Error: Could not create file.\n");
        return 1;
    }
    //llenar(file);
    char elim[50];
    scanf("%s", elim);
    EliminarProducto(elim);
    Visualizar();
    return 0;
}
