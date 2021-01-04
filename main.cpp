#include <chrono>
#include <cstdio>
#include <cstring>

const int N = 5;
const int Nd2 = N/2 + N%2;
const int NN = N*N;

FILE * pfile;

int total = 0;

void print(int a[][N], bool not_print){
    total++;
    if (not_print)
        return;
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
    memcpy(b, a, sizeof(int)*NN);
    
    b[i0][j0] = num;
    if(num++ == NN){
        print(b, true);
        return;
    }

    auto mv_l  = i0 > 0;
    auto mv_ll = i0 > 1;
    auto mv_r  = i0 < N - 1;
    auto mv_rr = i0 < N - 2;

    auto mv_t  = j0 > 0;
    auto mv_tt = j0 > 1;
    auto mv_b  = j0 < N - 1;
    auto mv_bb = j0 < N - 2;

    if (mv_l && mv_tt && !b[i0 - 1][j0 - 2]) foo(b, i0 - 1, j0 - 2, num);
    if (mv_l && mv_bb && !b[i0 - 1][j0 + 2]) foo(b, i0 - 1, j0 + 2, num);
    if (mv_ll && mv_t && !b[i0 - 2][j0 - 1]) foo(b, i0 - 2, j0 - 1, num);
    if (mv_ll && mv_b && !b[i0 - 2][j0 + 1]) foo(b, i0 - 2, j0 + 1, num);

    if (mv_r && mv_tt && !b[i0 + 1][j0 - 2]) foo(b, i0 + 1, j0 - 2, num);
    if (mv_r && mv_bb && !b[i0 + 1][j0 + 2]) foo(b, i0 + 1, j0 + 2, num);
    if (mv_rr && mv_t && !b[i0 + 2][j0 - 1]) foo(b, i0 + 2, j0 - 1, num);
    if (mv_rr && mv_b && !b[i0 + 2][j0 + 1]) foo(b, i0 + 2, j0 + 1, num);
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
