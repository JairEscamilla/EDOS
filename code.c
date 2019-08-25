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
void euler(float x0, float y0, int n, float h, Nodo** Inicio);
// FUNCION PRINCIPAL
int main(){
  int n;
  float h, x0, y0;
  Nodo* Inicio = NULL;
  printf("Ingresar x0-> ");
  scanf("%f", &x0);
  printf("Ingresar y0-> ");
  scanf("%f", &y0);
  printf("Ingresar tamaño de salto (h)-> ");
  scanf("%f", &h);
  printf("Ingresar numero de pasos (n)-> ");
  scanf("%d", &n);
  euler(x0, y0, n, h, &Inicio);
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

// Funcion que resuelve la ecuacion diferencial por el metodo de euler
void euler(float x0, float y0, int n, float h, Nodo** Inicio){
  float xaux, yaux;
  agregarNodo(x0, y0, Inicio);
  Nodo* ant = *Inicio;
  for(int i = 0; i < n; i++){
    yaux = ant->y + h*f(ant->x, ant->y);
    xaux = ant->x + h;
    agregarNodo(xaux, yaux, Inicio);
    ant = ant->sig;
  }
}
