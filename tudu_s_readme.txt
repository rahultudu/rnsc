There are three files which I have made.
1) noises.txt --- It stores the noises given to attributes.
2) model.txt  --- It stores the the values of comparators.
3) empty.txt  --- It helps in deleting the content of the above two files by
		  cp empty.txt noises.txt
		  cp empty.txt model.txt

Additionally this program will ask you for the value of e and this value of e is stored in a class variable e. It is assigned in the constructor.

For compiling please please run this command and nothing else because the files have been created there already.
	g++ -std=c++11 src/*.cpp -o rsnc

Once you run the program with empty files, the above mentioned two files will get filled. Next time when you run the program, data will be taken from these files. Thats's why there is an empty file to delete the contents whenever you want.


