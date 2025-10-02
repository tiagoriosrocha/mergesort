merge1.c -> implementação básica
merge2.c -> implementação do merge com ponteiros
merge3.c -> implementação do merge com o bublle sort
merge4.c -> implementação do merge com o bubble sort automatizada para o benchmark
merge4_count_instructions.c -> implementação do merge com bubble sort automatizada para o benchmark com contagem de intruções
merge4_count_memory -> quantidade de memória alocada
merge4_count_qtd_aloc.c -> quantidade de movimentações de dados (ida e volta)
merge5.c -> implementação do merge com o insertion sort automatizada para o benchmark
merge5_count_instructions.c -> implementação do merge com insertion sort automatizada com contagem de intruções
merge5_count_qtd_aloc.c -> quantidade de movimentações de dados (ida e volta)
merge6.c -> implementação do merge com o timsort automatizada para o benchmark
merge7.c -> implementação do merge com openmp automatizada para o benchmark
merge8.c -> implementação do merge com um vetor global

merge3.c
AMD® A8-5500b apu with radeon(tm) x 4, 8,0 GiB de RAM, Ubuntu 22.04.4 LTS, 64 bits

Tamanho 	Merge	Hybrid(1000)	Hybrid(100)	   Hybrid(50)	Hybrid(25)	 Hybrid(15)	  Hybrid(10)   Hybrid(5)
100000 ->    0,05      0.33          0.08          0.04         0.03         0,05         0.02         0.05
10000000->   3.89      26,83         5,24          3.98         3,43         3,17         3,18         3.17
100000000->  44.59                   65.45         47.50        40.41        36.96        35.86        37.48  


merge4.c
Intel® Core™ i7-14700KF × 28, 16.0 GiB de RAM, Ubuntu 24.04.3 LTS, 64 bits (bubble-sort)

Tamanho 	Merge	Hybrid(1000)	Hybrid(100)	Hybrid(50)	Hybrid(25)	Hybrid(15)	Hybrid(10)	Hybrid(5)
100000	    0.02	0.09	        0.02	    0.01	    0.01	    0.01	    0.01	    0.01
10000000	0.73	6.87	        1.63	    1.15	    0.89	    0.75	    0.75	    0.71
100000000	8.33	84.56	        19.81	    13.83	    10.70	    8.90	    8.25	    8.29


merge5.c
Intel® Core™ i7-14700KF × 28, 16.0 GiB de RAM, Ubuntu 24.04.3 LTS, 64 bits (insetion-sort)

Tamanho 	Merge	Hybrid(1000)	Hybrid(100)	   Hybrid(50)	Hybrid(25)	 Hybrid(15)	  Hybrid(10)   Hybrid(5)
100000	    0.01	0.01	        0.00	       0.00	        0.00	     0.00	      0.00	       0.01
10000000	0.71	0.82	        0.64	       0.64	        0.65	     0.67	      0.67	       0.69
100000000	8.25	10.12	        7.44	       7.44	        7.55	     7.73	      7.94	       8.10


merge6.c
Intel® Core™ i7-14700KF × 28, 16.0 GiB de RAM, Ubuntu 24.04.3 LTS, 64 bits (Timsort)

Tamanho 	Merge	Hybrid(1000)	Hybrid(100)	   Hybrid(50)	Hybrid(25)	 Hybrid(15)	  Hybrid(10)   Hybrid(5)
100000	    0.01	0.01	        0.01	        0.00	    0.00	     0.00	      0.00	       0.00
10000000	0.72	0.64	        0.65	        0.65	    0.65	     0.67	      0.67	       0.69
100000000	8.20	7.49	        7.53	        7.56	    7.53	     7.68	      7.88	       8.05


merge7.c 
Intel® Core™ i7-14700KF × 28, 16.0 GiB de RAM, Ubuntu 24.04.3 LTS, 64 bits (openmp - rodando para 28 núcleos)

100000      0.01
10000000    0.22
100000000   2.26

merge8.c
Intel® Core™ i7-14700KF × 28, 16.0 GiB de RAM, Ubuntu 24.04.3 LTS, 64 bits (vetor global)

100000      0.01
10000000    1.19
100000000   13.36

###################################################################################################
###################################################################################################
###################################################################################################
//contagem de instruções de comparação

