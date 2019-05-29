        # Format Strings Lab

# Questão 1

Testada:

```c
#include <stdarg.h>
#include <stdio.h>

void totallength(char* string1, ...) {
    int total = 0;
    va_list args;
    va_start(args, string1);
    while(string1 != NULL) {
        char c = string1[0];
        int i;
        for (c = string1[i = 0]; c != '\0'; c = string1[++i], total++) {
        }
        string1 = va_arg(args, char*);
    }
    printf("%d\n", total);
}
```

# Questão 2

No `Buffer Overflow`, escrevemos vários valores ao longo da pilha, até atingir o endereço do `return address`, no qual finalmente escrevemos o valor desejado.

Por outro lado, no `Format String Vulnerability`, escrevemos individualmente o endereço do `return address`, sem precisar modificar quaisquer outras posições da pilha.

Nesse sentido a segunda alternativa é menos restrita por permitir escolher o endereço cujo valor será modificado. No `Buffer Overflow`, estamos restritos a endereços "em cima" do buffer a ser explorado (se o buffer começa no endereço `x`, não é possível alterar nenhum endereço maior que `x`).

# Questão 3

Não é possível usar o `StackGuard` porque seu funcionamento pressupõe que, quando a pilha é alterada, isso é feito por modificações em vários endereços (como é o caso do `Buffer Overflow`). Em algum endereço, haverá um "guarda" que, se for alterado, denotará a ocorrência de uma irregularidade.

Mas, como o `Format String Vulnerability` permite alterar endereços singulares (individuais) dentro da pilha, o guarda não será tocado, e portanto não permitirá detectar o ataque.

# Questão 4

Usando `%d` para pular endereços (4 bytes) e `%s` para causar leitura de endereço proibido de memória (endereço 0), a menor `string` que com certeza derrubaria o programa é `%d%d%s`.

Por outro lado, usando `%lli` (geralmente 64 bits - 8 bytes), poderíamos ter `%lli%s` que ainda derrubaríamos o programa.

# Questão 5

- O input deve começar com o número `0xAABBCDA6`. 
- Em seguida, deve conter a `string` `%d%d%d%d%d%d%d` (7 vezes, para fazer o `va_list` pular os 28 bytes na pilha da figura). 
- Geramos quantidade suficiente de bytes escritos para chegar à contagem `0xAABB` (43707 em base decimal, que é a primeira parte do endereço onde residirá o código do atacante). Para atingir esse objetivo, continuamos o input com `%43704c` (pois o número que inicia o input já tinha impresso 4 bytes).
- Para 
- Neste ponto, nosso input já tem `4 + 14 + 7 = 25` bytes. 
-

> Muitos detalhes... sugou
> 
> Mas essa questão vai acabar mostrando a necessidade do @@@@ para separar os dois endereços no início do input

# Questão 6

A questão anterior já está escrita para isso.

# Questão 7

Se a `format string` não for um literal, isto é, for uma variável como em `printf(fmt)`, o compilador não conseguirá fazer a checagem (porque isso poderia envolver determinar o valor de `fmt`, o que não é factível no caso geral).

# Questão 8

Se desativarmos temporariamente o privilégio, o atacante pode inserir código que execute, como uma de suas primeiras instruções, a restauração do privilégio perdido. De nada adianta rebaixar o programa temporariamente.

# Questão 9

Sim, basta usar `Return to libc` (ver questão 10).

# Questão 10

- Precisamos alterar o valor contido no `return address` (endereço `0xAABBCDA6` na figura) para apontar a alguma função desejada da libc.
- Também precisamos alterar os endereços `0xAABBCDA6 +4 +4, +4 +8, ..., +4 +4n`, em que `n` é a quantidade de argumentos a ser fornecida para a função escolhida da libc. Isto porque são nesses endereços que a função procurará seus argumentos.

Isso pode ser feito, como no restante do lab, usando o formato `%n` para escrever em endereços arbitrários.

# Questão 11

Sim, é possível. Primeiro, usamos `%hn` para escrever 2 bytes de cada vez (em vez de 4 bytes, que é muito grande). Então, como 2 bytes suporta no máximo o `int` `2^16 - 1 = 65535`, basta fazermos o printf imprimir 65536 caracteres e então usar `%hn`, já que 65536 não cabe num int, donde gerará overflow e resultará em 0.

obs: Precisamos proceder analogamente para os outros 2 bytes.