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
typedef struct {
    unsigned int col;
    float v;
} ColV;
bool compare(ColV const& a, ColV const& b) {
    return a.col < b.col;
}
int main(void){
    ColV *colV = new ColV [5];
    colV[0].col = 1;
    colV[0].v = 1.0f;
    colV[1].col = 3;
    colV[1].v = 1.0f;
    colV[2].col = 2;
    colV[2].v = 1.0f;
    colV[3].col = 0;
    colV[3].v = 1.0f;
    colV[4].col = 4;
    colV[4].v = 1.0f;
    sort(&colV[0], &colV[5], &compare);
    for(int i=0;i<5;++i){
        cout<<colV[i].col<<" "<<colV[i].v<<endl;
    }
    return 0;
}