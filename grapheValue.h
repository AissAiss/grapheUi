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

    //mettre kruskal + dijkstra
    std::string getMatricePoids() const;

private :
    vector<vector<int>> d_matricePoidsArrete;
};

#endif // GRAPHEORIENTE_H
