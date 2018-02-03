//
// Created by KunstDerFuge on 1/26/18.
//

#ifndef HEADSPACE_UTILITIES_H
#define HEADSPACE_UTILITIES_H

#include <vector>
#include <string>

int randomChoiceOfN(int n);
float randomFloatZeroToN(float n);
float randomSampleNormal(float, float);
float randomSampleNormal(float mean, float dev, float min, float max);
int randomChoiceFromWeights(std::initializer_list<int>);
bool randomBool();

template<typename t>
t randomChoiceFromVector(std::vector<t> vector);

std::string toSentenceCase(std::string in);
std::string toLowercase(std::string in);
std::string toOrdinal(int in);
std::string concatenateWord(std::string& sentence, std::string word);
std::string namePosition(int position, int numberOfPositions, bool useLeftRight);


#endif //HEADSPACE_UTILITIES_H
