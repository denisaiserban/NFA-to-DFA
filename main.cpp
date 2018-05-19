#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int numar_simboluri, numar_stari, stare_initiala, numar_stari_finale;
vector<int> stari_finale;

vector < vector <vector <int > > > nfa;
vector < vector <vector <int > > > dfa;

void input()
{
    ifstream f("input");
    f>>numar_stari;
    f>>numar_simboluri;
    f>>stare_initiala;
    f>>numar_stari_finale;
    stari_finale.resize(numar_stari_finale);
    for(int i=0; i<numar_stari_finale; i++)
        f>>stari_finale[i];
    nfa.resize(numar_stari);
    for(int i=0; i<numar_stari; i++)
    {
        nfa[i].resize(numar_stari);
        for(int j=0; j<numar_stari; j++)
            nfa[i][j].resize(numar_simboluri, 0);
    }

    for(int i=0; i<numar_stari; i++)
        for(int j=0; j<numar_stari; j++)
            for(int k=0; k<numar_simboluri; k++)
            {
                f>>nfa[i][j][k];
            }

    for(int i=0; i<numar_stari; i++)
    {
        for(int k=0; k<numar_simboluri; k++)
        {
            cout<<"Starea "<<i<<" --> "<<char(97+k)<<" --> ";
            for(int j=0; j<numar_stari; j++)
                if(nfa[i][j][k]==1)
                    cout<<j<<" ";
            cout<<endl;
        }
        cout<<endl;
    }
    cout<<"Stare initiala : "<<stare_initiala<<endl;
    cout<<"Stari finale : ";
    for(int i=0; i<numar_stari_finale; i++)
        cout<<stari_finale[i]<<" ";
    cout<<endl;
    f.close();
}

void format( vector<int> &x )
{
    for(int i=0; i<x.size()-1; i++)
        for(int j=i+1; j<x.size(); j++)
            if(x[i]>x[j])
            {
                int aux=x[i];
                x[i]=x[j];
                x[j]=aux;
            }

    for(int i=1; i<x.size(); i++)
        if(x[i]==x[i-1])
        {
            x.erase(x.begin()+i);
            i--;
        }
}

void createDfa()
{
    dfa.resize(1);
    dfa[0].resize(numar_simboluri+1);
    dfa[0][0].resize(1);
    dfa[0][0][0]=stare_initiala;
    vector< vector <int > > viz;
    viz.resize(1);
    viz[0].resize(1);
    viz[0][0]=stare_initiala;

    for(int i=0; i<dfa.size(); i++)
    {
        for(int j=1; j<=numar_simboluri; j++)
        {
            vector<int>aux;
            int lungime_aux=0;
            for(int k=0; k<dfa[i][0].size(); k++)
            {
                for(int l=0; l<numar_stari; l++)
                {
                    if(nfa[dfa[i][0][k]][l][j-1]==1)
                    {
                        lungime_aux++;
                        aux.resize(lungime_aux);
                        aux[lungime_aux-1]=l;
                    }
                }
            }
            format(aux);
            dfa[i][j]=aux;
            int ok=0;
            for(int x=0; x<viz.size(); x++)
                if(viz[x]==aux)
                    ok=1;
            if(ok==0)
            {
                viz.push_back(aux);
                vector<vector< int > > aux2;
                aux2.resize(numar_simboluri+1);
                aux2[0]=aux;
                dfa.push_back(aux2);
            }
        }
    }
}
void afisareDfa()
{
    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<"Tabel DFA: "<<endl<<endl;
    for (int i=0; i<dfa.size(); i++)
    {
        for (int j=1; j<=numar_simboluri; j++)
        {
            cout<<"Starea ";
            for(int j=0; j<dfa[i][0].size(); j++)
                cout<<dfa[i][0][j];
            cout<<" --> "<<char (96+j)<<" --> " ;
            for(int k=0; k<dfa[i][j].size(); k++)
                cout<<dfa[i][j][k];
            cout<<endl;
        }
        cout<<endl;
    }

}

int main()
{
    input();
    createDfa();
    afisareDfa();

    return 0;
}
