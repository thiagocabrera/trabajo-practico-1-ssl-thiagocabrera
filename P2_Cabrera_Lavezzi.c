#include <stdio.h>
#include <string.h>

int tt[5][5] = {{1,3,2,2,4}, //D|0|+|-|*|
				{1,1,0,0,0},
				{1,4,4,4,4},
				{4,4,0,0,0},
				{4,4,4,4,4}};

int analizarOperacion(char *);

int main () {
	
	char errorFueraDelAlfabeto[] = "0-85-4+5*4*6000*+a-32*0+11+22-11*22";
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

//FUNCIONES DE VALIDACIÓN DE ERRORES
int errorCaracterNoPerteneceAlAlfabeto(int col, int caracter, int pos){ //si hay uno, da el mensaje y retorna true
	if(col == 5){
		printf("CARACTER '%c' en la pos %d no pertenece al alfabeto\n",caracter,pos);
		return 1;
	}
	return 0;
}

int errorLexico(int estado, int pos){ //si hay uno, da el mensaje y retorna true
	if(estado == 4){
		printf("Error lexico en la posicion %d\n",pos);
		return 1;
	}
	return 0;
}
//FIN DE LAS FUNCIONES DE VALIDACIÓN DE ERRORES

int multiplicacion(char *cadena, int *i, int *e, char *c, int *termino){ //opera todo un termino
	
	int neg = 0;
	int t = 0;
	*c = cadena[++*i];
	
	while(cadena[*i] != '\0'){
		int col = Columna(*c);
		if(errorCaracterNoPerteneceAlAlfabeto(col,*c,*i)) return 0;
		*e = tt[*e][col];
		if(errorLexico(*e,*i)) return 0;
		
		if(*e == 0){ //si aparece una operacion
			if(*c == '*'){
				*termino*=t;
				t = 0;
			}
			else break; //si no es *, es + o - por lo que salimos de la función
		}
		else convertirCaracter(&t,*c,&neg); //si no es una operación, vamos convirtiendo los caracteres
		*c = cadena[++*i];
	}
	*termino*=t;

	return 	1;

}

void operarTermino(int *termino, int *result, char op){
	if(op == '+') *result+=*termino;
	else *result-=*termino;
	*termino = 0;
}

int analizarOperacion(char *cadena){

	int result = 0;
	char op = '+';
	int e = 0; //estados
	int i=0; //index con el que recorreremos la cadena
	char c =cadena[i]; // caracter con el que recorremos la cadena
	
	int termino = 0; // donde vamos convirtiendo los numeros
	int neg = 0; // bandera con la que convertimos numeros a negativo
	
	while(c != '\0'){
		
		int col = Columna(c);
		if(errorCaracterNoPerteneceAlAlfabeto(col,c,i))	return 0;
		e = tt[e][col];
		if(errorLexico(e,i)) return 0;
		if(e == 0){ //si aparece una operacion
		
			//si es una multiplicacion vamos a querer obtener todo el termino
			if(c == '*') if(!multiplicacion(cadena,&i,&e,&c,&termino)) return 0; //si se encuentra un error en la funcion, se retorna falso
			operarTermino(&termino,&result,op); //al terminar de leer un termino operamos
			op = c;
			if(c == '\0') break; //puede ya estar en '\0' debido a la funcion multiplicar
		}
		else convertirCaracter(&termino,c,&neg); //si no, convertimos los caracteres
		c = cadena[++i];
	}
	operarTermino(&termino,&result,op);
	printf("RESULTADO: %d\n",result);
	
	return 1;
	
}
