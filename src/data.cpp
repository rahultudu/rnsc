#include "header.h"
#include<bits/stdc++.h>
// This method generates N samples each with D attributes
data::data (int n, int d, int * dim_domains) {
    N = n; D = d; // N is the number of sample sto be created, D is the number of dimensions
    for (int i = 0; i < N; i++) {
        point *p = new point;
        p->features = new int[D];
        p->id = i+1;
        p->timestamp = N*N;
        DATA.push_back(*p);              
    }
	fstream file;
	int empty = 0;
	file.open("noises.txt",fstream::in|fstream::out);
	file.seekg(0, ios::end);
	if (file.tellg() == 0)
		empty = 1;
	file.close();
	file.open("noises.txt",fstream::in|fstream::out);
    for (int j = 0; j < D; j++) {
        random_device rd;
        mt19937 rng(rd());    
        uniform_int_distribution<int> uni(0,dim_domains[j]-1);
        for (list<point>::iterator p = DATA.begin(); p != DATA.end(); p++) {
	if(empty == 1)
	{
            (*p).features[j] = uni(rng);  // randomly assign a noisy value to the attribute
	    file << (*p).features[j] << "\n";
	}
	else
	{
	    file >> (*p).features[j];
	}
        }
    }            
file.close();
}

// This method prints the data that was generated
void data::print (int mode) {
    for (list<point>::iterator p = DATA.begin(); p != DATA.end(); p++) {
        cout << (*p).id << ": ";
        for (int j = 0; j < D; j++) {
            if (mode == 0)
                cout << "\t" << j << "_" << (*p).features[j];
            else
                cout << "\t" << (*p).features[j];
        }
        cout << endl;
    }
}

// This method labels the attributes of the samples as per 
// the probabilistic world generated by the model object 
void data::label_data(vector<vector<int> > world) {
    for (list<point>::iterator p = DATA.begin(); p != DATA.end(); p++) {
        for (int j = 0; j < D; j++) {
            (*p).features[j] = world[j][(*p).features[j]];
        }
    }    
}
