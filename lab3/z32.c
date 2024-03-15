#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct employee{
    unsigned id;
    char* name;
    char* surname;
    double salary;
}employee;

int build_arr(char* file_name);
int line_count(char* file_name);


int main(int argc, char* argv[]){
    
}

int mall_arr(char* buff, unsigned* size, unsigned* ind_buff){
    size = 15;
    ind_buff = 0;
    buff = (char*)malloc(name_size*sizeof(char));
    if(buff==NULL){
        return -1;
    }
    return 0;
}
int string_read(char* file_name){
    FILE* file;
    file = fopen(file_name , "r");
    if (file == NULL){
        printf("unable to open file");
        return -1;
    }
    char sym = fgetc(file);
    unsigned name_size = 0;
    unsigned ind_buff_name = 0;
    unsigned lname_size = 0;
    unsigned ind_buff_lname = 0;
    char* fname = (char*)malloc(name_size*sizeof(char));
    char* lname = (char*)malloc(lname_size*sizeof(char));
    int rez_fname = mall_arr(fname, size, ind_buff);
    int rez_lname = mall_arr(lname, size, ind_buff);
    if (rez_fname == -1 || rez_lname == -1){
        printf("out of memory");
    }
    while(sym != '\n') {
        if(ind_buff >= name_size) {
            
        }
    }
    fclose(file);
}

