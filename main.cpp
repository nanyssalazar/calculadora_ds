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

int main() {
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
        // Concatena caracteres mientras no sea un operador
        do{
            concatStr += dataChar;
            datos >> dataChar;
        }while(isdigit(dataChar) and isdigit(concatStr[0]) and !datos.eof());

        // Asigna contenido y valor al nodo creado
        aux -> contenido = concatStr; cout << aux -> contenido << " ";
        asigna_tipo(aux);
        aux -> izq= NULL; aux -> der= NULL;

        // Se crea la raiz
        if(!raiz){
            raiz=aux;
        }
        // Si ya hay raiz
        else{
            ptr = raiz;
            // Si el contenido es un operador y no se tienen hojas
            if(aux -> tipo < 3 or (!raiz -> izq and !raiz -> der))
            {
                // Si la raiz es una suma o resta y el nuevo nodo es una mul o div
                if(raiz -> der and raiz -> tipo == 1 and aux -> tipo == 2){
                    aux -> izq = ptr -> der;
                    ptr -> der = aux;
                }
                // Si es un operador de menor jerarquia
                else{
                    aux -> izq = raiz;
                    raiz = aux;
               }
            }
            else{
                // Si es un numero se agrega a la derecha del ultimo nodo
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

// Asigna tipo segun la jerarquia de operaciones
void asigna_tipo(nodo *ptrNodo){
    if (ptrNodo->contenido == "+" or ptrNodo->contenido == "-" and !ptrNodo -> contenido[1]){
        ptrNodo->tipo = 1;
    }
    else if (ptrNodo -> contenido =="*" or ptrNodo -> contenido=="/"){
        ptrNodo->tipo = 2;
    }
    // Los numeros se toman como un tipo mas importante
    else{
        ptrNodo -> tipo = 3;
    }
}

// Recorre el arbol en modo postOrden
void postOrden(nodo *ptrNodo){
    if (ptrNodo!=NULL) {
        postOrden(ptrNodo->izq);
        postOrden(ptrNodo->der);
        // Si es un operador y sus hojas son digitos
        if(ptrNodo -> tipo != 3 and ptrNodo -> izq -> tipo == 3 and ptrNodo -> der -> tipo == 3) {
            float izq = stof(ptrNodo->izq->contenido); float der = stof(ptrNodo->der->contenido);
            // Se hace la operacion con las hojas del nodo
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

// Reemplaza el nodo
void replaceNodo(float contenido, nodo *ptrNodo){
    ptrNodo -> contenido = to_string(contenido);
    asigna_tipo(ptrNodo);
    ptrNodo -> izq = NULL; ptrNodo -> der = NULL;
}
