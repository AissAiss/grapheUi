#ifndef GRAPHE_H
#define GRAPHE_H

#include <vector>
#include <string>

class graphe {
public :
    graphe();
    graphe(const std::string& nomDuFichier);

    //distance
    void distance(int r);

    //rang
    void empilerDist(int x, std::vector<int>& v);
    void rang();

    //tarjan
    void empiler(int s, std::vector<int>& v);
    void empilerPilch(int x, std::vector<int>& v);
    int depiler(std::vector<int>& v);
    void depiler2(int s, std::vector<int>& v);
    void traverse(int s);
    void tarjan();

    //adj
    void adjacence();

    //save
    void sauvgarde() const;

    //getter
    int getNbSommet();

    //vue
    std::string getFs() const;
    std::string getAps() const;
    std::string getRang() const;
    std::string getRangddi() const;
    std::string getDist() const;
    std::string getTarjanPrem() const;
    std::string getTarjanPilch() const;
    std::string getTarjanCfc() const;
    std::string getTarjanNum() const;
    std::string getAdjacence() const;
    int getNumSommet() const;

    //build
    void build();

protected :

    std::vector<int> d_fs;
    std::vector<int> d_aps;

private :


    //distance
    std::vector<int> d_dist;
    int d_dist_sommet;

    //rang
    std::vector<int> d_rang;
    std::vector<int> d_rang_ddi;
    std::vector<int> d_rang_pilch;
    std::vector<int> d_rang_prem;

    //trajan
    std::vector<int> d_tarjan_num;
    std::vector<int> d_tarjan_prem;
    std::vector<int> d_tarjan_pilch;
    std::vector<int> d_tarjan_cfc;
    std::vector<int> d_tarjan_tarj;
    std::vector<int> d_tarjan_pred;
    std::vector<int> d_tarjan_ro;
    std::vector<bool> d_tarjan_entarj;

    //adj
    std::vector<std::vector<int>> d_matrice_adjacence;



    int d_tarjan_p = 0;
    int d_tarjan_nbr = 0;
    int d_tarjan_n;

};

#endif // GRAPHE_H
