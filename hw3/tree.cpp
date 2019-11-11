//
//  tree.cpp
//  tree
//
//  Created by Haley Kim on 2/11/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0)
        return 1;
    if (n1 <= 1)
    {
        if (n2 == 1 && a1[0] == a2[0])
            return 1;
        else
            return 0;
    }
    if (a1[0] == a2[0])
        return countIncludes(a1+1, n1-1, a2, n2) + countIncludes(a1+1, n1-1, a2+1, n2-1);
    else
        return countIncludes(a1+1, n1-1, a2, n2);
}

void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

void divide(double a[], int n, double divider,
            int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < divider)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > divider)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

void order(double a[], int n)
{
    if (n <= 1)
        return;
    int mid = n/2;
    int firstNotGreater = -1;
    int firstLess = n;
    divide(a, n, a[mid], firstNotGreater, firstLess);
    order(a, firstNotGreater);
    order(a + firstLess, n - firstLess);
}
