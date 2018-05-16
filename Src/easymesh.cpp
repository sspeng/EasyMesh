/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

using namespace std;

/*==========================================================================*/
int EasyMesh::algor(int argc, char *argv[])
{
 Options options;
 int Nn0;

 easy::timer.start();

 if(argc<2)
  {
   help(argv[0]); // send the name
   return 0;
  }

/*-----------------------------+
|  Parse command line options  |
+-----------------------------*/
  parse(argc, argv, & options);

/*------------------------------+ 
|  Create example domain files  |
+------------------------------*/
 if(options.exa==ON)
  {
   examples();
   return 0;
  }

 strcat(name, ".d");
 len=strlen(name);

 if(load(&options.ins)!=0)
   return 1;
 erase(options.ins);
 classify();

 if(options.m==ON)
   printf("Working.  Please wait !\n"); fflush(stdout);

 if(options.d==ON && options.ins==ON)
/*-------------------------------------------+ 
|  This do-while is taken from version 1.5d  | 
+-------------------------------------------*/
   do 
    {
     Nn0=node.size();
     new_node();
     classify();
     if(node.size()%100 ==0) printf("%d ",node.size());
#if DEBUG==ON
     printf("%d nodes;\n", node.size());
     draw_file(options.eps, options.epsDel, options.epsVor);
     printf("Encapsulated Post Script file created !\n");
     getchar();
#endif
     if(node.size()==Nn0) 
      {
       if(options.m==ON)
        {printf("\a");
         printf("Program stuck in an infinite loop.\n");
         printf("The mesh probably won't have the desired quality\n");}
       break;
      }
    }
   while(ugly!=OFF); 

 if(options.m==ON)
   printf("\n%5i nodes, %5i elements, %5i sides\n", 
                 node.size(), elem.size(), side.size());

 neighbours();
 
 if( (options.r==ON || options.s==ON) && options.ins==ON )
   if(options.m==ON)
     printf("Improving the mesh quality.  Please wait !\n"); fflush(stdout);
 if( options.r==ON && options.ins==ON )                   relax();
 if( (options.r==ON || options.s==ON) && options.ins==ON) smooth();

 if(options.ins==ON) 
   compress();

 if(options.m==ON && options.ins==ON)
   printf("Processing material marks. Please wait !\n"); fflush(stdout);
 if(options.ins==ON)
   materials();

 save();

 if(options.eps==ON) 
   draw_file(options.eps, options.epsDel, options.epsVor);

 if(options.eps==ON && options.m==ON) 
   printf("Encapsulated Post Script file created !\n");

 easy::timer.stop();
 easy::timer.report();

 return 1;
}
