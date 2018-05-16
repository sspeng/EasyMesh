/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "options.h"
#include "easymesh.h"

/*==========================================================================*/
void EasyMesh::parse(int argc, char *argv[], Options * options)
{
 for(int arg=1; arg<argc; arg++)
  {
   if(strcmp(argv[arg],"-d")           ==0) {options->d=OFF;  
                                             options->r=OFF; 
                                             options->s=OFF;}
   else if(strcmp(argv[arg],"+a")      ==0) 
    {for(int arg2=arg+1; arg2<argc; arg2++)
      {if(strcmp(argv[arg2],"0") ==0) {R_tol=0.70; arg++;}
       if(strcmp(argv[arg2],"1") ==0) {R_tol=0.75; arg++;}
       if(strcmp(argv[arg2],"2") ==0) {R_tol=0.80; arg++;}
       if(strcmp(argv[arg2],"3") ==0) {R_tol=0.85; arg++;}
       if(strcmp(argv[arg2],"4") ==0) {R_tol=0.90; arg++;}
       if(strcmp(argv[arg2],"5") ==0) {R_tol=0.95; arg++;}
       if(strcmp(argv[arg2],"6") ==0) {R_tol=1.00; arg++;}}}
   else if(strcmp(argv[arg],"+eps")    ==0) 
    {options->eps=ON;
     for(int arg2=arg+1; arg2<argc; arg2++)
      {if(strcmp(argv[arg2],"D") ==0) {options->epsDel=ON; arg++;}
       if(strcmp(argv[arg2],"V") ==0) {options->epsVor=ON; arg++;}}}
   else if(strcmp(argv[arg],"+example")==0) options->exa=ON;
   else if(strcmp(argv[arg],"-r")      ==0) options->r=OFF;
   else if(strcmp(argv[arg],"-s")      ==0) options->s=OFF;
   else if(strcmp(argv[arg],"-m")      ==0) options->m=OFF;
   else /* if not a valid command line option, then it is a name */
    {
     strcpy(name, argv[arg]);
     len=strlen(name);
     if(name[len-2]=='.')
       if(name[len-1]=='d' || name[len-1]=='D' )
	 name[len-2]='\0';
     strcpy(eps_name, name); strcat(eps_name, ".eps");
    }
  }
 if(options->epsDel==OFF && options->epsVor==OFF) 
  { options->epsDel= ON;    options->epsVor= ON;}
}
