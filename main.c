#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>

#define HOST "" // DB HOST
#define USER "" // DB USER
#define PASSWORD "" // DB PASSWORD
#define DBNAME "" // DB NAME
#define PORT **** // DB PORT

// Define Key
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ESC 27
#define KEY_ENTER 13

// Functions

bool file_exists(const char *Arquivo);
void menu();
void menuIsLogged();
void connDB();
void registerProf();
void loginProf();
void registerStudent();
void displayStudents();
void bestStudents();
void displayStudent();
void displayCourse();
void deleteStudent();
void deleteConfirm( int registration );
void editStudent();
void modifyStudent(int registration);
void exportTable();
int create_File();
void writeLogFile(const char *text);
void resetFile();
void animation();


// Variables

bool isLogged = false;
bool emailExists = false;
bool registrationValid = false;
int idTeacherLogged;


int main()
{
    setlocale(LC_ALL, "portuguese");

    // Menu

        menu();

    //isLogged = true;
    //menuIsLogged();

    // Conecction Test
    //connDB();

    return 0;
}

// Menu ( Not Logged )
void menu()
{
    int key;
    int value = 0;

    while(1)
    {
        system("cls");
        printf("\033[0;31m******  Menu Principal ******\033[0;0m\n");
        printf("\033[1;0m \n");
        printf(" %s  1 - Entrar \n", (value == 0) ? "\033[1;31m-> " : "\033[1;0m ");
        printf(" %s  2 - Cadastrar \n", (value == 1) ? "\033[1;31m-> " : "\033[1;0m ");
        printf(" %s  3 - Conex�o DB \n", (value == 2) ? "\033[1;31m-> " : "\033[1;0m ");
        printf(" %s  4 - Sair \n", (value == 3) ? "\033[1;31m-> " : "\033[1;0m ");
        printf("\033[1;0m \n");
        printf("\033[0;31m*****************************\033[0;0m\n");
        key = getch();

        if ( key == KEY_ESC ) return;

        if ( key == KEY_UP && value > 0) value -= 1;
        if ( key == KEY_DOWN && value < 3) value += 1;

        if ( key == KEY_ENTER && value == 0 )
        {
            loginProf();
            return;
        }
        if ( key == KEY_ENTER && value == 1 )
        {
            registerProf();
            return;
        }
        if ( key == KEY_ENTER && value == 2 )
        {
            connDB();
            return;
        }
        if ( key == KEY_ENTER && value == 3 )
        {
            system("cls");
            printf("Voc� est� saindo! Aguarde.");
            sleep(1);
            system("cls");
            printf("Voc� est� saindo! Aguarde..");
            sleep(1);
            system("cls");
            printf("Voc� est� saindo! Aguarde...");
            sleep(1);
            system("cls");
            return exit(1);
        }

    }
}

// Menu ( Is Logged )
void menuIsLogged()
{
    isLogged = true;

    int key;
    int value = 0;

    while(1)
    {
        system("cls");
        printf("*************  Painel de Controle *************\n");
        printf("\033[1;0m \n");
        printf(" %s  1 - Exibir Alunos ( Ordem Alfabetica ) \n", (value == 0) ? "\033[1;31m-> " : "\033[1;0m ");
        printf(" %s  2 - Exibir Aluno ( Matr�cula ) \n", (value == 1) ? "\033[1;31m-> " : "\033[1;0m ");
        printf(" %s  3 - Exibir Melhores Alunos \n", (value == 2) ? "\033[1;31m-> " : "\033[1;0m ");
        printf(" %s  4 - Exibir Nota Geral ( Determinado Curso )\n", (value == 3) ? "\033[1;31m-> " : "\033[1;0m ");
        printf(" %s  5 - Cadastrar Aluno \n", (value == 4) ? "\033[1;31m-> " : "\033[1;0m ");
        printf(" %s  6 - Editar Aluno \n", (value == 5) ? "\033[1;31m-> " : "\033[1;0m ");
        printf(" %s  7 - Excluir Aluno \n", (value == 6) ? "\033[1;31m-> " : "\033[1;0m ");
        printf(" %s  8 - Exportar Tabela \n", (value == 7) ? "\033[1;31m-> " : "\033[1;0m ");
        printf(" %s  9 - Sair \n", (value == 8) ? "\033[1;31m-> " : "\033[1;0m ");
        printf("\033[1;0m \n");
        printf("***********************************************\n");
        key = getch();

        if ( key == KEY_ESC ) return;

        if ( key == KEY_UP && value > 0) value -= 1;
        if ( key == KEY_DOWN && value < 8) value += 1;

        if ( key == KEY_ENTER && value == 0 )
        {
            displayStudents();
            return;
        }
        if ( key == KEY_ENTER && value == 1 )
        {
            displayStudent();
            return;
        }
        if ( key == KEY_ENTER && value == 2 )
        {
            bestStudents();
            return;
        }
        if ( key == KEY_ENTER && value == 3 )
        {
            displayCourse();
            return;
        }
        if ( key == KEY_ENTER && value == 4 )
        {
            registerStudent();
            return;
        }
        if ( key == KEY_ENTER && value == 5 )
        {
            editStudent();
            return;
        }
        if ( key == KEY_ENTER && value == 6 )
        {
            deleteStudent();
            return;
        }
        if ( key == KEY_ENTER && value == 7 )
        {
            exportTable();
            return;
        }
        if ( key == KEY_ENTER && value == 8 )
        {
            isLogged = false;
            emailExists = false;
            system("cls");
            printf("Voc� est� voltando ao menu principal!");
            sleep(4);
            system("cls");
            menu();
            return;
        }
    }
}

