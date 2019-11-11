#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int m_minSearchLength;
    vector<Genome> genomes;
    Trie<DNAMatch> subsequences;
    map<string,Genome> shortcut;
    bool equals(string word1, string word2, int mistakesAllowed) const;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
: m_minSearchLength(minSearchLength)
{}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    genomes.push_back(genome);
    for (int i = 0; i < genome.length() - (m_minSearchLength-1); i++)
    {
        string fragment;
        genome.extract(i, m_minSearchLength, fragment);
        DNAMatch sample;
        sample.genomeName = genome.name();
        sample.length = m_minSearchLength;
        sample.position = i;
        subsequences.insert(fragment, sample);
        shortcut.insert(pair<string,Genome>(sample.genomeName,genome));
    }
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;  // This compiles, but may not be correct
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    if (fragment.size() < minimumLength)
        return false;
    if (minimumLength < m_minSearchLength)
        return false;
    if (exactMatchOnly)
    {
        vector<DNAMatch> lessLikely;
        string part = fragment.substr(0, m_minSearchLength);
        lessLikely = subsequences.find(part, true);
        for (int i = 0; i < lessLikely.size(); i++)
        {
            vector<DNAMatch> moreLikely;
            auto itr = shortcut.find(lessLikely[i].genomeName);
            for (int j = minimumLength; j <= fragment.size(); j++)
            {
                string guinea;
                (itr->second).extract(lessLikely[i].position, j, guinea);
                if ((fragment.find(guinea) != string::npos) && ((itr->second).extract(lessLikely[i].position, j, guinea)))
                {
                    DNAMatch possibility;
                    possibility.genomeName = lessLikely[i].genomeName;
                    possibility.length = j;
                    possibility.position = lessLikely[i].position;
                    moreLikely.push_back(possibility);
                }
            }
            if (moreLikely.size() == 0)
                return false;
            DNAMatch finalOne = moreLikely[0];
            for (int k = 0; k < moreLikely.size()-1; k++)
            {
                if (moreLikely[k+1].length > moreLikely[k].length)
                    finalOne = moreLikely[k+1];
            }
            matches.push_back(finalOne);
        }
    }
    if (!exactMatchOnly)
    {
        vector<DNAMatch> lessLikely;
        string part = fragment.substr(0, m_minSearchLength);
        lessLikely = subsequences.find(part, false);
        for (int i = 0; i < lessLikely.size(); i++)
        {
            // going through each DNAMatch in lessLikely, follow it's name to its genome, and compare the string to fragment as the string gets longer by one, allowing it to increment as long as it is only off by one character
            vector<DNAMatch> moreLikely;
            auto itr = shortcut.find(lessLikely[i].genomeName);
            for (int j = minimumLength; j <= fragment.size(); j++)
            {
                string guinea;
                (itr->second).extract(lessLikely[i].position, j, guinea);
                if ((equals(guinea, fragment, 1)) && ((itr->second).extract(lessLikely[i].position, j, guinea)))
                {
                    DNAMatch possibility;
                    possibility.genomeName = lessLikely[i].genomeName;
                    possibility.length = j;
                    possibility.position = lessLikely[i].position;
                    moreLikely.push_back(possibility);
                }
            }
            if (moreLikely.size() == 0)
                return false;
            DNAMatch finalOne = moreLikely[0];
            for (int k = 0; k < moreLikely.size()-1; k++)
            {
                if (moreLikely[k+1].length > moreLikely[k].length)
                    finalOne = moreLikely[k+1];
            }
            matches.push_back(finalOne);
        }
    }
    return true;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    if (fragmentMatchLength < m_minSearchLength)
        return false;
    int total = query.length()/fragmentMatchLength;
    vector<DNAMatch> sample;
    vector<Genome> jackpot;
    for (int i = 0; i < total; i++)
    {
        string frag;
        query.extract(i*fragmentMatchLength, fragmentMatchLength, frag);
        if (findGenomesWithThisDNA(frag, fragmentMatchLength, exactMatchOnly, sample))
        {
            for (int j = 0; j < sample.size(); j++)
            {
                auto itr = shortcut.find(sample[j].genomeName);
                jackpot.push_back(itr->second);
            }
        }
    }
    return true;  // This compiles, but may not be correct
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}

//=============================================== Helper Functions =======================================================

bool GenomeMatcherImpl::equals(string word1, string word2, int mistakesAllowed) const
{
    if (word1 == word2) // if word1 equals word2, we can always return true
        return true;
    if (word1.length() == word2.length())
    { // if word1 is as long as word 2
        for (int i = 0; i < word1.length(); i++)
        { // go from first to last character index the words
            if(word1.at(i) != word2.at(i))
            { // if this character from word 1 does not equal the character from word 2
                mistakesAllowed--; // reduce one mistake allowed
                if (mistakesAllowed < 0)
                { // and if you have more mistakes than allowed
                    return false; // return false
                }
            }
        }
    }
    return true;
}

//int main()
//{
//    Genome g("Haley", "ATC");
//    Genome G("Jonathan", "ATG");
//    GenomeMatcher gm(2);
//    gm.addGenome(g);
//    gm.addGenome(G);
//    vector<DNAMatch> matches;
//    gm.findGenomesWithThisDNA("ZZZ", 3, false, matches);
//}
