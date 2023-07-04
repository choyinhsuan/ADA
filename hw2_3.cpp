#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
typedef struct Record{
    long long name;
    long long large;
    long long index;
    long long next;
}record;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin>>s;
    long long K;
    cin>>K;
    long long length = s.length();
    long long modify[length+10] = {0};
    long long final[length+10] = {0};
    long long count[63] = {0};
    long long first[63];
    long long tail[63];
    long long move[length+10] = {0};
    long long notmove[length+10] = {0};
    record records[length+10];
    long long index = 0;
    long long index2 = 0;
    long long index3 = 0;
    for (long long i = 0; i<62; i++){
        first[i] = -1;
        tail[i] = -1;
    }
    for (long long i = 0; i<length; i++){
        final[i] = -1;
        records[i].name = (long long)s[i];
        if (records[i].name <= 67)
            records[i].name -= 48;
        else if (records[i].name <= 90)
            records[i].name -= 55;
        else
            records[i].name -= 61;

        
        long long temp = records[i].name;

        records[i].next = -1;
        records[i].index = i;
        count[temp]++;
        

        if (first[temp] == -1){
            first[temp] = i;
            records[i].large = 0;
            for (long long j = temp+1; j<62; j++){
                if (first[j] != -1)
                    records[i].large += count[j];
            }
        }
        else{
            records[i].large = records[tail[temp]].large;
            for (long long j = tail[temp]+1; j<records[i].index; j++){
                if (records[j].name > records[i].name)
                    records[i].large++;
            }
            //records[i].large = (i-records[tail[temp]].index != 1)?records[tail[temp]].large + (i-records[tail[temp]].index-1):records[tail[temp]].large;
            records[tail[temp]].next = i;
        }
        tail[temp] = i;
    }

    //sort
    index = 0;
    for (long long i = 0; i<62; i++){
        long long locat = first[i];
        while(locat != -1){
            modify[index] = locat;
            index++;
            locat = records[locat].next;
        }
    }
    index = 0;
    move[index2] = -1;
    for (long long i = 0; i<length; i++){
        if (records[i].large > 0){
            move[index2] = i;
            index2++;
        }
        else{
            notmove[index3] = i;
            index3++;
        }
    }
    long long nmcount = index3;
    long long mcount = index2;
    move[mcount] = -2;
    notmove[nmcount] = -2;
    /*for (long long i = 0; i<length; i++){
        cout<<records[i].index<<" "<<records[i].large<<" "<<records[i].name<<" "<<records[i].next<<"\n";
    }*/
    /*for(long long i = 0; i<length; i++){
        cout<<move[i]<<" ";
    }
    cout<<"\n";
    for(long long i = 0; i<length; i++){
        cout<<notmove[i]<<" ";
    }*/
    long long prev[length+10] = {0};
    if (K >= (length*(length-1))/2 || move[0] == -1){
        for (long long i = 0; i<length; i++){
            cout<<s[modify[i]];
        }
    }
    else{
        index = 0;
        index2 = 0;
        index3 = 0;
        long long remain = K;
        long long broke = 0;
        record previous;
        previous.index = -1;
        for (long long i = 0; i<length; i++){
            record cur = records[modify[i]];
            broke = 0;
            while(broke != 1){
                cout<<cur.index<<" "<<cur.index-cur.large+prev[cur.index]<<"\n";
                if (remain >= cur.large){
                    if (previous.index - remain + prev[previous.index] <= cur.index-cur.large+prev[cur.index] && final[previous.index-remain+prev[previous.index]] == -1){
                        final[previous.index-remain+prev[previous.index]] = previous.index;
                        for (long long j = previous.index-remain+prev[previous.index]; j<previous.index; j++){
                            prev[j]++;
                        }
                        final[previous.index - remain + prev[previous.index]+1] = cur.index;
                        remain = 0;
                    }
                    else if (final[cur.index-cur.large+prev[cur.index]] == -1){
                        final[cur.index-cur.large+prev[cur.index]] = cur.index;
                        remain -= cur.large;
                        for (long long j = cur.index-cur.large+prev[cur.index]; j<cur.index; j++){
                            prev[j]++;
                        }
                    }
                }
                else if (cur.large > 0 && (previous.index == -1 || previous.index > cur.index)){
                    previous = cur;
                }

                if(cur.index == move[index2] && cur.index-cur.large+prev[cur.index] >= previous.index-remain+prev[previous.index]){
                    move[index2] = -1;
                    index2++;
                }
                if (cur.next != -1)
                    cur = records[cur.next];
                else
                    broke = 1;

            }

        }
        for (long long i = index2; i<mcount && remain > 0; i++){
            if (move[index2] != -1){
                final[records[move[index2]].index-remain+prev[move[index2]]] = records[move[index2]].index;
                remain = 0;
                index2++;
            }
        }


        for (long long i = 0; i<length; i++){
            cout<<final[i]<<" ";
        }
        cout<<"\n";

        index = 0;
        for (long long i = 0; i<length; i++){
            //cout<<index2<<" ";
            //cout<<index3<<"\n";
            //cout<<final[i]<<"\n";
            if (final[i] != -1){
                cout<<s[records[final[i]].index];
                s[records[final[i]].index] = -1;
            }
            else
                break;
        }
        
        for (long long i = 0; i<length; i++){
            if (s[i] != -1)
                cout<<s[i];
        }
    
    }
    return 0;
}