// Test DB connection
void connDB()
{
    MYSQL *conn = mysql_init(NULL);

    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ConnDB %d %s\n", mysql_errno(conn), mysql_error(conn));
        return;
    }
        else
    {
        system("cls");
        printf("Conex�o realizada com sucesso!\n\nVoltando ao menu principal...");
        sleep(3);
        menu();
        return;
    }

}

// Register Teacher
void registerProf()
{
    setbuf(stdin, NULL);
    MYSQL *conn = mysql_init(NULL);

    char *verifyEmail[255];
    char *query[255];
    char *name[255];
    char *email[255];
    char *password[255];
    char *confirmPassword[255];
    bool registeredEmail = false;


    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ao se cadastrar! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
        sleep(4);
        menu();
        return;
    }
        else
    {
        system("cls");
        printf("Digite seu nome: ");
        gets(name);
        printf("Digite seu email: ");
        gets(email);
        printf("Digite uma senha: ");
        gets(password);
        printf("Confirme sua senha: ");
        gets(confirmPassword);

        if ( strlen(name) == 0 )
        {
            printf("Por favor, digite um nome valido!");
            return;
        }

        if ( strlen(email) == 0)
        {
            printf("Por favor, digite um email valido!");
            return;
        }

        if ( strlen(password) == 0 )
        {
            printf("Por favor, digite uma senha valida!");
            return;
        }

        if ( strcmp(password, confirmPassword) != 0)
        {
            system("cls");
            printf("As senhas n�o conferem!");
            sleep(3);
            registerProf();
            return;
        }

        sprintf(verifyEmail, "SELECT * FROM teachers WHERE email = '%s';", email);
        if ( mysql_query(conn, verifyEmail) )
        {
            printf("Erro ao se cadastrar! Verifique sua conex�o ao banco de dados...\n");
            exit(1);
            return;
        }
            else
        {

            MYSQL_RES *result = mysql_store_result(conn);
            int num_fields = mysql_num_fields(result);
            MYSQL_ROW row;

            while ((row = mysql_fetch_row(result)))
            {
                for ( int i = 0; i < num_fields; i++ )
                {
                    registeredEmail = true;
                }
            }

            if ( registeredEmail == true )
            {
                printf("\033[0;31mEmail j� cadastrado! Tente outro...\033[0;0m\n\n");
                sleep(3);
                registerProf();
                return;
            }
                else
            {
                sprintf(query, "INSERT INTO teachers (name, email, password) VALUES ('%s','%s','%s');", name, email, password);
                if ( mysql_query(conn, query) )
                {
                    printf("Erro ao se cadastrar! Verifique sua conex�o ao banco de dados...");
                    exit(1);
                    return;
                }
                    else
                {
                    printf("Cadastro realizado com sucesso!\n\n");
                    printf("\033[0;32mVoltando ao menu principal...\033[0;0m\n");
                    sleep(3);
                    menu();
                    return;
                }
            }
        }
    }
}

