#include <stdio.h> // Incluyendo bibliotecas
#include <stdlib.h>

// PROTOTIPOS DE FUNCIONES
float f(float x, float y);

// FUNCION PRINCIPAL
int main(){
  int x0, y0, n;
  float h;
  printf("Ingresar x0-> ");
  scanf("%d", &x0);
  printf("Ingresar y0-> ");
  scanf("%d", &y0);
  printf("Ingresar tamaño de salto (h)-> ");
  scanf("%f", &h);
  printf("Ingresar numero de pasos (n)-> ");
  scanf("%d", &n);

  return 0;
}

// DESARROLLANDO LAS FUNCIONES

// Función de ecuacion diferencial
float f(float x, float y){
  return x + y;
}
