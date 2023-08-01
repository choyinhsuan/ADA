#include <iostream>
#include <limits.h>
#include <stdbool.h>
#include <vector>
#include <list>
#include <stdio.h>
#include <queue>
using namespace std;

int abs(int a){
    if (a>0)
        return a;
    else
        return -a;
}

int main(){
    int n;
    int m;
    cin>>n>>m;
    int v[n+1];
    for (int i = 0; i<n+1; i++){
        v[i] = -1;
    }
    long long count[n+1] = {0};
    
    int clause[m][3] = {0};
    for (int i = 0; i<m; i++){
        for (int j = 0; j<3; j++){
            cin>>clause[i][j];
            if (clause[i][j]>0)
                count[clause[i][j]]++;
            else
                count[-clause[i][j]]--;
        }
    }

    for (int i = 1; i<n+1; i++){
        int ET = 0;
        int EF = 0;
        for (int j = 0; j<m; j++){
            int a = abs(clause[j][0]);
            int b = abs(clause[j][1]);
            int c = abs(clause[j][2]);
            bool aa, bb, cc;
            aa = (clause[j][0]>0)?true:false;
            bb = (clause[j][1]>0)?true:false;
            cc = (clause[j][2]>0)?true:false;
            int one, two, thr;
            one = (aa)?v[a]:-v[a];
            two = (bb)?v[b]:-v[b];
            thr = (cc)?v[c]:-v[c];
            if (one||two||thr)
                EF++;
            if (a == i)
                one *= -1;
            if (b == i)
                two *= -1;
            if (c == i)
                thr *= -1;
            if (one||two||thr)
                ET++;
        }
        if (ET>EF)
            v[i] = 1;
        else if (ET==EF && count[i]>0)
            v[i] = 1;
    }
    for (int i = 1; i<n+1; i++){
        if (count[i]>0)
            v[i] = 1;
        else
            v[i] = -1;
    }


    for (int i = 1; i<n+1; i++){
        printf("%d", v[i]);
        (i == n)?printf("\n"):printf(" ");
    }
}