// Login Teacher
void loginProf()
{
    setbuf(stdin, NULL);
    MYSQL *conn = mysql_init(NULL);
    char *query[255];
    char *email[255];
    char *password[255];

    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ao efetuar o login! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
        sleep(4);
        menu();
        return;
    }
        else
    {
        system("cls");
        printf("Digite seu email: ");
        gets(email);
        printf("Digite sua senha: ");
        gets(password);

        if ( strlen(email) == 0 )
        {
            printf("Por favor, digite um email valido!");
            loginProf();
            return;
        }

        if ( strlen(password) == 0 )
        {
            printf("Por favor, digite uma senha valida!");
            loginProf();
            return;
        }

        sprintf(query, "SELECT email FROM teachers WHERE email = '%s' && password = '%s';", email, password);
        if ( mysql_query(conn, query) )
        {
            printf("Erro ao se cadastrar! Verifique sua conex�o ao banco de dados...");
            exit(1);
            return;
        }
            else
        {
            MYSQL_RES *result = mysql_store_result(conn);
            int num_fields = mysql_num_fields(result);
            MYSQL_ROW row;

            while (( row = mysql_fetch_row(result) ))
            {
                for ( int i = 0; i < num_fields; i++ )
                {
                    if ( num_fields > 0 )
                    {
                        emailExists = true;
                    }
                }
            }

            if ( emailExists == true )
            {
                menuIsLogged();
            }
                else
            {
                printf("\033[0;31mEmail ou senha incorreta!\033[0;0m\n");
                sleep(3);
                loginProf();
                return;
            }
        }
    }
}

// Register Student
void registerStudent()
{
    setbuf(stdin, NULL);
    char *query[255];
    char *name[255];
    char *course[255];
    char *queryRegistration[255];
    float note1;
    float note2;
    float note3;
    float average;
    int registration;
    bool registrationValid = true;

    MYSQL *conn = mysql_init(NULL);

    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ao efetuar o cadastro do aluno! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
        sleep(4);
        menu();
        return;
    }
        else
    {
        system("cls");
        printf("Digite o nome e sobrenome do aluno: ");
        gets(name);
        printf("Digite a matr�cula do aluno: ");
        scanf("%d", &registration);
        setbuf(stdin, NULL);
        printf("Digite o nome do curso em que o aluno frequenta: ");
        gets(course);

        // Validations
        if ( strlen(name) == 0 )
        {
            printf("Por favor, digite um nome valido!");
            sleep(3);
            registerStudent();
            return;
        }

        if ( registration == 0 )
        {
            printf("Por favor, digite uma matr�cula valida!");
            sleep(3);
            registerStudent();
            return;
        }

        if ( strlen(course) == 0 )
        {
            printf("Por favor, digite um curso valido!");
            sleep(3);
            registerStudent();
            return;
        }

        printf("\n\n\033[1;31mDigite as notas separadas por virgulas. Ex: 8,6\033[1;0m\n");
        printf("Digite a primeira nota do aluno: ");
        scanf("%f", &note1);
        setbuf(stdin, NULL);
        printf("Digite a segunda nota do aluno: ");
        scanf("%f", &note2);
        setbuf(stdin, NULL);
        printf("Digite a terceira nota do aluno: ");
        scanf("%f", &note3);
        setbuf(stdin, NULL);

        // Average
        average = (note1 + note2 + note3) / 3;

        sprintf(queryRegistration, "SELECT * FROM student WHERE registration = '%d';", registration);
        if ( mysql_query(conn, queryRegistration) )
        {
            printf("Erro ao validar matr�cula! Verifique sua conex�o ao banco de dados...");
            exit(1);
            return;
        }
            else
        {

            MYSQL_RES *result = mysql_store_result(conn);
            int num_fiels = mysql_num_fields(result);
            MYSQL_ROW row;

            while ( (row = mysql_fetch_row(result)) )
            {
                for ( int i = 0; i < num_fiels; i++ )
                {
                    registrationValid = false;
                }
            }

            if ( registrationValid == false )
            {
                printf("Matr�cula j� cadastrada no sistema! Voltando ao menu principal...\n");
                sleep(3);
                menuIsLogged();
                return;
            }
                else
            {
                sprintf(query, "INSERT INTO student (name, registration, course, note1, note2, note3, average) VALUES ('%s','%d','%s', '%.2f','%.2f','%.2f','%.2f');", name, registration, course, note1, note2, note3, average);
                if ( mysql_query(conn, query) )
                {
                    printf("Erro ao cadastrar estudante! Verifique sua conex�o ao banco de dados...");
                    exit(1);
                    return;
                }
                    else
                {
                    system("cls");
                    printf("\033[0;32mAluno cadastrado com sucesso! Voltando ao menu principal...\033[0;0m");
                    sleep(3);
                    menuIsLogged();
                    return;
                }
            }
        }
    }
}

