//
// Created by YoungTr on 2022/3/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#define TOK_ADD 5
#define MAXLINE 4096

jmp_buf jmpbuffer;

void do_line(char *);

void cmd_add(void);

int get_token(void);

int main(void) {
    char line[MAXLINE];

    if (setjmp(jmpbuffer) != 0)
        printf("error");
    while (fgets(line, MAXLINE, stdin) != NULL)
        do_line(line);
    exit(0);
}

char *tok_ptr; /* global pointer for get_token() */

void do_line(char *ptr) {
    int cmd;
    tok_ptr = ptr;

    while ((cmd = get_token()) > 0) {
        switch (cmd) {
            case TOK_ADD:
                cmd_add();
                break;
        }
    }
}

void cmd_add(void) {
    int token;
    token = get_token();
    if (token < 0)  // an error has accurred
        longjmp(jmpbuffer, 1);
}

int get_token(void) {
    printf("token");
}
