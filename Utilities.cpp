//
// Created by KunstDerFuge on 1/26/18.
//

#include <random>
#include <iostream>
#include "Utilities.h"

using namespace std;

static std::default_random_engine ENGINE;

int randomChoiceOfN(int n) {
    uniform_int_distribution<int> distribution(0, n-1);
    return distribution(ENGINE);
}

float randomFloatZeroToN(float n) {
    uniform_real_distribution<float> distribution(0.f, n);
    return distribution(ENGINE);
}

float randomSampleNormal(float mean, float dev) {
    normal_distribution<float> distribution(mean, dev);
    return distribution(ENGINE);
}

float randomSampleNormal(float mean, float dev, float min, float max) {
    normal_distribution<float> distribution(mean, dev);
    float out = distribution(ENGINE);
    if (out < min) out = min;
    if (out > max) out = max;
    return out;
}

template<typename t>
t randomChoiceFromVector(std::vector<t> vector) {
    size_t size = vector.size();
    return vector[randomChoiceOfN(size)];
}

int randomChoiceFromWeights(std::initializer_list<int> list) {
    vector<int> vector  = list;
    int sum = 0;
    for (auto number : vector) {
        sum += number;
    }
    int random = randomChoiceOfN(sum);
    for (int i = 0; i < vector.size(); i++) {
        if (random < vector[i]) {
            return i;
        }
        random -= vector[i];
    }
    throw;
}

bool randomBool() {
    return randomChoiceOfN(2) == 1;
}

string toLowercase(std::string in) {
    for (char c : in)
        tolower(c);
    return in;
}

string toSentenceCase(std::string in) {
    in = toLowercase(in);
    in[0] = toupper(in[0]);
    return in;
}

std::string toOrdinal(int in) {
    string ordinals[20] = {"first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eighth", "ninth",
                            "tenth", "eleventh", "twelfth", "thirteenth", "fourteenth", "fifteenth", "sixteenth",
                            "seventeenth", "eighteenth", "nineteenth", "twentieth"};
    if (in <= 19)
        return ordinals[in];

    if (in < 29)
        return "twenty-" + ordinals[in % 20];

    if (in == 29)
        return "thirtieth";

    if (in < 39)
        return "thirty-" + ordinals[in % 30];

    if (in == 39)
        return "fortieth";

    if (in < 49)
        return "forty-" + ordinals[in % 40];

    if (in == 49)
        return "fiftieth";

    cerr << "Number not supported by toOrdinal(): " << in << endl;
    return "ERROR";
}

std::string concatenateWord(std::string& sentence, std::string word) {
    if (!sentence.empty())
        sentence += ' ';
    sentence += word;
    return sentence;
}

std::string namePosition(int position, int numberOfPositions, bool useLeftRight) {
    if (numberOfPositions == 3 && useLeftRight) {
        if (position == 0) {
            return "left";
        } else if (position == 1) {
            return "middle";
        } else if (position == 2) {
            return "right";
        }
    } else if (numberOfPositions == 2 && useLeftRight) {
        if (position == 0) {
            return "left";
        } else {
            return "right";
        }
    }
    return toOrdinal(position);
}