// Display All Students
void displayStudents()
{
    setbuf(stdin, NULL);
    MYSQL *conn = mysql_init(NULL);
    char *query[255];
    int key;


    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ao listar alunos(a)! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
        sleep(4);
        menu();
        return;
    }
        else
    {

        if ( mysql_query(conn, "SELECT * FROM student ORDER BY name;") )
        {
            printf("Erro ao listar alunos(a)! Verifique sua conex�o ao banco de dados...");
            exit(1);
            return;
        }
            else
        {
            system("cls");
            char *text[255] = {"ID","Nome","Mart�cula","Curso","Nota 1","Nota 2","Nota 3","M�dia"};

            MYSQL_RES *result = mysql_store_result(conn);
            int num_filds = mysql_num_fields(result);
            MYSQL_ROW row;

            while ( (row = mysql_fetch_row(result)) )
            {
                printf("\n--------------------------------------------\n");
                for ( int i = 0; i < num_filds; i++ )
                {
                    printf("\033[0;36m %s: \033[0;33m %s \033[0;0m\t",text[i], row[i]);
                    printf("\n");
                }
                printf("\n--------------------------------------------\n");
            }

            printf("\033[0;31mDigite ENTER para voltar ao menu principal: \033[0;0m");
            key = getch();

            if ( key == KEY_ENTER )
            {
                system("cls");
                printf("\033[0;32mVoltando ao menu principal! Aguarde...\033[0;0m");
                sleep(3);
                menuIsLogged();
                return;
            }
        }

    }

}

// Display Best Students
void bestStudents()
{
    setbuf(stdin, NULL);
    MYSQL *conn = mysql_init(NULL);
    char *query[255];
    int key;


    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ao listar os melhores alunos(a)! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
        sleep(4);
        menu();
        return;
    }
        else
    {

        if ( mysql_query(conn, "SELECT * FROM student ORDER BY average DESC;") )
        {
            printf("Erro ao listar alunos(a)! Verifique sua conex�o ao banco de dados...");
            exit(1);
            return;
        }
            else
        {
            system("cls");
            char *text[255] = {"ID","Nome","Mart�cula","Curso","Nota 1","Nota 2","Nota 3","M�dia"};

            MYSQL_RES *result = mysql_store_result(conn);
            int num_filds = mysql_num_fields(result);
            MYSQL_ROW row;

            while ( (row = mysql_fetch_row(result)) )
            {
                printf("\n--------------------------------------------\n");
                for ( int i = 0; i < num_filds; i++ )
                {
                    printf("\033[0;36m %s: \033[0;33m %s \033[0;0m\t",text[i], row[i]);
                    printf("\n");
                }
                printf("\n--------------------------------------------\n");
            }

            printf("Digite ENTER para voltar ao menu principal: ");
            key = getch();

            if ( key == KEY_ENTER )
            {
                system("cls");
                printf("\033[0;32mVoltando ao menu principal! Aguarde...\033[0;0m");
                sleep(3);
                menuIsLogged();
                return;
            }
        }

    }
}

// Display Student
void displayStudent()
{
    setbuf(stdin, NULL);
    MYSQL *conn = mysql_init(NULL);
    char *query[255];
    int registration;
    int key;


    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ao listar os melhores alunos(a)! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
        sleep(4);
        menu();
        return;
    }
        else
    {
        system("cls");
        printf("Digite a matr�cula do aluno: ");
        scanf("%d", &registration);

        if ( registration == 0 )
        {
            printf("Por favor, digite uma matr�cula valida!");
            sleep(3);
            displayStudent();
            return;
        }

        sprintf(query ,"SELECT * FROM student WHERE registration = '%d';", registration);
        if ( mysql_query(conn, query) )
        {
            printf("Erro ao listar aluno(a)! Verifique sua conex�o ao banco de dados...");
            exit(1);
            return;
        }
            else
        {
            system("cls");
            char *text[255] = {"ID","Nome","Mart�cula","Curso","Nota 1","Nota 2","Nota 3","M�dia"};

            MYSQL_RES *result = mysql_store_result(conn);
            int num_filds = mysql_num_fields(result);
            MYSQL_ROW row;

            while ( (row = mysql_fetch_row(result)) )
            {
                printf("\n--------------------------------------------\n");
                for ( int i = 0; i < num_filds; i++ )
                {
                    printf("\033[0;36m %s: \033[0;33m %s \033[0;0m\t",text[i], row[i]);
                    printf("\n");
                }
                printf("\n--------------------------------------------\n");
            }

            if ( num_filds <= 0 )
            {
                system("cls");
                printf("Matr�cula n�o encontrada! Aguarde...");
                sleep(2);
                menuIsLogged();
                return;
            }

            printf("Digite ENTER para voltar ao menu principal: ");
            key = getch();

            if ( key == KEY_ENTER )
            {
                system("cls");
                printf("\033[0;32mVoltando ao menu principal! Aguarde...\033[0;0m");
                sleep(3);
                menuIsLogged();
                return;
            }
        }
    }
}

