#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[]){
    if(argc!=2){
        printf("Usage ./caesar key\n");
        return 1;
    }
    else{
        int j=strlen(argv[1]);
        for(int a=0;a<j;a++){
            if((int)argv[1][a]<48 || (int)argv[1][a]>57){
                printf("Usage ./caesar key\n");
                return 1;
            }
        }
        string m= get_string("plaintext:\n");
        int n= strlen(m);
        printf("plaintext: %s\n",m);
        int k= atoi(argv[1]);
        for(int i=0;i<n;i++){
            if((int)m[i]>64 && (int)m[i]<91){
                if((int)m[i]+k>90){
                    m[i]=((int)m[i]+k+65)%91;
                }
                else{
                    m[i]=(int)m[i]+k;
                }
            }
            else if((int)m[i]>96 && (int)m[i]<123){
                if((int)m[i]+k>122){
                    m[i]=((int)m[i]+k+97)%123;
                }
                else{
                    m[i]=(int)m[i]+k;
                }
            }
            else{
                m[i]=m[i];
            }
           
        
        }
        printf("ciphertext: %s\n",m);
    }
    return 0;


}