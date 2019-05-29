    Dirty COW Lab

# 8.1

Imprime `World` (porque começa no byte de índice 6, que é a letra `W`)

# 8.2

A cópia ocorre quando algum dos processos altera a memória por meio de uma escrita (`copy on write`)

# 8.3

1. O sistema operacional fará uma cópia do conteúdo do arquivo em memória (num outro endereço físico) e remapeará o endereço virtual para esse novo endereço físico, onde a escrita será efetivamente feita.

2. O ponto anterior fala em (i) remapeamento e (ii) escrita. O problema está no fato de a chamada `write` não fazer os dois passos atomicamente. Desta maneira, entre (i) e (ii), um atacante muda o mapeamento de volta para o original (chamando `madvise`) e, quando (ii) for executado, acabará escrevendo no endereço físico original, que não deveria ter sido tocado.

# 8.4

Não modifica o conteúdo do arquivo por causa da flag `MAP_PRIVATE`, que, segundo `man mmap` ativa `copy on write`.

# 8.5

Não é possível, porque o ataque se baseia na manipulação de endereços virtuais, que são únicos por processo.

# 8.6

> Não sei qual segundo arquivo poderia editar para ganhar privilégios de `root`...

`/etc/shadow` e `???`

# 8.7

Não. Vai simplesmente falhar porque o arquivo foi mapeado como `read-only`. A única "exceção" é escrevendo em `/proc/self/mem` com `write(...)`.

# 8.8

Porque `copy-on-write` é uma estratégia implementada a nível de `kernel`.