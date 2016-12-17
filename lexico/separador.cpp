//
// Created by sutil on 16/12/16.
//

#include <vector>
#include "separador.h"

std::vector<char> descartaveis = {' ', '\n'};


bool isSeparadorDescartavel(char caraceter) {
    for(int i = 0; i< descartaveis.size() ; i++)
        if(caraceter == descartaveis[i])
            return true;
    return false;
}
