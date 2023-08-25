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

## Funcionamento

Primeiro é criado a hash contento todas as palavras nos textos, cada vez que uma palavra é encontrada, ela tem sua frenquência na hash aumentada. Para achar palavras foi realizada a leitura de cada byte do arquivo por vez, assim cada byte entre uma marca de terminação e outra é considerado parte de uma palavra.

Aas marcas de terminação usadas são: 
- espaço; "!"; "?"; "."; nova linha;
- ",""; "("; ")"; ";"; "/"; 
- ":"; "—"; '"'; "\";

Assim a contagem dos elementos é feita em O(n), onde n representa o número de palavras. É importante notar que todas as palavras contidas no arquivo "stopwords.txt" serão disconsideradas pelo programa e não serão adicionadas à hash.

Foi-se utilizado também a condificação UTF-8 fornecida pelas bibliotecas do C++. Além disso, o programa não diferencia entre palavras com letras minúsculas e maiúsculas, assim, "CÓDIGO" e "código" são consideradas palavras iguais. O programa considera acento nas palavras, sendo assim, "código" e "codigo" são consideradas diferentes.

A hash utilizada foi o "unordered_map" do C++ TODO: Descrever como ele funciona e função hash

Depois se cria o heap de tamanho k (20), o heap é inicializado com os primeiros valores da hash e após isso ele será atualizado conforme for pertinente.

A atualização do heap é feita compararando cada palavra restante da hash com o menor valor do heap, isto é, a palavra com menor frequência. Se a contagem for maior do que o menor valor da heap, o elemento do heap é removido, e o novo elemento é inserido no heap. A cada elemento inserido o "heapify" é utilizado, mantendo a estrutura heap correta.

São utilizadas as funções "make_heap", "push_heap" e "pop_heap" para tal. "make_heap" inicializa o heap no vetor, "push_heap" é usado quando a palavra é adicionadae "pop_heap" quando a palavra é removida. Tais funções possuem o custom O(log n), onde n é a quantidade de items inseridos.

Assim, as lista dos k maiores é criado de acordo com a tabela toda. Após toda a tabela ser processada, o heap final é imprimido na tela.

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

## Conclusão

A implementação realizada oferece um exemplo concreto da aplicação das estruturas hash e heap de modo prático. Essa solução, apesar de rudmentar e feita por propósitos educativos, permite extrair informações significativas de vastos conjuntos de dados de modo otimizado.
A experiência obtida na tomada de decisões e uso de estruturas a fim de otimizar a resolução de um problema amplia a capacidade que o desenvolvedore possui para enfrentar uma variedade de desafios computacionais. Assim, ampliando a gama de problemas em que pode trabalhar e resolver.

Assim, o projeto se qualifica como um experiência didática proveitosa para o aprendizado, por combinar o processo de pesquisa sobre as estruturas e implementações na linguágem, assim como a parte prática sobre pensar jeitos mais eficientes de se resolver o mesmo problema utilizando estrategias possíveis graças ao uso de estruturas de dados inteligentes.

## Compilação e Execução

Esse código possui um arquivo Makefile que realiza todo o procedimento de compilação e execução.
O arquivo Makefile supporta as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |
