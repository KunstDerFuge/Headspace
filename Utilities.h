//
// Created by KunstDerFuge on 1/26/18.
//

#ifndef HEADSPACE_UTILITIES_H
#define HEADSPACE_UTILITIES_H

#include <vector>
#include <string>

struct Point;

int randomChoiceOfN(int n);
int randomFromXToY(int x, int y);
float randomFloatZeroToN(float n);
float randomSampleNormal(float, float);
float randomSampleNormal(float mean, float dev, float min, float max);
int randomChoiceFromWeights(std::initializer_list<int>);
bool randomBool(float chance=0.5);

template<typename t>
t randomChoiceFromVector(std::vector<t> vector);

void toSentenceCase(std::string& in);
void toLowercase(std::string& in);
std::string toPossessive(std::string in);
std::string toOrdinal(int in);
void concatenateWord(std::string& sentence, std::string word);
std::string concatenateWordToCopy(std::string sentence, std::string word);
std::string namePosition(int position, int numberOfPositions, bool useLeftRight);

#endif //HEADSPACE_UTILITIES_H
