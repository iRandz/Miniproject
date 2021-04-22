#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<array>
#include<chrono>
#include<ctime>

using namespace std;
using namespace std::chrono;

// SUPPLEMENTARY FUNCTIONS START //
void printArray(int array[], int arrSize, int newlineSize) {
    for(int i = 0; i < arrSize; i++) {
        cout << array[i] << " ";
        if ((i+1) % newlineSize == 0 && i != 0) {
            cout << "\n";
        }
    }
    cout << "\n";
}
// SUPPLEMENTARY FUNCTIONS END //
// RANDOMIZED SELECT START //
int Partition(int PArray[], int Pstart, int Pend) {
    int x = PArray[Pend];
    int i = Pstart - 1;
    for(int j = Pstart; j < Pend; j++) {
        if (PArray[j] <= x) {
            i = i + 1;
            int temp = PArray[i];
            PArray[i] = PArray[j];
            PArray[j] = temp;
        }
    }
    int temp = PArray[i+1];
    PArray[i+1] = PArray[Pend];
    PArray[Pend] = temp;
    return i+1;
}

int RandomizedPartition(int RPArray[], int RPstart, int RPend) {
    int i = rand()%(RPend-RPstart + 1) + RPstart;
    int temp = RPArray[RPend];
    RPArray[RPend] = RPArray[i];
    RPArray[i] = temp;
    return Partition(RPArray, RPstart, RPend);
}

int RandomizedSelect(int Array[], int start, int end, int target) {
    if (start == end) {
        return Array[start];
    }
    int pivot = RandomizedPartition(Array, start, end);
    int k = pivot - start+1;
    if (target == k) {
        return Array[pivot];
    } else if (target < k) {
        return RandomizedSelect(Array, start, pivot-1, target);
    } else {
        return RandomizedSelect(Array, pivot+1, end, target-k);
    }
}
// RANDOMIZED SELECT END //

// --- ShellSort Select Start --- //
int Shellsort(int SsArray[], int SsStart, int SsEnd){
    // Using N/2 for the gap
    int n = (SsEnd - SsStart) + 1;
    
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        // Do a insertion using the current gap size
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted 
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = SsArray[i];
  
            // shift earlier gap-sorted elements up until the correct 
            // location for a[i] is found
            int j;            
            for (j = i; j >= gap && SsArray[j - gap] > temp; j -= gap)
                SsArray[j] = SsArray[j - gap];
              
            //  put temp (the original a[i]) in its correct location
            SsArray[j] = temp;
        }
    }
    return 0;
}
int ShellsortSelect(int SssArray[], int SssStart, int SssEnd, int SssTarget) {
    Shellsort(SssArray, SssStart, SssEnd);

    return SssArray[SssTarget-1];
}
// --- Shellsort Select End --- //


int main() {

    const int dataSize = 1000;
    int dataArray[dataSize];
    //fstream dataSet("mediumSet.csv");
    fstream dataSet("small.csv");
    if (dataSet.is_open()) {
        for(int i = 0; i < dataSize; i++) {
            string lineElement;
            getline(dataSet, lineElement, ',');
            dataArray[i] = stoi(lineElement);
        }
    }

    //printArray(dataArray, dataSize, 20);

    cout << "---" << endl;
    {
    int inputStart = 0;
    int inputEnd = 999;
    int inputTarget = 54;

    if (inputEnd > dataSize)
    {
        inputEnd = dataSize-1;
    }
    {
        int dataArrayCopy[dataSize];
        copy(begin(dataArray), end(dataArray), begin(dataArrayCopy));

        steady_clock::time_point randSelectStart = steady_clock::now();
        cout << RandomizedSelect(dataArrayCopy, inputStart, inputEnd, inputTarget) << endl;
        steady_clock::time_point randSelectStop = steady_clock::now();

        auto randSelectDuration = randSelectStop - randSelectStart;

        for (int i = 0; i < 3; i++)
        {
            int dataArrayCopy[dataSize];
            copy(begin(dataArray), end(dataArray), begin(dataArrayCopy));

            randSelectStart = steady_clock::now();
            RandomizedSelect(dataArrayCopy, inputStart, inputEnd, inputTarget);
            randSelectStop = steady_clock::now();

            randSelectDuration = min(randSelectDuration, randSelectStop - randSelectStart);
        }

        cout << "--- Randomized Select Running Time: " << duration <double, milli> (randSelectDuration).count() << " ms " << " ---" << endl << endl;

    }

    {
        int dataArrayCopy[dataSize];
        copy(begin(dataArray), end(dataArray), begin(dataArrayCopy));

        steady_clock::time_point ShellsortSelectStart = steady_clock::now();
        cout << ShellsortSelect(dataArrayCopy, inputStart, inputEnd, inputTarget) << endl;
        steady_clock::time_point ShellsortSelectStop = steady_clock::now();

        auto shellDuration = ShellsortSelectStop - ShellsortSelectStart;

        for (int i = 0; i < 3; i++)
        {
            int dataArrayCopy[dataSize];
            copy(begin(dataArray), end(dataArray), begin(dataArrayCopy));

            ShellsortSelectStart = steady_clock::now();
            ShellsortSelect(dataArrayCopy, inputStart, inputEnd, inputTarget);
            ShellsortSelectStop = steady_clock::now();

            shellDuration = min(shellDuration, ShellsortSelectStop - ShellsortSelectStart);
        }

        cout << "--- Shellsort Select Running Time: " << duration <double, milli> (shellDuration).count() << " ms " << " ---" << endl << endl;
    }
    }


    return 0;
}