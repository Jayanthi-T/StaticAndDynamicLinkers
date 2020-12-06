#include<stdio.h>
#include<stdlib.h> 
#include<conio.h>
#include<string.h>    

int checkaddr(char var[],int arr[],int n)
{
    int m=atoi(var);
    int i,flag=0; 
    for(i=0;i<n;i++) 
    {
        if(m==arr[i])
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    char str[60],var[10],ext1[10];
    FILE *f1,*f2,*f3,*f4,*f5;
    f1=fopen("C:/Users/Vijay Robinson/Desktop/linker input 1.txt","r");
    fscanf(f1,"%s",var);
    int origin1,origin2,size1=16,s,line=0,i,result,ext,ext2;
    fclose(f1);
    origin1=atoi(var);
     char var1[4][10];
    f2=fopen("C:/Users/Vijay Robinson/Desktop/linker input2.txt","r");
    fscanf(f2,"%s",var);
    origin2=atoi(var);
    int tar_addr=900;
    int relocation_factor1,relocation_factor2,result_origin=900;
    relocation_factor1=result_origin-origin1;
    relocation_factor2=(result_origin+size1)-origin2;
    printf("MODULE P \nORIGIN:%d",origin1);
    printf("\nRELOCATION FACTOR: %d\nTARGET ORIGIN: %d\n",relocation_factor1,result_origin);
    printf("\nMODULE Q\nORIGIN:%d\nTARGET ORIGIN: %d\n",origin2,result_origin+size1);
    printf("RELOCATION FACTOR: %d\n",relocation_factor2);

    FILE *f6;
    f6=fopen("C:/Users/Vijay Robinson/Desktop/ntab.txt","w");               // FOR NTAB CREATION
    f4=fopen("C:/Users/Vijay Robinson/Desktop/linktab1.txt","r");
    fprintf(f6,"P\t%d\n",result_origin);
    while(!feof(f4))
    {
        fgets(str,40,f4);
        strtok(str,"\n");
        char link[3][10];
        int y=0;
        char *ptr=strtok(str,"\t");
        while(ptr!=NULL)
        {
            strcpy(link[y],ptr);
            ptr=strtok(NULL,"\t");
            y++;
        }
        if(strcmp(link[1],"PD")==0)
        {
            int temp;
            temp=atoi(link[2]);
            temp=temp+relocation_factor1;
               fprintf(f6,"%s\t%d\n",link[0],temp);
        }
        if(strcmp(link[1],"EXT")==0)
        {
               ext=atoi(link[2]);
               //ext=ext+relocation_factor1;
               strcpy(ext1,link[0]);
        }

        i=0;
    }
    fclose(f6);
    fclose(f4);
    f6=fopen("C:/Users/Vijay Robinson/Desktop/ntab.txt","a");
    f4=fopen("C:/Users/Vijay Robinson/Desktop/linktab2 (1).txt","r");
    fprintf(f6,"Q\t%d\n",origin2+relocation_factor2);
     while(!feof(f4))
    {

        fgets(str,40,f4);
        strtok(str,"\n");
        char link[3][10];    
        int y=0;
        char *ptr=strtok(str,"\t");
        while(ptr!=NULL)
        {
            strcpy(link[y],ptr);
            ptr=strtok(NULL,"\t");
            y++;
        }
        if(strcmp(link[1],"PD")==0)
        {
               fprintf(f6,"%s\t%d\n",link[0],(atoi(link[2])+relocation_factor2));
        }

        i=0;
    }


    fclose(f4);
    fclose(f6);

    f4=fopen("C:/Users/Vijay Robinson/Desktop/linktab2 (1).txt","r");           // PROCESSING EXTERN
     while(!feof(f4))
    {

        fgets(str,40,f4);
        strtok(str,"\n");
        char link[3][10];
        int y=0;
        char *ptr=strtok(str,"\t");
        while(ptr!=NULL)
        {
            strcpy(link[y],ptr);
            ptr=strtok(NULL,"\t");
            y++;
        }
        if(strcmp(link[1],"PD")==0&&strcmp(ext1,link[0])==0)
        {
               ext2=atoi(link[2]);
               ext2=ext2+relocation_factor2;
        }
        i=0;
    }


    fclose(f4);


    f1=fopen("C:/Users/Vijay Robinson/Desktop/relocat_linker-input1.txt","r");      // RELOCATION OF MODULE1 P
    while(!feof(f1))
    {
        fgets(str,40,f1);
        line++;
    }
    fclose(f1);
    int arr1[line];
    char str1[30];

    f1=fopen("C:/Users/Vijay Robinson/Desktop/relocat_linker-input1.txt","r");
     while(!feof(f1))
    {
        fgets(str1,40,f1);
        strtok(str1,"\n");
        char *ptr=strtok(str1," ");
        while(ptr!=NULL)
        {
            static int m=0;
            arr1[m]=atoi(str1);
            ptr=strtok(NULL," ");
            m++;
            s=m;
        }
    }
    fclose(f1);
    f3=fopen("C:/Users/Vijay Robinson/Desktop/linker input 1.txt","r");
    f5=fopen("C:/Users/Vijay Robinson/Desktop/linker_output.txt","w");
    char str2[60];
    i=0;
     while(!feof(f3))
    {
        fgets(str2,40,f3);
        strtok(str2,"\n");
        char *ptr=strtok(str2," ");
        while(ptr!=NULL)
        {
            strcpy(var1[i],ptr);
            i++;
            ptr=strtok(NULL," ");
        }
            result=checkaddr(var1[0],arr1,s);
            if(result==1)
            {
                int x,c;
                for(x=0;x<i;x++)
                {
                    c=atoi(var1[x]);
                    if(x==0||x==3)
                    {
                        c=c+relocation_factor1;
                    }

                    fprintf(f5,"%d ",c);
                }
                fprintf(f5,"\n");
            }
            if(result==0)
            {
                int x,c;
                int flag=0;
                for(x=0;x<i;x++)
                {

                    c=atoi(var1[x]);

                    if(x==0)
                    {
                        if(c==ext)                                          // CHECKING WHETHER THE ADDRESS IS EQUAL TO THE EXTERN ADDRESS IN LINKTAB
                        {
                            flag=1;
                        }
                        c=c+relocation_factor1;
                    }
                    if(flag==1&&x==3)
                        {
                            c=ext2;                                        // MAKING THE EXTERN TO POINT TO THE ORIGINAL MODOULE ADDRESS
                        }
                    fprintf(f5,"%d ",c);
                    c=0;
                }
                fprintf(f5,"\n");
                flag=0;
            }

        i=0;
    }
    fclose(f5);
    f2=fopen("C:/Users/Vijay Robinson/Desktop/relocat_linker-input2.txt","r");      // RELOCATION OF MODULE2 Q
    f4=fopen("C:/Users/Vijay Robinson/Desktop/linker input2.txt","r");
    f5=fopen("C:/Users/Vijay Robinson/Desktop/linker_output.txt","a");
    line=0;
    i=0;
      while(!feof(f2))
    {
        fgets(str,40,f2);
        line++;
    }
    fclose(f2);
    f2=fopen("C:/Users/Vijay Robinson/Desktop/relocat_linker-input2.txt","r");
    arr1[line];
    while(!feof(f2))
    {
        fgets(str1,40,f2);
        strtok(str1,"\n");
        char *ptr=strtok(str1," ");
        while(ptr!=NULL)
        {
            static int m=0;
            arr1[m]=atoi(str1);
            ptr=strtok(NULL," ");
            m++;
            s=m;
        }
    }
    fclose(f2);
     while(!feof(f4))
    {
        fgets(str2,40,f4);
        strtok(str2,"\n");
        char *ptr=strtok(str2," ");
        while(ptr!=NULL)
        {
            strcpy(var1[i],ptr);
            i++;
            ptr=strtok(NULL," ");
        }
            result=checkaddr(var1[0],arr1,s);
            if(result==1)
            {
                int x,c;
                for(x=0;x<i;x++)
                {
                    c=atoi(var1[x]);
                    if(x==0||x==3)
                    {
                        c=c+relocation_factor2;
                    }

                    fprintf(f5,"%d ",c);
                }
                fprintf(f5,"\n");
            }
            if(result==0)
            {
                int x,c;
                for(x=0;x<i;x++)
                {
                    c=atoi(var1[x]);
                    if(x==0)
                    {
                        c=c+relocation_factor2;
                    }
                    fprintf(f5,"%d ",c);
                }
                fprintf(f5,"\n");
            }

        i=0;
    }
    fclose(f5);

    printf("\nEXTERN:\nLINKTAB ADDRESS: %d\nTARGET ADDRESS: %d\nNAME OF THE EXTERN: %s\n",ext,ext2,ext1);
    return 0;
}
