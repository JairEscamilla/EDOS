#include <stdio.h> // Incluyendo bibliotecas
#include <stdlib.h>
#include <math.h>



// PROTOTIPOS DE FUNCIONES
float f(float x, float y);
void euler(float x0, float y0, int n, float h);
float* generarArreglo(int cant);
void liberarMemoria(float* arr);
void plot();
// FUNCION PRINCIPAL
int main(){
  int n, orden;
  float h, x0, y0, *valoresNuevos, *valoresIniciales, *uT;
  printf("Ingresar el orden de la EDO-> ");
  scanf("%d", &orden);
  printf("Ingresar tamaño de salto (h)-> ");
  scanf("%f", &h);
  printf("Ingresar numero de pasos (n)-> ");
  scanf("%d", &n);
  if(orden == 1){
    printf("Ingresar x0-> ");
    scanf("%f", &x0);
    printf("Ingresar y0-> ");
    scanf("%f", &y0);
    printf("Espere un momento mientras se calcula la solucion... \n");
    euler(x0, y0, n, h);
    printf("Ejecucion terminada... \n");
  }else{
    valoresNuevos = generarArreglo(orden);
    valoresIniciales = generarArreglo(orden);
    uT = generarArreglo(orden);

    liberarMemoria(valoresNuevos);
    liberarMemoria(valoresIniciales);
    liberarMemoria(uT);
  }
  plot();
  return 0;
}

// DESARROLLANDO LAS FUNCIONES

// Función de ecuacion diferencial
float f(float x, float y){
  return x + 3*y;
}



// Funcion que resuelve la ecuacion diferencial por el metodo de euler
void euler(float x0, float y0, int n, float h){
  FILE* fp = fopen("solucion.dat", "wt");
  float xaux, yaux, anty= y0, antx= x0;
  fprintf(fp, "%f, %f\n", antx, anty);
  for(int i = 0; i < n; i++){
    yaux = anty + h*f(antx, anty);
    xaux = antx + h;
    antx = xaux;
    anty = yaux;
    fprintf(fp, "%f, %f\n", xaux, yaux);
  }
  fclose(fp);
}


//  plot exp(x)*(-x*exp(-x)-exp(-x)+2), "solucion.dat" with lines

float* generarArreglo(int cant){
  return (float*)malloc(cant*sizeof(float));
}

void liberarMemoria(float* arr){
  free(arr);
}

// Función que gráfica el archivo de texto generado
void plot(){
  char * configGnuplot[] = {"set title \"Solucion a la ecuación diferencial\"",
                                "set ylabel \"Y\"",
                                "set xlabel \"X\"",
                                "plot \"solucion.dat\" with lines"
                               };
  FILE * ventanaGnuplot = popen ("gnuplot -persist", "w");
  for (int i=0; i < 4; i++){
    fprintf(ventanaGnuplot, "%s \n", configGnuplot[i]);
  }
}
