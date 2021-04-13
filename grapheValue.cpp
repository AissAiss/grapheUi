#include "grapheValue.h"


grapheValue::grapheValue(const std::string &nomFic) : graphe{}, d_matricePoidsArrete{}
{
    std::ifstream entree(nomFic);

    if(!entree)
        std::cout<<"Pb ouverture fichier";

    int nbSommet=0, nbArcs=0, nbSucc=0, numSucc=0,k=0 ;
    int poid;

    entree>>nbSommet>>nbArcs;
    d_fs.reserve(nbSommet+nbArcs);
    d_aps.reserve(nbSommet);

    d_aps.push_back(nbSommet);
    d_fs.push_back(nbSommet+nbArcs);

    d_matricePoidsArrete.resize(nbSommet+1);
    for(int i =0; i <= nbSommet;++i )
    {
        d_matricePoidsArrete[i].resize(nbSommet+1);
    }

    for(int i = 1; i <= nbSommet;  ++i )
    {
        d_aps.push_back(k+1);
        entree>>nbSucc;
        for(int j = 1; j <= nbSucc ;++j)
        {
            entree>>numSucc>>poid;
            d_matricePoidsArrete[i][numSucc] = poid;
            d_fs.push_back(numSucc);
            k++;

        }

        d_fs.push_back(0);
        k++;
    }

    this->adjacence();

    for(unsigned int i = 1; i < d_matrice_adjacence.size(); ++i)
    {
        for(unsigned int j = 1; j < d_matrice_adjacence[i].size(); ++j)
        {
            if(d_matrice_adjacence [i][j] == 0 && i!=j )
            {
                d_matricePoidsArrete[i][j] = INT_MAX;
            }
        }
    }
}

void grapheValue::sauvgarde() const
{
    std::ofstream ost("grapheDeTest.txt");
    ost<<"aps : "<<getAps()<<'\n';
    ost<<"fs : "<<getFs()<<'\n';
    ost<<'\n';
    ost<<"rang : "<<getRangddi()<<'\n'<<'\n';
    ost<<"distance depuis le sommet "<<getNumSommet()<<" : "<<getDist()<<'\n'<<'\n';
    ost<<"tarjan \n";
    ost<<"prem : "<<getTarjanPrem()<<'\n';
    ost<<"pilch : "<<getTarjanPilch()<<'\n';
    ost<<"cfc : "<<getTarjanCfc()<<'\n';
    ost<<"num : "<<getTarjanNum()<<'\n'<<'\n';
    ost<<"Matrice d'adjacence : \n"<<getAdjacence()<<'\n';
    ost<<"Dijkstra : \n";
    ost<<"Distance : "<<getDijkstraDist()<<"\n";
    ost<<"Prédecesseur : "<<getDijkstraPred()<<"\n";
}

void grapheValue::dijkstra(int s)
{
    d_dijkstra_dist.clear();
    d_dijkstra_pred.clear();
    vector<int> X;
    X.push_back(s);

    vector<int> S;
    for(int i = 1 ; i<=d_aps[0] ; ++i)
    {
        if(i != s){
            S.push_back(i);

        }
    }


    for(int i = 0 ; i<= d_aps[0] ; ++i)
    {
        d_dijkstra_dist.push_back(d_matricePoidsArrete[s][i]);
        d_dijkstra_pred.push_back(1);
    }

    int indiceJ = d_aps[s];
    int j = d_fs[indiceJ];

    while(!S.empty())
    {
        if(j<INT_MAX){
            for(unsigned int i = 0 ; i<S.size(); ++i)
            {
                if(S[i] == j)
                {
                    S.erase(S.begin()+i);
                }
            }
            X.push_back(j);
            int indiceK = d_aps[j];
            int k = d_fs[indiceK];
            while(k!=0)
            {
                if(dijkstra_appartient(k,S))
                {
                    int v = d_dijkstra_dist[j]+d_matricePoidsArrete[j][k];
                    if(v < d_dijkstra_dist[k])
                    {
                        d_dijkstra_dist[k] = v;
                        d_dijkstra_pred[k] = j;
                    }
                }
                indiceK++;
                k = d_fs[indiceK];
            }
        }
        j = dijkstra_dmin(S,d_dijkstra_dist);
    }
}

bool grapheValue::dijkstra_appartient(int k, vector<int> S)
{
    for(unsigned int i = 0 ; i<S.size() ; ++i)
    {
        if(S[i]==k)
            return true;
    }
    return false;
}

int grapheValue::dijkstra_dmin(vector<int>& S, vector<int>& d)
{
    if(!S.empty())
    {
        int mini = INT_MAX;
        int indice = 0;
        for(unsigned int i = 0 ; i<S.size() ; ++i){
            if(mini > d[S[i]])
            {
                mini = d[S[i]];
                indice = i;
            }
        }
        return S[indice];
    }
    else return INT_MAX;
}

std::string grapheValue::getMatricePoids() const
{
    std::string str = "";

    for(unsigned int i=1; i<d_matricePoidsArrete.size(); ++i)
        {
            for(unsigned int j=1; j<d_matricePoidsArrete.size(); ++j)
            {
                if(d_matricePoidsArrete[i][j] != INT_MAX)
                {
                    str += (std::to_string(d_matricePoidsArrete[i][j]) + " ");
                }else{
                    str+= "0 ";
                }
            }

            str += '\n';
        }

    return str;
}

std::string grapheValue::getDijkstraDist() const
{
    std::string str = "";

    for(unsigned int i=1; i<d_dijkstra_dist.size(); ++i)
        {
            if(d_dijkstra_dist[i] != INT_MAX && d_dijkstra_dist[i] >= -1)
                str += (std::to_string(d_dijkstra_dist[i]) + " ");
            else{
                str +="-1 ";
            }
        }

    return str;
}

std::string grapheValue::getDijkstraPred() const
{
    std::string str = "";

    for(unsigned int i=1; i<d_dijkstra_pred.size(); ++i)
        {
            str += (std::to_string(d_dijkstra_pred[i]) + " ");
        }

    return str;
}
