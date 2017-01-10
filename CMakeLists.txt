cmake_minimum_required(VERSION 3.6)
project(ProjetoU)

set(CMAKE_CXX_STANDARD 11)
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include")
endif()

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate
include_directories(cmake-build-debug/googletest-src/googlemock/include)
include_directories(cmake-build-debug/googletest-src/googletest/include)


set(SOURCE_FILES main.cpp tests/separadorTest.cpp sintatico/AnalisadorSintaticoMain.cpp lexico/AnalisadorLexico.cpp lexico/AnalisadorLexico.h lexico/separador.cpp lexico/separador.h tests/lexico/lexicoTest.cpp lexico/definidorToken.cpp lexico/definidorToken.h tests/lexico/definidorTokenTest.cpp lexico/leitorValorToken.cpp lexico/leitorValorToken.h tests/lexico/leitorValorTokenTest.cpp tests/lexico/abreArquivo.cpp tests/lexico/abreArquivo.h terminais.h sintatico/AnalisadorSintaticoMain.h lexico/contagem.cpp lexico/contagem.h sintatico/No.cpp sintatico/No.h table/table.cpp table/table.h table/controledetabela.cpp table/controledetabela.h table/util.cpp table/util.h)
add_executable(ProjetoU ${SOURCE_FILES})
target_link_libraries(ProjetoU gtest gtest_main)