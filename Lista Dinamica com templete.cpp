#include <iostream>
#include <list>
using namespace std;
template<class T>
class MyList {
private:
    class Cell {
    public:
        T val;
        Cell* prox;
        explicit Cell(const T &x) {
            val = x;
            prox=nullptr;
        }
    };
    void Esvazia(Cell *aux);
    void Mostra(Cell *aux);
    bool InsereNaPosicao(const T &num, const int &pos, Cell *aux, const int &atual);
    Cell *primeiro, *ultimo;
    bool Exclui(const int &pos,Cell *aux, const int &atual, Cell *ant);
    int tam;
public:
    int size(){return tam;};
    void Esvazia();
    void Mostra();
    bool InsereNaPrimeira(const T &val);
    void MostraIterativo();
    bool InsereNaPosicao(const T &num, const int &pos);
    bool InsereNoFim(const T &num);
    bool Exclui(const int &pos);

    MyList() {
        tam=0;
        primeiro=ultimo=nullptr;
    };
    ~MyList() {
        Esvazia();
    };

};
template<class T>
void MyList<T>::Esvazia() {
    Esvazia(primeiro);
    primeiro = ultimo = nullptr;
    tam=0;
};
template<class T>
void MyList<T>::Esvazia(Cell *aux){
    if(aux==nullptr) return;
    Esvazia(aux->prox);
    delete aux;
}
template<class T>
void MyList<T>::Mostra() {
    if(primeiro==nullptr)
        cout << endl<<"A lista esta vazia!"<<endl;
    else
        Mostra(primeiro);
};
template<class T>
void MyList<T>::Mostra(Cell *aux){
    if(aux==nullptr){
            cout << "\n";
        return;
    }
    cout<<"["<<aux->val<<"]";
    Mostra(aux->prox);
}
template<class T>
bool MyList<T>::InsereNaPrimeira(const T &val){
    //se n�o passar a posi��o insere no in�cio.
    if(primeiro==nullptr) {
        primeiro = new Cell(val);
        ultimo = primeiro;
        tam++;
    } else {
        Cell *aux = new Cell(val);
        aux->prox = primeiro;
        //(*aux).prox = primeiro; //equivalente no uso do ponteiro
        primeiro = aux;
        tam++;
    }
    return true;
}
template<class T>
bool MyList<T>::InsereNaPosicao(const T &num, const int &pos){
    if(pos>tam)
        return InsereNaPosicao(num,tam+1,primeiro,0);
    else
        return InsereNaPosicao(num,pos,primeiro,0);
}
template<class T>
bool MyList<T>::InsereNaPosicao(const T &num, const int &pos, Cell *aux, const int &atual) {
    if(pos!=0) {
    if(pos-1==atual) {
        Cell *aux2 = new Cell(num);
        aux2->prox=aux->prox;
        aux->prox=aux2;
        tam++;
        return true;
        //se der erro na inserção, return false;
    } else {
        return InsereNaPosicao(num,pos,aux->prox,atual+1);
    }
    }else{
        if(primeiro==nullptr) {
            primeiro = new Cell(num);
            ultimo = primeiro;
            tam++;
        } else {
            Cell *aux = new Cell(num);
            aux->prox = primeiro;
            primeiro = aux;
            tam++;
        }
        return true;
    }
}
template<class T>
bool MyList<T>::InsereNoFim(const T &num){
        if(primeiro==nullptr){
            primeiro=new Cell(num);
            ultimo = primeiro;
            tam++;
        }else {
        Cell *aux=ultimo;
        ultimo->prox = new Cell(num);
        ultimo=ultimo->prox;
        tam++;
        }
    return true;
}
template<class T>
bool MyList<T>::Exclui(const int &pos){
    if(pos==0){
        primeiro=primeiro->prox;
        tam--;
    }else {
    return Exclui(pos,primeiro->prox,1,primeiro);
    }
    return true;
}
template<class T>
bool MyList<T>::Exclui(const int &pos,Cell *aux, const int &atual, Cell *ant){
    if(pos==atual) {
            if(pos==tam){
                ultimo=ant;
                tam--;
            }else {
            ant->prox=aux->prox;
            tam--;
        }
    }else
    return Exclui(pos,aux->prox,atual+1,ant->prox);
}
char menu() {
    char c;
    cout << "\nopcoes: " <<endl;
    cout << "e: excluir" <<endl;
    cout << "i: inserir no inicio" <<endl;
    cout << "f: insere no fim" << endl;
    cout << "m: mostrar" << endl;
    cout << "q: insere na posicao desejada"<<endl;
    cout << "s: sair"<<endl;
    cout << endl;
    cin >> c;
    system("cls");
    return c;
}

int main() {
    MyList <string>l;
    int pos;
    string val;
    char opcao;
    opcao = menu();
    while(opcao!='s') {
        switch(opcao) {
            case 'e':
            case 'E':
                if(l.size()>0){
                    do {
                        cout<< "Entre com a posicao: [0.." <<(l.size()-1)<<"]: ";
                        cin>>ws>>pos;
                    } while(pos <0 || pos>(l.size()));
                    l.Exclui(pos);
                } else {
                    cout << "\nLISTA VAZIA!";
                }
                break;
            case 'i':
            case 'I':
                cout<< "Entre com o valor: ";
                cin>>ws>>val;
                if(!l.InsereNaPrimeira(val))
                    cout<< "LISTA CHEIA!" << endl;
                break;
            case 'f':
            case 'F':
                cout << "Entre com o valor:";
                cin >> ws>> val;
                if(!l.InsereNoFim(val))
                    cout << "VALOR INVALID0" << endl;
                break;
            case 'm':
            case 'M':
                l.Mostra();
                break;
            case 'q':
            case 'Q':
                do {
                    cout<< "Entre com a posicao: [0.." <<l.size()<<"]: ";
                    cin>>ws>>pos;
                } while(pos <0 || pos>(l.size()));
                    cout<< "Entre com o valor: ";
                    cin >> ws >> val;
                    if(!l.InsereNaPosicao(val,pos)) {
                        cout<< "VALOR INVALIDO" << endl;
                    }
                break;
            default:
                cout<<"OPCAO INVALIDA! " << endl;
        }
        opcao=menu();
    }
    return 0;
}
