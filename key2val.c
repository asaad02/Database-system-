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


/* This program will accept 2 command line arguments 1 the file name and the capacity*/
int main(int argc, char *argv[]){

    int len = strlen(argv[2]);      //get the length of the search term
    char * input = malloc(len+1);   //mollac the input
    strcpy(input, argv[2]);         // put the search term into varibale input
    int unsigned hashkey ;          // hash key variable
    char key[STRLEN];               // key variable
    char val[STRLEN];               // value variable
    int indexr = 0 ;                // variable hold the readindex
    int newhash  =0 ;               // new hash variable
    

    //This program will accept 2 command line arguments 
    if (argc != 3) // not three arguments 
    {
        // if more than two arguments will exit and print
        fprintf( stderr, "Usage: %s filename.kv ‘search term’\n", argv[0]);
        exit(1);
        
    }
    else
    {
        // open the giving binary file for reading 
        FILE *fb = fopen(argv[1], "rb");

        // if the file is nul print the message 
        if (fb == NULL)
        {
        printf("Cannot open file kV \n");
        exit(1);
        }
        //khs extension
        char *extension_khs =strtok(argv[1], "kv");
        strcat(extension_khs,"khs");

        FILE *khs = fopen(extension_khs, "rb");

        if (khs == NULL)
        {
        printf("Cannot open file khS \n");
        exit(1);
        }

        int capacity = get_capacity(khs);             // get capacity
        fseek( khs, 0, SEEK_SET );                   // seek to the first of the file 
        hashkey =hashfn(input, capacity );           // get the hash 
        read_index( khs, hashkey , &indexr);        // read index
        read_key( fb,indexr,key );                  // read the key

        while(strcmp(input,key) !=0) // loop until the match 
        {
            hashkey++;  // increase the hash 
            read_index( khs, hashkey , &indexr);
            read_key( fb,indexr,key );

            if (hashkey == capacity)                // if hash equal to capacity 
            {
                newhash = 0 ;                       // new hash 
                while (strcmp(key,input) !=0)       // loop from beginning
                {
                    read_index( khs, newhash , &indexr);
                    read_key( fb,indexr,key );
                    newhash ++;
                    if (newhash == hashkey)         // if the loop end at the beging of the search 
                    {
                        printf( "NOT FOUND\n" );    // not found 
                        fclose(fb);                 // close fb 
                        fclose(khs);                // close khs
                        free(input);                // free input
                        return 0 ;                  // return 0 
                    }
                }
                
                
                
            }

            
        }
        
        read_val(fb, indexr, val);
        printf("%s\n",val);             //print the value 
        fclose(fb);                     // close fb 
        fclose(khs);                    // close khs
        free(input);                    // free input
        return 0 ;                      // return 0 
    }     
        
}
