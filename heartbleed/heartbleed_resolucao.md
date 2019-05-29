# Heartbleed

# 1

Evitar que uma conexão SSL seja fechada por inatividade.

# 2

Acreditar no valor de `length` declarado no pacote, em vez de usar o valor verdadeiro inferido do próprio `payload`.

# 3

Não acredite que todos seguirão o protocolo.

# 4

Somente o cartão de crédito 2.

# 5

Algo como um `buffer overflow`.

# 6

Caso o tamanho declarado seja maior que o real, parte do `buffer` alocado não será sobrescrito com conteúdo do `payload`. Caso essa memória adicional tenha sido alocada sem ser "zerada", ela pode conter traços de dados anteriores, possivelmente sensíveis.

Caso o tamanho declarado seja menor que o real, acontecerá similarmente à questão (5), mas desta vez o atacante terá controle sobre o conteúdo (afinal, será o `payload content`).