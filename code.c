#include <stdio.h> // Incluyendo bibliotecas
#include <stdlib.h>
#include <math.h>



// PROTOTIPOS DE FUNCIONES
float f(float x, float y);
void euler(float x0, float y0, int n, float h);
float* generarArreglo(int cant);
float** generarMatriz(int ancho, int alto);
void pedirCoeficientes(float* valoresInicialesx, float* valoresInicialesy, int orden);
void valoresUT(float* ut, int orden);
void liberarMemoria(float* arr);
void liberarMemoriaMat(float** matriz, int alto);
void llenarMatriz(float** Matriz, int orden, float coeficientes[]);
void plot();
// FUNCION PRINCIPAL
int main(){
  int n, orden;
  float h, x0, y0, *valoresNuevos, *valoresInicialesy, *valoresInicialesx, *uT, **Matriz;
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
    valoresInicialesx = generarArreglo(orden);
    valoresInicialesy = generarArreglo(orden);
    uT = generarArreglo(orden);
    Matriz = generarMatriz(orden, orden);
    pedirCoeficientes(valoresInicialesx, valoresInicialesy, orden);
    valoresUT(uT, orden);
    llenarMatriz(Matriz, orden, valoresInicialesy);
    liberarMemoria(valoresNuevos);
    liberarMemoria(valoresInicialesx);
    liberarMemoria(valoresInicialesy);
    liberarMemoria(uT);
    liberarMemoriaMat(Matriz, orden);
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

float** generarMatriz(int ancho, int alto){
  float **Matriz = (float**)malloc(alto*sizeof(float*)); // Columnas
    for(int i = 0; i < alto; i++)
      Matriz[i] = (float*)malloc(ancho*sizeof(float)); // Filas
  return Matriz;
}

void pedirCoeficientes(float* valoresInicialesx, float* valoresInicialesy, int orden){
  for(int i = 0; i < orden; i++){
    printf("Ingresar x%d inicial-> ", i);
    scanf("%f", &valoresInicialesx[i]);
    printf("Ingresar y%d inicial-> ", i);
    scanf("%f", &valoresInicialesy[i]);
  }
}

void valoresUT(float* ut, int orden){
  for(int i = 0; i < orden; i++){
    if(i == orden-1)
      ut[i] = 1;
    else
      ut[i] = 0;
  }
}

void llenarMatriz(float** Matriz, int orden, float coeficientes[]){
  for(int i = 0; i < orden - 1; i++){
    for(int j = 0; j < orden; j++){
      Matriz[i][j] = 0;
    }
  }
  for(int i = 0; i < orden; i++)
    Matriz[i][i+1] = 1;
  for(int i = 0; i < orden; i++){
    Matriz[orden-1][i] = coeficientes[i];
  }

  /*for(int i = 0; i < orden; i++){
    for(int j = 0; j < orden; j++){
      printf("%f ", Matriz[i][j]);
    }
    printf("\n");
  }*/

}

void liberarMemoria(float* arr){
  free(arr);
}
void liberarMemoriaMat(float** matriz, int alto){
  for(int i = 0; i < alto; i++)
    free(matriz[i]);// Filas
  free(matriz); // Columnas
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
