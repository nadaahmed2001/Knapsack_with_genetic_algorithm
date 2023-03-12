#ifndef GENERATUIN_H_INCLUDED
#define GENERATUIN_H_INCLUDED
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAX_LINE_LENGTH 1000
#define polpulationSize 4
#define generationNum 4
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstdlib>
using namespace std;


bool fitnessSort(const pair <int, int>& a, const pair <int, int>& b)
{
    return (a.second < b.second);
}
struct Bag
{
    int weight, value;
};
class Chromosome
{

public:
    vector<bool> genes;

    
    Chromosome makeMutation(Chromosome chrom,int iremsNum)
    {
        double Pm = 0.1;
        for (int i = 0; i <iremsNum ; i++)
        {
            //get random number between 0,1
            double r = ((double)rand() / (RAND_MAX));
            if (r <= Pm)   //bit_flibing each offspring
            {
                chrom.genes[i]=!chrom.genes[i];
            }
        }
        return chrom;
    }
};

class Generation
{

public:
    vector<Chromosome>chromosomes;
    vector<Bag>bags;
    vector< pair <int, int> >fitness; //Chromsome_index-->FitnessNumber.
    vector< pair <int, int> >ranks;
    vector< pair <int, double> >percentage;
    int crossIndex1, crossIndex2;
    int itemsNum;
    int knapSnakSize;



public:
    void finalOutput()
    {
        calFitness(false);

        if(fitness[fitness.size()-1].second!=0)
        {
            int selectedItems=0,totalW=0;
            Chromosome chrom=chromosomes[(fitness[fitness.size()-1].first)];
            //get number of selected items
            for(int j=0; j<itemsNum; j++)
            {
                if(chrom.genes[j]==1)
                {
                    selectedItems++;
                    totalW+=bags[j].weight;
                }
            }


            cout<<"The KnapSnak Size is:  "<<knapSnakSize<<endl;
            cout<<"Total Value of Best Chromosome is:  "<<fitness[fitness.size()-1].second<<endl;
            cout<<"Total Weight of Best Chromosome is:  "<<totalW<<endl;
            cout<<"Number of Selected Items:  "<<selectedItems<<endl;

            for(int j=0; j<itemsNum; j++)
            {
                if(chrom.genes[j]==1)
                {
                    cout<<"     BagId Selected is: "<<(j+1)<<endl;
                    cout<<"            With Value: " <<bags[j].value<<endl;
                    cout<<"            With Weight: " <<bags[j].weight<<endl;
                }
            }
        }
        else
            cout<<"NO Exist Best Fitness All of Generation Chromesomes are notvalid ";
    }

