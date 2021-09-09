#ifndef ELAPSED_T_INCLUDED
#define ELAPSED_T_INCLUDED
#include <chrono>
#include <iostream>

using namespace std;

int elapsedTime (){

auto start = chrono::steady_clock::now();

    // do some stuff here
    sleep(3);

auto end = chrono::steady_clock::now();

    cout << "Elapsed time in nanoseconds: "
        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
        << " ns" << endl;

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;

    cout << "Elapsed time in milliseconds: "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms" << endl;

    cout << "Elapsed time in seconds: "
        << chrono::duration_cast<chrono::seconds>(end - start).count()
        << " sec";

    return 0;
}


#endif // ELAPSED_T_INCLUDED
