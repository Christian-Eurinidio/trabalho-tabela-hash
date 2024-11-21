##Contatos com Tabela Hash

Este é um programa em C para gerenciar uma lista de contatos utilizando uma tabela hash com encadeamento (listas ligadas). O programa permite adicionar, buscar, remover e exibir contatos, além de salvar e carregar os dados em um arquivo.

## Funcionalidades

- **Adicionar contato**: Permite adicionar um novo contato com nome e telefone.
- **Buscar contato**: Permite buscar um contato pelo nome e exibe o telefone associado.
- **Remover contato**: Permite remover um contato da lista.
- **Exibir todos os contatos**: Exibe todos os contatos armazenados na tabela hash.
- **Salvar contatos**: Salva todos os contatos em um arquivo chamado `contacts.txt`.
- **Carregar contatos**: Carrega os contatos do arquivo `contacts.txt` ao iniciar o programa.
- **Medição de tempo**: Mede o tempo de execução das operações de inserção e busca.

## Estrutura de Dados

O programa utiliza uma tabela hash para armazenar os contatos. A chave de hash é gerada com base na soma dos valores ASCII dos caracteres do nome do contato. Cada posição na tabela hash contém uma lista encadeada de contatos que compartilham a mesma chave de hash.

### Definição de `Contact`

```c
typedef struct Contact {
    char name[50];
    char phone[15];
    struct Contact* next;
} Contact;
```

- `name`: Nome do contato.
- `phone`: Número de telefone do contato.
- `next`: Ponteiro para o próximo contato na lista encadeada.

### Tamanho da Tabela

A tabela hash é implementada com um tamanho fixo de `100` posições (`TABLE_SIZE`).

## Como Usar

1. **Inicialização**: Ao iniciar o programa, ele automaticamente carrega os contatos armazenados no arquivo `contacts.txt` (se o arquivo existir).
   
2. **Menu**:
    - **1 - Adicionar contato**: Digite o nome e o telefone do novo contato.
    - **2 - Buscar contato por nome**: Digite o nome do contato e o programa retornará o telefone associado.
    - **3 - Remover contato**: Digite o nome do contato para removê-lo da lista.
    - **4 - Exibir todos os contatos**: Exibe todos os contatos armazenados na tabela hash.
    - **0 - Sair**: Encerra o programa.

3. **Salvar dados**: Ao sair, o programa salva todos os contatos no arquivo `contacts.txt`.

## Funções Importantes

### Função Hash

A função hash é simples e utiliza a soma dos valores ASCII dos caracteres do nome do contato para gerar um índice. A função retorna o índice dentro do tamanho da tabela.

```c
unsigned int hashFunction(const char* name);
```

### Medição de Tempo

A função `measureTime` mede o tempo de execução de operações como a inserção de um novo contato ou a busca de um contato.

```c
double measureTime(void (*func)(const char*, const char*), const char* arg1, const char* arg2);
```

### Manipulação de Contatos

- **Adicionar contato**:
    ```c
    void addContact(const char* name, const char* phone);
    ```
  
- **Buscar contato**:
    ```c
    void searchContact(const char* name);
    ```

- **Remover contato**:
    ```c
    void removeContact(const char* name);
    ```

- **Exibir contatos**:
    ```c
    void displayContacts();
    ```

- **Salvar contatos no arquivo**:
    ```c
    void saveContactsToFile();
    ```

- **Carregar contatos do arquivo**:
    ```c
    void loadContactsFromFile();
    ```

## Arquivo `contacts.txt`

O arquivo `contacts.txt` é utilizado para armazenar os contatos de forma persistente. Cada linha do arquivo contém o nome e o telefone de um contato, separados por vírgula. Por exemplo:

```
João,123456789
Maria,987654321
```

## Compilação e Execução

1. Compile o programa utilizando um compilador C, como o `gcc`:
    ```
    gcc -o contatos contatos.c
    ```

2. Execute o programa:
    ```
    ./contatos
    ```

3. Siga as instruções no menu para interagir com o programa.

## Observações

- A tabela hash utiliza o encadeamento (listas ligadas) para resolver colisões.
- O arquivo `contacts.txt` será sobrescrito a cada execução, portanto, seus dados serão perdidos se não forem salvos corretamente.
- O programa realiza a medição de tempo das operações de inserção e busca, fornecendo o tempo de execução em milissegundos.

## Licença

Este projeto está licenciado sob a [MIT License](https://opensource.org/licenses/MIT).
