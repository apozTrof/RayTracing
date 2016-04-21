//
//  main.cpp
//  RayTracer
//

#include <iostream>
#include <memory>
#include <ctime>

#include "World.h"

int main(int argc, const char * argv[])
{
    std::shared_ptr<World> wp (new World());
    wp->build();
    
    time_t t1, t2;
    
    time(&t1);
    
    wp->m_pCamera->renderScene(wp, "RT.bmp");
    
    time(&t2);
    
    std::cout << difftime(t2, t1) << " secondes." << std::endl;
    
    return 0;
}

