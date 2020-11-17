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


int main() {
    string operacion;
    int i(0);
    bool x, exists2;
    string operadores2 [4] = {"+","-","*","/"};
    ifstream datos("datos.txt");
    nodo *raiz, *ptr, *aux;
    raiz = NULL;
    cout << "Datos leidos: ";
    while (!datos.eof()) {
        datos >> operacion;
        cout << operacion << endl;
    }
    string array[operacion.length()];
    for (i=0;i<operacion.length();i++){
        array[i] = operacion[i];
    }
    i=0;
    while (i < operacion.length()) {
        aux = new nodo;
        exists2 = find(begin(operadores2), end(operadores2), array[i]) != end(operadores2);
        while (!exists2 and i<operacion.length()) {
            aux->contenido.append(array[i]);
            i++;
            exists2 = find(begin(operadores2), end(operadores2), array[i]) != end(operadores2);
            if(exists2){
                i--;
            }
            x=true;
        }
        if (!x){
            aux->contenido = array[i];}
        asigna_valor(aux);
        aux->izq = NULL;
        aux->der = NULL;

        if (raiz == NULL) {
            raiz = aux;
        } else {
            ptr = raiz;
            if (aux->valor == 1 or (raiz->izq == NULL and raiz->der == NULL)) {
                if (raiz->der == NULL) {
                    aux->izq = raiz;
                    raiz = aux;
                } else if (raiz->der->valor == 2 or (raiz->der->valor == 3 and aux->valor >= raiz->valor)) {
                    aux->izq = ptr->der;
                    ptr->der = aux;
                } else {
                    aux->izq = raiz;
                    raiz = aux;
                }
            } else {
                while (ptr != NULL) {
                    if (ptr->der == NULL) {
                        ptr->der = aux;
                        break;
                    } else if (ptr->der->valor == 3) {
                        aux->izq = ptr->der;
                        ptr->der = aux;
                        break;
                    } else {
                        ptr = ptr->der;
                    }
                }
            }
        }
        i++;
        x = false;
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
