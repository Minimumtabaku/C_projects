#include <stdio.h>
#include <stdlib.h>

int compity_dawg(const void * a, const void * b)
{
  return ( *(char*)a - *(char*)b );
}


void swapityy_swap(char* A, char* B){
	char riggidy_rick=*A;
	*A=*B;
	*B=riggidy_rick;
}

void sperm(char* perm, int len_arr, int done){
	
	if(done==len_arr-1){


		for(int i=0;i<len_arr;i++){
			printf("%c",perm[i]);
			
		}

		printf("\n");

	}else{
		for(int i = done; i < len_arr; i++){
		qsort(perm + done,len_arr-done,sizeof(perm[0]),compity_dawg);
			swapityy_swap(&perm[done], &perm[i]);

			sperm(perm, len_arr, done + 1);

			swapityy_swap(&perm[done], &perm[i]);

		}
	}
	
}

int main()
{
	char c;
	int count=0;
	char* input = (char*)malloc(8*sizeof(char));
	
	while((c=getchar()) !='\n'){
		if ((c<'1' || c>'9') && (c<'a' || c>'z') && (c<'A'||c>'Z')){
			fprintf(stderr, "Error: Chybny vstup!\n");
			free(input);
			return 100;
		}else{
			
			input[count]=c;
			count += 1;


		}

		
	}
	
	sperm(input, count, 0);
	free(input);
	return 0;

}