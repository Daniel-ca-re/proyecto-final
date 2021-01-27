#include "txtinfo.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

txtinfo::txtinfo()
{

}

txtinfo::txtinfo(std::string donde)
{
    txt=donde;
    std::string data="";

    // Abre el archivo en modo lectura
    ifstream infile;

    // Se pone de manera explicita la ruta relativa donde se encuentra el archivo
    infile.open(donde);

    // Se comprueba si el archivo fue abierto exitosamente
    if (!infile.is_open())
    {
      cout << "Error abriendo el archivo" << endl;
      exit(1);
    }
    infile >> data;
    int ii=0;
    std::string x="";
    for(int i =0; i < data.size();i++)
    {

        if(data[i]==',')
        {
            info[ii]=stoi(x);
            ii++;
            x.clear();
        }
        else
        {
            x.push_back(data[i]);
        }
        if(i+1==data.size())
        {
            info[ii]=stoi(x);
            ii++;
            x.clear();
        }
    }



    infile.close();
}

void txtinfo::saveinfo()
{

    // abrir un archivo en modo escritura
    ofstream outfile;

    // Se pone de manera explicita la ruta relativa donde se encuentra el archivo
    outfile.open(txt,ios::out);

    // Se comprueba si el archivo fue abierto exitosamente
    if (!outfile.is_open())
    {
      cout << "Error abriendo el archivo" << endl;
      exit(1);
    }


    for(int i=0; i<info.size();i++)
    {

                std::ostringstream x;
                x << info[i];
                outfile << x.str() ;
                if(i+1!=info.size())
                {
                    outfile << ',';
                }

    }
    // Se cierra el archivo
    outfile.close();
}

void txtinfo::addnew(int x)
{
    for(int i =(info.size()-1); i>-1;i--)
    {
        if(info[i]<x)
        {
            int z=x;
            x=info[i];
            info[i]=z;
        }
    }
}
