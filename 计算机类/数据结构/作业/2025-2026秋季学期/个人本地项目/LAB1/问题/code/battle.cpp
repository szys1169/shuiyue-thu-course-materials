#include <cstdio>
#include <cstdlib>
int main(){
    system("g++ rand_input.cpp -o rand_input");
    system("g++ check_input.cpp -o check_input");
    system("g++ solution_1.cpp -o solution_1");
    system("g++ solution_2.cpp -o solution_2");
    system("g++ solution_3.cpp -o solution_3");
    system("rand_input.exe > rand.in");
    //system("solution_1.exe < rand.in > 1.out");
    //system("solution_2.exe < rand.in > 2.out");
    system("solution_3.exe < rand.in > 3.out");
    return 0;
}