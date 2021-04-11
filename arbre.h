#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

#include <string>
#include <vector>

using namespace std;

class arbre {
public :
    arbre(const string& nom);
    void codage();
    string getCodage() const;
private :
    vector<vector<int>> d_adjacence;
	vector<int> d_codage;
};

#endif // ARBRE_H_INCLUDED
