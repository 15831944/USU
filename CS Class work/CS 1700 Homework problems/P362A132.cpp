// 362
// marks
// Mark Salisbury
// P362A132.cpp
/*
A132. Write a program that generates from the string 
"abcdefghicolumnklmnopqrstuvwxyz{" the following:
                         a
                        bcb
                       cdedc
                      defgfed
                     efghihgfe
                    fghicolumnkcolumnihgf
                   ghicolumnklcolumnlkcolumnihg
                  hicolumnklmnonmlkcolumnih
                 icolumnklmnopqponmlkcolumni
                columnklmnopqrsrqponmlkcolumn
               klmnopqrstutsrqponmlk
              lmnopqrstuvwvutsrqponml
             mnopqrstuvwxyxwvutsrqponm
            nopqrstuvwxyz{zyxwvutsrqpon

You must use the string and address parts of the string as an array. 
Refer to problem 19.26 of your text.
*/
#include <iostream.h>

void tree(const char [], int len);

void main(void){

	const char letters[] = "abcdefghijklmnopqrstuvwxyz{";
	//const char a[] = "*%#$!$&T:SH^^**&^=!{}r4T";

	tree(letters, sizeof(letters));
	//tree(a, sizeof(a));

}

void tree(const char list[], int len){
	int position;
	int middle = len / 2;
	for (int row = 0; row < (middle); row++){
		position = row;
		for (int column = 0; column < len; column++){
			if (column < (middle - (row + 1)) || column > (middle + (row - 1)))
				cout << ' ';
			else{
				cout << list[position];
				if (column < middle - 1)
					position++;
				else
					position--;
			}	
		}
		cout << endl;
	}
}