# Lab 1: Programas set-uid

[Link para perguntas] (https://docs.wixstatic.com/ugd/ff94d5_6a9f8b3c69bd490a912fc17c2552c8f5.pdf)

## 1.1

Não ! Testei !

## 1.2

Não ! É equivalente ao anterior.

## 1.3

O programa está escrito para fazer só uma determinada coisa, não o que o usuário quiser

## 1.4

Não, porque as permissões de arquivo são configuradas por usuário. Ou seja, quando trocar o proprietário, as permissões também trocarão para refletir as permissões "default" desse novo usuário. 

Por outro lado, caso o proprietário original seja restaurado (com um novo chown), as permissões configuradas por ele serão reestabelecidas.

## 1.5

**Resposta possivelmente superficial**: Um programa setuid executa com permissões do proprietário. Ao trocar de proprietário, mas esquecer de desativar o bit setuid, poderíamos dar "poderes demais" ao arquivo (por exemplo, se o novo proprietário fosse *root*).

## 1.6

**Parece** que o setuid bit é retirado (!!!) quando qualquer edição é feita ao binário. Então, não dá para modificar e continuar com EUID de root ao executar.

**Mas a pergunta não era essa ! Era sobre modificar num debugger!** E é óbvio que o programa de debug não será setuid e, portanto, não executará como root ele próprio

## 1.7

*system()* usa */bin/sh* por trás. Isso pode, por exemplo, executar dados como se fosse código (consequência possível: Executar mais de um comando quando o intencionado era 1 só).

## 1.8

Sob teste, não é possível ("bash: /etc/shadow: Permission denied"). Ao que parece, a ação de abrir o arquivo do qual o processo irá ler é por conta do shell sendo executado, ou seja, é feito com as permissões do usuário.

## 1.9

Como o processo pai é executado com RUID bob, entendemos que bob é o usuário que invocou o programa. Pela descoberta da questão anterior, stdin e stdout desse processo só podem ser coisas que bob tenha permissão de abrir. Então não há "capability leaking" porque stdin e stdout não são recursos protegidos (desde o início, eram acessíveis pelo próprio bob)

## 1.10

Testado e funciona: de acordo com o manual (*man more*), *more* lê a variável de ambiente *SHELL* para saber com que shell executar comandos (pois o programa possibilita execução interativa de comandos usando a diretiva *!command*). Basta manipular essa variável de ambiente e fazê-la apontar para um arquivo malicioso (que executará com permissão de *root*).

## 1.11

Bom, não vai funcionar se o usuário não for *sudoer*, mas uma alternativa é criar um grupo e adicionar a ele todos (e somente) os usuários com ID menor que 1000. Nas permissões do arquivo, o usuário define *r--* na seção *others*.

## 1.12

O ataque é simples: Coloque um ";" na url e, depois dele, qualquer comando que queira executar no computador do Sam. 

Para evitar esse tipo de ataque, em que dados são tratados como código, Sam poderia usar **execve()** em vez de **system()**.

## Interessante

SETUID geralmente é ignorado em arquivos com shebang. Conferir [aqui](https://unix.stackexchange.com/questions/364/allow-setuid-on-shell-scripts)