// Display Courses
void displayCourse()
{
    setbuf(stdin, NULL);
    MYSQL *conn = mysql_init(NULL);
    char *query[255];
    char *course[255];
    int key;

    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ao listar os melhores alunos(a)! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
        sleep(4);
        menu();
        return;
    }
        else
    {

        if ( mysql_query(conn, "SELECT course FROM student;") )
        {
            printf("Erro ao listar cursos! Verifique sua conex�o ao banco de dados...");
            exit(1);
            return;
        }
            else
        {
            MYSQL_RES *result = mysql_store_result(conn);
            int num_filds = mysql_num_fields(result);
            MYSQL_ROW row;

            system("cls");
            printf("\033[0;36m***** Cursos dispon�veis *****\033[0;0m\n\n");
            while( (row = mysql_fetch_row(result)) )
            {
                for ( int i = 0; i < num_filds; i++ )
                {
                    printf("\033[0;33m * %s \033[0;0m\t", row[i]);
                }
                printf("\n");
            }

            printf("\n\n\033[0;32mDigite o nome do curso que deseja visualizar: \033[0;0m");
            gets(course);

            if ( strlen(course) == 0 )
            {
                printf("Por favor, digite um curso valido!");
                sleep(3);
                displayCourse();
                return;
            }

            sprintf(query, "SELECT * FROM student WHERE course = '%s' ORDER BY average DESC;", course);
            if ( mysql_query(conn, query) )
            {
                printf("Erro ao listar carregar curso! Verifique sua conex�o ao banco de dados...");
                exit(1);
                return;
            }
                else
            {
                char *text[255] = {"ID","Nome","Mart�cula","Curso","Nota 1","Nota 2","Nota 3","M�dia"};
                MYSQL_RES *result2 = mysql_store_result(conn);
                int num_filds2 = mysql_num_fields(result2);
                MYSQL_ROW row2;

                system("cls");
                printf("\033[0;31m************* Estudantes de %s *************\033[0;0m\n\n", course);
                while ( (row2 = mysql_fetch_row(result2)) )
                {
                    printf("\n--------------------------------------------\n");
                    for ( int i = 0; i < num_filds2; i++ )
                    {
                        printf("\033[0;36m %s: \033[0;33m %s \033[0;0m\t",text[i], row2[i]);
                        printf("\n");
                    }
                    printf("\n--------------------------------------------\n");
                }

                printf("\n\033[0;32mDigite ENTER para voltar ao menu principal: \033[0;0m\n\n");
                key = getch();

                if ( key == KEY_ENTER )
                {
                    system("cls");
                    printf("\033[0;32mVoltando ao menu principal! Aguarde...\033[0;0m");
                    sleep(3);
                    menuIsLogged();
                    return;
                }

            }
        }

    }

}

