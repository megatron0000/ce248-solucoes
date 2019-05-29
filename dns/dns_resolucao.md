# DNS

# 1

Adicionar uma entrada `127.0.0.1 myhost` no arquivo `/etc/hosts`

# 2

Usando `root server` `a.root-servers.net`, fazemos:

- `dig @a.root-servers.net nsf.gov`
- `dig @a.gov-servers.net nsf.gov`
- `dig @ns1.nsf.gov nsf.gov`

Finalmente, vem a resposta: 128.150.4.107

# 3

Um servidor DNS usa protocolo UDP e porta 53

# 4

Verificado ! (opção `+vc` no `dig`)

# 5

Já fiz na 2 (em síntese, é `top-down`, supondo que começamos sem nada no `cache` do servidor de DNS local).

# 6

`93.184.216.34.in-addr.<algo>`

# 7

O IP do `root-server` vem incluído com o sistema operacional

# 8

O campos `ID` é aleatório (16 bits) e, de certa forma, a porta de origem também é aleatória (outros 16 bits).

# 9

Consiste em forjar respostas DNS de maneira que um servidor local armazene em `cache` um mapa `domínio -> IP` incorreto.

# 10

Quando um pacote de resposta é recebido, não há nenhum mecanismo de autenticação da resposta, ou seja, não foi prevista uma maneira de verificar se o pacote realmente foi enviado pelo servidor de DNS verdadeiro.

# 11

(1): Encontrar os números aleatórios corretos descritos na questão 8. Também mitigar o problema de, quando o ataque falha e o mapa `domínio -> IP` é recebido corretamente pela vítima, o `cache` dela demorar a expirar e, antes de isso acontecer, ser impossível fazê-la gerar um pedido DNS pelo mesmo nome de domínio que já está em cache.

(2): O ataque Kaminsky gera pedidos para subdomínios aleatórios, cada pedido com um domínio diferente. Por isso, a máquina vítima não aproveita seu cache e dispara um pedido DNS toda hora. Com isso, cedo ou tarde, o atacante consegue acertar os números aleatórios da resposta forjada, e então manda a resposta contendo um `Authority Section` que informa um valor incorreto para o domínio do `nameserver` responsável pelo subdomínio pedido.

# 12

A ataque pode dar certo. Para isso, Bob responderia (no lugar de `.COM`) com uma `Answer Section` contendo o mapeamento `domínio -> IP` que Bob deseja.

# 13

Ele pode forjar uma resposta do `nameserver` de `.com`. Nela, na `Authority Section`, haverá a entrada dizendo que `bank32.com` tem `nameserver` `x`, em que `x` é o domínio do servidor comandado por Bob.

# 14

O `Authority Section` está OK (afinal, o `nameserver` de um domínio não necessariamente coincide com o domínio em si), mas o `Additional Section` não. Como ele informa um nome de domínio `out of zone`, o IP lá descrito não será confiado.

# 15

Os 3 mapeamentos `domínio -> IP` descritos na `Additional Section` serão descartados, bem como o `example.net` da `Authority Section`. Nos dois casos, isso será feito porque os nomes de domínio correspondentes estão `out of zone` com relação ao pedido (`www.example.com`).

# 16

Lance um ataque ao DNS de maneira que o `lookup` reverso seja comprometido.

# 17

Como são vários servidores, se um falhar, ainda existem os outros.

# 18

Ter redundância de servidores.

# 19

?

# 20

O atacante manda vários pedidos DNS com IP de origem forjado. As resposta irão todas para a vítima.
