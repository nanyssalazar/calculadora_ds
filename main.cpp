#include <iostream>
#include <fstream>
using namespace std;

struct nodo{
    string contenido;
    int tipo;
    nodo *izq;
    nodo *der;
};

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
    cout << endl << "Datos leidos: ";

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
        }
        else{
            ptr = raiz;
            // si es suma, resta o la raiz no tiene elementos a los lados
            if(aux -> tipo < 3 or (!raiz -> izq and !raiz -> der))
            {
                raizDer = raiz -> der;
                // si hay elemento a la derecha de la raiz
                if(raizDer and (raizDer -> tipo == 3 or aux->tipo >= raizDer->tipo) and raiz -> tipo == 1 and aux->tipo== 2){
                    aux -> izq = ptr -> der; // este if se puede comentar
                    ptr -> der = aux;
                }
                else{
                    aux -> izq = raiz;
                    raiz = aux;
               }
            }
            else{
                while(ptr != aux){
                    if(!ptr -> der){ptr -> der = aux;}
                    ptr = ptr -> der;
                }
            }
        }
    }

    cout << endl;
    datos.close();
    cout << "Resultado con recorrido postOrden: ";
    postOrden(raiz);
    cout << raiz -> contenido << endl;
    return 0;
}

void asigna_tipo(nodo *ptrNodo){
    if (ptrNodo->contenido == "+" or ptrNodo->contenido == "-" and !ptrNodo -> contenido[1]){
        ptrNodo->tipo = 1;
    }
    else if (ptrNodo -> contenido =="*" or ptrNodo -> contenido=="/"){
        ptrNodo->tipo = 2;
    }
    else{
        ptrNodo -> tipo = 3;
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
                    resultado = izq / der;
                    replaceNodo(resultado, ptrNodo);
                    break;
            }
        }
    }
}

// reemplaza el nodo
void replaceNodo(float contenido, nodo *ptrNodo){
    ptrNodo -> contenido = to_string(contenido);
    asigna_tipo(ptrNodo);
    ptrNodo -> izq = NULL; ptrNodo -> der = NULL;
}
