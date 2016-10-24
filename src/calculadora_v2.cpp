                              //David Bolaños y Sebastian Aguila        Grupo 05 de PF

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;


int menu(int &opcion); //funcion menu
void CargEscrConf(ofstream &conf2, ifstream &conf1, char &suma, char &resta, char &multiplicacion, char &division, char &raiz, char &factorial, char &potencia, char &clear, char &finalizar, char &simplificacion); //configuracion por defecto
void configuracion(ofstream &conf2, char &suma, char &resta, char &multiplicacion, char &division, char &raiz, char &factorial, char &potencia, char &clear, char &finalizar, char &simplificacion);	 //configuracion segun el usuario
void Case1(ofstream &log, char suma, char resta, char multiplicacion, char division, char raiz,  char factorial, char potencia,  char clear, char finalizar);											 //calculadora modo normal
void funcSumResMulDiv1(ofstream &log, char &operacion, char suma, char resta, char multiplicacion, char division, char raiz, long double &op1, bool &error, string &tipoError);							 //Suma, resta, multiplicacion y division de la calculadora normal
void funcPot(ofstream &log, long double &op1, string &tipoError, bool &error);												   						  //funcion potencia calculadora normal
void funcFact(ofstream &log, long double &op1, string &tipoError, bool &error);																		  //funcion factorial
void Case2(ofstream &log, char suma, char resta, char multiplicacion, char division, char potencia, char clear, char simplificacion, char finalizar); //calcualdora modo fracciones
void leerFrac1(ofstream &log, int &op1, int &den1);											    //funcion lectura de op1 y den1
void leerFrac2(ofstream &log, int &op2, int &den2);												//funcion lectura de op2 y den2
void funcPot1(ofstream &log, int &op1, int op2, string &tipoError, bool &error);				//funcion potencia calculadora modo fracciones
void funcSimpl(ofstream &log, int &op1, int &den1, string &tipoError, bool &error);				//funcion simplificacion
int mcd(int a,int b);																			//funcion maximo comun divisor

//funcion principal
int main()
{							
	int opcion;
	char suma, resta, multiplicacion, division, factorial, raiz, potencia, clear, finalizar, simplificacion;
	bool cerrar = false;
	ifstream conf1;
	ofstream log, conf2;

	log.open("log.txt");
	conf1.open("conf.txt");
	if(conf1.is_open()){                                       //Si se abre correctamente, se leen los operadores
		conf1 >> suma >> resta >> multiplicacion >> division >> raiz >> factorial >> potencia >> clear >> finalizar >> simplificacion;
		conf1.close();
	}
	else{
		conf1.close();
		CargEscrConf(conf2, conf1, suma, resta, multiplicacion, division, raiz, factorial, potencia, clear, finalizar, simplificacion);
	}

	while (cerrar == false){
		opcion = menu(opcion);														//Se pide la opcion en una funcion
		switch (opcion){
		case 1:																																	// Abrir calculadora normal																															
			Case1(log, suma, resta, multiplicacion, division, raiz, factorial, potencia, clear, finalizar);	break;					         
		case 2:																																	// Abrir calculadora de fracciones
			Case2(log, suma, resta, multiplicacion, division, potencia, clear, simplificacion, finalizar); break;							    		   
		case 3: 																																//Configuracion
			configuracion(conf2, suma, resta, multiplicacion, division, raiz, factorial, potencia, clear, finalizar, simplificacion);	break;
		case 4:																																	// Salir del programa																														
			cerrar = true; break;
		}
	}
	log.close();
	conf2.close();
	cout << endl << " Hecho por David Bolanios y Sebastian Aguila, Grupo 5 de FP" << endl << "" << endl;
	return 0;
}

