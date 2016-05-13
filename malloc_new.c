/************************** Malloc in C - without structures ***************************
*************************** Dynamic Memory allocation in C   ***************************
*************************** Author : Ayesh Almeida	     ***************************
*************************** Date   : 12-05-2016              ***************************
*************************** Moratuwa, Sri Lanka              ***************************/

#include <stdio.h>
#include <string.h>

/* Size of the memory to be used in 'malloc'*/
#define ARRAY_SIZE 20000
/* Memory to be used in 'malloc' - consists of 20000 bytes*/
static unsigned char memory[ARRAY_SIZE];

/* Flags for availability of memory chunks */
#define TRUE 1
#define FALSE 0

/* head of the array */
#define HEAD 0

/*---------------------------------------------------------------------------------------------------------------------------------------------*/
/* function prototypes */
static int power(int);
static int giveSize(int);
static int isAvailable(int);
static int nextPosition(int);
static void insert_size(int,int);
static void insert_pos(int,int);
void *MyMalloc(int);
void MyFree(void*);
/*---------------------------------------------------------------------------------------------------------------------------------------------*/

#define db "Hello"

/* Malloc Function */
void *MyMalloc(int size){
	
	//checking whether given size is lesser than the (array_size - 1000) if okay then proceed, else give an error
	if(size < (ARRAY_SIZE - 1000)){
		
		//void pointers to be used
		void *vir,*adr;
	
		//checking for the HEAD : to find out the initial starting point
		if(!memory[HEAD] && (size+13)<(ARRAY_SIZE - 4)){
			//setting initial starting point
			memory[HEAD]=4;	
			//pointing vir_pointer to the starting address
			vir = &memory[memory[HEAD]];
			//setting the previous point for the block
			insert_pos(HEAD,4);
			memory[4]=0;
			memory[8]=size;
			vir += 8;
			adr = vir;
			memory[12+size] = TRUE;
			insert_pos(17+size,13+size);
			//returning the address
			return adr;					
		}

		/* if HEAD is initialized then check for the next position which HEAD points */
		else{
			int x = memory[HEAD];
			if((isAvailable(x) == TRUE) && (giveSize(x) == size || giveSize(x) > size)){
				void *vir,*adr;
				vir = &memory[x];
				vir += 8;
				adr = vir;
				//setting the chunck is filled
				memory[x+8+size] = TRUE;
				return adr;						
			}
			else{
				int prev = x;
				int next = nextPosition(x);//taking the next position adjacent to 'x'
				//try to find a available slot from the memory
				while(((isAvailable(next) == FALSE) ||  (giveSize(next) < size )) && (next+13+giveSize(next)+size<19996) && giveSize(next) != 0){
					//if not found then go into the loop : set 'prev' to current 'next' and 'next' to next_position of 'next'
					prev = next;
					next = nextPosition(next);
					//check whether new 'next' is available : if available then allocate it, else continue the loop
					if((isAvailable(next) == TRUE) && (giveSize(next)==0)){
						void *vir,*adr;
						insert_pos(prev,next);
						insert_size(size,next+4);
						vir = &memory[next];
						vir += 8;
						adr = vir;
						//setting the chunk is filled
						memory[next+8+size] = TRUE;
						insert_pos(next+size+13,next+size+9);
						return adr;							
					}
					else{
						continue;
					}
				}
				//if available memory slot is found, then allocate it , else give an error 
				if(isAvailable(next) && (next+13+giveSize(next)+size < 19996) && (giveSize(next) == size || giveSize(next) > size || giveSize(next) == 0)){
					
						void *vir,*adr;
						insert_pos(prev,next);
						insert_size(size,next+4);
						vir = &memory[next];
						vir += 8;
						adr = vir;
						//setting the chunk is filled
						memory[next+8+size] = TRUE;
						insert_pos(next+size+13,next+size+9);
						return adr;							
				}
				printf("Cannot allocate space. Memory is filled.\n");
			}			
		}
	

	}

	else{
		printf("The asked Memory Portion cannot be allocated.\n");
	}
	


}

/* utility function to insert an index to a given position */
static void insert_pos(int index,int pos){
	int i = 0;
	while(index){
		memory[pos+i] = index%10;
		i++;
		index /= 10;
	}
	return;
}

/* utility function for insert size to a given position */
static void insert_size(int size,int pos){
	int i = 0;
	while(size){
		memory[pos+i] = size%10;
		i++;
		size /= 10;
	}
	return;
}

/* utility function to find the size of a memory chunck when starting index of the block given */
static int giveSize(int pos){
	int i = pos+4;
	int sum = 0;
	int j;
	for(j=0;j<4;j++){
		sum += (memory[i+j]*power(j));
	}
	return sum;
}


/* utility function to check availability of the memory chunk when the starting index of the block given */
static int isAvailable(int pos){
	int s = giveSize(pos);
	int answer = memory[pos+8+s];
	if(answer == 1)
		return FALSE;
	else
		return TRUE;
}

/* utility function to find the first index of the next block when the starting index of the current block given */
static int nextPosition(int pos){
	int s = giveSize(pos);
	int i = pos+s+9;
	int sum = 0;
	int j;
	for(j=0;j<4;j++){
		sum += (memory[i+j]*power(j));
	}
	return sum;
}

/* utility function to calculate powers of 10 */
static int power(int i){
	int sum = 1;
	int j;
	if(i == 0)
		return sum;
	else{
		for(j = 0;j<i;j++)
			sum *= 10;
		return sum;
	}
}

/* The Free Function : this will set free the memory you allocated earlier */
void MyFree(void *p){

	void *head;
	//get a new pointer to the head of the 'memory' array
	head = &memory;
	int l;
	//take the distance from the 'head' to the pointer 'p'
	l = p - head;
	//(previous result will give you the index where 'p' was pointing)get to the head of the memory block which you are pointing
	l-=8; 
	int o;
	//get the size of the block you are pointing
	o = giveSize(l);
	//set the availability to 'TRUE' : the memory chunck you previously allocated is free now
	memory[l+8+o]=TRUE;
	printf("Memory is freed.\n");
	return;
}


