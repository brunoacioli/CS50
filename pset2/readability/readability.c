#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

float media(int s, int palavras);

int main(void)
{
    int contl=0;
    int contp=1;
    int contf=0;
    string x= get_string("text:\n");
    int n=strlen(x);
    char aux[n];
    for(int i=0;i<n;i++){
        aux[i]= tolower(x[i]);
        if(x[i]==' '){
            contp++;
        }
        if(x[i]=='!'|| x[i]=='.'|| x[i]=='?'){
            contf++;
        }
        if(aux[i]>='a' && aux[i]<='z'){
            contl++;
        }

    }
    printf("%i word(s)\n",contp);
    printf("%i sentence(s)\n",contf);
    printf("%i letter(s)\n",contl);
    float l= media(contl,contp);
    float s= media(contf,contp);
    float score=0.0588*l -0.296*s -15.8;
    printf("L = %.1f\n",l);
    printf("S = %.1f\n",s);
    printf("SCORE = %.1f\n",score);

    if(score>=16){
        printf("GRADE 16+\n");
    }
    else if(score<1){
        printf("GRADE BEFORE 1\n");
    }
    else if(score- (int)score<0.5){
        printf("GRADE: %i\n",(int)score);
    }
    else{
        printf("GRADE: %i\n",(int)score+1);
    }


}
float media(int s, int palavras){
    return (float)s*100/(float)palavras;
}