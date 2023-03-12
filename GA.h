#ifndef GA_H_INCLUDED
#define GA_H_INCLUDED
#define MAX_LINE_LENGTH 1000
#define polpulationSize 4
#define generationNum 4
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "Generation.h"
using namespace std;


class File {
private:
    ifstream file;
    int currenyKnapSize;
    int currentItemsNum;
    int testCases;
    vector<Bag>currentBags;

public:
    //File(char * path){file.open(path);}
    int readTestNum() {
        file >> testCases;
        return testCases;
    }
    vector<Bag> readBags() {
        currentBags.clear();
        file >> currenyKnapSize;
        file >> currentItemsNum;
        for (int j = 0; j < currentItemsNum; j++) {
            Bag bag;
            file >> bag.weight >> bag.value;
            currentBags.push_back(bag);
        }
        return currentBags;
    }
    int getCurrItemsNum() { return currentItemsNum; }
    int getCurrKnapSize() { return currenyKnapSize; }
    int getTestNum() { return testCases; }
    void openFile() { file.open("knapsack_input.txt"); }

};


class GeneticAlgo {

public:
    File file;

    GeneticAlgo() {
        file.openFile();
    }

    void geneticAlgo() {
        int testCases = file.readTestNum();

        for (int i = 0; i <testCases; i++) {

            Generation generation;
            generation.setBags(file.readBags());
            generation.setItemNum(file.getCurrItemsNum());
            generation.setKnapSize(file.getCurrKnapSize());

            //Step 1-->Initialize populationIntial with Default size -->4.
            generation.populationIntial();
            for (int j = 0; j <generationNum; j++) {
                generation.calFitness(true);
                generation.rankSelection();
                generation.crossOver();
                generation.mutation();
            }
            cout<<"TestIndex: "<<(i+1)<<endl;
            generation.finalOutput();
            cout<<"---------------------------------------"<<endl;
        }

    }
};

#endif // GA_H_INCLUDED

