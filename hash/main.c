#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 100
#define FILE_NAME "contacts.txt"

typedef struct Contact {
    char name[50];
    char phone[15];
    struct Contact* next;
} Contact;

Contact* hashTable[TABLE_SIZE];

// Funcao hash simples: soma dos valores ASCII dos caracteres do nome
unsigned int hashFunction(const char* name) {
    unsigned int hash = 0;
    while (*name) {
        hash += *name++;
    }
    return hash % TABLE_SIZE;
}

// Adicionar contato
void addContact(const char* name, const char* phone) {
    unsigned int index = hashFunction(name);
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->next = hashTable[index];
    hashTable[index] = newContact;
    printf("Contato adicionado com sucesso.\n");
}

// Buscar contato
void searchContact(const char* name) {
    unsigned int index = hashFunction(name);
    Contact* current = hashTable[index];

    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("Telefone de %s: %s\n", name, current->phone);
            return;
        }
        current = current->next;
    }
    printf("Contato nao encontrado.\n");
}

// Remover contato
void removeContact(const char* name) {
    unsigned int index = hashFunction(name);
    Contact* current = hashTable[index];
    Contact* prev = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                hashTable[index] = current->next;
            }
            free(current);
            printf("Contato removido com sucesso.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Contato nao encontrado.\n");
}

// Exibir todos os contatos
void displayContacts() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contact* current = hashTable[i];
        if (current) {
            printf("Indice %d:\n", i);
            while (current) {
                printf("  Nome: %s, Telefone: %s\n", current->name, current->phone);
                current = current->next;
            }
        }
    }
}

// Salvar contatos no arquivo
void saveContactsToFile() {
    FILE* file = fopen(FILE_NAME, "w");
    if (!file) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        Contact* current = hashTable[i];
        while (current) {
            fprintf(file, "%s,%s\n", current->name, current->phone);
            current = current->next;
        }
    }

    fclose(file);
    printf("Contatos salvos no arquivo.\n");
}

// Carregar contatos do arquivo
void loadContactsFromFile() {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    char line[100];
    char name[50], phone[15];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%49[^,],%14s", name, phone) == 2) {
            addContact(name, phone);
        }
    }

    fclose(file);
    printf("Contatos carregados do arquivo.\n");
}

// Medir tempo de execucao de uma funcao
double measureTime(void (*func)(const char*, const char*), const char* arg1, const char* arg2) {
    clock_t start = clock();
    func(arg1, arg2);
    clock_t end = clock();
    return ((double)(end - start) / CLOCKS_PER_SEC) * 1000; // Tempo em ms
}

int main() {
    int choice;
    char name[50], phone[15];

    // Inicializar a tabela hash
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    // Carregar contatos do arquivo
    loadContactsFromFile();

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nome: ");
                scanf(" %49[^\n]", name);
                printf("Telefone: ");
                scanf(" %14s", phone);
                printf("Tempo de insercao: %.2f ms\n", measureTime((void (*)(const char*, const char*))addContact, name, phone));
                break;
            case 2:
                printf("Nome: ");
                scanf(" %49[^\n]", name);
                printf("Tempo de busca: %.2f ms\n", measureTime((void (*)(const char*, const char*))searchContact, name, ""));
                break;
            case 3:
                printf("Nome: ");
                scanf(" %49[^\n]", name);
                removeContact(name);
                break;
            case 4:
                displayContacts();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (choice != 0);

    // Salvar contatos no arquivo
    saveContactsToFile();

    // Liberar memoria
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contact* current = hashTable[i];
        while (current) {
            Contact* toFree = current;
            current = current->next;
            free(toFree);
        }
    }

    return 0;
}
