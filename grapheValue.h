#ifndef GRAPHEORIENTE_H
#define GRAPHEORIENTE_H
#include "graphe.h"
#include <iostream>
#include <fstream>

using std::vector;
using std::cout;
using std::endl;

class grapheValue : public graphe{
public :
    grapheValue(const std::string& nomFic);

    virtual void sauvgarde() const override;

    void dijkstra(int s);
    bool dijkstra_appartient(int k, vector<int> S);
    int dijkstra_dmin(vector<int> &S, vector<int> &d);

    //dijkstra
    std::string getMatricePoids() const;   
    std::string getDijkstraDist() const;
    std::string getDijkstraPred() const;


private :
    vector<vector<int>> d_matricePoidsArrete;
    vector <int> d_dijkstra_dist;
    vector <int> d_dijkstra_pred;
};

#endif // GRAPHEORIENTE_H
