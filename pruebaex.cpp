#include<iostream>
#include<string>

using namespace std;

struct Producto{
	int id;
	string name;
	int price;
	int stock;
};

void MostrarProducto(int c, Producto *A);
void InfoProducto(int c, int x, Producto *A);
void ActuProducto(int c, int x, int ns, Producto *A);
void ValorInv(int c, int value, Producto *A);


int main(){
	int n, num;
	
	cout<<"Cuantos productos quiere ingresar: ";
	cin>>num;
	Producto A[num];
	
	for(int i=0; i<num; i++){
		cout<<"Producto "<<i+1<<": \n";
		cout<<"Identificador del producto: \n";
		cin>>A[i].id;
		cout<<"Nombre del producto: \n";
		cin>>A[i].name;
		cout<<"Precio del producto (COP): \n";
		cin>>A[i].price;
		cout<<"Cantidad del producto: \n";
		cin>>A[i].stock;
		cout<<endl;
	}
	do{
		cout<<"Opciones para el inventario: \n 1. Mostrar todos los productos del inventario \n 2. Obtener informacion de un producto especifico \n 3. Actualizar la cantidad de un producto dado \n 4. Calcular el valor total del inventario \n 0. Salir \n";
		cout<<"Opcion: ";
		cin>>n;
		cout<<endl;
	
		switch (n){
			case 1:{
				cout<<"Los productos del inventario son: \n";
				MostrarProducto(num, &A[0]);
				break;
			}
			
			case 2:{
				int x;
				cout<<"Informacion sobre el producto (ID): ";
				cin>>x;
				InfoProducto(num, x, &A[0]);
				break;
			}
			
			case 3:{
				int x, ns;
				cout<<"Actualizar cantidad del producto (ID): ";
				cin>>x;
				ActuProducto(num, x, ns, &A[0]);
				break;
			}
			
			case 4:{
				int x;
				ValorInv(num, x, &A[0]);
				break;
			}
			case 0:{
				
				break;
			}
		}
	} 
	while(n!=0);
	
	
	return 0;
}

void MostrarProducto(int c, Producto *A){
	for(int i=0; i<c; i++){
		cout<<"Identificador: "<<A[i].id<<endl;
		cout<<"Nombre: "<<A[i].name<<endl;
		cout<<"Precio: "<<A[i].price<<endl;
		cout<<"Cantidad: "<<A[i].stock<<endl;
		cout<<endl;
	}
	cout<<endl;
}

void InfoProducto(int c, int x, Producto *A){
	for(int i=0; i<c; i++){
		if (A[i].id==x){
		cout<<"Nombre: "<<A[i].name<<endl;
		cout<<"Precio: "<<A[i].price<<endl;
		cout<<"Cantidad: "<<A[i].stock<<endl;
		}
	}
}

void ActuProducto(int c, int x, int ns, Producto *A){
	for(int i=0; i<c; i++){
		if (A[i].id==x){
			cout<<"La cantidad actual de "<<A[i].name<<" es "<<A[i].stock<<endl;
			cout<<"La nueva cantidad de "<<A[i].name<<" va a ser: ";
			cin>>A[i].stock;
			cout<<"La cantidad actual de "<<A[i].name<<" es "<<A[i].stock<<endl;
		}
	}
}

void ValorInv(int c, int value, Producto *A){
	value = 0;
	for(int i=0; i<c; i++){
		value += A[i].price*A[i].stock;
	}
	cout<<"El valor total del inventario es: "<<value<<endl;
}