// Delete Student
void deleteStudent()
{
    setbuf(stdin, NULL);
    MYSQL *conn = mysql_init(NULL);
    char *name[255];
    char *query[255];
    char *registrationExists[255];
    int registration;
    int key;
    int value = 1;

    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ao listar os melhores alunos(a)! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
        sleep(4);
        menu();
        return;
    }
        else
    {

        system("cls");
        printf("Digite a matr�cula do aluno: ");
        scanf("%d", &registration);

        if ( registration == 0 )
        {
                printf("Por favor, digite uma matr�cula valida!");
                sleep(3);
                displayStudent();
                return;
        }

        sprintf(registrationExists, "SELECT * FROM student WHERE registration = '%d';", registration);
        if ( mysql_query(conn, registrationExists) )
        {
            system("cls");
            printf("Erro ao listar os melhores alunos(a)! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
            sleep(4);
            menu();
            return;
        }
            else
        {

            system("cls");
            MYSQL_RES *result = mysql_store_result(conn);
            int num_fields = mysql_num_fields(result);
            MYSQL_ROW row;

            while ( (row = mysql_fetch_row(result)) )
            {
                for ( int i = 0; i < num_fields; i++ )
                {
                    registrationValid = true;
                }
            }

            printf("%d", registrationValid);

            if ( registrationValid == false )
            {
                system("cls");
                printf("Matr�cula n�o cadastrada! Tente outra...");
                sleep(2);
                deleteStudent();
                return;
            }

            sprintf(query, "SELECT * FROM student WHERE registration = '%d';", registration);
            if ( mysql_query(conn, query) )
            {
                printf("Erro ao listar aluno(a)! Verifique sua conex�o ao banco de dados...");
                exit(1);
                return;
            }
                else
            {
                system("cls");
                char *text[255] = {"ID","Nome","Mart�cula","Curso","Nota 1","Nota 2","Nota 3","M�dia"};

                MYSQL_RES *result2 = mysql_store_result(conn);
                int num_fields2 = mysql_num_fields(result2);
                MYSQL_ROW row2;

                while ( (row2 = mysql_fetch_row(result2)) )
                {
                    printf("\n--------------------------------------------\n");
                    for ( int i = 0; i < num_fields2; i++ )
                    {
                        printf("\033[0;36m %s: \033[0;33m %s \033[0;0m\t",text[i], row2[i]);
                        printf("\n");
                    }
                    printf("\n--------------------------------------------\n");
                    printf("\n\n");
                }

                    printf("Aperte ENTER para confirmar... \n");
                    printf("Caso queira cancelar a opera��o, aperte ESC...\n");

                    key = getch();

                    if ( key == KEY_ESC )
                    {
                        system("cls");
                        printf("Voltando ao menu principal! Aguarde...\n");
                        sleep(3);
                        menuIsLogged();
                        return;
                    }

                    if ( key == KEY_ENTER )
                    {
                        deleteConfirm(registration);
                    }
            }

        }
    }
}

// Delete Confirm
void deleteConfirm( int registration )
{
    setbuf(stdin, NULL);
    MYSQL *conn = mysql_init(NULL);
    char *query[255];

    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ao deletar aluno(a)! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
        sleep(4);
        menu();
        return;
    }
        else
    {
        sprintf(query ,"DELETE FROM student WHERE registration = '%d';", registration);
        if ( mysql_query(conn, query) )
        {
            printf("Erro ao deletar aluno(a)! Verifique sua conex�o ao banco de dados...");
            exit(1);
            return;
        }
            else
        {
            system("cls");
            printf("Aluno(a) deletado(a) com sucesso! Voltando ao menu principal...");
            sleep(3);
            menuIsLogged();
            return;
        }

    }
}

// Edit Student
void editStudent()
{
    setbuf(stdin, NULL);
    MYSQL *conn = mysql_init(NULL);
    char *query[255];
    int registration;
    int key;

    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ao editar o aluno(a)! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
        sleep(4);
        menu();
        return;
    }
        else
    {

        system("cls");

        setbuf(stdin, NULL);
        printf("Digite a matr�cula do estudante: \n");
        scanf("%d", &registration);

        sprintf(query, "SELECT * FROM student WHERE registration = '%d';", registration);
        if ( mysql_query(conn, query) )
        {
            printf("Erro ao editar aluno(a)! Verifique sua conex�o ao banco de dados...");
            exit(1);
            return;
        }
            else
        {
            system("cls");
            char *text[255] = {"ID","Nome","Mart�cula","Curso","Nota 1","Nota 2","Nota 3","M�dia"};

            MYSQL_RES *result = mysql_store_result(conn);
            int num_filds = mysql_num_fields(result);
            MYSQL_ROW row;

            while ( (row = mysql_fetch_row(result)) )
            {
                printf("\n--------------------------------------------\n");
                for ( int i = 0; i < num_filds; i++ )
                {
                    printf("\033[0;36m %s: \033[0;33m %s \033[0;0m\t",text[i], row[i]);
                    printf("\n");
                }
                printf("\n--------------------------------------------\n");
            }

            if ( mysql_num_rows(result) == NULL )
            {
                system("cls");
                printf("Matr�cula n�o encontrada! Aguarde...");
                sleep(2);
                menuIsLogged();
                return;
            }

            printf("Aperte ENTER caso queira continuar com a edi��o: \n\n");
            printf("\033[0;31mDigite ESC para voltar ao menu principal: \033[0;0m\n");
            key = getch();

            if ( key == KEY_ESC )
            {
                system("cls");
                printf("\033[0;32mVoltando ao menu principal! Aguarde...\033[0;0m");
                sleep(3);
                menuIsLogged();
                return;
            }
            if ( key == KEY_ENTER )
            {
                modifyStudent(registration);
                return;
            }
        }
    }
}

