#ifndef PROTOTIPOS
#define PROTOTIPOS
//Structs
typedef struct _nodo
{
  char* dato;
  struct _nodo* izquierdo; //No
  struct _nodo* derecho; //Si
} nodo;
//Prototipos de funciones

  //Entrada de datos
void Inicio();
int crearPregunta(nodo*);
int respuestas(char*);

 //Arbol binario
nodo* crearArbol(void);
void buscar_personajes(nodo**,nodo**);
void anadirPregunta(nodo**);

  //Lectura de archivos
void obtenerTXT(FILE**);
void abrirTXT(FILE **);
void leerArbol(nodo**, FILE*);
void guardarTXT(FILE*,nodo*);
#endif