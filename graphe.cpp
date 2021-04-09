#include "graphe.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <iostream>

graphe::graphe(const std::string& nomDuFichier) : d_fs{}, d_aps{}
{
    std::ifstream ist(nomDuFichier);

    if(!ist)
        std::cout<<"Pb ouverture fichier";

    int nbSommet=0, nbArcs=0, nbSucc=0, numSucc=0, k=0;

    ist>>nbSommet>>nbArcs;

    d_fs.reserve(nbSommet+nbArcs);
    d_aps.reserve(nbSommet);

    d_aps.push_back(nbSommet);
    d_fs.push_back(nbSommet+nbArcs);

    for(int i=1; i<=nbSommet; ++i)
    {
        d_aps.push_back(k+1);

        ist>>nbSucc;
        for(int j=1; j<=nbSucc; ++j)
        {
            ist>>numSucc;
            d_fs.push_back(numSucc);
            k++;
        }

        d_fs.push_back(0);
        k++;
    }
}

void graphe::distance(int r)
{
    d_dist_sommet = r;

    int nb_som = d_aps[0];
    int i=0, j=1, k=0, ifin, s, t, it;

    std::vector<int> fil(nb_som+1, 0);

    d_dist.resize(nb_som+1);

    fil[0] = nb_som;
    d_dist[0] = nb_som;

    fil[1] = r;

    for(int h=1; h<=nb_som; h++)
        d_dist[h] = -1;

    d_dist[r] = 0;

    while(i<j)
    {
        k++;
        ifin = j;

        while(i < ifin)
        {
            i++;
            s = fil[i];
            it = d_aps[s];
            t = d_fs[it];

            while(t > 0)
            {
                if(d_dist[t] == -1)
                {
                    j++;
                    fil[j] = t;
                    d_dist[t] = j;
                }

                t = d_fs[++it];
            }
        }
    }
}

void graphe::empilerDist(int x, std::vector<int>& v)
{
    v[x] = v[0];
    v[0] = x;
}

void graphe::rang()
{
    int n = d_aps[0], taillefs = d_fs[0], s, k, h, t;

    d_rang.resize(n+1);

    d_rang_ddi.resize(n+1, 0);
    d_rang_pilch.resize(n+1, 0);
    d_rang_prem.resize(n+1, 0);

    //for(int i=1; i <=n ; i++) ddi[i]=0;

    //calcul de ddi
    for(int i=1; i <= taillefs ; i++)
    {
        s = d_fs[i];

        if (s >0)
            d_rang_ddi[s]++;
    }
    //calcul du rang
    d_rang_pilch[0]=0;

    for(s = 1; s <= n; s++)
    {
        d_rang[s] = -1; // n : nombre de sommets de G represente l'infini
        if (d_rang_ddi[s] == 0) empilerDist(s,d_rang_pilch);
    }

    k=-1;
    s=d_rang_pilch[0];
    d_rang_prem[0] = s;
    while (d_rang_pilch[0] > 0)
    {
        k++;
        d_rang_pilch[0] = 0;
        while (s > 0)
        {
            d_rang[s] = k;
            h = d_aps[s]; t = d_fs[h];
            while (t > 0)
            {
                d_rang_ddi[t]--;
                if (d_rang_ddi[t] == 0) empilerDist(t,d_rang_pilch);
                h++;
                t=d_fs[h];
            }
            s = d_rang_pilch[s];
        }
        s = d_rang_pilch[0];
        d_rang_prem[k+1] = s;
    }
}

void graphe::empiler(int s, std::vector<int>& v)
{
    v.push_back(s);
}

void graphe::empilerPilch(int x, std::vector<int>& v)
{
    v[x] = v[0];
    v[0] = x;
}

int graphe::depiler(std::vector<int>& v)
{
    int tmp = v.back();
    v.pop_back();
    return tmp;
}

void graphe::depiler2(int s, std::vector<int>& v)
{
    v[s] = 0;
}

void graphe::traverse(int s)
{
    d_tarjan_p++;
    d_tarjan_num[s] = d_tarjan_p;
    d_tarjan_ro[s] = d_tarjan_p;
    empiler(s, d_tarjan_tarj);
    d_tarjan_entarj[s] = true;
    d_tarjan_cfc[0] = d_tarjan_cfc.size()-1;

    int t;

    for(int k = d_aps[s]; (t = d_fs[k]) != 0; k++)
    {
        if(d_tarjan_num[t] == 0)
        {
            d_tarjan_pred[t] = s;
            traverse(t);
            if(d_tarjan_ro[t] < d_tarjan_ro[s])
                d_tarjan_ro[s] = d_tarjan_ro[t];
        }
        else
        {
            if((d_tarjan_num[t] < d_tarjan_ro[s]) && d_tarjan_entarj[t])
                d_tarjan_ro[s] = d_tarjan_num[t];
        }
    }

    if(d_tarjan_ro[s] == d_tarjan_num[s])
    {
        int u = depiler(d_tarjan_tarj);
        d_tarjan_nbr++;

        d_tarjan_cfc[s] = d_tarjan_nbr;
        while(u != s)
        {
            d_tarjan_entarj[u] = false;
            empilerPilch(u, d_tarjan_pilch);
            d_tarjan_cfc[u] = d_tarjan_nbr;
            u = depiler(d_tarjan_tarj);
        }

        depiler2(s, d_tarjan_tarj);
        d_tarjan_entarj[s] = false;
        empilerPilch(s, d_tarjan_pilch);
        d_tarjan_pilch[0] = 0;
        d_tarjan_prem[d_tarjan_nbr] = s;
    }
}

