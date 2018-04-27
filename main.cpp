#include <chrono>
#include <cstdio>

const int N = 5;
const int Nd2 = N/2 + N%2;
const int NN = N*N;

FILE * pfile;

void print(int a[][N]){
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            fprintf(pfile, "%*i", 3, a[i][j]);
        }
        fprintf(pfile, "\n");
    }
    fprintf(pfile, "\n");
}

void foo(int a[][N], int i0, int j0, int num){

    int b[N][N];
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            b[i][j] = a[i][j];
        }
    }

    if (i0 > -1 && i0 < N && j0 > -1 && j0 < N && b[i0][j0] == 0){
        b[i0][j0] = num;

        if(num == NN){
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

    pfile = fopen("output.txt", "w");
    auto startTime = std::chrono::steady_clock::now();
    int a[N][N];

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            a[i][j] = 0;
        }
    }

    for(int i = 0; i < Nd2; ++i){
        for(int j = 0; j < Nd2; ++j){
            foo(a, i, j, 1);
        }
    }


    fclose(pfile);
    auto stopTime = std::chrono::steady_clock::now();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count();
    printf("%s%i%s", "Program executed in ",  ms, " milliseconds.\n");

    return 0;
}
