# automato-finito
Programa para reconhecimento de linguagens regulares através de autômatos finitos.  
**A descrição do problema pode ser encontrado no PDF "TP1-descrição.pdf"** na raíz do diretório.

# Execução
Executar na raíz do diretório:
- gcc -c src/tp.c src/main.c
- gcc -o tp tp.o main.o
- ./tp

Ou utilizando o make:
- make all
- ./tp

## O arquivo "automaton.txt"
Este arquivo é utilizado para representar os estados e as transições dos autômatos.  
> 7  
> 
> 0    
> 4,1  
> 
> 1    
> 0,2  
> 8,3  
> ...

### Regras do arquivo
- A primeira linha deve conter a quantidade de estados do autômato e deve ser seguida de uma linha vazia.
- O indice de um estado deve estar sozinho em uma linha e as linhas seguintes a ele representam suas transições no formato símbolo_lido, indice_destino.

## O arquivo "words.txt"
Este arquivo é um modelo de entrada para reconhecimento de múltiplas palavras.
> 48a0l7  
> 48a8a8a0l
> 8a8a8a0l7
> 40l0l0l0l7
> ...
 
As palavras devem ser inseridas uma por linha
