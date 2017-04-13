#include<iostream>
#include<string>
#include<cstring>

extern int size;
extern int seed;
extern bool collectingData;
extern int verbosity;

void parseArgs(int argc, char* argv[]){
   using namespace std;
   int length = 0;
   for(int index = 1; index < argc; index++){
      length = strlen(argv[index]); // get length of argument
      if(argv[index][0] == '-'){ // if option
         if(length >= 2){
            if(argv[index][1] == '-'){ // if long option
               // long opts
            } else{ // short option
               for(int opt = 1; opt < length; opt++){
                  switch(argv[index][opt]){
                     case 'v':
                        if(verbosity < 4)
                           verbosity++;
                     break;
                     case 'c':
                        collectingData = true;
                     break;
                     case 's':
                        if(opt < length) // if s is not last opt
                           if(index + 1 < argc)
                              index++, size = atoi(argv[index]);
                           else
                              cerr << "Incorrect format: -s <int>" << endl, exit(EXIT_FAILURE);
                        else
                           cerr << "Inorrect format: -s <int>" << endl, exit(EXIT_FAILURE);
                     break;
                     case 'e':
                        if(opt < length)
                           if(index + 1 < argc)
                              index++, seed = atoi(argv[index]);
                           else
                              cerr << "Incorrect format: -e <int>" << endl, exit(EXIT_FAILURE);
                        else
                           cerr << "Incorrect format: -e <int>" << endl, exit(EXIT_FAILURE);
                     break;
                  }
               }
            }
         }
      }
   }
   if(collectingData)
      verbosity = 0;
}
