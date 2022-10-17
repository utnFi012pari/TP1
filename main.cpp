#include<iostream>
#include<fstream>

using namespace std;

void ordenamientoDeLaListaDeKmRecorridos(float columnas[],int posiciones[], int dim,int& posCol, string tiposDeprod[]){	
	cout<<endl;
	float ax = 0;
	int ax2 = 0;
	//columnas[3] = 2400; //purbea para ver si funciona la funcion
	cout<<"Listado de km recorrido por el tipo de producto que más veces superoro los 13k kg"<<endl;
	for(int i=0;i<dim;i++){
		for(int j = 0;j<dim-1;j++){
			if(columnas[j]>columnas[j+1]){								
				ax = columnas[j];
				columnas[j] = columnas[j+1];
				columnas[j+1] = ax;		

				ax2 = posiciones[j];
				posiciones[j] = posiciones[j+1];
				posiciones[j+1] = ax2;					
			}
		}
		cout<<tiposDeprod[posiciones[i]]<<": "<<columnas[i]<<endl;
		posCol = posiciones[i];		
	}
	cout<<endl;
	cout<<"------------------------------------------------------------------------";
	cout<<endl;	
}
int elClienteConMayorTiposDeProd(int vecTiProdCli[], int cClien){
	int aux = 0;	
	for(int i = 1;i<cClien;i++){
		if(vecTiProdCli[i]>vecTiProdCli[aux]){
			aux = i;
		}
	}
	return aux;
}
void tipoDeProductoMayora13000(int m[][5],int cClien, string tipoProc[],int tProd,string clientes[],int vecTiProdCli[]){	
	int lim = 13000;
	int uax{0};
	const int col{5};
	for(int i=0;i<cClien;i++){
		cout<<clientes[i]<<": ";
		for(int j = 0;j<col;j++){
			if(m[i][j]>lim && uax==i){
				vecTiProdCli[i] = vecTiProdCli[i]+1;
				cout<<tipoProc[j]<<" ";
			}			
			//cout<<"El tipo de producto: "<<tipoProc[j]<<" supera el limite de "<<lim<<" con un total de : "<<m[i][j]<<" del cliente: "<<clientes[i]<<endl;
		}		
		cout<<"------------> "<<"hay "<<vecTiProdCli[i]<< " tipos de productos"<<endl;
		//cout<<"           --------> "<<vecTiProdCli[i]<<" tipos de productos superaron los "<<lim<<" Kilos"<<endl;
		uax++;		
	}
			
}

int main(){
	

	const int cClien {8};
	const int tProd {5};
	int codigoDeCliente[cClien][tProd] {};  //matriz que cargara los kg por cada tipo de producto
	int CantDeEntregas[cClien][tProd] = {0}; //veces en la que se hacen las entregas
	float distancia[cClien][tProd]={};//matriz que cargara los kmetros por cada tipo de producto	
	int tiposDeProdcutoPorCliente[cClien]={};	
	int posiciones[tProd]={}; //posiciones de los tipos de producto
	float kmRocorridos[tProd]={}; //valor de cada tipo de posicion del vector posiciones[tProd]={}	
	string clientes[cClien]; //para cargar el nombre de los clientes
	string tipoProd[tProd]; //para cargar el nombre de los tipo de productos	
	ifstream Archivo;
	Archivo.open("Nombres.txt");
	if (!Archivo) {
		cout << "Error al tratar de abrir el archivo de nombres" << endl;
		return 1;
	}
	for (int i = 0; i < cClien && Archivo >> clientes[i]; i++);					
	for (int i = 0; i < tProd && Archivo >> tipoProd[i]; i++);	
	Archivo.close();	
	Archivo.open("Datos.txt");
	if (!Archivo) {
		cout << "Error al tratar de abrir el archivo de producción" << endl;
		return 1;
	}
	int cCli, CtiDP; 
	float Kilo, Dr;
	while (Archivo >> cCli >> CtiDP >> Kilo >> Dr) {
		codigoDeCliente[cCli][CtiDP] += Kilo;		
		CantDeEntregas[cCli][CtiDP] = CantDeEntregas[cCli][CtiDP] + 1;
		distancia[cCli][CtiDP]+=Dr;
	}
	Archivo.close();	
	cout << endl;
	//punto 1
	tipoDeProductoMayora13000(codigoDeCliente,cClien,tipoProd,tProd,clientes,tiposDeProdcutoPorCliente);
	cout << endl;
	cout<<"------------------------------------------------------------------------";
	cout << endl;		
	int posiF = elClienteConMayorTiposDeProd(tiposDeProdcutoPorCliente,cClien);	
	for(int i=0;i<tProd;i++){		
		kmRocorridos[i] = distancia[posiF][i]; //float
		posiciones[i] += i; //int		
	}
	int posCol{0};
	ordenamientoDeLaListaDeKmRecorridos(kmRocorridos,posiciones,tProd,posCol,tipoProd);

	int sumTotalDeLaColu = 0;
	for(int i=0;i<cClien;i++){		
		sumTotalDeLaColu = sumTotalDeLaColu + CantDeEntregas[i][posCol]; //float
	}
	cout<<"Cantidad de entregas para el tipo de prodcuto: "<<tipoProd[posCol]<<": "<<sumTotalDeLaColu<<endl;
	cout<<endl;
	return 0;
}