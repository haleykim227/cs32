//
//  landmark.cpp
//  landmark
//
//  Created by Haley Kim on 2/7/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

class Landmark
{
public:
    Landmark(string name);
    virtual ~Landmark() = 0;
    virtual string color() const;
    virtual string icon() const = 0;
    string name() const;
private:
    string m_name;
};

Landmark::Landmark(string name)
{
    m_name = name;
}

string Landmark::name() const
{
    return m_name;
}

string Landmark::color() const
{
    return "yellow";
}

Landmark::~Landmark()
{}

class Hotel: public Landmark
{
public:
    Hotel(string name);
    virtual ~Hotel();
    virtual string icon() const;
};

Hotel::Hotel(string name)
: Landmark(name)
{}

string Hotel::icon() const
{
    return "bed";
}

Hotel::~Hotel()
{
    cout << "Destroying the hotel " << Landmark::name() << "." << endl;
}

class Restaurant: public Landmark
{
public:
    Restaurant(string name, int capacity);
    virtual ~Restaurant();
    virtual string icon() const;
private:
    int m_capacity;
};

Restaurant::Restaurant(string name, int capacity)
: Landmark(name)
{
    m_capacity =  capacity;
}

string Restaurant::icon() const
{
    if (m_capacity >= 40)
        return "large knife/fork";
    else
        return "small knife/fork";
}

Restaurant::~Restaurant()
{
    cout << "Destroying the restaurant " << Landmark::name() << "." << endl;
}

class Hospital: public Landmark
{
public:
    Hospital(string name);
    virtual ~Hospital();
    virtual string color() const;
    virtual string icon() const;
};

Hospital::Hospital(string name)
: Landmark(name)
{}

string Hospital::color() const
{
    return "blue";
}

string Hospital::icon() const
{
    return "H";
}

Hospital::~Hospital()
{
    cout << "Destroying the hospital " << Landmark::name() << "." << endl;
}
