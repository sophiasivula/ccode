#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>

#define BUF_SIZE 256
#define SQL_BUF_SIZE 512

// Function prototypes
void process_request(const char *user_input);
void func1(const char *data);
void func2(const char *path);
void func3(const char *log_entry);
void func4(const char *username);
void func5(const char *length_input);
void func6(const char *free_input);
void func7(const char *cmd);
void func8(const char *type_cast_input);
void log_event(const char *event);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input>\n", argv[0]);
        return 1;
    }

    process_request(argv[1]);
    return 0;
}

void process_request(const char *user_input) {
    // Simulate different parts of a request handling process
    func1(user_input);
    func2(user_input);
    func3(user_input);
    func4(user_input);
    func5(user_input);
    func6(user_input);
    func7(user_input);
    func8(user_input);
}

void func1(const char *data) {
    char buffer[BUF_SIZE];
    strcpy(buffer, data);
    printf("Buffer content: %s\n", buffer);
}

void func2(const char *path) {
    char command[BUF_SIZE + 10];
    snprintf(command, sizeof(command), "ls %s", path);
    system(command);
}

void func3(const char *log_entry) {
    char buffer[BUF_SIZE];
    snprintf(buffer, sizeof(buffer), log_entry);
    log_event(buffer);
}

void func4(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[SQL_BUF_SIZE];

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return;
    }

    // Connect to database (replace with actual credentials)
    if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return;
    }

    // construction of SQL query
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username='%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "SELECT query failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    while ((row = mysql_fetch_row(res))) {
        printf("User: %s\n", row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);
}

void func5(const char *length_input) {
    int len = strlen(length_input);
    if (len < 0) {
        printf("Length error detected!\n");
        return;
    }

    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        return;
    }

    strcpy(buffer, length_input);
    printf("Buffer content: %s\n", buffer);
    free(buffer);
}

void func6(const char *free_input) {
    char *buffer = (char *)malloc(BUF_SIZE);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        return;
    }

    strcpy(buffer, free_input);
    free(buffer);

    
    printf("Buffer content after free: %s\n", buffer);
}

void func7(const char *cmd) {
    char command[BUF_SIZE];
    snprintf(command, sizeof(command), "ping -c 1 %s", cmd);
    system(command);
}

void func8(const char *type_cast_input) {

    void *ptr = (void *)type_cast_input;
    int *int_ptr = (int *)ptr;  
    printf("Interpreted integer value: %d\n", *int_ptr);
}

void log_event(const char *event) {
    FILE *log_file = fopen("application.log", "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }
    fprintf(log_file, event); 
    fprintf(log_file, "\n");
    fclose(log_file);
}
