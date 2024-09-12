#include<stdio.h>
#include<string.h>

int main(){
    int n;
    char s[100];
    char c[100];
     int d;
    printf("Enter the String to encrypt");
    fgets(s,sizeof(s),stdin);
    int l=strlen(s);
    l=l-1;
    printf("Enter the key ");
    int k;
    scanf("%d",&k);
    k=k%26;

    int num;   
    char dict[]="abcdefghijklmnopqrstuvwxyz";
    for(int i=0;i<l;i++)
    {
      d= s[i]-'a';
      
      num=(d+k)%26;
      
      
      c[i]=dict[num];
    }
   printf("Encrypted text:%s",c);
}
