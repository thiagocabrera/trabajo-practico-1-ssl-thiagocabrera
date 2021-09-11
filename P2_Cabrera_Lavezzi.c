#include <stdio.h>
#include <string.h>

int tt[5][5] = {{1,3,2,2,4}, //D|0|+|-|*|
				{1,1,0,0,0},
				{1,4,4,4,4},
				{4,4,0,0,0},
				{4,4,4,4,4}};

int main () {
	
	char errorSintactico[] = "0-85-4+5*4*6000*+a-32*0+11+22-11*22";
	char errorLexico[] = "0-85-4+5*4*06000*-32*0+11+22-11*22";
	char opValida[] = "0-85-4+5*4*6000*-32*0+11+22-11*22";

	if(analizarOperacion(opValida)) printf("Operacion valida\n");
	else printf("Operacion invalida\n");
	return 0;
}

int decimal(char c){
	if(c > 48 && c < 58) return 1;
	return 0;
}

int Columna(int c) {
	
	if(decimal(c)) return 0;
	
	if(c == '0') return 1;
	
	if(c == '+') return 2;

	if(c == '-') return 3;

	if(c == '*') return 4;
		
	return 5;
	
}

void convertirCaracter(int *t, char c, int *neg){
	if(c == '-') *neg = 1;
	else if(c != '+'){
		*t*=10;
		if(*t < 0) *t-=(c-48);
		else *t+=(c-48);
		if(*neg == 1){
			*neg = 0;
			*t *=-1;
		}
	}
}

int multiplicacion(char *cadena, int *i, int *e, char *c, int *termino){ //opera todo un termino
	
	int resultado = *termino; //vamos guardando los resultados acá
	int neg = 0;
	int t = 0;
	*i=*i+1;
	*c = cadena[*i];
	
	while(cadena[*i] != '\0'){
		int col = Columna(*c);
		if(col == 5){ //validamos si el caracter es parte del alfabeto
			printf("CARACTER '%c' en la pos %d no pertenece al alfabeto\n",*c,*i);
			return 0;
		}
		*e = tt[*e][col];
		if(*e == 4){
			printf("Error lexico en la posicion %d\n",*i);
			return 0; // si llegamos a un estado de rechazo, directamente retornamos false
		}
		
		if(*e == 0){ //si aparece una operacion
			if(*c == '*'){
				resultado*=t;
				t = 0;
			}
			else break; //si no es *, es + o - por lo que salimos del loop
		}
		else convertirCaracter(&t,*c,&neg); //si no, vamos convirtiendo los caracteres
	*i = *i+1;
	*c = cadena[*i];
	
	}
	*termino = resultado*t;

	return 	1;

}

int analizarOperacion(char *cadena){

	int terminos[100] = {};
	int longTerminos = 0;
	char operaciones[50] = {};
	int longOperaciones = 0;
	
	int e = 0; //estados
	int i=0; //index con el que recorreremos la cadena
	char c =cadena[i]; // caracter con el que recorremos la cadena
	
	int termino = 0; // donde vamos convirtiendo los numeros
	int neg = 0; // bandera con la que convertimos numeros a negativo
	
	while(c != '\0'){
		
		int col = Columna(c);
		if(col == 5){ //validamos si el caracter es parte del alfabeto
			printf("CARACTER '%c' en la pos %d no pertenece al alfabeto\n",c,i);
			return 0;
		}
		e = tt[e][col];
		if(e == 4){
			printf("Error lexico en la posicion %d\n",i);
			return 0; // si llegamos a un estado de rechazo, directamente retornamos false
		}
		if(e == 0){ //si aparece una operacion
		
			//si es una multiplicacion vamos a querer obtener todo el termino
			if(c == '*') if(!multiplicacion(cadena,&i,&e,&c,&termino)) return 0; //si se encuentra un error en la funcion, se retorna falso
			terminos[longTerminos++] = termino;
			termino = 0;
			if(c == '\0') break; //puede ya estar en '\0' debido a la funcion multiplicar
			operaciones[longOperaciones++] = c; //si no lo está, agregamos la operacion al array
		
		}
		else convertirCaracter(&termino,c,&neg); //si no, vamos convirtiendo los caracteres
		c = cadena[++i];	//la cadena puede ya estar en el \0 debido a la funcion multiplicar
		if(c == '\0') terminos[longTerminos++] = termino;
	}
	
	int j;
	for(j=0;j<longOperaciones;j++){
		if(operaciones[j] == '+') terminos[0] += terminos[j+1];
		else terminos[0] -= terminos[j+1];
	}
	printf("RESULTADO: %d\n",terminos[0]);
	
	return 1;
	
}
