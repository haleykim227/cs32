//
//  main.cpp
//  linear
//
//  Created by Haley Kim on 2/11/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

bool anyTrue(const double a[], int n)
{
    if ((n == 0) || (n < 0))
        return false;
    if (somePredicate(a[n-1]))
        return true;
    else
    {
        return anyTrue(a, n-1);
    }
}

int countTrue(const double a[], int n)
{
    if (n <= 0)
        return 0;
    if (somePredicate(a[n-1]))
        return 1 + countTrue(a, n-1);
    return countTrue(a, n-1);
}

int firstTrue(const double a[], int n)
{
    if (n <= 0)
        return -1;
    if (somePredicate(a[0]))
        return 0;
    else
    {
        if (firstTrue(a+1, n-1) == 1)
            return 1;
        else
            return 1 + firstTrue(a+1, n-1);
    }
}

int positionOfMin(const double a[], int n)
{
    if (n <= 0)
        return -1;
    int position = 1 + positionOfMin(a+1, n-1);
    if(a[0] < a[position])
        return 0;
    else
        return position;
}

bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if (n1 == 0 && n2 == 0)
        return true;
    if (n1 == 0 && n2 != 0)
        return false;
    if (a2[0] == a1[0])
        return includes(a1+1,n1-1,a2+1,n2-1);
    else
        return includes(a1+1, n1-1, a2, n2);
}
