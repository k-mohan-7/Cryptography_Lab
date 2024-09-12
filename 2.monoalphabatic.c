#include<stdio.h>
#include<string.h>
int main(){
    char c[100]="";
    char s[100];
    printf("Enter the string");
    fgets(s,sizeof(s),stdin);
    char dict[]="abcdefghijklmnopqrstuvwxyz";
    int d,n;
    int l=strlen(s);
    l=l-1;
    for(int i=0;i<l;i++)
    {
        if(s[i]!='1'){
        d=s[i]-'a';
        n=(d+3)%26;
        c[i]=dict[n];
        
           for(int k=i+1;k<l;k++)
           {
            if(s[i]==s[k])
            {
                c[k]=dict[n];
                s[k]='1'; 
            }
           
        }
        }
    }
    printf("cipher text %s",c);
}