merge4_count_instructions.c
Tamanho 	Merge	    Hybrid(1000)	Hybrid(100)	Hybrid(50)	Hybrid(25)	Hybrid(15)	Hybrid(10)	Hybrid(5)
100000	    1536368	    39712278	    5830856	    3487474	    2363244	    1845517	    1626343	    1549008
10000000	220099907	3186726951	    546224246	365237269	279373030	240848655	240848655	225314194
100000000	2532932550	39796715064	    6716422256	4430300145	3334234722	2830470861	2618073645	2545558028


merge5_count_instructions.c
Tamanho	    Merge	    Hybrid(1000)	Hybrid(100)	    Hybrid(50)	    Hybrid(25)	Hybrid(15)	Hybrid(10)	Hybrid(5)
100000	    1536368	    20357557	    3522065	        2387088	        1862654	    1639659	    1558202	    1536917
10000000	220099907	1673199393	    367404285	    281256662	    242317491	226426734	226426734	221110074
100000000	2532932550	20846531617	    4451768217	    3353736383	    2847241815	2631320955	2552898160	2533300072

###################################################################################################
###################################################################################################
###################################################################################################
//contagem de memória
merge4_count_memory.c
Tamanho 	Merge	    Hybrid(1000)	Hybrid(100)	    Hybrid(50)	    Hybrid(25)	    Hybrid(15)	    Hybrid(10)	    Hybrid(5)
100000	    1200000	    1200000	        1200000	        1200000	        1200000	        1200000	        1200000	        1200000
10000000	120000000	120000000	    120000000	    120000000	    120000000	    120000000	    120000000	    120000000
100000000	1200000000	1200000000	    1200000000	    1200000000	    1200000000	    1200000000	    1200000000	    1200000000

Por que não precisamos realocar memória recursivamente

Vetor temporário global:
O temp é alocado uma vez por chamada de teste (test_sort).
Ele tem o mesmo tamanho do vetor array que será ordenado.
Durante a recursão, cada chamada merge copia apenas a porção relevante do array para temp, mas não cria novas alocações.

Eficiência:
Se você alocasse temp a cada chamada recursiva, seriam feitas milhões de alocações, o que seria muito lento e desnecessário.
O algoritmo funciona porque cada chamada recursiva opera em subintervalos do vetor e temp já tem espaço suficiente para qualquer intervalo que precise ser mesclado.

Cálculo de memória alocada:
A memória total alocada é sempre o tamanho do vetor original + vetor temporário, pois não há novas alocações recursivas.
Por isso, no seu resultado, memória alocada = n * 4 (array) + n * 4 (temp) = 2 * n * sizeof(int) (assumindo int com 4 bytes).

Para n = 1000000:
array: 1000000 * 4 bytes = 4.000.000
temp : 1000000 * 4 bytes = 4.000.000
Total = 8.000.000 bytes

###################################################################################################
###################################################################################################
###################################################################################################
//contagem de quantidade de alocações dos dados do vetor original para o temporário

merge4_count_qtd_aloc.c
Tamanho	    Merge	    Hybrid(1000)	Hybrid(100)	Hybrid(50)	Hybrid(25)	Hybrid(15)	Hybrid(10)	Hybrid(5)
100000	    3437856	    60176172	    9388482	    5901338	    4258525	    3542754	    3284849	    3255760
10000000	476445568	4860039185	    914927237	648642028	525573489	474246956	474246956	458543488
100000000	5431564544	60643223849	    11177732399	7801611001	6213565677	5519545523	5272477081	5248343398



merge5_count_qtd_aloc.c
Tamanho     Merge	    Hybrid(1000)	Hybrid(100)	Hybrid(50)	Hybrid(25)	Hybrid(15)	Hybrid(10)	Hybrid(5)
100000	    3505294	    21258488	    4727420	    3696366	    3278217	    3165409	    3198688	    3297534
10000000	483322689	1833313664	    558049995	482366647	454178911	449450225	449450225	455800208
100000000	5498714820	22747479961	    6657172947	5663091266	5263051183	5157300828	5193890910	5290583852









## O que você pode fazer para melhorar **muito** o desempenho:

### 1. **Substituir Bubble Sort por Insertion Sort**

**Insertion Sort** é muito mais eficiente que Bubble Sort em vetores pequenos:

* Mesmo tempo assintótico (`O(n²)`)
* Menor número de comparações e trocas
* Melhora notável em `n` até 10.000