// Insert Student Modification in DB
void modifyStudent(int registration)
{
    setbuf(stdin, NULL);
    MYSQL *conn = mysql_init(NULL);
    char *query[255];
    char *name[255];
    char *course[255];
    char *queryRegistration[255];
    float note1;
    float note2;
    float note3;
    float average;
    int registrationNew;
    int key;

    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ao editar o aluno(a)! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
        sleep(4);
        menu();
        return;
    }
        else
    {

        system("cls");

        sprintf(query, "SELECT * FROM student WHERE registration = '%d';", registration);
        if ( mysql_query(conn, query) )
        {
            printf("Erro ao editar aluno(a)! Verifique sua conex�o ao banco de dados...");
            exit(1);
            return;
        }
            else
        {
            system("cls");
            char *text[255] = {"ID","Nome","Mart�cula","Curso","Nota 1","Nota 2","Nota 3","M�dia"};

            MYSQL_RES *result = mysql_store_result(conn);
            int num_filds = mysql_num_fields(result);
            MYSQL_ROW row;

            while ( (row = mysql_fetch_row(result)) )
            {
                printf("\n--------------------------------------------\n");
                for ( int i = 0; i < num_filds; i++ )
                {
                    printf("\033[0;36m %s: \033[0;33m %s \033[0;0m\t",text[i], row[i]);
                    printf("\n");
                }
                printf("\n--------------------------------------------\n\n");
            }

            setbuf(stdin, NULL);
            printf("Digite o nome e sobrenome do aluno: ");
            gets(name);
            setbuf(stdin, NULL);
            printf("Digite a matr�cula do aluno: ");
            scanf("%d", &registrationNew);
            setbuf(stdin, NULL);
            printf("Digite o nome do curso em que o aluno frequenta: ");
            gets(course);

            // Validations
            if ( strlen(name) == 0 )
            {
                printf("Por favor, digite um nome valido!");
                sleep(3);
                registerStudent();
                return;
            }

            if ( registrationNew == 0 )
            {
                printf("Por favor, digite uma matr�cula valida!");
                sleep(3);
                registerStudent();
                return;
            }

            if ( strlen(course) == 0 )
            {
                printf("Por favor, digite um curso valido!");
                sleep(3);
                registerStudent();
                return;
            }

            printf("\n\n\033[1;31mDigite as notas separadas por virgulas. Ex: 8,6\033[1;0m\n");
            printf("Digite a primeira nota do aluno: ");
            scanf("%f", &note1);
            setbuf(stdin, NULL);
            printf("Digite a segunda nota do aluno: ");
            scanf("%f", &note2);
            setbuf(stdin, NULL);
            printf("Digite a terceira nota do aluno: ");
            scanf("%f", &note3);
            setbuf(stdin, NULL);

            average = (note1 + note2 + note3) / 3;

            sprintf(queryRegistration, "UPDATE student SET name = '%s', registration = '%d', course = '%s',  note1 = '%.2f', note2 = '%.2f', note3 = '%.2f', average = '%.2f' WHERE registration = '%d';", name, registrationNew, course, note1, note2, note3, average, registration);
            if ( mysql_query(conn, queryRegistration) )
            {
                system("cls");
                printf("Erro ao editar o aluno(a)! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
                sleep(4);
                menu();
            }
                else
            {
                system("cls");
                printf("\033[0;32mAluno alterado com sucesso! Voltando ao menu principal...\033[0;0m");
                sleep(3);
                menuIsLogged();
                return;
            }
        }
    }
}

