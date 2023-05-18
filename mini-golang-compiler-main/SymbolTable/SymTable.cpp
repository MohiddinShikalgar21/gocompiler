#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "SymbolTable.h"

using namespace std;
int token_count=0;
int r=100,c=5;
//int* ptr = malloc((r * c) * sizeof(int));
list<string> myCon[3000];
vector<vector<string>> vect;

SymbTab table[10000];

void lookup(char *token,int line,char type,char *value,char *datatype)
{ 
  ///printf("%d | %s | %s | %d | %s | %s\n",token_count,token,type,value,datatype);   
  printf("Token %s line number %d\n",token,line);
  int flag = 0;
  for(int i = 0;i < token_count;i++)
  {
    if(!strcmp(table[i].symbol,token))
    {
      flag = 1;
      if(table[i].line_no != line)
      {
        table[i].line_no = line;
      }
    }
  }
  
  //Insert
  if(flag == 0)
  {
    table[token_count].token_id = (char*)malloc(sizeof(char)*20);
    string token_id = "TK_" + to_string(token_count);
    strcpy(table[token_count].token_id,(char *)token_id.c_str());
    strcpy(table[token_count].symbol,token);
    table[token_count].symbol_type = type;
    //printf("helloworld");
    if(value==NULL){
        table[token_count].value=NULL;
        //printf("Token at count %d %s is replaced by its value %s\n",token_count,token,&value);
    }
    else{
        strcpy(table[token_count].value,value);
        //printf("hellothere\n");
        //printf("Token at count %d %s is replaced by its value %s\n",token_count,token,value);
    }
        
    if(datatype==NULL)
        table[token_count].datatype=NULL;
    else
        table[token_count].datatype=datatype;
        
    table[token_count].line_no = line;
    token_count++;
  }
}

void search_id(char *token,int lineno,int isDeclaration)
{
  int flag = 0;
  for(int i = 0;i < token_count;i++)
  {
    if(!strcmp(table[i].symbol,token))
    {
      flag = 1;
      break;
    }
  }
  //If its being referenced without initialisation
  if(isDeclaration==0 && flag == 0)
  { printf("\033[0;31m Line : %d | Semantic Error : %s is not defined\n \n\033[0m\n",lineno,token);
    exit(0);
  }
  //If it is declartion and symbol entry exists
  if(isDeclaration==1 && flag == 1)
  { printf("\033[0;31m Line : %d | Semantic Error : %s is already defined, can't redefine identifier.\n \n\033[0m\n",lineno,token);
    exit(0);
  }
  return;
}
void type_check(char * token1, char * token2, int lineno)
{
    int flag1 = -1;
    int flag2= -1;
    //Search for both tokens
    for(int i = 0;i < token_count;i++)
    {
      if(!strcmp(table[i].symbol,token1))
        flag1 = i;
      if(!strcmp(table[i].symbol,token2))
        flag2 = i;
    }
    //If both tokens found
    if (flag1>=0 && flag2>=0)
    { //Check if they have datatypes
      if (table[flag1].datatype && table[flag2].datatype)
        { //If datatype dont match
          if(strcmp(table[flag1].datatype,table[flag2].datatype)!=0)
            {
              printf("\033[0;31m Line : %d | Semantic Error : Type Mismatch for %s : %s and %s : %s \n \n\033[0m\n",lineno,token1,table[flag1].datatype,token2,table[flag2].datatype);
              exit(0);
            }
        }
    }
}
void update(char *token,int lineno,char *value)
{
  int flag = 0;
  
  for(int i = 0;i < token_count;i++)
  {
    if(!strcmp(table[i].symbol,token))
    {
      flag = 1;
      table[i].value = (char*)malloc(sizeof(char)*strlen(value));
      //sprintf(table[i].value,"%s",value);
      printf("Token at count %d %s is replaced by its value %s\n",token_count,token,value);
      string s="";
      char a=table[i].symbol_type;
      if(a=='O') s="Operand";
      else if(a=='I') s="Identifier";
      else if(a=='K') s="Keyword";
      else s="else";
      vect.push_back({token,value,s});

      strcpy(table[i].value,value);
      table[i].line_no = lineno;
      return;
    }
  }
  if(flag == 0)
  {
    printf("\033[0;31m Line : %d | Semantic Error : %s is not defined\n\033[0m\n",lineno,token);
    exit(0);
  }
}

int get_val(char *token,int lineno)
{
  int flag = 0;
  for(int i = 0;i < token_count;i++)
  {
    if(!strcmp(table[i].symbol,token))
    {
      flag = 1;
      if(table[i].symbol_type=='I')
        return atoi(table[i].value);
      if(table[i].symbol_type=='C')
        return atoi(table[i].symbol);
    }
  }
  if(flag == 0)
  {
    printf("\033[0;31m Line : %d | Semantic Error : %s is not defined\n\033[0m\n",lineno,token);
    exit(0);
  }
}

void Display(){
  int k=1;
  for(int i=0;i<vect.size();i++){
    cout<<k++<<" \t";
		for(int j=0;j<vect[i].size();j++){
			cout<<vect[i][j]<<" \t";
    }
		cout<<endl;
}
}