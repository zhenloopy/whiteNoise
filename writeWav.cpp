#include <fstream>
#include <random>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;


const int sampleRate {44100};
const int bitDepth {16};
const int duration {20};

class RandomOscillator {

    private:
        //  should contain amplitude under 1
        int upper_freq {};
        default_random_engine generator;
    public:
        RandomOscillator(int upper) : upper_freq{upper} {}
        float process () {
            //  random number
            uniform_real_distribution<> dis(-upper_freq, upper_freq);
            float randomNumber = dis(generator);
            randomNumber = randomNumber * (pow(2, bitDepth-1)-1);
            return randomNumber;
        }
};

int main() {

    RandomOscillator myRandom = RandomOscillator(800);
    ofstream output;
    string outputString {};
    output.open("rawdata", ios::binary);

    int sample {};
    for (int i = 0; i < duration*sampleRate; i++) {
        sample = myRandom.process();
        output.write(reinterpret_cast<char*> (&sample), 2);
    }


    return 0;
}
