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
void asigna_tipo(nodo *ptrNodo);
void replaceNodo(float contenido, nodo *ptrNodo);
float resultado;

int main(){
    ifstream datos("datos.txt");
    nodo *raiz,*ptr,*aux, *raizDer;
    raiz = NULL;
    char dataChar;
    datos >> dataChar;
    string concatStr;
    cout<<"Datos leidos: ";

    while (!datos.eof()){
        aux = new nodo;
        // concatena chars hasta que encuentre un operador o se termine de leer el archivo
        concatStr.clear();
        do{
            concatStr += dataChar;
            datos >> dataChar;
        }while(isdigit(dataChar) and isdigit(concatStr[0]) and !datos.eof());

        aux -> contenido = concatStr; cout << aux -> contenido << " ";
        asigna_tipo(aux);
        aux -> izq= NULL; aux -> der= NULL;

        if(!raiz){
            raiz=aux;
        }else{
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
    cout<<"Resultado con recorrido postOrden: ";
    while(raiz -> izq && raiz -> der){postOrden(raiz);}
    cout << raiz -> contenido;
    return 0;
}

void asigna_tipo(nodo *ptrNodo){
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
        postOrden(ptrNodo->izq);
        postOrden(ptrNodo->der);
        // si es un operador y sus hojas son digitos
        if(ptrNodo -> tipo != 3 and ptrNodo -> izq -> tipo == 3 and ptrNodo -> der -> tipo == 3) {
            float izq = stof(ptrNodo->izq->contenido); float der = stof(ptrNodo->der->contenido);
            // se hace la operacion con las hojas del nodo
            switch (ptrNodo->contenido[0]) {
                case '*':
                    resultado = izq * der;
                    replaceNodo(resultado, ptrNodo);
                    break;
                case '+':
                    resultado = izq + der;
                    replaceNodo(resultado, ptrNodo);
                    break;
                case '-':
                    resultado = izq - der;
                    replaceNodo(resultado, ptrNodo);
                    break;
                case '/':
                    if (!ptrNodo->der->der) { resultado = izq / der; }
                    else { resultado = der / izq; }
                    replaceNodo(resultado, ptrNodo);
                    break;
            }
            //reinicia el contador
            digitos = 0;
        }
    }
}

// convierte strings a integers
int toInt(string s){
    int a;
    try{ a = stoi(s); } catch (...){}
    return a;
}

// reemplaza el nodo
void replaceNodo(float contenido, nodo *ptrNodo){
    ptrNodo -> contenido = to_string(contenido);
    asigna_tipo(ptrNodo);
    ptrNodo -> izq = NULL; ptrNodo -> der = NULL;
}
