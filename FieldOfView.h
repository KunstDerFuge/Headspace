//
// Created by main on 3/4/18.
//

#ifndef HEADSPACE_FIELDOFVIEW_H
#define HEADSPACE_FIELDOFVIEW_H


#include <vector>

class FieldOfView {
private:
    std::vector<bool> squares;
public:
    bool isVisible(long x, long y);
};


#endif //HEADSPACE_FIELDOFVIEW_H
