/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "easymesh.h"

/*==========================================================================*/
int EasyMesh::diamond()
{
 int    ea, eb, eac, ead, ebc, ebd, s;

 for(s=0; s<side.size(); s++)
   if(side[s].mark!=OFF)
    {
     ea=side[s].ea;
     eb=side[s].eb;

     bool eac_done = false;
     bool ead_done = false;
     bool ebc_done = false;
     bool ebd_done = false;

     if(ea != OFF && eb != OFF) { /* OK */

       if(elem[ea].state!=DONE && elem[ea].state!=DONE) {

         if(elem[ea].ei==eb) {ead=elem[ea].ej; eac=elem[ea].ek;}
         if(elem[ea].ej==eb) {ead=elem[ea].ek; eac=elem[ea].ei;}
         if(elem[ea].ek==eb) {ead=elem[ea].ei; eac=elem[ea].ej;}

         if(elem[eb].ei==ea) {ebc=elem[eb].ej; ebd=elem[eb].ek;}
         if(elem[eb].ej==ea) {ebc=elem[eb].ek; ebd=elem[eb].ei;}
         if(elem[eb].ek==ea) {ebc=elem[eb].ei; ebd=elem[eb].ej;}

         if( eac==OFF )                   eac_done = true;
         else if( elem[eac].state==DONE ) eac_done = true;

         if( ebc==OFF )                   ebc_done = true;
         else if( elem[ebc].state==DONE ) ebc_done = true;

         if( ead==OFF )                   ead_done = true;
         else if( elem[ead].state==DONE ) ead_done = true;

         if( ebd==OFF )                   ebd_done = true;
         else if( elem[ebd].state==DONE ) ebd_done = true;

         if( eac_done && ead_done && ebc_done && ebd_done )
          {
           elem[ea].state=DONE;
           elem[eb].state=DONE;
          }
        }
      } /* ea!=OFF && eb!=OFF */
    }

 return 0;
}
