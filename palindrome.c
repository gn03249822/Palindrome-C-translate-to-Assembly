/*
 * Filenmae: palindrome.c
 * Author: Daniel Huang
 * Userid: cs30ubp
 * Description: The main C code for the program
 * Date: 07/22/2016
 * Sources of help: PIAZZA
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "palindrome.h"

/*
 * Function name: main()
 * Function prototype: int main(int argc,char *argv[]);
 * Description: The main function that process command line arguments
 * Parameters:
 *    arg1 - int argc - the number of passed in arguments
 *    arg2 - char *argv[] - the string array that represents all
 *                          arguments
 * Return: 1 if exit successfully; -1 otherwise
 */
int main(int argc, char *argv[])
{

  /*opt represents the option that is recognized and returned by getopt*/
  int opt;
  int flag=0;
  char *openFile;

  /*initialize a palindromes struct*/
  struct palindromes palin;
  palin.number=0;
  char** array=malloc(sizeof(char*)*palin.number);
  palin.palindrome=array;
  while((opt=getopt(argc, argv, OPT_STRING))!=-1){

    if((opt=='s'||opt=='b')&&flag!=0)
    {  /*flag has already been set*/
      /*the case when both -s and -b are specified*/ 
      (void)fprintf(stderr,EXCLUSIVE_ARGS);
      return EXIT_FAILURE;
    }

    if(opt=='b'&&flag==0)   
    {
      flag=BFLAG; /*set the flag*/
    }
    if(opt=='s'&&flag==0)

    {
      flag=SFLAG; /*set the flag*/
    }
    if(opt=='f')
    {
      openFile=optarg;
    }

    if(opt=='?')

    {
      /*cases when -f is specified without following argument*/
      (void)fprintf(stderr,USAGE);
      return EXIT_FAILURE;

    }
  }

  /*handle cases when neither -b nor -s has been specified*/
  if(flag==0)
  { 
    (void)fprintf(stderr,MISSING_FLAGS); 
    (void)fprintf(stderr,USAGE);
    return EXIT_FAILURE;

  }



  /*handle cases for passing in extra arguments*/
  if(argv[optind]!=NULL)
  {
    (void)fprintf(stderr,TOO_MANY_ARGS,argv[optind]);
    return EXIT_FAILURE;
  }


  /*-f filename option is used*/
  if(openFile!=NULL) {
    FILE *filePtr;

    filePtr=fopen(openFile,OPEN_MODE);


    /*handle the error case when the file is opened unsuccessfully*/
    if(filePtr==NULL)
    {
      char errStr[BUFSIZ];
      (void)snprintf(errStr,BUFSIZ,"%s", openFile);
      perror(errStr);
      return EXIT_FAILURE;
    }

    /*create a local array of chars*/
    char str[BUFSIZ];
    char *ret;

    char newline='\n';
    /*get one line at a time from the file*/
    while(fgets(str,BUFSIZ,filePtr)) {
      ret=strchr(str,newline);
      if(ret!=NULL){
        /*if a '\n' is found at the end of the line*/
        *ret='\0'; /*replace it with '\0'*/
      }
      /*call the appropriate function to check if it's palindrome*/
      if(flag==SFLAG)
      {
        if(isStringPalindrome(str)==1) {
          (void)printf(IS_STRING_PALINDROME,str); 
          /*call addPalindrome to keep track of the palindromes found*/
          addPalindrome(&palin,str);

        }
        else {
          (void)printf(NOT_STRING_PALINDROME,str);
        }

      }
      else if(flag==BFLAG)
      {
        if(isBinaryPalindrome(str)==1) {
          (void)printf(IS_BIN_PALINDROME,str);
          /*call addPalindrome to keep track of the palindromes found*/
          addPalindrome(&palin,str);
        }
        else {
          (void)printf(NOT_BIN_PALINDROME,str);
        }

      }
    }
    /*print out all palindromes */
    if(palin.number!=0) {
      (void)printf(SEEN,palin.number);
      int i;
      for(i=0;i<palin.number;i++) {
        (void)printf("%s\n",palin.palindrome[i]);

      }

    }
    else if(palin.number==0) {

      (void)printf(NONE_SEEN);
    }


    (void)fclose(filePtr); /*close the file at the end*/
  }

  else if(openFile==NULL) {


    /*implement the default stdin input cases*/

    if(flag==SFLAG) {/*if the string flag is set*/

      char inputStr[BUFSIZ];
      /*read the input from keyboard*/
      while(fgets(inputStr,BUFSIZ,stdin)!=NULL) {

        /*remove traling newline, if there.*/
        if((strlen(inputStr)>0)&&(inputStr[strlen(inputStr)-1]=='\n')){
          inputStr[strlen(inputStr)-1]='\0'; 
        }
        if(isStringPalindrome(inputStr)==1) {
          (void)printf(IS_STRING_PALINDROME,inputStr);

          addPalindrome(&palin,inputStr);

        }
        else {
          (void)printf(NOT_STRING_PALINDROME,inputStr);

        }

      }
      /*print all seen palindromes*/
      if(palin.number!=0) {
        (void)printf(SEEN,palin.number);
        int i;
        for(i=0;i<palin.number;i++) {
          (void)printf("%s\n",palin.palindrome[i]);

        }

      }
      else if(palin.number==0) {

        (void)printf(NONE_SEEN);
      }

    }


    else if(flag==BFLAG) {/*if the bit flag is set*/

      char inputStr[BUFSIZ];
      /*read the standard input from keyboard*/
      while(fgets(inputStr,BUFSIZ,stdin)!=NULL) {

        /*remove traling newline, if there.*/
        if((strlen(inputStr)>0)&&(inputStr[strlen(inputStr)-1]=='\n')){
          inputStr[strlen(inputStr)-1]='\0'; 
        }
        if(isBinaryPalindrome(inputStr)==1) {
          (void)printf(IS_BIN_PALINDROME,inputStr);

          addPalindrome(&palin,inputStr);

        }
        else {
          (void)printf(NOT_BIN_PALINDROME,inputStr);

        }

      }
      /*print all seen palindromes*/
      if(palin.number!=0) {
        (void)printf(SEEN,palin.number);
        int i;
        for(i=0;i<palin.number;i++) {
          (void)printf("%s\n",palin.palindrome[i]);

        }

      }
      else if(palin.number==0) {

        (void)printf(NONE_SEEN);
      }

    }

  }


  free(array);
  return EXIT_SUCCESS;
}
