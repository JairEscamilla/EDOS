#include <stdio.h> // Incluyendo bibliotecas
#include <stdlib.h>

// Definiendo estructura
typedef struct defNodo{
  float x, y;
  struct defNodo* sig;
}Nodo;

// PROTOTIPOS DE FUNCIONES
float f(float x, float y);
void agregarNodo(float x, float y, Nodo** Inicio);
// FUNCION PRINCIPAL
int main(){
  int x0, y0, n;
  float h;
  Nodo* Inicio = NULL;
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

// Funcion que agrega un nodo a la lista dinamica
void agregarNodo(float x, float y, Nodo** Inicio){
  Nodo* temp = *Inicio;
  Nodo* temp2 = (Nodo*)malloc(sizeof(Nodo));
  temp2->x = x;
  temp2->y = y;
  temp2->sig = NULL;
  if (temp == NULL) {
    *Inicio = temp;
  }else{
    while (temp->sig != NULL) {
      temp = temp->sig;
    }
    temp->sig = temp2;
  }
}
