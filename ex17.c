#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


struct Address {
    int id;
    int set;
    char *name;
    char *email;
    char *phone;
};

struct Database {
    int maxData;
    int maxRows;
    //This is an array
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

struct Connection *conn;


void Database_close();

void die(const char *message){
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    Database_close();

    exit(1);
}

char *load_string(){
    
        //allocate memory for the string
        char *string = (char*) calloc(conn->db->maxData, sizeof(char));
        if(!string) die("Memmory Error");

        //read in the string
        int rc = fread(string, sizeof(char), conn->db->maxData, conn->file);
        if (rc != conn->db->maxData) die("Failed to load a name.");

        return string;
}

void write_string( char* string){
    int rc = fwrite(string, sizeof(char), conn->db->maxData, conn->file);
    if(rc == -1) die("Failed to write database.");
}

void free_string(char* string){
    if (string){
        free(string);
    }
}


void Address_print(struct Address *addr){
    printf("%d %s %s\n", 
            addr->id, addr->name, addr->email);
}

void Database_load() {
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) die("Failed to load database.");

    //allocate address array
    conn->db->rows = (struct Address*)calloc(conn->db->maxRows, sizeof(struct Address));
    if (!conn->db->rows) die("Failed to allocate memory for database");

    int i = 0;
    for (i=0; i<conn->db->maxRows; i++){
        //read in the address struct
        rc = fread(conn->db->rows+i, sizeof(struct Address), 1, conn->file);
        if (rc != 1) die("Failed to load addresses.");
        conn->db->rows[i].name = load_string();
        conn->db->rows[i].email = load_string();
        conn->db->rows[i].phone= load_string(conn);

    }
}

void Database_open(const char *filename, char mode){
    conn = malloc(sizeof(struct Connection));
    if (!conn) die("Memmory error");

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) die("Memory error");

    if (mode == 'c'){
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");
        if (conn->file){
            Database_load();
        }
    }

    if(!conn->file) die("Failed to open the file");
}

void Database_close(){
    if (conn){
        if (conn->file) fclose(conn->file);
        if (conn->db->rows) {
            int i= 0;
            for(i=0; i < conn->db->maxRows; i++){
                struct Address *addr = conn->db->rows+i;
                free_string(addr->name);
                free_string(addr->email);
                free_string(addr->phone);
            }
            free(conn->db->rows);
        }
        if (conn->db) free(conn->db);
        free(conn);
    }
}

void Database_write() {
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc == -1) die("Failed to write database.");
    int i = 0;
    for(i = 0; i < conn->db->maxRows; i++){ 
        rc = fwrite(conn->db->rows+i, sizeof(struct Address), 1, conn->file);
        if(rc == -1) die("Failed to write database.");
        write_string(conn->db->rows[i].name);
        write_string(conn->db->rows[i].email);
        write_string(conn->db->rows[i].phone);

    }
    rc = fflush(conn->file);
    if (rc == -1) die("Cannot flush database.");
}

void Database_create(){
    int i = 0;
    conn->db->rows = (struct Address*)calloc(conn->db->maxRows, sizeof(struct Address));
    if (!conn->db->rows) die("Failed to allocate memory for database");

    for(i = 0; i< conn->db->maxRows; i++){
        //make a prototype to initialize it
        struct Address addr = {.id =i, .set=0};
        //then just assign it
        addr.name = calloc(conn->db->maxData, sizeof(char));
        addr.email = calloc(conn->db->maxData, sizeof(char));
        addr.phone= calloc(conn->db->maxData, sizeof(char));
        conn->db->rows[i] = addr;
    }
}

void Database_set( int id, const char *name, const char *email){
    struct Address* addr = &conn->db->rows[id];
    if(addr->set) die("Already set, delete it first");

    addr->set = 1;
    //WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, conn->db->maxData);
    addr->name[conn->db->maxData-1]= '\0';
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed");

    res = strncpy(addr->email, email, conn->db->maxData);
    addr->email[conn->db->maxData-1] = '\0';
    if (!res) die("Email copy failed");
}

void Database_get( int id){
    struct Address *addr = &conn->db->rows[id];
    if(addr->set){
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_find( char *search){
    int i = 0;
    struct Database *db = conn->db;
    for(i=0; i < db->maxRows; i++){
        if (db->rows[i].set){
            if(strstr(db->rows[i].name, search) || strstr(db->rows[i].email, search) || strstr(db->rows[i].phone, search)){
                Address_print(db->rows+i);
            } 
        }
    }
    
}

void Database_delete( int id){
    struct Address *oldAddr = conn->db->rows+id;
    free_string(oldAddr->name);
    free_string(oldAddr->email);
    free_string(oldAddr->phone);
    struct Address addr = {.id = id, .set = 0};
    addr.name = calloc(conn->db->maxData, sizeof(char));
    addr.email= calloc(conn->db->maxData, sizeof(char));
    addr.phone = calloc(conn->db->maxData, sizeof(char));
    conn->db->rows[id]=addr;
}

void Database_list(){
    int i = 0;
    struct Database *db = conn->db;

    for(i=0; i<conn->db->maxRows; i++){
        struct Address *cur = &db->rows[i];

        if(cur->set){
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[]){
    if (argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");
    char *filename = argv[1];
    char action = argv[2][0];
    Database_open(filename, action);
    int id=0;
    if (argc >3) id = atoi(argv[3]);
    if (conn->db) {
        if (action != 'c' && conn->db->maxRows < id) die("There's not that many records.");
    }
    switch(action){
        case 'c':
            if (argc != 5) die("Need maxRows and maxData to create");
            conn->db->maxRows = id;
            conn->db->maxData = atoi(argv[4]);
            Database_create();
            Database_write();
            break;
            
        case 'g':
            if(argc != 4) die("Need an id to get");

            Database_get(id);
            break;

        case 's':
            if (argc != 6) die("Need id, name, and email to set");
            Database_set(id, argv[4], argv[5]);
            Database_write();
            break;

        case 'd':
            if(argc != 4) die("Need id to delete");

            Database_delete( id);
            Database_write();
            break;

        case 'l':
            Database_list();
            break;

        case 'f':
            Database_find( argv[3]);
            break;

        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close();

    return 0;
}
