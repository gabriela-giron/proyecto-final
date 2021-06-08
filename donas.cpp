//librerías
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>

//teclas direccionales
#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13

using namespace std;

//estructura de menus
void menu_productos();
void menu_datos();
void modificar_prod();
int menu(const char* titulo, const char *subtitulo, const char *opciones[], int n);

//escribir, añadir y leer clientes
void lectura2();
void crear2();
void aniadir();
void buscar();

//estructura para escribir, añadir y leer txt de productos
void buscar2();
void borrar2();
void aniadir2();
void lectura();

//marco
void pintar();

//ocultar cursor 
void OcultarCursor();

//funcion principal
void gotoxy(int x, int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	
	SetConsoleCursorPosition(hcon, dwPos);
}
//ocultar cursor
void OcultarCursor(){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize= 50;
	cci.bVisible=FALSE;
	
	SetConsoleCursorInfo(hcon,&cci);
}
//marco del programa
void pintar(){
	for(int i=2;i<163;i++){ //lineas horizontales
		gotoxy(i,1);
		printf("%c",205); 
		gotoxy(i,41);
		printf("%c",205);
	}
	for(int i=2;i<41;i++){//lineas verticales
		gotoxy(2,i);
		printf("%c",186); 
		gotoxy(163,i);
		printf("%c",186);	
	}
	gotoxy(2,1); //esquinas
	printf("%c",201);
	gotoxy(2,41); 
	printf("%c",200);
	gotoxy(163,1); 
	printf("%c",187);
	gotoxy(163,41); 
	printf("%c",188);
}
//void para leer productos.txt
void lectura(){
	system("cls");
	ifstream archivo;
	string texto;
	
	archivo.open("productos.txt",ios::in);//modo lectura
	
	if(archivo.fail()){
		cout<<"no se pudo abrir el archivo";
		exit(1);
	}
	while(!archivo.eof()){//mientras no sea el final del archivo eof fstream
		getline(archivo,texto);//todo lo que hay en el archivo
		cout<<texto<<endl;
	}
	archivo.close();
	getch();
}
void crear(ofstream &file){
	system("cls");
	string descrip;
	string numserie;
	string precio;
	
	file.open("productos.txt",ios::out);
	
	if(file.fail()){
		cout<<"No se pudo crear el archivo";
		exit(1);
	}
		fflush(stdin);
		cout<<"Descripcion: "<<endl;
		cin>>descrip;
		cout<<"Numero de Serie: "<<endl;
		cin>>numserie;
		cout<<"Precio Unitario: "<<endl;
		cin>>precio;
		
		file<<"\t\t "<<descrip<<"\t\t "<<numserie<<"\t\t\t\t "<<precio<<"\n";
		
		file.close();
	}	
bool verifica(string Numserie){
	ifstream file("productos.txt", ios::in);
	string descrip;
	string numserie;
	string precio;
	
	file>>descrip;
	while(!file.eof()){
		file>>numserie;
		file>>precio;
		if(numserie == Numserie){
			file.close();
			return false;
		}
		file>>descrip;
	}
	file.close();
	return true;
}
//estructura paraa añadir productos
void aniadir2(ofstream &file){
	system("cls");
	int n=0, i, h;
	string descrip;
	string numserie;
	string precio;
	
	file.open("productos.txt", ios::app);
	
	cout<<"Ingrese el numero de registros que desee ingresar: "<<endl;
	cin>>n;
	
	if(file.fail()){
		cout<<"No se pudo crear el archivo";
		exit(1);
	}
	for(i=0, h=1; i<n; i++, h++){
		fflush(stdin);
		cout<<"Descripcion  "<<h<<": "<<endl;
		cin>>descrip;
		cout<<"Numero de Serie "<<h<<": "<<endl;
		cin>>numserie;
		cout<<"Precio Unitario  "<<h<<": "<<endl;
		cin>>precio;
		if(verifica(numserie)){
			file<<"\t\t "<<descrip<<"\t\t "<<numserie<<"\t\t\t\t "<<precio<<"\n";
		}
	}
	file.close();	
}
//buscar productos
void buscar2(ifstream &archivo){
 	system ("cls");
 	archivo.open("productos.txt", ios::in);
 	string numserie,descrip,precio,nserie;
 	bool encontrado = false;
 	
  	cout<<"Ingresa el numero de serie que deseas encontrar: ";
 	cin>>nserie;
 	archivo>>descrip;
 	
 	while(!archivo.eof() && !encontrado){
 		archivo>>numserie;
		archivo>>precio;
 		if(numserie == nserie){
			cout<<"Descripcion: "<<descrip<<endl;
			cout<<"Numero de Serie: "<<numserie<<endl;
			cout<<"Precio Unitario: "<<precio<<endl;
			encontrado = true;		
		 }
 		archivo>>descrip;
	 }
 	archivo.close();
 	
 	if (!encontrado){
 	cout<<"Este registro no existe"<<endl;
	}
 	system("pause");
 }
