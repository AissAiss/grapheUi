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

}

std::string grapheValue::getMatricePoids() const
{
    std::string str = "";

    for(unsigned int i=1; i<d_matricePoidsArrete.size(); ++i)
        {
            for(unsigned int j=1; j<d_matricePoidsArrete.size(); ++j)
                str += (std::to_string(d_matricePoidsArrete[i][j]) + " ");

            str += '\n';
        }

    return str;
}
