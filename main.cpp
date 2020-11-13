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
            if(aux->valor==4){
                datos >> aux->contenido;
                asigna_valor(aux);
            }
            raiz=aux;
        } // aqui si va all lo anterior
        else{
            ptr=raiz;
            while (ptr!=NULL){
                // Checo si el que cree es mayor al nodo ptr donde estoy

                // Si la operacion esta dentro de un parentesis de (, entonces es caso especial
                if (raiz->izq== NULL or raiz->der== NULL or aux->valor<3){
                    if(raiz->der!=NULL) {
                        if (raiz->der->valor == 3 or (raiz->der->valor == 5 and aux->valor >= raiz->valor)) {
                            aux->izq = ptr->der; // DEBE ENTRAR AQUI EN EL CASO DE MENOR A DER DE RAIZ
                            ptr->der = aux;
                            break;
                        }
                    }
                    if(aux->valor==1){
                        // Si se tiene un signo un despues parentesis )
                        break;
                    }
                    if (aux->valor==4){
                        //if (ptr->der!=NULL){
                        if ((ptr->der==NULL or aux->valor>ptr->der->valor) and ptr->valor==5) {
                                aux->contenido = "*";
                                asigna_valor(aux);
                                continue;
                            //}
                        }
                        else{
                            // SE PUEDE SUSTITUIR POR UN BREAK
                            break;
                        }
                    }
                    aux->izq = raiz;
                    raiz = aux; // AQUI ENTRA
                    ptr = ptr->der;
                }
                else if(aux->valor==4){
                    // Si se tiene un numero antes de parentesis
                    if (ptr->der!=NULL){
                        if (aux->valor>ptr->der->valor){
                            aux->contenido = "*";
                            asigna_valor(aux);
                            continue;
                        }
                    }
                    else{
                       // SE PUEDE SUSTITUIR POR UN BREAK
                        break;
                    }
                }
                    // Si es una operación mas importante (mul y division)
                else if (aux->valor>=ptr->valor){
                    // Si a la derecha esta un numero
                    if(ptr->der->valor == 5){
                        aux->izq = ptr->der; // DEBE ENTRAR AQUI EN EL CASO DE MENOR A DER DE RAIZ
                        ptr->der = aux;
                        break;
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
    ptrNodo->valor = 5;
    if (ptrNodo->contenido==")"){
        ptrNodo->valor = 1;
    }
    if (ptrNodo->contenido == "+" or ptrNodo->contenido =="-"){
        ptrNodo->valor = 2;
    }
    if (ptrNodo->contenido =="*" or ptrNodo->contenido=="/"){
        ptrNodo->valor = 3;
    }
    if (ptrNodo->contenido=="("){
        ptrNodo->valor = 4;
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