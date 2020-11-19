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
    if(!datos){
        cout << "No se encontro datos.txt";
        return 0;
    }
    nodo *raiz,*ptr,*aux;
    raiz = NULL;
    string concatStr;
    char dataChar;
    datos >> dataChar;
    cout << "Datos leidos: ";

    while (!datos.eof()){
        aux = new nodo;
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
            if(aux -> tipo < 3 or (!raiz -> izq and !raiz -> der))
            {
                if(raiz -> der and raiz -> tipo == 1 and aux -> tipo == 2){
                    aux -> izq = ptr -> der;
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

    datos.close();
    cout << endl;

    postOrden(raiz);
    if(raiz){
        cout << "Resultado con recorrido postOrden: ";
        cout << raiz -> contenido;
    }
    else{
        cout << "No se encontraron operaciones.";
    }

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
