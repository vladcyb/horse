#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#define RESULTS_PER_FILE 100

const int N = 5;
const int NN = N * N;

std::ofstream fout("1.txt", std::ofstream::out);
int total = 0;

std::stringstream ss;

void print(int a[][N]){
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            ss << std::setw(3) << a[i][j];
        }
        ss << std::endl;
    }
    ss << std::endl;
}

void foo(int a[][N], int i0, int j0, int num) {

    int b[N][N];
    std::copy(a[0], a[0] + N * N, b[0]);

    if (i0 > -1 && i0 < N && j0 > -1 && j0 < N && b[i0][j0] == 0){
        b[i0][j0] = num;

        if(num == NN){
            if (total % RESULTS_PER_FILE == 0) {
              fout << ss.rdbuf();
              fout.close();
              fout.open(std::to_string(total / RESULTS_PER_FILE + 1) + ".txt");
            }
            ++total;
            print(b);
            return;
        }
        if(i0 > 1){
            if(j0 > 0){
                foo(b, i0-2, j0-1, num+1);
            }
            if(j0 < N - 1){
                foo(b, i0-2, j0+1, num+1);
            }
        }
        if(i0 > 0){
            if(j0 > 1){
                foo(b, i0-1, j0-2, num+1);
            }
            if(j0 < N - 2){
                foo(b, i0-1, j0+2, num+1);
            }
        }
        if (i0 < N - 1){
            if(j0 < N - 2){
                foo(b, i0+1, j0+2, num+1);
            }
            if(j0 > 1){
                foo(b, i0+1, j0-2, num+1);
            }
        }
        if (i0 < N - 2){
            if(j0 < N - 1){
                foo(b, i0+2, j0+1, num+1);
            }
            if(j0 > 0){
                foo(b, i0+2, j0-1, num+1);
            }
        }
    }
}

int main(){
    auto startTime = std::chrono::steady_clock::now();
    int a[N][N];

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            a[i][j] = 0;
        }
    }

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            foo(a, i, j, 1);
        }
    }

    auto stopTime = std::chrono::steady_clock::now();
    int time = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count();
    std::ofstream result("summary.txt", std::ofstream::out);
    result << "Total: " << total << "." << std::endl;
    result << "Every file has maximum " << RESULTS_PER_FILE << " variants." << std::endl;
    result << "Program executed in " <<  time << " milliseconds.\n";
    result.close();
    if (!ss.eof()) {
      fout << ss.rdbuf();
    }
    fout.close();
    return 0;
}
