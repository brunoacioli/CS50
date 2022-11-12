#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

void compara(string a,string b);

int main(int argc, string argv[]){
    if(argc!=2){
        printf("Usage ./substitution key\n");
        return 1;
    }
    else{
        for(int i=0;i<strlen(argv[1]);i++){
            if(isalpha(argv[1][i])==0){
                printf("Usage ./substitution key\n");
                return 1;
                
            }
            else if(strlen(argv[1])<26 && isalpha(argv[1][i])!=0){
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
        string m= get_string("plaintext:\n");
        printf("plaintext: %s\n",m);
        compara(m, argv[1]);
        printf("ciphertext: %s\n",m);

    }
}

void compara(string a, string b){
    int n=strlen(a);
    string aux= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int n1=strlen(aux);
    for(int i=0;i<n;i++){
        for(int j=0;j<n1;j++){
            if(tolower(a[i])==tolower(aux[j])){
                if(islower(a[i])==0){
                    a[i]=toupper(b[j]);
                    j=0;
                    i++;
                    
                }
                else{
                    a[i]=tolower(b[j]);
                    j=0;
                    i++;
                }
            }
        }

    }
}