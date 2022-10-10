
# Segmento de Memória Compartilhada
Códigos feitos em C para criar um segmento de memória compartilhada, além de escrever, ler e apagar o conteúdo.

# Observações adicionais:
Para compilar: `cc progN.c -o progN`  
Para executar: `./progN`  
Obter informações do IPC (semáforos, memória compartilhada e filas de mensagens): `ipcs`

## Bibliotecas:
`#include <sys/ipc.h>`  
`#include <sys/shm.h>`

## Criando variaveis:
```
key_t  key;
int    shmid, tamanho=2048;
```
- "key" do tipo "key_t" para armazenar a chave hexadecimal de acesso do segmento.
- "shmid" para armazenar o endereço (id) do segmento.
- "tamanho" para definir um tamanho.

## Comando para criar uma chave hexadecimal.
```
...
key=ftok("/tmp",'a');
...
```
Os parâmetros são: nome do diretório de armazenamento e nome arquivo de armazenamento.

## Comando para **criar** um segmento de memória.
```
...
shmid=shmget(key, tamanho, 0600|IPC_CREAT);
...
```
Os parâmetros são: variável da chave, tamanho desejado e permissões para o segmento junto do comento de criar.

- **OBSERVAÇÃO: O comando shmid() pode ser usado também apenas para descobrir se um segmento existe.**

## Comando para **descobrir** um segmento de memória.
```
...
shmid=shmget(key, tamanho, 0);
...
```
Os parâmetros são: variável da chave, tamanho desejado e 0.

- Se O shmid não conseguir criar ou descobrir o segmento de memória, irá retorna -1, caso contrári, irá retorna qualquer outro valor.
**Os comandos de descobrir e criar chave são usados em todos os programas, porém decidi ocultá-los para melhor explicação dos outros**.

## Comando para **criar** um segmento de memória (P1 - Produtor).
- Antes de mais nada, precisamos criar um ponteiro para ser o intermediário e conectá-lo.
```
...
char mensagem[80] = "Oi mundo.", *shm;
...
shm=shmat(shmid,0,0); //Conexão
...
strcpy(shm,mensagem); //Escrevendo
...
```
O comando shmat é o responsável pela **conexão do processo com o segmento**.  
Os parâmetros de shmat são: o endereço (id) do segmento, 0 e 0.
- Neste código, estamos copiando a mensagem "Oi mundo" para o ponteiro, ou seja, copiando para o segmento.
- Função Produtor.

## Comando para **ler** um segmento de memória (P1 - Consumidor).
- Antes de mais nada, precisamos criar um ponteiro para ser o intermediário e conectá-lo.
```
...
shm=shmat(shmid,0,0); //Conexão
...
printf("Recuperando %s do segmento %d.\n",shm,shmid); //Lendo
...
```
Para ler, basta apenas imprimir o conteúdo do ponteiro.

## Comando para **remover** um segmento de memória.
```
...
shmctl(shmid,IPC_RMID,0);
...
```
Este comando examina e modificar o segmento de memória.  
Os parâmetros são: endereço (id) do segmento, ação que desejar executar e 0.
- A instrução IPC_RMID é a responsável pela remoção.