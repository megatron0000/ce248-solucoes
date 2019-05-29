# VPN

# 1

Túnel SSH não é transparente: caso use `-L`, por exemplo, aplicação local deverá endereçar seus pacotes explicitamente para a porta em que o SSH está ouvindo localmente (e então ele encaminhará os pacotes para o servidor remoto). Não há "IPs falsos".

# 2

(a): 192.168.0.13

> Não ! É 128.230.153.80 ! Observar que toda a subrede é mapeada para essa interface. Só pode ser ela a virtual.

(b): 128.230.153.12
(c): 128.230.153.80

> Não ! É 192.168.0.13 ! 

(d): Ele deve adicionar uma entrada dizendo para usar a interface TUN no caso de o IP de destino ser 8.8.8.8

# 3

(a): O payload de (2) é (1), apesar de criptografado.

(b): Relação contrária à anterior

(c): 
    1: 10.0.4.1 -> 10.0.20.100
    2: 209.164.131.32 -> 128.230.208.97
    3: Igual a 2
    4: Igual a 1

(d): 
    Mapear 10.0.20.0/24 para a interface 10.0.4.1
    ... parece que só

(e):
    Mapear 10.0.4.1 para a interface 10.0.5.1

(f):
    Mapear 10.0.4.1 para o gateway IP(eth2)

(g): Acho que vai ficar tentando retransmitir no socket real. Quando restaurar a conexão, parece que a transmissão se efetivará.

# 4

(a)
- Host U
    - Mapear 192.168.80.0/24 para o gateway 192.168.60.5
- VPN Client
   - Mapear 192.168.80.0/24 para a interface 10.5.0.21
- VPN Server
    - Mapear 192.168.60.0/24 para a interface 10.4.0.99
- Host V
    - Mapear 192.168.60.0/24 para o gateway 192.168.80.5

(b)
IP de origem será 192.168.60.6

(c)
IP de origem: 91.2.2.2
IP de destino: 128.3.3.3

(d)

(1) FROM: Host U TO: Host V

Chega ao gateway, que manda para tun0, que manda pela interface externa

(2) FROM: VPN Client ethExterna TO: VPN Server ethExterna PAYLOAD: Encrypt(1)

Chega ao VPN Server, que processa (aplicação de VPN) e descriptografa. Manda para seu tun0.

tun0 escreve na interface local. 

Host V recebe. O pacote é como (1). Host V responde:

(3): FROM: Host V TO: Host U

Chega ao gateway, que manda para tun0, que manda pela interface externa.

Restante do processo é análogo
