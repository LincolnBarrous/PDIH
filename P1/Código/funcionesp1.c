#include<dos.h>
#include<string.h>
#include<stdio.h>
#define BYTE unsigned char

BYTE letra=15; //variable con el color blanco de la letra
BYTE fondo=0; //variable con el color negro de fondo de letra

int numero_filas_texto=25; 

//Funcion gotoxy()
//coloca el cursor en una posición determinada
void gotoxy(int x, int y){
  union REGS inregs, outregs;
  
  inregs.h.dh=y;
  inregs.h.dl=x;
  inregs.h.ah=0x02;
  inregs.h.bh=0x00;

  int86(0x10, &inregs, &outregs);
}

//Funcion setcursortype()
//fijar el aspecto del cursor, debe admitir tres valores: 1:INVISIBLE, 2:NORMAL y 3:GRUESO.
void setcursortype(int tipo){

  union REGS inregs, outregs;
 
  switch (tipo)
	{

    case 1:
				inregs.h.ch=010;
    		inregs.h.cl=000;
        break;
    case 2:
				inregs.h.ch=010;
    		inregs.h.cl=010;
        break;
    case 3:
				inregs.h.ch=000;
    		inregs.h.cl=010;
        break;
    default:
    		printf("Tipo no permitido ");
    	
	}

  inregs.h.ah=0x01;

  int86(0x10, &inregs, &outregs);

}

//Funcion setvidemode()
//fija el modo de video deseado
void setvideomode(BYTE mode){
  union REGS inregs, outregs;
  
  inregs.h.ah = 0x00;
  inregs.h.al = mode;
  
  int86(0x10,&inregs,&outregs);
}

//Funcion getvideomode()
//obtiene el modo de video actual
int getvideomode(){
  union REGS inregs, outregs;
  
  inregs.h.ah = 0x0F;
  
  int86(0x10,&inregs,&outregs);
  
  return outregs.h.al;
}

//Funcion textcolor()
//modifica el color de primer plano con que se mostrarán los caracteres
void textcolor(int color){
  letra=color;
}

//Funcion textbackground()
//modifica el color de fondo con que se mostrarán los caracteres
void textbackground(int color){
  fondo=color;
}

//Funcion clrsrc
//borra toda la pantalla
void clrsrc(){
  union REGS inregs, outregs;
  
  inregs.h.ah = 0x06;
  inregs.h.al = 0x00;
  inregs.h.bh = fondo_c;
  inregs.h.ch = 0x00;
  inregs.h.cl = 0x00;
  inregs.h.dh = getfilas()-1;
  inregs.h.dl = getcolumnas()-1;

  int86(0x10,&inregs,&outregs);

  gotoxy(0,getfilas());

}

//Funcion cputchar()
//escribe un carácter en pantalla con el color indicado actualmente
void cputchar(char caracter){
  union REGS inregs, outregs;

  BYTE color_fondo_byte;
  BYTE color_final;

  color_fondo_byte = fondo;

  color_fondo_byte = color_fondo_byte << 4;

  color_final = color_fondo_byte | letra;

  inregs.h.ah = 0x09;
  inregs.h.al = caracter;
  inregs.h.bl = color_final;
  inregs.h.bh = 0x00;
  inregs.x.cx = 1;
  
  int86(0x10, &inregs, &outregs);
}

//Funcion getche()
//obtiene un carácter de teclado y lo muestra en pantalla
void getche(int imprimir){
  union REGS inregs, outregs;
  char caracter;

  inregs.h.ah = 0x01;
  
  int86(0x21, &inregs, &outregs);

  caracter = outregs.h.al;

  if(imprimir == 1){
    printf("\nCaracter pulsado: ");
    cputchar(caracter);
  }
}


//obtener numero filas 
int getfilas(){

  return numero_filas_texto;
}

//obtener numero columnas
int getcolumnas(){
  union REGS inregs, outregs;
  int n_columnas;

  inregs.h.ah = 0x0F;

  int86(0x10,&inregs,&outregs);

  n_columnas = outregs.h.ah;

  return n_columnas;
}