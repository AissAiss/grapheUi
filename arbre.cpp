#include "arbre.h"
#include <fstream>
#include <iostream>


arbre::arbre(const string& nom): d_adjacence{}, d_codage{}
{
    int nb_som, som;
	ifstream fichier(nom);
	if (!fichier)
	{
		cout << "Probleme d'ouverture du fichier " << nom << endl;
		//exit (1);
	}
	fichier >> nb_som;

	d_adjacence.resize(nb_som+1);
	d_adjacence[0].resize(nb_som+1);

	d_adjacence[0][0] = nb_som;

	for(int i=1; i<=nb_som; i++)
		d_adjacence[i].resize(nb_som+1);


	for (int i = 1; i <= nb_som; i++)
        for (int j = 1; j <= nb_som; j++)
            {
                fichier >> som;
                d_adjacence[i][j] = som;
                d_adjacence[i][0] += som;
            }
}

void arbre::codage()
{
    int nb_som = d_adjacence[0][0];

	d_codage.resize(nb_som-1);

	d_codage[0] = nb_som-2;

	int k = 1;

	while (k <= nb_som-2)
	{
	    int i = 1, j = 1;

		while(d_adjacence[i][0] != 1)
            ++i;

		while(d_adjacence[i][j] != 1)
            ++j;

		d_codage[k++]=j;
		d_adjacence[i][j]=0;
		d_adjacence[j][i]=0;
		d_adjacence[i][0]=0;
		d_adjacence[j][0]--;
	}

}

string arbre::getCodage() const
{
    std::string str = "";

    for(const auto& i : d_codage)
        str += (std::to_string(i) + " ");

    return str;
}