//modificar precio productos
void modificar_precio(ifstream &archivo){
	system("cls");
	string precio;
	string descrip;
	string numserie;
	string precaux;
	
	archivo.open("productos.txt", ios::in);
	ofstream auxi("auxiliar.txt", ios::out);
	
	if(archivo.is_open()){
		cout<<"Digite el precio a modificar: ";
		cin>>precaux;
		archivo>>descrip;
		while(!archivo.eof()){
			archivo>>numserie;
			archivo>>precio;
			if(precio == precaux){
				cout<<"Digite el nuevo precio: ";
				cin>>precaux;
				auxi<<"\t\t "<<descrip<<"\t\t "<<numserie<<"\t\t\t\t "<<precaux<<"\n";
			}else{
				auxi<<"\t\t "<<descrip<<"\t\t "<<numserie<<"\t\t\t\t "<<precio<<endl;
			}
			archivo>>descrip;
		}
		archivo.close();
		auxi.close();	
	}else
		cout<<"Hubo un error, intentélo de nuevo"<<endl;
	remove("productos.txt");
	rename("auxiliar.txt", "productos.txt");
}
//modificar numero de serie
void modificar_serie(ifstream &archivo){
	system("cls");
	string precio;
	string descrip;
	string numserie;
	string nseraux;
	
	archivo.open("productos.txt", ios::in);
	ofstream auxi("auxiliar.txt", ios::out);
	
	if(archivo.is_open()){
		cout<<"Digite el numero de serie a modificar: ";
		cin>>nseraux;
		archivo>>descrip;
		while(!archivo.eof()){
			archivo>>numserie;
			archivo>>precio;
			if(numserie == nseraux){
				cout<<"Digite el nuevo numero de serie: ";
				cin>>nseraux;
				auxi<<"\t\t "<<descrip<<"\t\t "<<nseraux<<"\t\t\t\t "<<precio<<"\n";
			}else{
				auxi<<"\t\t "<<descrip<<"\t\t "<<numserie<<"\t\t\t\t "<<precio<<endl;
			}
			archivo>>descrip;
		}
		archivo.close();
		auxi.close();	
	}else
		cout<<"Hubo un error, intentélo de nuevo"<<endl;
	remove("productos.txt");
	rename("auxiliar.txt", "productos.txt");
}
//modificar descrip
void modificar_descrip(ifstream &archivo){
	system("cls");
	string precio;
	string descrip;
	string numserie;
	string descaux;
	
	archivo.open("productos.txt", ios::in);
	ofstream auxi("auxiliar.txt", ios::out);
	
	if(archivo.is_open()){
		cout<<"Digite la descripcion a modificar: ";
		cin>>descaux;
		archivo>>descrip;
		while(!archivo.eof()){
			archivo>>numserie;
			archivo>>precio;
			if(descrip == descaux){
				cout<<"Digite la nueva descripcion: ";
				cin>>descaux;
				auxi<<"\t\t "<<descaux<<"\t\t "<<numserie<<"\t\t\t\t "<<precio<<"\n";
			}else{
				auxi<<"\t\t "<<descrip<<"\t\t "<<numserie<<"\t\t\t\t "<<precio<<endl;
			}
			archivo>>descrip;
		}
		archivo.close();
		auxi.close();	
	}else
		cout<<"Hubo un error, intentélo de nuevo"<<endl;
	remove("productos.txt");
	rename("auxiliar.txt", "productos.txt");
}
//eliminar registros
void eliminar(ifstream &archivo){
	system("cls");
	string precio;
	string descrip;
	string numserie;
	string nserie;
	
	archivo.open("productos.txt", ios::in);
	ofstream auxi("auxiliar.txt", ios::out);
	
	if(archivo.is_open()){
		cout<<"Digite el numero de serie a eliminar: ";
		cin>>nserie;
		archivo>>descrip;
		while(!archivo.eof()){
			archivo>>numserie;
			archivo>>precio;
			if(numserie == nserie){
				cout<<"El registro fue eliminado correctamente";
				getch();
			}else{
				auxi<<"\t\t "<<descrip<<"\t\t "<<numserie<<"\t\t\t\t "<<precio<<endl;
			}
			archivo>>descrip;
		}
		archivo.close();
		auxi.close();	
	}else
		cout<<"Hubo un error, intentélo de nuevo"<<endl;
	remove("productos.txt");
	rename("auxiliar.txt", "productos.txt");
}	
//coso para flechas direccionales
int menu(const char* titulo, const char *subtitulo, const char *opciones[], int n){
	int opcionSeleccionada = 1;
	int tecla;
	bool repite = true;
	
	do{
		system("cls");
		gotoxy(75,23 + opcionSeleccionada);
		cout<<">";
		
		gotoxy(73,19);
		cout<<titulo;
		gotoxy(80,20);
		cout<<subtitulo;
		for(int i=0; i<n; i++){
			gotoxy(76, 24 + i);
			cout<<i + 1<<". "<<opciones[i];
		}
		do{
			tecla = getch();
		}while(tecla!=TECLA_ARRIBA && tecla!=TECLA_ABAJO && tecla!=ENTER);
		
		switch(tecla){
			case TECLA_ARRIBA:
				opcionSeleccionada--;
				
				if(opcionSeleccionada == 0){
					opcionSeleccionada = n;
				}
				break;
			case TECLA_ABAJO:
				opcionSeleccionada++;
				
				if(opcionSeleccionada > n){
					opcionSeleccionada = 1;
				}
				break;
			case ENTER:
				repite = false;
				break;	
		}

	}while(repite);
	return opcionSeleccionada;
}
//modificar productos
void modificar_prod(){
	ifstream archivo;
	ofstream file;
	OcultarCursor();
	system("color 5E");
	bool repite = true;
	int opcion;
	const char *titulo = "Keren's Donuts & Coffee'";
	const char *subtitulo = "Modificar Producto(s)";
	const char *opciones[]= {"Modificar Descripcion", "Modificar Numero de Serie", "Modificar Precio", "Regresar"};
	int n = 4;
	
	do{
		opcion = menu(titulo,subtitulo,opciones,n);
		
		switch(opcion){
			case 1:
				pintar();
				modificar_descrip(archivo);
				break;
			case 2:
				pintar();
				modificar_serie(archivo);
				break;
			case 3:
				pintar();
				modificar_precio(archivo);
				break;
			case 4: 
				repite = false;
				break;
		}
		
	}while(repite);
}
int main(){
	ifstream archivo;
	ofstream file;
	OcultarCursor();
	system("color 5E");
	bool repite = true;
	int opcion;
	const char *titulo = "Keren's Donuts & Coffee'";
	const char *subtitulo = "Productos";
	const char *opciones[]= {"Ver Precios", "Crear Registro", "Anadir Producto(s)","Buscar Producto", "Modificar Productos", "Eliminar Producto", "Salir"};
	int n = 7;
	
	do{
		opcion = menu(titulo,subtitulo,opciones,n);
		
		switch(opcion){
			case 1:
				pintar();
				lectura();
				break;
			case 2:
				pintar();
				crear(file);
				break;
			case 3:
				pintar();
				aniadir2(file);
				break;
			case 4: 
				pintar();
				buscar2(archivo);
				break;
			case 5: 
				pintar();
				modificar_prod();
				break;
			case 6:
				pintar(); 
				eliminar(archivo);
				break;
			case 7: 
				repite = false;
				break;
		}
		
	}while(repite);
	
	system("pause");
	getch();
	return 0;
}




