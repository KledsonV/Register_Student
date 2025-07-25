# Sistema de Gerenciamento de Estudantes

Um sistema de linha de comando desenvolvido em C para gerenciar informações de estudantes e professores, com interface de menus navegável e integração com banco de dados MySQL.

## 📋 Funcionalidades

### Autenticação
- **Login de Professores**: Sistema de autenticação com email e senha
- **Cadastro de Professores**: Registro de novos usuários com validação de email único
- **Validação de Sessão**: Controle de acesso às funcionalidades do sistema

### Gerenciamento de Estudantes
- **Cadastrar Aluno**: Registro com nome, matrícula, curso e três notas
- **Listar Alunos**: Visualização ordenada alfabeticamente
- **Buscar por Matrícula**: Consulta individual de estudante
- **Ranking**: Exibição dos melhores alunos por média
- **Filtrar por Curso**: Listagem de estudantes por curso específico
- **Editar Dados**: Modificação completa das informações do aluno
- **Excluir Aluno**: Remoção com confirmação de segurança

### Recursos Adicionais
- **Cálculo Automático**: Média das três notas calculada automaticamente
- **Exportação**: Geração de arquivo de texto com dados dos estudantes
- **Interface Colorida**: Terminal com cores para melhor experiência
- **Navegação por Teclado**: Controle via setas direcionais e Enter

## 🛠️ Tecnologias Utilizadas

- **Linguagem**: C
- **Banco de Dados**: MySQL
- **Biblioteca**: MySQL C API
- **Sistema**: Windows (uso de `windows.h` e `conio.h`)

## 🏗️ Estrutura do Banco de Dados

### Tabela `teachers`
```sql
- id (INT, AUTO_INCREMENT, PRIMARY KEY)
- name (VARCHAR)
- email (VARCHAR, UNIQUE)
- password (VARCHAR)
```

### Tabela `student`
```sql
- id (INT, AUTO_INCREMENT, PRIMARY KEY)
- name (VARCHAR)
- registration (INT, UNIQUE)
- course (VARCHAR)
- note1 (FLOAT)
- note2 (FLOAT)
- note3 (FLOAT)
- average (FLOAT)
```

## ⚙️ Configuração

1. **Instalar MySQL**: Configure o servidor MySQL
2. **Configurar Conexão**: Edite as constantes no código:
   ```c
   #define HOST "seu_host"
   #define USER "seu_usuario"
   #define PASSWORD "sua_senha"
   #define DBNAME "nome_do_banco"
   #define PORT sua_porta
   ```
3. **Compilar**: Use um compilador C com suporte ao MySQL:
   ```bash
   gcc -o sistema main.c -lmysqlclient
   ```

## 🎮 Como Usar

### Menu Principal
- **Opção 1**: Login (para professores cadastrados)
- **Opção 2**: Cadastrar novo professor
- **Opção 3**: Testar conexão com banco de dados
- **Opção 4**: Sair do sistema

### Painel de Controle (Após Login)
1. **Exibir Alunos**: Lista todos em ordem alfabética
2. **Buscar Aluno**: Pesquisa por matrícula específica
3. **Melhores Alunos**: Ranking por média decrescente
4. **Alunos por Curso**: Filtragem e ordenação por curso
5. **Cadastrar Aluno**: Novo registro completo
6. **Editar Aluno**: Modificar dados existentes
7. **Excluir Aluno**: Remover com confirmação
8. **Exportar Dados**: Gerar arquivo de texto
9. **Logout**: Retornar ao menu principal

## 🎯 Navegação

- **↑/↓**: Navegar entre opções
- **Enter**: Confirmar seleção
- **ESC**: Voltar/Cancelar operação

## 📁 Recursos de Arquivo

- **Exportação**: Cria pasta `Tabela` com arquivo `Alunos.txt`
- **Formatação**: Dados organizados e legíveis
- **Animação**: Barra de progresso durante exportação

## 🔐 Validações Implementadas

- Email único para professores
- Matrícula única para estudantes
- Campos obrigatórios não vazios
- Confirmação de senha no cadastro
- Verificação de existência antes de operações

## 📊 Funcionalidades de Relatório

- Ordenação alfabética de estudantes
- Ranking por performance acadêmica
- Agrupamento por curso
- Cálculo automático de médias
- Exportação formatada para arquivo

💡 Autor
Desenvolvido por Kledson Vinicius
