# SQL Injection

# 1

Sim, basta o usuário malicioso passar um `$eid` como `bla, 256)'; DROP TABLE bla; #`

> Mesmo se só 1 comando for permitido, ainda é possível pelo menos ganhar acesso à tabela inteira.

# 2

Não tem mais vulnerabilidade. O valor de `$eid` não tem mais como transgredir os limites da função hash.



# 3

Sim, basta injetar tanto o comando desejado quanto um comando adicional que servirá meramente para dar a continuidade necessária:

`$eid === '; DROP TABLE bla; SELECT * FROM employee WHERE eid=bla`

> Mesmo se só 1 comando for permitido, basta inserir um `OR` antes do `#` (afinal, o comentário não se estenderá à linha seguinte).

# 4

Ele (i.) finaliza o comando atual, (ii.) insere o comando desejado (aumentar o salário) e (iii.) insere um inicializador de comentário

> Mesmo se só 1 comando for permitido, ainda é possível !

# 5

Mesmo das anteriores.

> O Du diz que ainda é possível mesmo que só 1 comando seja permitido. Mas esquece de pôr no enunciado que o atacante também tem acesso a `$eid`, já que, sem isso, o atacante teria que já conhecer de antemão a senha do Bob.

# 6

`$eid` finaliza o comando, insere um comando arbitrário e inicializa outro comando, a ser fechado pelo `$passwd`

> Mais fácil: em vez de iniciar um comando por último, só inserir um `#`.

# 7

Sim, basta usar o `;`.

> Du diz que depende (consultar livro).

# 8

Não, porque um atacante pode forjar o pedido ao servidor de maneira autônoma (não necessitando do navegador). Mesmo no navegador, ainda é possível manipular manualmente o pedido HTTP antes de ele ser finalmente enviado.

# 9

Não. 

Se dois comandos forem permitidos, o usário malicioso simplesmente não usa comentários (`#`), optando pela técnica de inserir uma finalização de comando, seguida de um comando arbitrário e, finalmente, por uma inicialização de comando.

Se só um comando for permitido, o atacante insere um `?` e só depois o comentário (`#`). Assim o `bind` do parâmetro ainda ocorrerá com sucesso, mas de maneira a não atrapalhar o atacante.

# 10

```php
$sql = "UPDATE employee SET password=? WHERE eid=? and password=?";
if ($stmt = $conn->prepare($sql)) {
    $stmt->bind_param("sss", $newpwd, $eid, $oldpwd);
    $stmt->execute();
}
```

# 11

Não há caminho direto à base de dados, mas há caminho indireto, passando pelo servidor web. É por esse caminho indireto que o ataque ocorre.

# 12

Em ambos os casos, a contramedida é uma garantia de que campos de dados não serão manipulados e acabar sendo tratados como campos de código.
