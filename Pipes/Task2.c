#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char progA[10], progB[10];
char outA[500], outB[500];
int stat = 0;
void split(char cmd[])
{
  int cmdLength = 100, i = 0;
  while (cmd[i] != '\0')
  {
    if (((i + 1) < strlen(cmd) && cmd[i - 1] == ' ' && (cmd[i] == 'p' || cmd[i] == 'c') && cmd[i + 1] == ' '))
    { if(cmd[i] == 'c'){stat = 1;}
      cmd[i] = '|';
    }
    i++;
  }
  i = 0;

  char *token = strtok(cmd, "|");
  strcpy(progA, token);
  token = strtok(NULL, "|");
  strcpy(progB, token);
}

char * parseCmdLineArgs(char *argv[])
{
  int i = 1;
  static char cmd[30];
  //printf("%s\n", argv[0]);
  
  while (argv[i] != '\0')
  {
    //printf("%s\n", argv[i]);
    strcat(cmd,argv[i]);
    strcat(cmd," ");
    i++;
  }
  
  i = 0;
  return cmd;
}

int main(int argc, char *argv[])
{
  
  if(argc < 4){
    printf("Invalid Command Line Arguments\n");
    exit(1);
  }
  char *cmd1,cmd[30];
  cmd1 = parseCmdLineArgs(argv);
  strcpy(cmd,cmd1);

  
  //scanf("%[^\n]%*c", cmd);
  split(cmd);
  int fd[2];
  int cd[2];
  pipe(fd);
  pipe(cd);
  pid_t pro1, pro2;

  pro1 = fork();

  if (pro1 == 0)
  {
	if(stat == 1){
	close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
    system(progA);
}
	else{
    //first child
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
    system(progA);

    return 0;}
  }
  else
  {

    pro2 = fork();

    if (pro2 == 0)
    {
	if(stat == 1){
	close(cd[0]);
    dup2(cd[1], 1);
    close(cd[1]);
    system(progB);	
	}
	else{
      //second child
      close(fd[1]);
      dup2(fd[0], 0);
      close(fd[0]);
      system(progB);}
    }
    //Parent
if(stat == 1){

read(fd[0],outA,500);
read(cd[0],outB,500);
if(strcmp(outA,outB) == 0){printf("TRUE \n");}
else{
printf("FALSE \n");
printf("\nCommand(%s) OUTPUT: \n",progA);
printf("%s",outA);
printf("\nCommand(%s) OUTPUT: \n",progB);
printf("%s",outB);
}
return 0;
}
else{
    wait(NULL);
close(fd[1]);
close(fd[0]);
	wait(NULL);
 }   
  }
}
