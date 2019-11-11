#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_sequence;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
: m_name(nm), m_sequence(sequence)
{}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    string total, part, past, name, sequence;
    int numOfLines = 0;
    while(getline(genomeSource, part))
    {
        // checking validity
        total = total + part + "/";
        numOfLines += 1;
        // non name lines having anything but A T C G N
        if (part[0] != '>')
        {
            for (int i = 0; i < part.size(); i++)
            {
                if ((part[i] != 'A') && (part[i] != 'T') && (part[i] != 'C') && (part[i] != 'G') && (part[i] != 'N') && (part[i] != 'a') && (part[i] != 't') && (part[i] != 'c') && (part[i] != 'g') && (part[i] != 'n'))
                    return false;
            }
        }
        // no empty lines
        if (part.size() == 0)
            return false;
        // no line starting with greater than and no other character
        if ((part[0] == '>') && (part.size() == 1))
            return false;
        // no base line after name line
        if ((part[0] == '>') && (past[0] == '>') && (part.size() != 0))
            return false;
        past = part;
        
        // loading
        if (part[0] == '>')
        {
            if (sequence.size() != 0)
            {
                Genome addition = Genome(name, sequence);
                genomes.push_back(addition);
            }
            name = part.substr(1,part.size()-1);
            sequence = "";
        }
        if (part[0] != '>')
        {
            sequence += part;
        }
    }
    if (sequence.size() != 0)
    {
        Genome addition = Genome(name, sequence);
        genomes.push_back(addition);
    }
    // not starting with name line
    if (total[0] != '>')
        return false;
    if (past[0] == '>')
        return false;
    return true;
}

int GenomeImpl::length() const
{
    return m_sequence.size();  // This compiles, but may not be correct
}

string GenomeImpl::name() const
{
    return m_name;  // This compiles, but may not be correct
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (position + length > m_sequence.size())
        return false;
    if (length < 0)
        return false;
    if (position < 0)
        return false;
    fragment = m_sequence.substr(position, length);
    return true;  // This compiles, but may not be correct
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes) 
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}

//int main()
//{
//    ifstream file("/Users/haleykim/Desktop/Halobacterium_jilantaiense.txt");
//    vector<Genome> genomes;
//    cout << Genome::load(file, genomes) << endl;
//    for (int i = 0; i < genomes.size(); i++)
//    {
//        cout << genomes[i].name() << endl;
//        cout << genomes[i].length() << endl;
//    }
//    Genome test("Haley", "ATCGATCGATCG");
//    string fragment1, fragment2;
//    bool result1 = test.extract(0, 8, fragment1);
//    bool result2 = test.extract(-1, 8, fragment2);
//    cout << fragment1 << endl;
//    cout << fragment2 << endl;
//    cout << result1 << endl;
//    cout << result2 << endl;
//}
