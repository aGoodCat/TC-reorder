//
// Created by lizhi on 1/25/23.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>
#include "omp.h"
#include <bits/stdc++.h>
using namespace std;
typedef struct{
    unsigned int col;
    float v;
}ColV;
bool compare(ColV const& a, ColV const& b) {
    return a.col < b.col;
}
class CSR{
public:
    unsigned int M;
    unsigned int N;
    unsigned int NNZS;
    unsigned int *rowPtr;
    unsigned int *cols;
    unsigned int *vals;
    CSR(std::string input_file);
};
CSR::CSR(std::string input_file) {
    std::ifstream infile;
    infile.open(input_file);
    if (!infile) {
        cerr<<"read graph file error "<<endl;
        exit(-1);
    }
    std::string line;
    unsigned int i = 0;
    ColV *colVTemp;
    ColV *colV;
    unsigned int *coox;
    while(getline(infile,line)){
        if(line.find('%') == std::string::npos){
            continue;
        }else{
            if(i == 0){
                istringstream ss(line);
                string word;
                ss >> word;
                unsigned int s = std::stoi(word);
                ss >> word;
                unsigned int e = std::stoi(word);
                ss >> word;
                unsigned int v = std::stoi(word);
                M = s;
                N = e;
                NNZS = v;
                i++;
                rowPtr = new unsigned int [M+1];
                memset(rowPtr,0,(M+1)*sizeof(unsigned int));
                colVTemp = new ColV [NNZS];
                colV = new ColV [NNZS];
                coox = new unsigned int [NNZS];
            }else{
                istringstream ss(line);
                string word;
                ss >> word;
                unsigned int s = std::stoi(word);
                ss >> word;
                unsigned int e = std::stoi(word);
                ss >> word;
                float v = std::stof(word);
                coox[i - 1] = s - 1;
                colVTemp[i - 1].col = e - 1;
                colVTemp[i - 1].v = v;
                rowPtr[s] ++;
                i++;
            }
        }
    }
    infile.close();
    for(i = 0; i<M; ++i){
        rowPtr[i + 1] += rowPtr[i];
    }
    unsigned int* rowPtrTemp = new unsigned int [M];
    memcpy(rowPtrTemp, rowPtr, M*sizeof(unsigned int));
    #pragma omp parallel for
    for(i = 0; i<NNZS; ++i){
        unsigned int row = coox[i];
        unsigned int index = __sync_add_and_fetch(&rowPtrTemp[row], 1);
        colV[index] = colVTemp[i];
    }
    cout<<"finished reading graph file"<<endl;
    #pragma omp parallel for
    for(i = 0; i<M; ++i){
        std::sort(&colV[rowPtr[i]], &colV[rowPtr[i+1]], &compare);
    }
    #pragma omp parallel for
    for(i = 0; i<NNZS; ++i){
        cols[i] = colV[i].col;
        vals[i] = colV[i].v;
    }
    delete []rowPtrTemp;
    delete []coox;
    delete []colV;
    delete []colVTemp;
}