/**
 * @file buildidx.c
 * @author Abdullah Saad | 1043850 | asaad02@uoguelph.ca
 * @date november 12th 2020
 * @brief File containing the function definitions and implementations of a key2val
 **/

#include "util.h"   // support binary function
#include "hashfn.h" // support hash function
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prints( char num[STRLEN] ){

    FILE *nm = fopen("name.basics.kv", "rb");

    // if the file is nul print the message 
    if (nm == NULL)
    {
        printf("Cannot open file name.basics.kv \n");
        exit(1);
    }
    
    char actors[STRLEN];
    char names[STRLEN];
    char a[STRLEN];

    int capacity = get_capacity(nm);             // get capacity
    fseek( nm, 0, SEEK_SET );                   // seek to the first of the file 

    for (int i = 0; i < capacity; i++)
    {
            
    read_key(nm,i,names );
    //printf("%s\n",names);
    if(strcmp(num,names) == 0)
    {
        read_val(nm, i, actors);
         if (strcmp(a,actors) == 0)
            {
                exit(1);
            }
            strcpy(a,actors );
        printf("%s\n",actors);
        


    }

                
                
            
    }


}


/* This program will accept 2 command line arguments 1 the file name and the capacity*/
int main(int argc, char *argv[]){

    int len = strlen(argv[1]);      //get the length of the search term
    char * input = malloc(len+1);   //mollac the input
    strcpy(input, argv[1]);         // put the search term into varibale input
    int unsigned hashkey ;          // hash key variable
    char key[STRLEN];               // key variable
    char val[STRLEN];               // value variable
    int indexr = 0 ;                // variable hold the readindex
    int newhash  =0 ;               // new hash variable
    void prints(char names[STRLEN] );
    

    //This program will accept 2 command line arguments 
    if (argc != 2) // not three arguments 
    {
        // if more than two arguments will exit and print
        fprintf( stderr, "Usage: %s filename.kv ‘search term’\n", argv[0]);
        exit(1);
        
    }
    else
    {
        // open the giving binary file for reading 
        FILE *fb = fopen("title.basics.kv", "rb");

        // if the file is nul print the message 
        if (fb == NULL)
        {
        printf("Cannot open file kV \n");
        exit(1);
        }


        FILE *vhs = fopen("title.basics.vhs", "rb");

        if (vhs == NULL)
        {
        printf("Cannot open file vhs \n");
        exit(1);
        }

        int capacity = get_capacity(vhs);           // get capacity
        fseek( vhs, 0, SEEK_SET );                  // seek to the first of the file 
        hashkey =hashfn(input, capacity );          // get the hash 
        read_index( vhs, hashkey , &indexr);        // read index
        read_val( fb,indexr,val );                  // read the value

        while(strcmp(input,val) !=0)                // loop until the match 
        {
            hashkey++;
            read_index( vhs, hashkey , &indexr);
            read_val( fb,indexr,val );

            if (hashkey == capacity)                // if hash equal to capacity 
            {
                newhash = 0 ;                       // new hash 
                while (strcmp(val,input) !=0)       // loop from beginning
                {
                    read_index( vhs, newhash , &indexr);
                    read_val( fb,indexr,val );
                    newhash ++;
                    if (newhash == hashkey)         // if the loop end at the beging of the search 
                    {
                        printf( "NOT FOUND\n" );    // not found
                        fclose(fb);                 // close fb 
                        fclose(vhs);                // close vhs
                        free(input);                // free input
                        return 0 ;                   // return 0 
                    }
                }
                
                
                
            }

            
        }
        
        
        read_key(fb, indexr, key);
        //printf("%s\n",key);                         //print the value 
 

        /*-------------------------------------*/

        FILE *tp = fopen("title.principals.kv", "rb");

        // if the file is nul print the message 
        if (tp == NULL)
        {
        printf("Cannot open file title.principals.kv \n");
        exit(1);
        }
       

        FILE *khs = fopen("title.basics.khs", "rb");

        if (khs == NULL)
        {
        printf("Cannot open file khS \n");
        exit(1);
        }
        

        int capacity1 = get_capacity(khs); 
        fseek( khs, 0, SEEK_SET );                   // seek to the first of the file 
         t =hashfn(key, capacity1 );
        char num[STRLEN];
        while( hashkey  < capacity1 ) // loop until the match 
        {
            hashkey++;  // increase the hash 
            read_index( khs, hashkey , &indexr);
            read_val( tp,indexr,num );
            if(strcmp(num,key) ==0){
                read_val( tp,indexr,num );
                prints(num );
            }



            
        }
        
        //fclose(nm);             //print the value 
        fclose(fb);                     // close fb 
        fclose(tp);                    // close khs
        free(input);

    }     
        
}
