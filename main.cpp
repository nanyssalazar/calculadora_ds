#include <iostream>
#include <fstream>
using namespace std;

struct nodo {
    string contenido;
    int valor;
    nodo *izq;
    nodo *der;
};

void preOrden(nodo *ptrNodo);
void inOrden(nodo *ptrNodo);
void postOrden(nodo *ptrNodo);
void asigna_valor(nodo *ptrNodo);

int main(){
    ifstream datos("datos.txt");
    nodo *raiz,*ptr,*aux;
    raiz = NULL;
    cout<<"Datos leidos: ";
    while (!datos.eof()){
        aux = new nodo;
        datos>>aux->contenido; cout<<aux->contenido<<" ";
        asigna_valor(aux);
        aux->izq=NULL; aux->der=NULL;
        if (raiz==NULL){
            raiz=aux;
        } // aqui si va all lo anterior
        else{
            ptr=raiz;
            while (ptr!=NULL){
                // Checo si el que cree es mayor al nodo ptr donde estoy

                // Si la operacion esta dentro de un parentesis de (, entonces es caso especial
                if ((raiz->izq== NULL and raiz->der== NULL) or aux->valor<2){
                    if(raiz->der!=NULL) {
                        if (raiz->der->valor == 2 or (raiz->der->valor == 3 and aux->valor >= raiz->valor)) {
                            aux->izq = ptr->der; // DEBE ENTRAR AQUI EN EL CASO DE MENOR A DER DE RAIZ
                            ptr->der = aux;
                            break;
                        }
                    }
                    aux->izq = raiz;
                    raiz = aux; // AQUI ENTRA
                    break;
                }
                    // Si es una operación mas importante (mul y division)
                else if (aux->valor>=ptr->valor){
                    // Si a la derecha esta un numero
                    if(ptr->der!=NULL){
                        if(ptr->der->valor == 3){
                            aux->izq = ptr->der; // DEBE ENTRAR AQUI EN EL CASO DE MENOR A DER DE RAIZ
                            ptr->der = aux;
                            break;
                        }
                    }
                        // Para agregar el valor al final de las derechas
                    else if (ptr->der==NULL) {
                        ptr->der = aux;
                        ptr = aux;
                    }
                    // para recorrer
                    ptr=ptr->der;
                }
                else {
                    aux->izq = ptr->der; // DEBE ENTRAR AQUI EN EL CASO DE MENOR A DER DE RAIZ
                    ptr->der = aux;
                    break;
                }

            }
        }
    }
    cout<<endl;
    datos.close();
    cout<<"Recorrido preOrden: ";
    preOrden(raiz);
    cout<<endl;
    cout<<"Recorrido inOrden: ";
    inOrden(raiz);
    cout<<endl;
    cout<<"Recorrido postOrden: ";
    postOrden(raiz);
    cout<<endl;
    return 0;
}

void asigna_valor(nodo *ptrNodo){
    // Default
    char contenido = ptrNodo -> contenido[0];
    switch(contenido){
        case '+':
        case '-':
            ptrNodo -> valor = 1;
            break;
        case '*':
        case '/':
            ptrNodo -> valor = 2;
            break;
        default:
            ptrNodo -> valor = 3;
    }
    cout << "Valor: " << ptrNodo->valor << " ";
}

void preOrden(nodo *ptrNodo){
    if (ptrNodo!=NULL){
        cout<<ptrNodo->contenido<<" ";
        preOrden( ptrNodo->izq );
        preOrden( ptrNodo->der );
    }

}

void inOrden(nodo *ptrNodo){
    if (ptrNodo!=NULL) {
        inOrden(ptrNodo->izq);
        cout<<ptrNodo->contenido<<" ";
        inOrden(ptrNodo->der);
    }
}

void postOrden(nodo *ptrNodo){
    if (ptrNodo!=NULL) {
        postOrden( ptrNodo->izq );
        postOrden( ptrNodo->der );
        cout<<ptrNodo->contenido<<" ";
    }
}
