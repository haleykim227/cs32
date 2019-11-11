//
//  list.cpp
//  list
//
//  Created by Haley Kim on 3/4/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

void listAll(const MenuItem* m, string path) // two-parameter overload
{
    if ((m->menuItems() == nullptr) || (m->menuItems()->size() == 0))
        return;
    for (vector<MenuItem*>::const_iterator itr = m->menuItems()->begin(); itr != m->menuItems()->end(); itr++)
    {
        cout << path + (*itr)->name() << endl;
        listAll(*itr, path + (*itr)->name() + "/");
    }
}
