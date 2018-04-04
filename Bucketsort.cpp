#include <iostream>
#include <stdio.h>
using namespace std;
struct{
	int minval;
	int maxval;
	int *values[];
} Bucket;

void BucketSort(int* array, int len){
	int max = array[0];
	for(int i = 0; i < len; i++){
		if(array[i] > max){
			max = array[i];
		}
	}

}

int* SubArray(int* array, int begin_index, int end_index){
	int *newarray = new int[end_index - begin_index + 1];
	for(int i = begin_index; i <= end_index; i++){
		newarray[i - begin_index] = array[i];
	}
	return newarray;
}

int Pivotprocess(int* array, int len, int pivotkey){
	for(int i = 0; i < len; i++){
		if(array[i] == pivotkey){
			int index = i;
			break;
		}
	}
	int temp;
	for(int i = 0; i < index; i++){
		if(array[i] > pivotkey){
			temp = array[i];
			for(int j = i; j < len; j ++){
				array[j] = array[j + 1];
			}
			array[len - 1] = temp;
			index --;
		}
	}
	for(int i = len - 1; i > index; i--){
		if(array[i] < pivotkey){
			temp = array[i];
			for(int j = i; j > 0; j --){
				array[j] = array[j - 1];
			}
			array[0] = temp;
			index ++;
		}
	}
	return index;
}

void QuickSort(int* array, int len){
	int temp = array[len / 2];
	int index = Pivotprocess(array, len, temp);
	QuickSort(SubArray(array, 0, index), index + 1);
	QuickSort(SubArray(array, index + 1, len - 1), len -index - 1);
}

int main(int argc, char *argv[])
{
	//printf("Hello, world\n");
	
	return 0;
}