//Suma, resta, multiplicacion. division y raiz de la calculadora normal
void funcSumResMulDivRaiz1(ofstream &log, char &operacion, char suma, char resta, char multiplicacion, char division, char raiz, long double &op1, bool &error, string &tipoError){
	long double op2;
	if (operacion == raiz){
					if (op1 >= 0)
						op1 = sqrt(op1);
					else{
						tipoError = "Error! Numero de la raiz no positivo!";
						error = true;
					}
	}
	else{
		cin >> op2;
		log << op2;
		if (operacion == suma)
			op1 = op1 + op2;	
		else if (operacion == resta)	
			op1 = op1 - op2;
		else if (operacion == multiplicacion)
			op1 = op1 * op2;	
		else if (operacion == division){
			if (op2 != 0){
				op1 = op1 / op2;
			}
			else{
				tipoError = "Error!, imposible dividir entre 0!";
				error = true;
			}
		}
	}
}

//funcion que muestra un menu, lee la opcion y la devuelve
int menu(int &opcion){					   
	cout << "-------------------------------" << endl
		<< "1. CALCULADORA: MODO NORMAL" << endl
		<< "2. CALCULADORA: MODO FRACCIONES" << endl
		<< "3. CONFIGURACION" << endl 
		<< "4. TERMINAR" << endl
		<< "-------------------------------" << endl
		<< "Opcion: ";
	cin >> opcion;
	return opcion;
}

//Funcion que, en el caso que no se haya abierto el archivo con la configuracion, crea una configuracion por defecto en el archivo, ademas de asignar los correspondientes caracteres a las variables
void CargEscrConf(ofstream &conf2, ifstream &conf1, char &suma, char &resta, char &multiplicacion, char &division, char &raiz, char &factorial, char &potencia, char &clear, char &finalizar, char &simplificacion){
	conf2.open("conf.txt");
	conf2 << '+' << '-' << '*' << '/' <<'r' <<'!' << '^' << 'c' << 'x' << 's';
	conf2.close();
	conf1.open("conf.txt");
	conf1 >> suma >> resta >> multiplicacion >> division >> raiz >> factorial >> potencia >> clear >> finalizar >> simplificacion;
	conf1.close();
}

//funcion que es el case 3 y se dedica a pedir los caracteres de configuracion al usuario, ademas de guardarlo en un archivo de texto para su posterior carga.
void configuracion(ofstream &conf2, char &suma, char &resta, char &multiplicacion, char &division, char &raiz, char &factorial, char &potencia, char &clear, char &finalizar, char &simplificacion){
	char oper;
	conf2.open("conf.txt");
	cin.sync();
	cout << "Caracter para la suma (Intro para mantener " << suma << ")" << endl;
	oper = cin.peek();
	if (oper != '\n')
		suma = oper;
	conf2 << suma;
	cin.sync();
	cout << "Caracter para la resta (Intro para mantener " << resta << ")" << endl;
	oper = cin.peek();
	if (oper != '\n')
		resta = oper;
	conf2 << resta;
	cin.sync();
	cout << "Caracter para la multiplicacion (Intro para mantener " << multiplicacion << ")" << endl;
	oper = cin.peek();
	if (oper != '\n')
		multiplicacion = oper;
	conf2 << multiplicacion;
	cin.sync(); 
	cout << "Caracter para la division (Intro para mantener " << division << ")" << endl;
	oper = cin.peek();
	if (oper != '\n')
		division = oper;
	conf2 << division;
	cin.sync(); 
	cout << "Caracter para la factorial (Intro para mantener " << factorial << ")" << endl;
	oper = cin.peek();
	if (oper != '\n')
		factorial = oper;
	conf2 << factorial;
	cin.sync();
	cout << "Caracter para la potencia (Intro para mantener " << potencia << ")" << endl;
	oper = cin.peek();
	if (oper != '\n')
		potencia = oper;
	conf2 << potencia;
	cin.sync(); 
	cout << "Caracter para la raiz (Intro para mantener " << raiz << ")" << endl;
	oper = cin.peek();
	if (oper != '\n')
		raiz = oper;
	conf2 << raiz;
	cin.sync(); 	
	cout << "Caracter para poner a 0 (Intro para mantener " << clear << ")" << endl;
	oper = cin.peek();
	if (oper != '\n')
		clear = oper;
	conf2 << clear;
	cin.sync();
	cout << "Caracter para terminar (Intro para mantener " << finalizar << ")" << endl;
	oper = cin.peek();
	if (oper != '\n')
		finalizar = oper; 
	conf2 << finalizar;
	cin.sync();
	cout << "Caracter para simplificar (Intro para mantener " << simplificacion << ")" << endl;
	oper = cin.peek();
	if (oper != '\n')
		simplificacion = oper; 
	conf2 << simplificacion;
	cin.sync();
}

