/**
 * @file buildidx.c
 * @author Abdullah Saad | 1043850 | asaad02@uoguelph.ca
 * @date november 12th 2020
 * @brief File containing the function definitions and implementations of a buildidx
 **/

// header files
#include "util.h"   // support binary function
#include "hashfn.h" // support hash function
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* This program will accept 2 command line arguments */
int main(int argc, char *argv[]){
    //convert string to integer
    long capacity = atoi(argv[2]) ;     // get capacity 
    int sum = 2 ;                       // sum of the read_keyval return
    int unsigned hashkey ;              // hash value of the key
    int unsigned hashvalue ;            // hash value of the value 
    char key[STRLEN];                   // store the kay
    char val[STRLEN];                   // store the value 
    int unsigned index = 0 ;            // index for loop
    int indexr = 0 ;                    // variable to hold the parameter return of the read index
        
    //This program will accept 2 command line arguments 
    if (argc != 3)
    {
        // if more than two arguments will exit and print
        fprintf( stderr, "Usage: %s filename.kv capacity\n", argv[0] );
        return -1 ;
    }
    else
    {
        // open the giving binary file name for reading 
        FILE *fb = fopen(argv[1], "rb");

        if (fb == NULL)
        {
            printf("Cannot open file kv \n");
            exit(1);
        }

        //khs extension
        char *extension_khs =strtok(argv[1], "kv");
        strcat(extension_khs,"khs");
            

        //open khs files for reading and writing
        FILE *khs = fopen(extension_khs, "wb+");
        if (! khs )
        {
            printf("Cannot open file kHS \n");
            exit(1);
        }
        // initialized by calling the write_empty
        write_empty( khs,capacity);

        //vhs extension
        char *extension_vhs =strtok(argv[1], "kv");
        strcat(extension_vhs,"vhs");
        
        //open vhs files for reading and writing
        FILE *vhs = fopen(extension_vhs, "wb+");
        if (! vhs)
        {
            printf("Cannot open file VHS \n");
            exit(1);
        }
        // initialized by calling the write_empty
        write_empty( vhs , capacity );

        while (index < capacity && sum == 2 )
        {   
            // read content of kv and vhs file using read_keyval
            sum = read_keyval(fb, key, val);
            //for each key and value compute the hashfn
            hashkey = hashfn( key, capacity );
            hashvalue =hashfn( val, capacity );
            read_index( khs, hashkey,&indexr );
                
            // if the return of the read_index not equal to -1 
            while ( indexr != -1 )
            {
                // increase the hash 
                hashkey++;
                read_index( khs, hashkey,&indexr );
                    
                if (hashkey == capacity) // if index reaches capacity , index set to zero 
                {
                    hashkey = 0 ; //set the hashkey to zero
                    read_index( khs, hashkey,&indexr );
                    while ( indexr != -1 )
                    {
                        hashkey ++;
                        read_index( khs, hashkey,&indexr );
                    }  
                }

            }
            write_index( khs, index, hashkey ); // write the index */

            // check if the location of the hash occupied
            read_index( vhs, hashvalue,&indexr );

            while (indexr != -1 )
            {
                hashvalue++; // increase the hash
                read_index( vhs, hashvalue,&indexr );

                if (hashvalue == capacity) // if index reaches capacity , index set to zero 
                {
                    hashvalue = 0 ;
                    read_index( vhs, hashvalue,&indexr );
                    while ( indexr != -1)
                    {
                        hashvalue++;
                        read_index( vhs, hashvalue,&indexr );
                    }
                    
                    
                }
            }
                
            write_index( vhs, index, hashvalue );

            index++;

        }

        fclose(khs); // close KHS
        fclose(vhs); // close VHS
        fclose(fb);  // close fb
        return 0;
    }   
        
}

