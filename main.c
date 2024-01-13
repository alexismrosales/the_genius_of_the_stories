#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
int main() {
  Inicio();
  return 0; 
}
//Funciones de entrada de datos
void Inicio()
{
  char resp[2];
  int respn; 
  nodo * raiz;
  nodo * secundario;
  FILE * archivo;
  FILE * archivoG;
  do{
    printf("---------------------THE GENIUS OF THE STORIES---------------------\n");
    do
    {
      printf("Deseas cargar las preguntas de un archivo de texto? Si/No\n");
      scanf(" %s",resp);
      respn = respuestas(resp);
      if(respn)
      {
        obtenerTXT(&archivo);
        leerArbol(&raiz,archivo);
        fclose(archivo);
        printf("Archivo abierto correctamente...\n");
        break;
      }
      else if (respn == 0)
      {
        printf("Se creara un documento nuevo!...\n");
        raiz = crearArbol();
        break;
      }
      else{
        printf("El dato introducido es invalido, vuelva a intentarlo...\n");
      }
    } while (respn == 0 || respn != 1);
    system("cls");
    printf("-------THE GENIUS OF THE STORIES-------\n");
    char nombretxt[20];
    while (1)
    {
      buscar_personajes(&raiz,&secundario);
      
      if(crearPregunta(secundario) == 1)
        printf("He ganado! B) \n");
      else{
          printf("He perdido esta vez! :(\n");\
          anadirPregunta(&secundario);
      }
      printf("El documento se guardara, introduce el nombre que deseas para el archivo(sin espacios) agregando la extension .txt:\n");
      scanf("%s",nombretxt);
      archivoG = fopen(nombretxt,"w");
      guardarTXT(archivoG,raiz);
      fclose(archivoG);
      printf("Te gustaria volver a jugar? Si/No\n");
      scanf("%s",resp);
      if(respuestas(resp) == 0 || respuestas(resp) == 1)
        break;
    }
    free(raiz);
    free(secundario);
    system("cls");
  }while (respuestas(resp) == 1);
   printf("-------THE GENIUS OF THE STORIES-------\n");
  printf("Gracias por jugar!\n");
}

int crearPregunta(nodo* n)
{
  char respuestaU[2];
  int respuestaUn;
  printf("-Tu personaje es %s?-Si/No\n",n->dato);
  scanf(" %s",respuestaU);
  respuestaUn=respuestas(respuestaU);
  if(respuestaUn == 0)
    return 0;
  else if(respuestaUn == 1)
     return 1;
  else if(respuestaUn != 0 || respuestaUn != 1)
  {
    printf("La respuesta introducida es invalida, vuelva a intentarlo...\n");
    crearPregunta(n);
  }
}

int respuestas(char respuesta[2])
{    
    int i;
    for(i = 0; i < 2; i++)
      respuesta[i] = tolower(respuesta[i]);
    if(strcmp(respuesta,"si") == 0)
      return 1;
    else if(strcmp(respuesta,"no") == 0)
      return 0;
    else
      return -1;
}

//Funciones del arbol binario y agregar preguntas
nodo* crearArbol(void)
{
  
  nodo* raiz = malloc(sizeof(nodo)); //Pregunta default
  nodo* ramaDer = malloc(sizeof(nodo)); //En caso de que la respuesta sea si
  nodo* ramaIzq = malloc(sizeof(nodo)); //En caso de que la respuesta sea n
 
  ramaDer->dato = "Blanca nieves";
  ramaDer->derecho = NULL;
  ramaDer->izquierdo = NULL;

  ramaIzq->dato = "El rey leon";
  ramaIzq->derecho = NULL;
  ramaIzq->izquierdo = NULL;

  raiz->dato = "Tu personaje es humano?";
  raiz->derecho = ramaDer;
  raiz->izquierdo = ramaIzq;
  
  return raiz;
}

void buscar_personajes(nodo** principal, nodo** ultimo)
{
  *ultimo = *principal;
  int respuestaUn;
  char respuestaU[2];
  int i;
  if((*principal)->derecho == NULL  && (*principal)->izquierdo == NULL)
        return;
  else
  {
      printf("- %s - Si/No\n", (*principal)->dato);
      scanf("%s",respuestaU);
      respuestaUn=respuestas(respuestaU);
      if(respuestaUn == 0) //Si responde que no ira a la rama izquierda
         buscar_personajes(&((*principal)->izquierdo),&(*ultimo));
      else if(respuestaUn == 1) //En caso contrario a la derecha
        buscar_personajes(&((*principal)->derecho),&(*ultimo));
      else
      {
        printf("La respuesta introduccida es invalida, vuelva a intentarlo...\n");
        buscar_personajes(&(*principal),&(*ultimo));
      }
  }
}

void anadirPregunta(nodo** n)
{
  nodo* ramaDer = malloc(sizeof(nodo));
  nodo* ramaIzq = malloc(sizeof(nodo));
  fflush(stdin);
  char referencia[150], personaje[150];
  printf("He perdido, pero quisiera saber en que personaje estas pensando para poder memorizarlo para la proxima vez. \nEn que personaje estas pensando? \n");
  scanf("%[^\n]",personaje);
  fflush(stdin);
  printf("Para ayudar a mejorar al genio, puedes ayudarnos introduciendo una pregunta cerrada que diferencie a  %s y %s: \n",personaje,(*n)->dato);
  scanf("%[^\n]",referencia);
  fflush(stdin);
  
  ramaDer->dato =strdup(personaje);
  ramaDer->derecho = NULL;
  ramaDer->izquierdo = NULL;

  ramaIzq->dato = strdup((*n)->dato);
  ramaIzq->derecho = NULL;
  ramaIzq->izquierdo = NULL;

  
  (*n)->izquierdo = ramaIzq;
  (*n)->derecho = ramaDer;
  (*n)->dato = strdup(referencia);
   
}

//Funciones lectura y escritura de texto
void obtenerTXT(FILE ** txt)
{
  char archivo[50];
  printf("Introduzca el nombre del archivo seguido con la extension .txt\n");
  scanf("%s",archivo);
  *txt = fopen(archivo,"r+");
  
  if(*txt == NULL)
  {
    printf("El archivo es invalido...\n");
    obtenerTXT(txt); 
  }
  else
    return;
}

void abrirTXT(FILE ** txt)
{
  char archivo[50];
  printf("El documento se guardara, introduce el nombre que deseas para el archivo(sin espacios) agregando la extension .txt:\n");
  scanf("%s",archivo);
  *txt = fopen(archivo,"w");
}

void guardarTXT(FILE* txt,nodo* n)
{
  char buffer[100];
  if(n == NULL)
    fprintf(txt,"*\n");
  else
  {
    strcat(strcpy(buffer,n->dato),"\n");
    fputs(buffer,txt); 
    //printf("Esto se va a guardar: %s\n",n->dato);
    guardarTXT(txt,n->derecho);
    guardarTXT(txt,n->izquierdo);
  }
}

void leerArbol(nodo** n, FILE* txt)
{
  char dato[150];
  fgets(dato, 150, txt);
  if(dato[0] != '*')
  {
    dato[strlen(dato)-1] = '\0';
    *n = malloc(sizeof(nodo));
    (*n)->dato = strdup(dato);
    //printf("%s\n",(*n)->dato); Datos que se guardaran en el nodo
    leerArbol(&((*n)->derecho),txt);
    leerArbol(&((*n)->izquierdo),txt);
  }
  else
    *n = NULL;
}