void graphe::adjacence()
{
    int k;
    int n = d_aps[0];
    int m = d_fs[0] - n;

    d_matrice_adjacence.resize(n+1);

    for(int i = 0; i<= n; ++i)
        d_matrice_adjacence[i].resize(n+1);

    d_matrice_adjacence[0][0] = n;
    d_matrice_adjacence[0][1] = m;

    //for(int j = 1; j<=n; ++j)
            //d_matrice_adjacence[i][j]=0;

    for(int i = 1; i<=n; ++i)
    {
        k = d_aps[i];
        while(d_fs[k] != 0)
        {
            d_matrice_adjacence[i][d_fs[k]] = 1;
            k++;
        }
    }
}

void graphe::sauvgarde() const
{
    std::ofstream ost("grapheDeTest.txt");

    ost<<"aps : "<<getAps()<<'\n';
    ost<<"fs : "<<getFs()<<'\n';
    ost<<'\n';
    ost<<"rang : "<<getRangddi()<<'\n'<<'\n';
    ost<<"distance depuis le sommet "<<getNumSommet()<<" : "<<getDist()<<'\n'<<'\n';
    ost<<"tarjan : \n";
    ost<<"prem : "<<getTarjanPrem()<<'\n';
    ost<<"pilch : "<<getTarjanPilch()<<'\n';
    ost<<"cfc : "<<getTarjanCfc()<<'\n';
    ost<<"num : "<<getTarjanNum()<<'\n'<<'\n';
    ost<<"Matrice d'adjacence : \n"<<getAdjacence()<<'\n';


}

std::string graphe::getFs() const
{
    std::string str = "";

    for(const auto& i : d_fs)
        str += (std::to_string(i) + " ");

    return str;
}


std::string graphe::getAps() const
{
    std::string str = "";

    for(const auto& i : d_aps)
        str += (std::to_string(i) + " ");

    return str;
}

std::string graphe::getRang() const
{
    std::string str = "";

    for(const auto& i : d_rang)
        str += (std::to_string(i) + " ");

    return str;
}

std::string graphe::getRangddi() const
{
    std::string str = "";

    for(const auto& i : d_rang_ddi)
        str += (std::to_string(i) + " ");

    return str;
}

std::string graphe::getDist() const
{
    std::string str = "";

    for(const auto& i : d_dist)
        str += (std::to_string(i) + " ");

    return str;
}

std::string graphe::getTarjanPrem() const
{
    std::string str = "";

    for(const auto& i : d_tarjan_prem)
        str += (std::to_string(i) + " ");

    return str;
}

std::string graphe::getTarjanPilch() const
{
    std::string str = "";

    for(const auto& i : d_tarjan_pilch)
        str += (std::to_string(i) + " ");

    return str;
}

std::string graphe::getTarjanCfc() const
{
    std::string str = "";

    for(const auto& i : d_tarjan_cfc)
        str += (std::to_string(i) + " ");

    return str;
}

std::string graphe::getTarjanNum() const
{
    std::string str = "";

    for(const auto& i : d_tarjan_num)
        str += (std::to_string(i) + " ");

    return str;
}

std::string graphe::getAdjacence() const
{
    std::string str = "";

    for(int i=0; i<=d_matrice_adjacence[0][0]; ++i)
        {
            for(int j=0; j<=d_matrice_adjacence[0][0]; ++j)
                str += (std::to_string(d_matrice_adjacence[i][j]) + " ");

            str += '\n';
        }

    return str;
}

int graphe::getNumSommet() const
{
    return d_dist_sommet;
}

void graphe::tarjan()
{
    d_tarjan_num.resize(d_aps[0]+1);
    d_tarjan_prem.resize(d_aps[0]+1);
    d_tarjan_pilch.resize(d_aps[0]+1);
    d_tarjan_cfc.resize(d_aps[0]+1);
    d_tarjan_tarj.resize(d_aps[0]+1);
    d_tarjan_pred.resize(d_aps[0]);
    d_tarjan_ro.resize(d_aps[0]+1);
    d_tarjan_entarj.resize(d_aps[0]+1);

    for(unsigned int i=0; i<=d_tarjan_entarj.size(); i++)
        d_tarjan_entarj[i] = false;

    d_tarjan_n = d_aps[0];

    for(int s=1; s<=d_tarjan_n; s++)
        if(d_tarjan_num[s] == 0)
            traverse(s);

    d_tarjan_prem[0] = d_tarjan_nbr;
}

void graphe::build()
{
    distance(0);
    rang();
    tarjan();
    adjacence();
}




