// Export table
void exportTable()
{
    setbuf(stdin, NULL);
    MYSQL *conn = mysql_init(NULL);

    if ( mysql_real_connect(conn, HOST, USER, PASSWORD, DBNAME, PORT, NULL, 0) == NULL)
    {
        system("cls");
        printf("Erro ao listar alunos(a)! Verifique a conex�o com o banco de dados!\n\nVoltando ao menu principal!\n");
        sleep(4);
        menu();
        return;
    }
        else
    {

        if ( mysql_query(conn, "SELECT * FROM student ORDER BY name;") )
        {
            printf("Erro ao listar alunos(a)! Verifique sua conex�o ao banco de dados...");
            exit(1);
            return;
        }
            else
        {
            system("cls");

            MYSQL_RES *result = mysql_store_result(conn);
            int num_filds = mysql_num_fields(result);
            MYSQL_ROW row;

            resetFile();
            char *text[255] = {"ID","Nome","Mart�cula","Curso","Nota 1","Nota 2","Nota 3","M�dia"};

            while ( (row = mysql_fetch_row(result)) )
            {
                writeLogFile("\n---------------------------------\n");
                for ( int i = 0; i < num_filds; i++ )
                {
                    FILE *arquivo;

                    create_File();
                    arquivo = fopen(".\\Tabela\\Alunos.txt", "a");

                    fprintf(arquivo, "%s: %s \t\n", text[i], row[i]);
                    fclose(arquivo);
                }
                writeLogFile("\n---------------------------------\n");
            }
            animation();
        }
    }
}

// File Create
int create_File()
{
    RemoveDirectory(".\\Tabela");
    if (CreateDirectory(".\\Tabela", NULL)) {
        if (file_exists(".\\Tabela\\Alunos.txt")) {
            return;
        } else {
            return;
        }
    }
}

bool file_exists(const char *Arquivo)
{
    FILE *arquivo;
    if (arquivo = fopen(Arquivo, "r")) {
        //printf("J� existente!");
        fclose(arquivo);
        return;
    } else {
        arquivo = fopen(Arquivo, "w");
        if (arquivo == NULL) {
            //printf("Erro na abertura do arquivo %s!\n", Arquivo);
            return;
        } else {
            fclose(arquivo);
            //printf("Arquivo %s criado com sucesso!\n", Arquivo);
            return;
        }
    }
}

// Write File
void writeLogFile(const char *text)
{

    FILE *arquivo;

    create_File();
    arquivo = fopen(".\\Tabela\\Alunos.txt", "a");

    fprintf(arquivo, "%s \t\t", text);
    fclose(arquivo);

}

// Reset File
void resetFile()
{
    FILE *arquivo;

    arquivo = fopen(".\\Tabela\\Alunos.txt", "w");

    fprintf(arquivo, "");
    fclose(arquivo);
}

// Animation
void animation()
{
    setbuf(stdin, NULL);
    system("cls");
    int time = 1;
    char *text = "Download";
    char *colorRed = "\033[0;31m";
    char *colorGreen = "\033[0;32m";
    char *clear = "\033[0;0m";
    char *msg = "Aguarde enquanto ocorre a extra��o dos arquivos\n\n";

    printf("%s", msg);

    printf("%s %s: *_________ %s", text, colorRed, clear);
    sleep(time);
    system("cls");
    printf("%s", msg);

    printf("%s %s: **________ %s", text, colorRed, clear);
    sleep(time);
    system("cls");
    printf("%s", msg);

    printf("%s %s: ***_______ %s", text, colorRed, clear);
    sleep(time);
    system("cls");
    printf("%s", msg);

    printf("%s %s: ****______ %s", text, colorRed, clear);
    sleep(time);
    system("cls");
    printf("%s", msg);

    printf("%s %s: *****_____ %s", text, colorRed, clear);
    sleep(time);
    system("cls");
    printf("%s", msg);

    printf("%s %s: ******____ %s", text, colorRed, clear);
    sleep(time);
    system("cls");
    printf("%s", msg);

    printf("%s %s: *******___ %s", text, colorRed, clear);
    sleep(time);
    system("cls");
    printf("%s", msg);

    printf("%s %s: ********__ %s", text, colorRed, clear);
    sleep(time);
    system("cls");
    printf("%s", msg);

    printf("%s %s: *********_ %s", text, colorRed, clear);
    sleep(time);
    system("cls");
    printf("%s", msg);

    printf("%s %s: ********** %s", text, colorRed, clear);
    sleep(time);
    system("cls");

    printf("%sExporta��o Concluida! Voltando ao menu principal...%s\n\n", colorGreen, clear);
    setbuf(stdin, NULL);

    sleep(3);
    menuIsLogged();
    return;
}
/*

*/
