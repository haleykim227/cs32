//
//  main.cpp
//  Project 2
//
//  Created by Haley Kim on 1/25/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#include <iostream>
#include <string>
#include "Set.h"
using namespace std;

int main()
{
    Set ss;
    ss.insert("a");
    ss.insert("b");
    ss.insert("d");
    ss.insert("c");
    ss.insert("f");
    ss.insert("e");
    ss.insert("e");
    ss.erase("a");
    ss.insert("a");
    cerr << ss.contains("a") << endl;
    cerr << ss.contains("z") << endl;
    Set ss2;
    cerr << ss2.contains("a") << endl;
    ss.dump();
    ItemType z = "zzz";
    cerr << ss.get(5,z) << endl;
    cerr << z << endl;
    cerr << ss2.get(0,z) << endl;
    ss2.insert("x");
    ss2.insert("y");
    ss2.insert("z");
    ss2.dump();
    ss.swap(ss2);
    ss.dump();
    cerr << ss.size() << endl;
    cerr << endl;
    cerr << endl;
    cerr << endl;
    cerr << endl;
    cerr << ss2.size() << endl;
    ss2.dump();
    cerr << endl;
    cerr << endl;
    ss.dump();
    Set ss3(ss);
    ss3.dump();
    cerr << ss3.size() << endl;
    cerr << ss.size() << endl;
    ss2.dump();
    Set ss4(ss2);
    ss4.dump();
    cerr << ss4.size() << endl;
    ss.dump();
    ss2.dump();
    unite(ss, ss2, ss3);
    cerr << endl;
    ss3.dump();
    subtract(ss3, ss, ss2);
    cerr << endl;
    ss2.dump();
    cerr << endl;
    Set set1;
    set1.insert("hello");
    set1.insert("world");
    set1.dump();
    Set set2;
    set2.insert("안녕");
    set2.insert("지구");
    set2.dump();
    unite(set1, set2, set1);
    cerr << endl;
    set1.dump();
    subtract(set1, set2, set2);
    set2.dump();
    Set s1;
    s1.insert("a");
    s1.insert("b");
    s1.insert("c");
    Set s2;
    s2.insert("d");
    s2.insert("e");
    s2.insert("f");
    s1.swap(s2);
    cerr << endl;
    s1.dump();
}
