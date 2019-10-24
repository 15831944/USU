template <class T>
void msort(T data[], int first, int last)
{
	T * tempArray = new T[last - first + 1];
	MergeSort(data, first, last, tempArray);
	delete [] tempArray;
}

template <class T>
void Merge(T data[], int first, int middle, int last, T *tempArray){
	
	int leftPos = first;
	int rightPos = middle + 1;
	int tempPos = 0;

	while (leftPos <= middle && rightPos <= last){
	
		if (data[leftPos] < data[rightPos])
			tempArray[tempPos++] = data[leftPos++];
		else 
			tempArray[tempPos++] = data[rightPos++];
	}

	while (leftPos <= middle){
		tempArray[tempPos++] = data[leftPos++];
	}

	while (rightPos <= last){
		tempArray[tempPos++] = data[rightPos++];
	}

	for (int i = 0; i <= last - first; i++){
		data[first + i] = tempArray[i];
	}
}

template <class T>
void MergeSort(T data[], int first, int last, T *tempArray){
	
	if (first < last){
		int middle = (first + last) / 2;
		MergeSort(data, first, middle, tempArray);
		MergeSort(data, middle + 1, last, tempArray);
		Merge(data, first, middle, last, tempArray);
	}
	
}