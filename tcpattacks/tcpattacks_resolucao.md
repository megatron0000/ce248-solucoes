# TCP attacks

# 1

(1): O sistema operacional aloca aleatoriamente uma porta ao cliente

(2): A linha que desencadeia o "three-way handshake" é a que faz `connect()`

(3): Não há mapeamento direto entre uma chamada a `write()` e a montagem de um pacote TCP. Se os dados a serem enviados forem muitos extensos, por exemplo, o sistema operacional pode (por baixo dos panos) criar mais de um pacote para um só chamada de `write()`.

# 2

(1): Não bloqueia. Só habilita a capacidade de ouvir na porta (quando cliente se conectar, seu TCB será enfileirado)

(2): O `accept()` bloqueia o programa até que a fila de "half-open connections" tenha algum elemento.

(3): O socket criado por `listen()` especifica onde a aplicação está ouvindo por novas conexões, mas esse socket não é exclusivo para cada cliente conectado. Já o socket criado por `accept()` tem esse papel de identificar cada cliente individualmente.

# 3

(1): Não, porque cada cliente tem seu IP e número de porta.

(2): Também não. Os "datagramas" recebidos identificam o IP e a porta do cliente, então ainda há diferenciação entre eles.

# 4

(1): Se cada datagrama contiver uma das "partes", então o servidor sabe que a divisão entre partes é a mesma que a divisão entre datagramas.

(2): Como o TCP faz buffering e não é possível controlar diretamente quantos bytes de payload são alocados para cada pacote individual, a aplicação precisará de um protocolo adicional (um "combinado") para especificar delimitadores no próprio "stream" de dados.

# 5

Não. O SYN flooding só faz o servidor alocar TCBs em demasia (para armazenar as conexões em estado "half-open"), até atingir o limite máximo da fila, o que faz com que novos clientes não consigam estabelecer conexão.

# 6

Na verdade, poderia usar sempre o mesmo endereço IP, mas ainda teria que variar a porta de origem. Caso contrário, o servidor perceberia todos os pacotes como vindos do mesmo cliente (mesmo par IP-porta), então não alocaria um TCB para cada pacote, e sim um TCB único.

>> Du fala que usar um só IP facilitaria o bloqueio do ataque por filtro de firewall (mas, convenhamos, isso não vem ao caso...)

# 7

A máquina vai receber o SYN+ACK do servidor, percebendo que há algo de errado (afinal, ela não tinha iniciado conexão nenhuma). Então mandaráu um RST ao servidor.

# 8

Essa pergunta é equivalente a "a fila de mensagens half-open é individual para cada porta do servidor ?"

E parece que a fila é mesmo individual por porta ([fonte](https://antmeetspenguin.blogspot.com/2011/04/hardening-tcpip-stack-to-syn-attacks.html)), significando que a 8023 ainda estará disponível.

# 9

Sim, já que é possível manter um só IP de envio caso se varie a porta usada para conexão. Há em torno de 60000 portas efêmeras disponíveis para criar conexões TCP num computador, o que provavelmente é maior que a capacidade da "fila de espera" para conexões half-open.

> ERRADO !!!! Mesmo usando o IP da máquina do atacante, não é possível simplesmente burlar o "three-way handshake", já que ele é feito pelo sistema operacional.

# 10

Como há (supostamente) bastante memória disponível num servidor, o atacante precisará também de bastante potência de ataque para esgotá-la. Por outro lado, atacando a fila de conexões half-open, não estaremos tentando superar a capacidade de armazenamento da RAM do servidor, e sim simplesmente preencher toda a fila de entrada (que tem capacidade de algumas centenas).

>> NÃO É o PONTO !!! É que não conseguiríamos estabelecer conexões com IPs forjados, já que seria difícil acerta o número de sequência inicial adotado pelo servidor.

# 11

Como o número de sequência inicial é fixo, apesar de que o pacote SYN+ACK mandado pelo servidor nunca vai atingir seu destino (porque o IP foi forjado e provavelmente não existe a máquina), o atacante pode simplesmente mandar um ACK com "ACK=número de sequência seguinte".

O servidor, ao receber o segundo pacote, vai entender que a conexão foi estabelecida e alocar toda a memória necessária para tratá-la.

# 12

Se a única medida adotada for abolir a fila, então o servidor não terá como saber se um pacote ACK de um cliente desconhecido é legítimo ou não. Acabará por criar conexões que deveriam ter sido tomadas como inválidas.

# 13

Descobrir o número de sequência e a porta da máquina-cliente

# 14

Sim, já que o SSH está por cima do TCP, e o RST é tratado no nível do TCP

# 15

Não, já que nem há "conexão" (no sentido lógico) em UDP

>> Du diz que uma aplicação pode implementar um mecanismo de reset (claro que pode...). Então, dependendo da aplicação, daria certo mandar um RST

# 16

- Source IP = 10.0.2.5
- Destination IP = 10.0.2.9
- Source Port = porta do cliente (não foi dito qual é)
- Destination Port = porta do servidor (provavelmente 23, já que é telnet)
- Sequence number = 1100 (ou algo parecido, maior que 1000)
- Data = "\n<comando>" (mas codificado em HEX)

# 17

Sim, já que o payload de nosso pacote seria meramente "guardado para depois" no servidor.

# 18

Não, já que não temos como enviar um payload válido (para isso, precisaríamos criptografar o payload com a chave simétrica em uso na conexão, a qual não conhecemos).

# 19


Mitinick mandaria um pacote SYN forjado ao servidor, que responderia com um número de sequência previsível (mas endereçaria o pacote a A, e portanto nunca chegaria ao destino).

Então Mitinick mandaria outro pacote forjado, agora ACK. O servidor, quando o recebesse, entenderia como a resposta de A, e consideraria estabelecida a conexão.

# 20

Suponho que a ideia é mandar um pacote UDP forjado a um servidor A (contendo como "ip de origem" um servidor B que é o alvo do ataque). A então responderia com payload longo, e a resposta iria para B, que seria sobrecarregado caso muitos "A"s fizessem o mesmo.

Isso não funcionaria com TCP porque, quando A mandasse o pacote para B, este, como não tinha anteriormente uma conexão estabelecida com A, simplesmente desconsideraria o pacote.