//funcion en la que se encuentra la calculadora normal
void Case1(ofstream &log, char suma, char resta, char multiplicacion, char division, char raiz, char factorial, char potencia,  char clear, char finalizar){
	cin.sync();
	long double op1 = 0;
	string tipoError;
	bool error = false;
	char p, operacion;
	cout << endl << "Calculadora: modo normal" << endl << endl;
	log << endl << "Calculadora: modo normal" << endl << endl;

	do{
		cout << "Introduce una operacion aritmetica (" << finalizar << " para terminar):" << endl;
		cout << suma << ":suma  " << resta <<  ":resta  " << multiplicacion << ":mult.  " << division << ":div.  " << factorial << ":fact.  " << raiz << ":raiz  " << potencia << ":potencia  " << clear << ":clear  " << endl;
		cout << ">>> ";
		p = cin.peek();
		if(p >= '0' && p <= '9')
			cin >> op1;
		log << op1;
		do{
			cin.get (operacion);
			log << operacion;
			if(operacion != '\n'){
				error = false;
				if ((operacion == suma)||(operacion == resta)||(operacion == multiplicacion)||(operacion == division)||(operacion == raiz))
					funcSumResMulDivRaiz1(log, operacion, suma, resta, multiplicacion, division, raiz, op1, error, tipoError);
				else if (operacion == potencia){
					funcPot(log, op1, tipoError, error);
				}
				else if (operacion == factorial){
					funcFact(log, op1, tipoError, error);
				}
				else if (operacion == clear){
					op1 = 0;
				}
				else if (operacion == finalizar){
					error = false;
				}
				else{
					tipoError = "Error!, Expresion incorrecta!";
					error = true;
				}
			}
		} while(operacion != '\n' );
		if (error == true){
			cout << tipoError << endl << endl;
			op1 = 0;
			log << ">>> " << tipoError << endl << endl;
		}
		else if((error == false)&&(operacion != finalizar)){
			cout << ">>> " << op1 << endl << endl;
			log << ">>> " << op1 << endl << endl;;
		}
	} while(p != finalizar);
}

//funcion potencia (modo normal)
void funcPot(ofstream &log, long double &op1, string &tipoError, bool &error){ 
	double op2;
	cin >> op2;
	log << op2;

	if((floor(op1)) == op1){
		double aux = 1;
		for(int i = 0; i < op2; i++){
			aux = aux * op1;
		}
		if (op2 > 0)
			op1 = aux;
		else if(op2 == 0)
			op1 = 1;
		else
			op1 = 1/aux;
	}
	else{
		tipoError = "Error! Numero del exponente no entero!";							
		error = true;
	}
}

//funcion factorial
void funcFact(ofstream &log, long double &op1, string &tipoError, bool &error){ 
	if(op1 > 0){
		if((floor(op1)) == op1)
		{
			int fact= 1;
			for (double i = op1; i > 1; i--)
			{
				fact *= i;
			}
			op1 = (double)fact;
		}
		else{
			tipoError = "Error!, Numero del factorial no entero!"; 
			error = true; 
		}
	}
	else{
		tipoError = "Error!, Numero del factorial no positivo!";
		error = true; 
	}
}

