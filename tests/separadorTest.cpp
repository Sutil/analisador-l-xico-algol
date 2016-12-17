//
// Created by sutil on 16/12/16.
//


#include <gtest/gtest.h>
#include "../lexico/separador.h"

TEST(SeparadorTeste, esparcoEmBrandoEhSeparador) {
    ASSERT_TRUE(isSeparadorDescartavel(' '));
}

TEST(SeparadorTeste, quebraDeLinhaEhUmSeparador){
    ASSERT_TRUE(isSeparadorDescartavel('\n'));
}
