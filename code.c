#include <stdio.h> // Incluyendo bibliotecas
#include <stdlib.h>
#include <math.h>


typedef enum defErrores{
  TODOBIEN, INGRESO_CADENA, INGRESO_CARCTER_INCORRECTO
}Errores;


// PROTOTIPOS DE FUNCIONES
float f(float x, float y);
void euler(float x0, float y0, int n, float h);
float* generarArreglo(int cant);
float** generarMatriz(int ancho, int alto);
void pedirValoresIniciales(float* valoresInicialesx, float* valoresInicialesy, int orden);
void valoresUT(float* ut, int orden);
void liberarMemoria(float* arr);
void liberarMemoriaMat(float** matriz, int alto);
void llenarMatriz(float** Matriz, int orden, float coeficientes[]);
void resolverEcuacion(float** Matriz, float* valoresInicialesy, float* valoresInicialesx, float* uT, float h, int n, int orden);
float* multiplicarMatrices(float** Matriz1, float* Matriz2, int orden);
float* matrizporEscalar(float* ut, float h, float x, float y, int orden);
void pedirCoeficientes(float* coeficientes, int orden);
float* sumarVectores(float* v1, float* v2, int orden);
void verificarErrores(Errores error[], int cantidad);
void plot();


// FUNCION PRINCIPAL
int main(){
  Errores error[5];
  int n, orden;
  float h, x0, y0, *valoresNuevos, *valoresInicialesy, *valoresInicialesx, *uT, **Matriz, *coeficientes;
  printf("Ingresar el orden de la EDO-> ");
  error[0] = scanf("%d", &orden);
  printf("Ingresar tamaño de salto (h)-> ");
  error[1] = scanf("%f", &h);
  printf("Ingresar numero de pasos (n)-> ");
  error[2] = scanf("%d", &n);
  if(orden == 1){
    printf("Ingresar x0-> ");
    error[3] = scanf("%f", &x0);
    printf("Ingresar y0-> ");
    error[4] = scanf("%f", &y0);
    verificarErrores(error, 5);
    printf("Espere un momento mientras se calcula la solucion... \n");
    euler(x0, y0, n, h);
    printf("Ejecucion terminada... \n");
  }else{
    valoresInicialesx = generarArreglo(orden);
    valoresInicialesy = generarArreglo(orden);
    coeficientes = generarArreglo(orden);
    uT = generarArreglo(orden);
    Matriz = generarMatriz(orden, orden);
    pedirValoresIniciales(valoresInicialesx, valoresInicialesy, orden);
    pedirCoeficientes(coeficientes, orden);
    valoresUT(uT, orden);
    llenarMatriz(Matriz, orden, coeficientes);
    resolverEcuacion(Matriz, valoresInicialesy, valoresInicialesx, uT, h, n, orden);
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
  return cos(x);
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

void pedirValoresIniciales(float* valoresInicialesx, float* valoresInicialesy, int orden){
  Errores er[orden*2];
  int cont = 0;
  for(int i = 0; i < orden; i++){
    printf("Ingresar x%d inicial-> ", i);
    er[cont] = scanf("%f", &valoresInicialesx[i]);
    cont++;
    printf("Ingresar y%d inicial-> ", i);
    er[cont] = scanf("%f", &valoresInicialesy[i]);
    cont++;
  }
  verificarErrores(er, orden*2);
}

void valoresUT(float* ut, int orden){
  for(int i = 0; i < orden; i++){
    if(i == orden-1)
      ut[i] = 1;
    else
      ut[i] = 0;
  }
}

void resolverEcuacion(float** Matriz, float* valoresInicialesy, float* valoresInicialesx, float* uT, float h, int n, int orden){
  FILE* fp = fopen("solucion.dat", "wt");
  fprintf(fp, "%f, %f\n", valoresInicialesx[orden-1], valoresInicialesy[orden-1]);
  for(int i = 0; i < n; i++){
    valoresInicialesy = sumarVectores(multiplicarMatrices(Matriz, valoresInicialesy, orden), matrizporEscalar(uT, h, valoresInicialesx[orden-1], valoresInicialesy[orden-1], orden), orden);
    for(int j = 0; j < orden; j++){
      valoresInicialesx[j] = valoresInicialesx[j] + h;
    }
    fprintf(fp, "%f, %f\n", valoresInicialesx[orden-1], valoresInicialesy[orden-1]);
  }
  fclose(fp);
}


float* multiplicarMatrices(float** Matriz1, float* Matriz2, int orden){
  float contador = 0;
  float* resultado = generarArreglo(orden);
  for(int i = 0; i < orden; i++){
    contador = 0;
    for(int j = 0; j < orden; j++){
      contador+= Matriz1[i][j] * Matriz2[j];
    }
    resultado[i] = contador;
  }
  return resultado;
}

void verificarErrores(Errores error[], int cantidad){
  int err = 0;
  for(int i = 0; i < cantidad; i++){
    if(error[i] == 0)
      err = 1;
  }
  if(err){
    printf("\nHa ocurrido el error con codigo: %d\n", error[err]);
    exit(0);
  }
}

float* matrizporEscalar(float* ut, float h, float x, float y, int orden){
  float *resultados = generarArreglo(orden);
  for(int i = 0; i < orden; i++){
    resultados[i] = ut[i]*h*f(x, y);
  }
  return resultados;
}

float* sumarVectores(float* v1, float* v2, int orden){
  float* resultado = generarArreglo(orden);
  for(int i = 0; i < orden; i++){
    resultado[i] = v1[i] + v2[i];
  }
  return resultado;
}

void pedirCoeficientes(float* coeficientes, int orden){
  Errores er[orden];
  for(int i = 0; i < orden; i++){
    printf("Ingresar el coeficiente a%d-> ", i);
    er[i] = scanf("%f", &coeficientes[i]);
  }
  verificarErrores(er, orden);
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
                                "plot \"solucion.dat\" with lines",
                                "set autoscale",
                                "replot"
                               };
  FILE * ventanaGnuplot = popen ("gnuplot -persist", "w");
  for (int i=0; i < 4; i++){
    fprintf(ventanaGnuplot, "%s \n", configGnuplot[i]);
  }
}
