#include <iostream>
#include <stack>
using namespace std;
#define endl "\n"


void built(long num, stack<long> &Stack, stack<long> &stack1, stack<long> &stack2);
long calculate(long n);

    long pairs = 0;
    long lindex = l;
    long rindex = mid+1;
    cout<<lindex<<" "<<rindex<<"\n";
    /*for (long i = l; i<=r; i++){
        cout<<x_y[i].x<<" "<<x_y[i].y<<"  ";
    }
    cout<<"\n";*/
    xy left[mid-l+1];
    xy right[r-mid];
    for (long i = l; i<= mid; i++){
        left[i] = x_y[i];
        cout<<left[i].x<<" "<<left[i].y<<" ";
    }
    for (long i = mid+1; i<= r; i++){
        right[i] = x_y[i];
        cout<<right[i].x<<" "<<right[i].y<<" ";
    }
    cout<<"\n";
    for(long i = l; i<=r; i++){
        if (lindex > mid){
            x_y[i] = right[rindex];
            rindex++;
            //cout<<x_y[i].x<<" "<<x_y[i].y<<" ";
        }
        else if (rindex > r){
            x_y[i] = left[lindex];
            lindex++;
            //cout<<x_y[i].x<<" "<<x_y[i].y<<" ";
        }
        else if (x_y[lindex].y > x_y[rindex].y ){
            pairs += rindex-lindex;
            x_y[i] = right[rindex];
            rindex++;
            //cout<<x_y[i].x<<" "<<x_y[i].y<<" ";
        }
        else{
            x_y[i] = left[lindex];
            lindex++;
            cout<<x_y[i].x<<" "<<x_y[i].y<<" ";
        }
    }

    cout<<pairs<<"\n";
    return pairs;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    long n;
    cin >> n;
    long mv = 0;
    stack<long> Stack;
    stack<long> stack1;
    stack<long> stack2;
    mv = calculate(n);
    cout<<mv<<endl;
    for (long i = 0; i < n; i++){
        Stack.push(n-i);
        cout<<"PLACE "<< n-i<<"\n";
    }



    built(n, Stack, stack1, stack2);

    return 0;
}

void built(long num, stack<long> &Stack, stack<long> &stack1, stack<long> &stack2){
    if (num == 1){

        cout << "PHOTO" << endl;
    }
    else{
        built((num-num/2), Stack, stack1, stack2);
        for (long i = 0; i < num; i++){
            if(i <num-num/2){
                stack1.push(Stack.top());
                Stack.pop();
                cout << "POP" << endl;
            }
            else{
                stack2.push(Stack.top());
                Stack.pop();
                cout << "POP" << endl;
            }
        }
        for (long i = 0; i<num; i++){
            if (!stack1.empty()){
                long long k = stack1.top();
                Stack.push(k);
                stack1.pop();

                cout << "PLACE " << k << endl;
            }
            else{
                long long k = stack2.top();
                Stack.push(k);
                stack2.pop();

                cout << "PLACE " << k << endl;
            }
        }

        built((num/2), Stack, stack1, stack2);

    }
    return;

}

long calculate(long n){
    if (n == 1){
        return 2;
    }
    else if (n % 2 != 0){
        return calculate(n/2)+calculate(n-n/2)+n*2;
    }
    else{
        return 2*calculate(n/2)+n*2;
    }


}

