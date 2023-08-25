# Top-K-elementos
---

É muito commum em situações de análise de dados ter que encontrar a parte mais significativa ou valiosa de uma grande massa de dados, isso é, identificar os elemontos mais valiosos dentre diversos menos releventes. A partir desse processo, pode-se partir para análise de dados e retirar conclusoes valiosas a respeito dos dados que não seria possível se fazer a mão devido ao tamanho da massa de dados.

Esse projeto fornece uma solução para tal problema utilizando uma tabela hash e estrutura heap para análise de palavras em textos. O intuito é descobrir qual são os "top k elementos" na massa de dados, isto é, qual elementos se repetem (aparecem mais vezes) mais dentro os demais.

Utilizando a tabela hash e estrutura heap podemos apresentar uma solução eficiente computacionalmente para esse problema. O que torna o processo escalável à relativamente grandes massas de dados mesmo em dispositivos modestos.

Em suma, esse trabalho realiza a leitura e análise de diferentes textos fornecidos pelo usuário e retorna qual foram os top k elementos mais frenquentes nos textos fornecidos. O valor de k é considerado como 20 por definição.

## Formatação da entrada

- O programa recebe um arquivo com conteudo de texto onde cada sentença deve terminar com sinal de pontuação ex: ".","?","!";
- Cada parágrafo é separado por uma linha em branco;
- Uma palavra é definida como uma sequência de letras delimitadas (pela frente e trás) por espaço ou sinal de pontuação;
- Os arquivos de input são nomeados na forma "input{n}.data", onde n é seu número a partir de 1;
- A análise a ser feita no texto desconsidera as "stop words", palavras como "a","e","mas", etc. A lista de "stop words" deve ser fornecida através de um arquivo "stopwords.txt" na pasta dataset;

## Decisões de implementação 

Foi optado pelo uso de um heap mínimo devido a praticidade para encontrar o menor valor do heap. Ao utilizar um heap mínimo, podemos a todo momento verificar e fazer a remoção apenas da raiz, assim tornando mais eficiente a remoção e procura do elemento.

É optado por transferir o arquivo todo da memória secundária para a principal para ser realizada a leitura do arquivo, tal decisão apresenta tanto pontos fortes, como pontos fracos:

### Pontos fortes:
- Leitura rápida dos arquivos;
- Menos uso da memória secundária o que normalmente acelera a execução.

### Pontos fracos:
- Arquivos grandes demais para a memória principal não podem ser processados pelo programa;
- Se o arquivo for muito grande, pode consumir uma quantidade significativa de memória e pode gerar má performance.

Tendo em vista o escopo do trabalho, foi optado utilizar esse método devido aos seguintes pontos:
- Arquivos em texto utilizam pouca memória em comparação com outros arquivos, assim mesmo muitos textos muito longos não apresentam grandes chances de ultrapassar o tamanho da memória principal de maquinas modernas;
- É mais fácil e barato expandir a capacidade da memória principal do que a capacidade de processamento;
- Nesse tipo de projeto a velocidade de execução tem a maior importância.

O arquivo de stopwords foi lido de forma sequêncial devido ao seu tamanho pequeno o que torna a diferença de performance obtida ao otmizar o processo quase insignificante em comparação aos arquivos de entrada.
