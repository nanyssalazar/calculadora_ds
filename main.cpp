#include <iostream>
#include <fstream>
using namespace std;

struct nodo{
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
        }
        else{
            ptr = raiz;
            while (true){
                if ((raiz -> izq == NULL and raiz -> der == NULL) or aux -> valor == 1){
                    if(raiz->der != NULL) {
                        if (raiz ->der -> valor == 2 or (raiz -> der -> valor == 3 and aux -> valor >= raiz -> valor)) {
                            // DEBE ENTRAR AQUI EN EL CASO DE MENOR A DER DE RAIZ
                            aux->izq = ptr->der;
                            ptr->der = aux;
                            break;
                        }
                    }
                    aux->izq = raiz;
                    raiz = aux;
                    break;
                }
                else {
                    aux->izq = ptr->der;
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
