Esse repositório é referente aos trabalhos realizados na disciplina de Organização de Computadores.

# Trabalho 1 - Processador com Pipeline

Nesse trabalho, implementamos um processador MIPS-like com pipeline em SystemC. Fotos contendo o diagrama de blocos do processador, junto com sua máquina de estados, podem ser encontradas em trab1/photos.

## Componentes

Todos os componentes utilizados estão localizados dentro da pasta trab1.

## Testes

Testes para alguns dos componentes implementados podem ser encontrados em trab1/tests.

## O Processador

O arquivo que reúne e conecta todos os componentes implementados na forma de um processador com pipeline se encontra em trab1/main/main.cpp.

## Algoritmos

O funcionamento das instruções do processador foi testada por meio de alguns algoritmos, encontrados na pasta trab1/executions. Nessa pasta, também é possível encontrar o log dos resultados das simulações desses algoritmos.

Para a execução desses algoritmos, assim como de outras instruções, será necessário modificar o arquivo trab1/memory_instructions.h, de forma a inserir as instruções desejadas a serem executadas. 

Dependendo da quantidade de instruções executadas, também será necessário mudar a quantidade de ciclos de relógio simuladas pelo processador, informação presente em trab1/main/main_testbench.h.

## Tratamento de Dependência de Dados e Saltos

No momento, se faz necessário inserir instruções "no_op" manualmente entre instruções que possuam dependência de dados entre si. Essas instruções são utilizadas para criar uma "bolha" no pipeline, já que não realizam nenhuma operação relevante, servindo apenas para esvaziar os buffers.

Além disso, se faz necessário inserir algumas instruções "no_op" após instruções de salto, a fim de realizar um "flush" nos buffers do pipeline.

## Compilação e Execução

A fim de compilar e executar, é necessário ter instalado a biblioteca SystemC. Nesse projeto, fui utilizada a versão 2.3.3 do SystemC.

Estando na pasta trab1/main, utilize os seguintes comandos para compilar:

```
export SYSTEMC_HOME=/usr/local/systemc-2.3.3/
```
```
g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o main main.cpp -lsystemc -lm
```

Para executar, utilize o comando:
```
./main
```