    void populationIntial()
    {
        chromosomes.clear();
        for (int i = 0; i < polpulationSize; i++)
        {
            Chromosome chromG;
            for (int j = 0; j < itemsNum; j++)
            {
                int value = (std::rand() % 2);
                chromG.genes.push_back(value);
            }
            chromosomes.push_back(chromG);

        }
    }
    void printTest()
    {
        cout<<"KNAP "<<knapSnakSize<<endl;

        cout<<"BAGSSSSSSSSSSS------------"<<endl;
        for (int i = 0; i < bags.size(); i++)
            cout << bags[i].weight << ' ' << bags[i].value << endl;

        cout<<"Chrommmmmmmmmmm"<<endl;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < itemsNum; j++)
            {
                Chromosome c = chromosomes[i];
                cout << c.genes[j] << ' ';
            }
            cout << endl;
        }


        cout<<"FITTTTTTTTTNESS"<<endl;
        for (int i = 0; i < fitness.size(); i++)
            cout << fitness[i].first << ' ' << fitness[i].second << endl;

        cout<<"RANKS-------"<<endl;
        for (int i = 0; i < ranks.size(); i++)
            cout << ranks[i].first << ' ' << ranks[i].second << endl;


        cout<<"PERCENTAGE----"<<endl;
        for (int j = 0; j < percentage.size(); j++)
            cout << percentage[j].first << " " << percentage[j].second << endl;

        cout<<"crossIndex "<<crossIndex1<<' '<<crossIndex2<<endl;



    }
    void setBags(vector<Bag>cBags)
    {
        bags.clear();
        bags = cBags;
        //for(int i=0;i<bags.size();i++) cout<<bags[i].weight<<' ' <<bags[i].value<<endl;
    }

    void setItemNum(int itemsNUm)
    {
        itemsNum = itemsNUm;
    }
    void setKnapSize(int size)
    {
        knapSnakSize = size;
    }


    int solveInfeasible(int notValidIndex)
    {

        int totalFitnessV = 0,totalW = 0;

        for (int n = 0; n < itemsNum; n++)
            chromosomes[notValidIndex].genes[n] = 0;

        ///////////////////Here I want to generate a random N bit string and then check if valid or not, if valid, replace

        //2-Check if this is valid
        for (int k = 0; k < itemsNum; k++)
        {
            int randomIndex = (std::rand() % itemsNum);
            chromosomes[notValidIndex].genes[randomIndex] = 1;
            if (bags[k].weight <= knapSnakSize)
            {
                totalW += bags[randomIndex].weight;
                totalFitnessV += bags[randomIndex].value;
                break;
            }
            else
                chromosomes[notValidIndex].genes[randomIndex] = 0;
        }
        return totalFitnessV;
    }

    void calFitness(bool ifRepair)
    {
        fitness.clear();
        for (int j = 0; j < polpulationSize; j++)  //Loop over C1,C2,..Cn
        {
            int  totalW = 0;
            int totalFitnessV = 0;
            bool valid = false;//boolean to check if all zeros

            for (int i = 0; i < itemsNum; i++)  //Loop inside each C (with the given list count)
            {
                if (chromosomes[j].genes[i] == 1)
                {
                    totalW += bags[i].weight;
                    totalFitnessV += bags[i].value;
                    valid = true;
                }
            }

            //Case Infeasible solution:
            if (totalW > knapSnakSize || !valid)
            {
                totalFitnessV=0;
                if(ifRepair)
                    totalFitnessV=solveInfeasible(j);
            }
            fitness.push_back(make_pair(j,totalFitnessV));    //push the number of chromosome that is valid and its total fitness
        }
        //sort the Fitness from smallest to largest.
        sort(fitness.begin(), fitness.end(), fitnessSort);
    }

    //Step3 Select parents using rank selection
    void  rankSelection()
    {

        //check
        ranks.clear();
        percentage.clear();
        int totalRanks = getTotalRanks();
        calPercentage(totalRanks);

        int counter = 0;
        while (counter != 50)
        {
            //select random numbers between [0,100]-->that refer to percentage.
            double random1 = (rand() % 100);
            double random2 = (rand() % 100);


            int index1 = chromRange(random1);
            int index2 = chromRange(random2);
            //check equal chromsomes or not?
            if (!checkEqual(index1, index2))
            {
                crossIndex1 = index1;
                crossIndex2 = index2;
                break;
            }
            counter++;
        }

    }

    void printTest2()
    {

        /*cout << "Number of test cases: " << testCasesNum << endl<<endl;
        cout << "----------------New Testcase----------------: " << endl;

        cout << "Size of the knapsack: " << knapSnakSize<<endl;
        cout << "Number of items: " << itemsNum << endl;


        cout << "Wieghts and values from the file : " << endl;
        for (int i = 0; i < bags.size(); i++)
            cout <<"Weight: " << bags[i].weight << "  value:  " << bags[i].value << endl;*/
    }

    int getTotalRanks()
    {
        int currentRank = 1;
        int sumRanks = 1;
        //the fitness is sort from smallest to largest.
        //ranks-->is pair(chromsomeIndex,RankNumber).
        ranks.push_back(make_pair(fitness[0].first, 1));
        for (int i = 1; i < fitness.size(); i++)
        {
            //same Fitness will have same rank.
            //so will start with index 1 and compare it with previous index;
            //different fitness have different rank.
            int fChrom1S = fitness[i].second;
            int fChrom2S = fitness[i - 1].second;
            if (fChrom1S == fChrom2S)
                ranks.push_back(make_pair(fitness[i].first, currentRank));
            else
                ranks.push_back(make_pair(fitness[i].first, ++currentRank));
            sumRanks += currentRank;
        }
        //return total Ranks to use it in the next step to get probability.
        return sumRanks;
    }

    void calPercentage(int sumRanks)
    {
        //the Probailty equation is rankNumber/totalRanks.
        //AFTER get the Probailty multiply it by 100
        //to make ranges sum previous range with new range.
        for (int i = 0; i < ranks.size(); i++)
        {
            double prob;
            //if i!=0 -->so there is no previous value of range so the start will be 0;
            if (i != 0)
            {
                prob = (((double)ranks[i].second / sumRanks) * 100) + (percentage[i - 1].second);
            }
            else
                prob = ((double)ranks[i].second / sumRanks) * 100;
            percentage.push_back(make_pair(ranks[i].first, prob));
        }
    }

    int chromRange(double random)
    {
        double startCompare = 0;
        for (int i = 0; i < percentage.size(); i++)
        {
            if (startCompare <= random && random < percentage[i].second)
            {
                return percentage[i].first;
            }
            else
                startCompare = percentage[i].second;
        }
        return 0;
    }


    bool checkEqual(int index1, int index2)
    {
        Chromosome sol1 = chromosomes[index1];
        Chromosome sol2 = chromosomes[index2];
        for (int i = 0; i < itemsNum; i++)
        {
            if (sol1.genes[i] != sol2.genes[i])
                return false;
        }

    };



    //Step4:Crossover
    void crossOver()
    {
        int Xc = 1;
        double rc = ((double)rand() / (RAND_MAX)); //random from 0 to 1
        double Pc = 0.6;
        if (rc <= Pc)   //Making the crossover
        {
            for (int i = Xc; i < itemsNum; i++)
            {
                int temp=chromosomes[crossIndex1].genes[i];
                chromosomes[crossIndex1].genes[i]=chromosomes[crossIndex2].genes[i];
                chromosomes[crossIndex2].genes[i]=temp;
            }
        }
    }


    //Step 5 :Mutation
    void mutation()
    {
        chromosomes[crossIndex1]=chromosomes[crossIndex1].makeMutation(chromosomes[crossIndex1],itemsNum);
        chromosomes[crossIndex2]=chromosomes[crossIndex2].makeMutation(chromosomes[crossIndex2],itemsNum);
    }
};



#endif // GENERATION_H_INCLUDED
