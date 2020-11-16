#include <iostream>
#include <fstream>
using namespace std;

struct nodo{
    string contenido;
    int tipo;
    nodo *izq;
    nodo *der;
};

void preOrden(nodo *ptrNodo);
void inOrden(nodo *ptrNodo);
void postOrden(nodo *ptrNodo);
void asigna_valor(nodo *ptrNodo);

int main(){
    ifstream datos("datos.txt");
    nodo *raiz,*ptr,*aux, *raizDer;
    raiz = NULL;
    cout<<"Datos leidos: ";
    while (!datos.eof()){
        aux = new nodo;
        datos>>aux->contenido; cout<<aux->contenido<<" ";
        asigna_valor(aux);
        aux->izq=NULL; aux->der=NULL;

        if(!raiz){
            raiz=aux;
        }
        else{
            ptr = raiz;
            // si es suma, resta o la raiz no tiene elementos a los lados
            if(aux -> tipo == 1 or (!raiz -> izq and !raiz -> der)){
                raizDer = raiz -> der;
                // si hay elemento a la derecha de la raiz
                if(raizDer and (raizDer -> tipo == 2 or (raizDer -> tipo == 3 and raiz -> tipo == 1))){
                    aux -> izq = ptr -> der;
                    ptr -> der = aux;
                }else{
                    aux -> izq = raiz;
                    raiz = aux;
                }
            }else{
                while(ptr){
                    if(!ptr -> der){
                        ptr -> der = aux;
                        break;
                    // si el elemento a la derecha es un numero
                    }else if(ptr -> der -> tipo == 3){
                        aux -> izq = ptr -> der;
                        ptr -> der = aux;
                        break;
                    }else{
                        ptr = ptr -> der;
                    }
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
    // str a char para efectuar switch
    char contenido = ptrNodo -> contenido[0];
    switch(contenido){
        case '+':
        case '-':
            ptrNodo -> tipo = 1;
            break;
        case '*':
        case '/':
            ptrNodo -> tipo = 2;
            break;
        default:
            ptrNodo -> tipo = 3;
    }
    cout << "Valor: " << ptrNodo->tipo << " ";
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
