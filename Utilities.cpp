//
// Created by KunstDerFuge on 1/26/18.
//

#include <random>
#include <iostream>
#include <algorithm>
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
    float out = randomSampleNormal(mean, dev);
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
    vector<int> vector = list;
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

bool randomBool(float chance) {
    if (chance == 0.5)
        return randomChoiceOfN(2) == 1;

    return randomFloatZeroToN(1.f) < chance;
}

void toLowercase(std::string& in) {
    std::transform(in.begin(), in.end(), in.begin(), ::tolower);
}

void toSentenceCase(std::string& in) {
    toLowercase(in);
    in[0] = toupper(in[0]);
}

std::string toOrdinal(int in) {
    string ordinals[20] = {"first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eighth", "ninth",
                            "tenth", "eleventh", "twelfth", "thirteenth", "fourteenth", "fifteenth", "sixteenth",
                            "seventeenth", "eighteenth", "nineteenth", "twentieth"};
    if (in <= 19)
        return ordinals[in];

    if (in < 29)
        return "twenty-" + ordinals[in - 20];

    if (in == 29)
        return "thirtieth";

    if (in < 39)
        return "thirty-" + ordinals[in - 30];

    if (in == 39)
        return "fortieth";

    if (in < 49)
        return "forty-" + ordinals[in - 40];

    if (in == 49)
        return "fiftieth";

    cerr << "Number not supported by toOrdinal(): " << in << endl;
    return "ERROR";
}

void concatenateWord(std::string& sentence, std::string word) {
    if (word.empty())
        return;
    char lastChar = sentence[sentence.size()-1];
    if (!sentence.empty() && lastChar != ' ')
        sentence += ' ';
    sentence += word;
}

/*
 * Same as concatenateWord, but doesn't modify the sentence, just returns the concatenated sentence.
 */
std::string concatenateWordToCopy(std::string sentence, std::string word) {
    if (word.empty())
        return sentence;
    char lastChar = sentence[sentence.size()-1];
    if (!sentence.empty() && lastChar != ' ')
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

int randomFromXToY(int x, int y) {
    return randomChoiceOfN(y-x + 1) + x;
}

std::string toPossessive(std::string in) {
    char lastChar = in[ in.size()-1 ];
    if (lastChar == 's')
        return in + "\'";

    return in + "'s";
}

sf::Vector2f tileToRenderCoord(float x, float y) {
    return {x*TILE_WIDTH, y*TILE_WIDTH};
}

long mod(long k, long n) {  // https://stackoverflow.com/questions/12276675/modulus-with-negative-numbers-in-c
    return ((k %= n) < 0) ? k+n : k;
}

const std::string assetsPath() {
    return "../assets";
}
const std::string graphicsPath() {
    return assetsPath() + "/graphics";
}
const std::string fontsPath() {
    return assetsPath() + "/fonts";
}
const std::string shadersPath() {
    return assetsPath() + "/shaders";
}
