#include "header.h"
#include<bits/stdc++.h>
// This method generates a comparison model for all the possible attribute values
model::model(int d, int* dd, double val_e) {
    D = d;
    e = val_e;
    dim_domains = new int[D]; // This array stores the number of possible values for each dimension
    for (int i = 0; i < D; i++) {
        dim_domains[i] = dd[i];
    }
    comparators = new double**[D];

    // Create the Random Number Generator Object
    mt19937_64 rng;
    uint64_t timeSeed = chrono::high_resolution_clock::now().time_since_epoch().count();
    seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);

	fstream file;
	int empty = 0;
	file.open("noises.txt",fstream::in|fstream::out);
	file.seekg(0, ios::end);
	if (file.tellg() == 0)
		empty = 1;
	file.close();
	file.open("model.txt",fstream::in|fstream::out);

    // initialize a uniform distribution between 0 and 1
    std::uniform_real_distribution<double> unif(0, 1);
    for (int i = 0; i < D; i++) {
        comparators[i] = new double*[dim_domains[i]];
        for (int x = 0; x < dim_domains[i]; x++) {
            comparators[i][x] = new double[dim_domains[i]];
            comparators[i][x][x] = 0;
            for (int y = 0; y < x; y++) {
		if(empty == 1)
		{
                comparators[i][x][y] = unif(rng);
		file << comparators[i][x][y] << "\n";
                comparators[i][y][x] = 1 - comparators[i][x][y];
		}
		else
		{
		file >> comparators[i][x][y];
		comparators[i][y][x] = 1 - comparators[i][x][y];
		}
            }
        }
    }
    file.close();
}

// This method prints the noisy comparison model generated by the above method
void model::print() {
    cout << fixed;
    cout << setprecision(2);
    for (int i = 0; i < D; i++) {
        cout << "Comparison Model for Dimension: " << i << endl;
        for (int x = 0; x < dim_domains[i]; x++) {
            for (int y = 0; y < dim_domains[i]; y++) {
                cout << comparators[i][x][y] << " ";
            }
            cout << endl;
        }
    }            
}


// IMPLEMENT NOISY COMPARISON HERE ///////////////////////////////////////////
bool model::operator () (const int &x, const int &y) { 
    // Can use the member variables of the model object here :) GREAT :D
    //double e = 0.1; // The error parameter for noisy comparison
    double p = comparators[oracle_state][x][y];
    int t = dim_domains[oracle_state];
    t = 1 + log2(t*log2(t)/e);
    random_device rd;
    mt19937 gen(rd());
    if (p < 0.5)
        p = p + e;
    else
        p = p - e;
    discrete_distribution<> distrib({1-p, p});
    int comp = 0;
    for (int i = 0; i < t; i++) {
        comp += distrib(gen);
    }
    return comp > t/2;
}
/////////////////////////////////////////////////////////////////////////////

// This method creates a probabilistic world instance of the attribute values 
// as per the noisy comparison model
void model::create_world() {
    
    for (int i = 0; i < D; i++) {
        list<int> L;
        for (int j = 0; j < dim_domains[i]; j++) {
            L.push_back(j);
        }
        oracle_state = i;
        L.sort(*this);
        //cout << "sorted " << i << endl;
        vector<int> V;
        for (list<int>::iterator d = L.begin(); d != L.end(); d++) {
            V.push_back(*d);
        }       
        world.push_back(V);
        L.clear();
        V.clear();
    }
}

// This method prints the probabilistic world instance created
void model::print_world() {
    cout << "The World Instance: " << endl;
    for (vector<vector<int> >::iterator L = world.begin(); L != world.end(); L++) {
        auto dim = *L;
        for (vector<int>::iterator d = dim.begin(); d != dim.end(); d++) {
            cout << *d << " ";
        }
        cout << endl;
    }
}
