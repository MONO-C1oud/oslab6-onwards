#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#include<math.h>


void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

int main(int argc, char** argv) {

	int* sharedmem;
	char string[100];
	int shmid;

	int size = 100;
	//int size = pow(2,18);
	int size2 = size * 4;

	shmid = shmget((key_t)1080, size2, 0666);
	printf("key of shared mem is %d\n", shmid);
	sharedmem = shmat(shmid, NULL, 0);
	printf("Process attached at %p\n",sharedmem);
	printf("Data: %s\n", (char* )sharedmem);

	//get array
	int arr[size];
	for (int i = 0; i < size; i++) {
		arr[i] = sharedmem[i];
		//printf("%d) %d\n", i, arr[i]);
	}
	printf("Array recieved...");

	/*
	//set array
	for (int i = 0; i < size; i++) {
		sharedmem[i] = arr[i];
	}
	*/	

	int high,low;

	if (argv[2] == NULL) {
		low = 0;
		high = atoi(argv[1]);
	}
	else {
		low = atoi(argv[1]);
		high = atoi(argv[2]);
	}

	


	if ((high - low) > 16) {
		int mid = (low+high)/2;
		printf("low: %d, mid: %d, high: %d", low, mid, high);

		char space[] = " ";
		char arlow[15];
		char armid[15];
		char armid1[15];
		char arhigh[15];
		char cmd1[50] = "./cons.o";
		char cmd2[50] = "./cons.o";

		if (low != 0)
			tostring(arlow, low);
		tostring(armid, mid);

		tostring(armid1, mid + 1);
		tostring(arhigh, high);

		char* r1;
		r1 = strcat(cmd1, space);
		if (low != 0)
			r1 = strcat(cmd1, arlow);
		r1 = strcat(cmd1, space);
		r1 = strcat(cmd1, armid);
		

		char* r2;
		r2 = strcat(cmd2, space);
		r2 = strcat(cmd2, armid1);
		r2 = strcat(cmd2, space);
		r2 = strcat(cmd2, arhigh);

		printf("\ncmd1: %s", r1);
		printf("\ncmd2: %s\n", r2);
		system(r1);
		system(r2);

		for (int i = low; i <= high; i++) {
			for (int j = low; j <= high; j++) {
				if (arr[j] < arr[j-1]) {
					int temp = arr[j];
					arr[j] = arr[j-1];
					arr[j-1] = temp;
				}
			}
		}
		//set array
		for (int i = low; i <= high; i++) {
			sharedmem[i] = arr[i];
		}
	}
	else if ((high - low) <= 16) {
		for (int i = low; i <= high; i++) {
			for (int j = low; j <= high; j++) {
				if (arr[j] < arr[j-1]) {
					int temp = arr[j];
					arr[j] = arr[j-1];
					arr[j-1] = temp;
				}
			}
		}
		//set array
		for (int i = low; i <= high; i++) {
			sharedmem[i] = arr[i];
		}

	}


	return 0;
}