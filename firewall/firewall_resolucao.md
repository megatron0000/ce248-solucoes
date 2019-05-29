# Firewall

# 1

Uma funcionalidade do Linux que oferece `hooks` para vários pontos do ciclo de vida de `packets` ao longo da `kernel network stack`. Usando `kernel modules`, é possível registrar funções para serem executadas nesses `hooks`, possivelmente para atuar como `logger` ou filtro de pacotes.

# 2

... Ah, vai olhar o manual para lembrar...

# 3

Porque queremos executar código, e ainda no kernel !! O linux permite isso (i.e. executar código no kernel) por meio de `kernel modules`.

# 4

- `1 == block` 
- `2 == filterHook`
- `3 == block`
- `4 == setUpFilter`
- `5 == removeFilter`
- `6 == skb`
- `7 == 10.0.2.5`
- `8 == 80`
- `9 == NF_DROP`

# 5

- `NF_IP_PRE_ROUTING`
- `NF_IP_POST_ROUTING`

# 6

Sim, pode, já que os `hooks` do netfilter disponibilizam o próprio pacote que navega pelo kernel, em oposição a uma mera cópia dele.

# 7

Ele intercepta a conexão do cliente, e estabelece a conexão com ele como se fosse o próprio servidor. Em seguida, já tendo conectado com o cliente, o SYNPROXY estabelece uma conexão com o servidor mandando pacotes forjados, de maneira que o servidor pensará que o próprio cliente está estabelencendo a conexão.

Uma vez completado o processo, o SYNPROXY pode parar de interceptar o tráfego que tudo seguirá normalmente.

A utilidade do SYNPROXY é que, nas conexões iniciais com o cliente, ele faz a mitigação de SYN flooding usando SYN COOKIES por conta própria.

# 8

Exemplo: queremos bloquear pacotes de entrada que usem o protocolo TCP, a não ser que eles façam parte de uma conexão cliente-servidor usada para navegar na web. Com um `stateful firewall`, poderemos distinguir esses últimos pacotes (que desejamos deixar passar) dos primeiros (que desejamos bloquear).

# 9

Esses protocolos não têm um mecanismo de "estabelecimento de conexão", mas podem muito bem seguir padrões de `request-response` tradicionais (verificações de integridade e similares ficam a cargo das aplicações, entretanto). Assim sendo, um `stateful firewall` pode usar o fato de que outros pacotes já transitaram na mesma quádrupla `sourceIp-sourcePort-destIp-destPort` para entender que "existe uma conexão".

# 10

Não. É uma interface "mais fácil" para o `iptables`.

# 11

`sudo iptables -A INPUT -s 192.168.10.0/24 -j ACCEPT`

# 12

`sudo iptables -A INPUT --dport 22 -j DROP`.

Repetir para as outras portas.

# 13

(1): `ssh -L <porta qualquer>:sirius:9090 alien@mars`

(2): `nc localhost <porta escolhida acima>`

# 14

Os pacotes vão para um socket escutando na porta local. Lá, eles são encriptados e mandados como payload da conexão ssh à máquina remota. Na máquina remota, são reconstituídos e enviados (com um `source ip diferente`) para o destino intencionado.

# 15

`ssh -D <porta local qualquer> alien@mars`

# 16

`ssh -R <porta em que o servidor vai escutar>:localhost:<minha porta> alien@mars`