#include<stdio.h>
#include<stdlib.h>
#define BUFFERSIZE 1024
#define LSH_TOK_BUFFERSIZE 64
#define LSH_TOK_DELIM "\t\r\n\a"
#include<stdio.h>
#include<stdlib.h>
#include "main.h"
int main(int ac,char **arvg)
{
    char *prompt="(Shell-Tool)$";
    char *lineptr;
    size_t n=0;
    char *line;
    char **args;
    int status;
    //(void)ac; (void)arvg;
    line=lsh_read_line();
    args=lsh_split_line(line);
    status=lsh_execute(args);
    printf("%s ",prompt);
    printf("%s\n",lineptr);
    getline(&lineptr,&n,stdin);
    free(lineptr);
    return EXIT_FAILURE;
}
char *lsh_read_line(void)
{
    int buffersize=BUFFERSIZE;
    int position=0;
    char *buffer;
    buffer=malloc(sizeof(char)*buffersize);
    int c;
    if(!buffer)
    {
        fprintf(stderr,"allocation error :\n");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        c=getchar();
        if(c==EOF || c=='\n')
        {
            buffer[position]='\0';
            return buffer;
        }
        else
        {
            buffer[position]=c;
        }
        position++;
        if(position>=buffersize)
        {
            buffersize+=BUFFERSIZE;
            buffer=realloc(buffer,buffersize);
            if(!buffer)
            {
                fprintf(stderr,"allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
char **lsh_split_line(char *line)
{
    int buffersize=LSH_TOK_BUFFERSIZE;
    int position=0;
    char **tokens=malloc(buffersize * sizeof(char*));
    char *token;
    if(!tokens)
    {
        fprintf(stderr,"allocation error \n");
        exit(EXIT_FAILURE);
    }
    token=strtok(line,LSH_TOK_DELIM);
    while(token!=NULL)
    {
        tokens{position}=token;
        position++;
        if(position>=buffersize)
        {
            buffersize+=LSH_TOK_BUFFERSIZE;
            tokens=realloc(tokens,buffersize* sizeof(char*));
            if(!tokens)
            {
                fprintf(stderr,"allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token=strtok(NULL,LSH_TOK_DELIM);
    }
    tokens[position]=NULL;
    return tokens;
}
int lsh_lanuch(char **args)
{
    pid_t pid,wpid;
    int status;
    pid=fork();
    if(pid==0)
    {
        if(execvp(args[0],args)==-1)
        {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
        else
        {
            if(pid<0)
            {
                perror("lsh");
                else
                {
                    while(!WIFEXITED(status) && !WTFSIGNALED(status))
                    {
                        wpid=waitpid(pid,&status,WUNTRACED);
                    }
                }
            }
        }
    }
    return 1;
}
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
char *builtin_str[]={
    "cd",
    "help",
    "exit"
};
int (*builtin_func[]) (char **)={
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};
int lsh_num_builtins()
{
    return sizeof(builtin_str)/sizeof(char*);
}
int lsh_cd(char **args)
{
    if(args[1]==NULL)
    {
        fprintf(stderr,"lsh: expected argument to "\cd\"\n");
    }
    else
    {
        if(chdir(args[1])!=0)
        {
            perror("lsh");
        }
    }
    return 1;
}
int lsh_help(char **args)
{
    int i;
    printf("Kamran Akthar\n");
    printf("Type program names and arguments, and hit enter \n");
    printf("The following are built in :\n");
    for(i=0; i<lsh_num_builtins(); i++)
    {
        printf("%s\n",builtin_str[i]);
    }
    printf("Use the man command for information to other programs. \n");
    return 1;
}
int lsh_exit(char **args)
{
    return 0;
}
int lsh_execute(char **args)
{
    int i;
    if(args[0]==NULL)
    {
        return 1;
    }
    for(i=0; i<lsh_num_builtins(); i++)
    {
        if(strcmp(args[0],builtin_str[i])==0)
        {
            return (*builtin_func[i])(args);
        }
    }
    return lsh_lauch(args);
}