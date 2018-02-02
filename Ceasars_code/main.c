#include <stdio.h>
#include <stdlib.h>
unsigned char shift_to(unsigned char c,int shift)
{
    unsigned char result;
    result= c +shift;
   // printf("c = %d shift = %d result =  %d\n", c, shift, result);
   
    if(c<='Z' && result>90)
        result +=6;
   
    if(result>122)
    {
        result -=58;
   
        if(result>90)
            result+=6;
    }
   
    return result;
 
}
int find_best_shift(unsigned char* a,unsigned char* b, int count)
{
    int occurence[52];
    for(int i = 0; i < 52; i++)
        occurence[i] = 0;

    int best_i = -1;
    
    for (int i=0;i<count;i++){
        
        int kokot, vyjebany;
        kokot = a[i];
        vyjebany = b[i];
        if(kokot >= 'a')
            kokot -=6;
        if(vyjebany >= 'a')
            vyjebany-=6;
        if(kokot <= vyjebany){
            b[i] = vyjebany - kokot ;
        }else{
            b[i]= 52 - (kokot - vyjebany);
        }
        occurence[b[i]]++;
        if(best_i == -1 || occurence[b[i]] > occurence[best_i])
            best_i = b[i];
    }

    return best_i;
}
 
int main(void)
{
    int count_1=0;
    int count_2=0;
    int c;
    unsigned char *f_list;
    f_list = NULL;
    unsigned char *s_list;
    s_list = NULL;
 
    while((c=getchar()) != '\n')
    {    
    	
    	if (c<65 || c>122){
    	fprintf(stderr, "Error: Chybny vstup!\n");
    	free(f_list);
        free(s_list);
    	return 100;
    	}

        if(c==EOF)
        {
            free(f_list);
            free(s_list);
            return 0;
        }

        f_list=realloc(f_list,(sizeof(unsigned char)*(count_1+1)));
        f_list[count_1]=(unsigned char)c;
        count_1 +=1;       
    }
    while((c=getchar()) != '\n')
    {
    	if (c<65 || c>122){
    	fprintf(stderr, "Error: Chybny vstup!\n");
    	free(f_list);
        free(s_list);
    	return 100;
    	}

        s_list=realloc(s_list,(sizeof(unsigned char)*(count_2+1)));
        s_list[count_2]=(unsigned char)c;
        count_2 +=1;   

    }
    
     

   
    if (count_1!=count_2){
    	fprintf(stderr, "Error: Chybna delka vstupu!\n");
    	free(f_list);
        free(s_list);
    	return 101;
    }

    if ((c<65 || c>122) && (count_1!=count_2)){
    	fprintf(stderr, "Error: Chybny vstup!\n");
    	free(f_list);
        free(s_list);
    	return 100;
    }


    int TheShift = find_best_shift(f_list,s_list,count_1);

    
    for(int i = 0; i<count_1; i++)
        printf("%c", shift_to(f_list[i], TheShift));
 
    printf("\n");
    free(s_list);
    free(f_list);
    return 0;
}