//funcion en la que se encuentra la calculadora de fracciones
void Case2(ofstream &log, char suma, char resta, char multiplicacion, char division, char potencia, char clear, char simplificacion, char finalizar){
	int op1 = 0, den1 = 1, op2, den2;
	char operacion;
	bool error = true, salir = false, mostError = false;
	string tipoError;

	cout << endl << "Calculadora: modo fracciones" << endl << endl;
	log << "Calculadora: modo fracciones" << endl << endl;

	do{
		leerFrac1(log, op1, den1);

		do{
			cin.get(operacion);
			log << operacion;
			
				if(error == false){
					if((operacion == suma) || (operacion == resta) || (operacion == multiplicacion) || (operacion == division) || (operacion == potencia))
					leerFrac2(log, op2, den2);
					
					if (operacion == suma){
						op1 = op1 * den2 + den1 * op2;
						den1 = den1 * den2;
						error = false;
					}
					else if (operacion == resta){
						op1 = op1 * den2 - den1 * op2;
						den1 = den1*den2;
						error = false;
					}
					else if (operacion == multiplicacion){
						op1 = op1 * op2;
						den1 = den1 * den2;
						error = false;
					}
					else if (operacion == division){
						op1 = op1 * den2;
						den1 = den1 * op2;
						error = false;
					}
					else if (operacion == potencia){
						int aux;
						funcPot1(log, op1, op2, tipoError, error);
						aux = op1;
						op1 = den1;
						funcPot1(log, op1, op2, tipoError, error);
						den1 = op1;
						op1 = aux;
						error = false;
					}
				
				else if (operacion == simplificacion){
					funcSimpl(log, op1, den1, tipoError, error);
					error = false;
				}
				else if (operacion == clear){
					op1 = 0;
					den1 = 1;
					error = false;
				}
				else if (operacion == finalizar){
					salir = true;
					error = false;
				}	
				else if (operacion != '\n'){
					tipoError = "Error!, Expresion incorrecta!";
					error = true;
					op1 = 0;
					den1 = 1;
				}
				}
		}while(operacion != '\n');

		if (salir == false){
		if (error == false){
			cout << ">>> " << op1 << "|" << den1 << endl << endl;
			log << ">>> " << op1 << '|' << den1 <<  endl << endl;
		}
		if ((error == true) && (mostError == true)){
		cout << tipoError << endl << endl;
		log << tipoError << endl << endl;
		op1 = 0;
		den1 = 1;
		error = false;
		}
		
			cout << "Introduce una operacion aritmetica (" << finalizar << " para terminar):" << endl;
			cout << suma << ":suma  " << resta <<  ":resta  " << multiplicacion << ":mult.  " << division << ":div.  "  << potencia << ":potencia  " << clear << ":clear  " << simplificacion << ":simplificar"<< endl;
			cout << ">>> ";
		mostError = true;
		}
		
	}while(salir == false);
}

//lectura fraccion 1
void leerFrac1(ofstream &log, int &op1, int &den1){
	char t;
	t = cin.peek();														 
	if(t >= '0' && t <= '9'){
		cin >> op1;
		log << op1;
		if (cin.peek() == '|'){
			cin >> t;                             
			cin >> den1; 
		}
		else if (cin.peek() != '\n')
			den1 = 1;
		log << '|';
		log << den1;

	}
}

//lectura fraccion 2
void leerFrac2(ofstream &log, int &op2, int &den2){
	char t;
	cin >> op2;
	log << op2;
	if (cin.peek() == '|'){
		cin >> t;
		cin >> den2; 
	}
	else 
		den2 = 1;
	log << '|';
	log << den2;
}

//funcion potencia calculadora fracciones
void funcPot1(ofstream &log, int &op1, int op2, string &tipoError, bool &error){ 
	log << op2;
	double aux = 1;
	for(int i = 0; i < op2; i++){
		aux = aux * op1;
	}
	if (op2 > 0)
		op1 = aux;
	else if(op2 == 0)
		op1 = 1;
	else
		op1 = 1/aux;
}

//funcion que simplifica (si es posible) una fraccion
void funcSimpl(ofstream &log, int &op1, int &den1, string &tipoError, bool &error){  
	int aux;
	aux = den1;
	den1 = den1 / mcd(op1, den1);
	op1 = op1 / mcd(op1, aux);
}

//funcion que calcula el maximo comun divisor mediante el algoritmo de euclides y devuelve el numero (se utiliza para simplificar)
int mcd(int a,int b){				
	int r;
	while (b != 0){
		r = (a % b);
		a = b;                                                          //"a" es el mcd, que es devuelto por la funcion para dividir al op1 y den1
		b = r;  
	}
	return a;
}







