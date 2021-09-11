#include <stdio.h>
#include <string.h>
int Columna (int);
void analizarCadena (char *);

int tt[8][6] = {{1,2,3,1,7,7}, //D|S|0|Oct|H|x
				{1,7,1,1,7,7},
				{1,7,7,1,7,7},
				{7,7,4,4,7,5},
				{7,7,4,4,7,7},
				{6,7,6,6,6,7}, // estados finales: 1, 4 y 6
				{6,7,6,6,6,7},
				{7,7,7,7,7,7}}; //7 es el estado de rechazo

int main () {

	char s[] = "45&+45&-86&-052&047&028&0x45F&0x69D&0x44H&00x0d5&0x0&00&0";
	
	analizarCadena(s);
	
	return 0;
}

int octal(char c){
	if(c > 48 && c < 56) return 1;
	return 0;
}
int signo(char c){
	if(c == 43 || c == 45) return 1;
	return 0;
}
int decimal(char c){
	if(c > 48 && c < 58) return 1;
	return 0;
}
int letraHexa(char c){
	if((c > 96 && c < 103)||(c > 64 && c < 71)) return 1;
	return 0;
}


int Columna(int c) {
	
	if(octal(c)) return 3;
	
	if(decimal(c)) return 0;
	
	if(signo(c)) return 1;
	
	if(c == '0') return 2;
	
	if(letraHexa(c)) return 4;
	
	if(c == 'x') return 5;
	
	return 6;
	
}

void aumentarContador(int e, int *contadorDecimales,int *contadorOctales,int *contadorHexadecimales,int *contadorErroresLexicos){
	switch(e){
		case 1: //si el estado final fue el de un numero decimal
			(*contadorDecimales)++;
			break;
		case 3:
			(*contadorDecimales)++;
			break;			
		case 4: // si el estado final fue el de un numero octal
			(*contadorOctales)++;
			break;
		case 6: // si el estado final fue el de un numero hexadecimal
			(*contadorHexadecimales)++;
			break;
		default:
			(*contadorErroresLexicos)++;
			break;
	}
}

void analizarCadena (char *cadena)
{
	
	int contadorDecimales = 0;
	int contadorHexadecimales = 0;
	int contadorOctales = 0;
	int contadorErroresLexicos = 0;
		
	const char delim[2] = "&";
	char *token = strtok(cadena,delim);

	int e = 0; 
	
	while(token != NULL){
		e = 0; 
		unsigned int i = 0; 
		int c = token[0];
		
		while (c != '\0')
		{
			e = tt[e][Columna(c)];
			c = token[++i];
		}

		token = strtok(NULL,delim);
		aumentarContador(e,&contadorDecimales,&contadorOctales,&contadorHexadecimales,&contadorErroresLexicos);
	}
	
	printf("Cant. de decimales ----------> %d\n",contadorDecimales);
	printf("Cant. de octales ------------> %d\n",contadorOctales);
	printf("Cant. de hexadecimales ------> %d\n",contadorHexadecimales);
	printf("Cant. de errores lexicos ----> %d\n",contadorErroresLexicos);
}
