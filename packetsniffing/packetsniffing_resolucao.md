# Packet Sniffing & Spoofing

# 1

A interface `eth0` não existe no computador que está executando o código.

# 2

O terceiro argumento a `pcap_open_live` habilita ou desabilita o modo promíscuo. Em `0`, ele desativa o tal modo, significando que somente pacotes destinados à própria máquina serão recebidos.

# 3

A chamada `pcap_open_live()` é a que exige privilégios de `root` (afinal, por baixo dos panos, a biblioteca abrirá um `raw socket`, algo que exige privilégios).

# 4

Imediatamente antes da chamada a `pcap_setfilter()`, desativar o privilégio temporariamente com `seteuid(seed)`.

> Du afirma que fez o teste e viu que `pcap_setfilter()` não mais precisa de privilégios.

# 5

A primeira permite filtros arbitrários (afinal, é a aplicação que decidirá o que fazer com cada pacote recebido). A segunda é mais eficiente, porque o filtro BPF é implementado a nível de kernel, evitando a necessidade de criar uma cópia do pacote a ser passado para a aplicação caso o filtro já acuse que o tal pacote não é desejado por ela.

# 6

Fatalmente, veremos que algum subprocesso estará como `root`.

> ERRADO ! Du encontra um processo `dumpcap` que tem uma `capability` (`CAP_NET_RAW` e `CAP_NET_ADMIN`) que permite a ele abrir `raw sockets`. 

# 7

Se o programa começar como `root`, ele pode abrir um `raw socket` e configurar filtros (ações só possíveis como `root`). Tendo feito isso, pode rebaixar o privilégio, pois, como o `socket` já estará aberto, o programa ainda terá acesso a ele e nada parará de funcionar.

Essa possibilidade existe para evitar que eventuais brechas durante a execução possam provocar danos que não ocorreriam sem `root privilege`.

# 8

Rebaixar o privilégio após ter aberto o `socket` e configurado os filtros.

# 9

...

# 10

Numa máquina `little endian`, serão alocados `255 * 2^24` bytes, ou quase 4 gigabytes.

# 11

Numa máquina `little endian`, os resultados serão `255 * 2^24` nos dois `printf`. Numa máquina `big endian`, ambos os `printf` imprimirão `255`.

# 12

Talvez o IP seja o da própria máquina A e, por algum motivo, o pacote nunca saia dela (afinal, ele é endereçado à própria máquina).

> Não é essa a justificativa do Du ! Ele diz que, para saber o MAC de destino do pacote, o OS envia um pedido `ARP`. Provavelmente, a tal máquina não existe na rede, então ninguém responde ao pedido e, consequentemente, o OS não fica sabendo o MAC de destino e não envia pacote algum.

# 13

Fake news ! ARP poisoning requer que o atacante tenha acesso interno à LAN da empresa, o que não foi o caso (eles interagiram com a empresa através do `gateway` dela).

> Du fala muito melhor: ARP é protocolo de nível 2 (link layer) ! Então nunca sairá da rede local em que circula (afinal, link layer lida com MACs).

# 14

De acordo com a o manual do Linux, pacotes maiores que 64k não são enviados (é gerado um erro `EMSGSIZE`).

> Du dá a alternativa de programar na mão o mecanismo (já existente) de fragmentação: Preencher o campo `fragment offset` do header IP corretamente.

# 15

O Du não fala, mas há uma **resposta** de cada recipiente do `broadcast`. Então, para o atacante, basta forjar o pacote com IP de destino igual ao da máquina que se deseja atacar.

# 16

Forge vários pacotes com IP de destino igual ao da máquina que se deseja atacar.
