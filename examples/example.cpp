#include "eg1_capture.h"
#include "eg2_properties.h"
#include "eg3_camera_looper.h"
#include "eg4_exposure_fusion.h"
#include "eg5_disconnect_process.h"
#include "eg6_stub.h"
#include "eg7_arpara_camera.h"
#include "eg8_direct_arpara_camera.h"
#include "eg9_direct_arpara_camera.h"
#include "eg10_dual_arpara_camera.h"
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Example 1: Capture Image." << std::endl;
    std::cout << "Example 2: Properties." << std::endl;
    std::cout << "Example 3: Camera Looper." << std::endl;
    std::cout << "Example 4: Exposure Fusion." << std::endl;
    std::cout << "Example 5: Disconnect Process." << std::endl;
    std::cout << "Example 6: Stub." << std::endl;
    std::cout << "Example 7: ArparaCamera." << std::endl;
    std::cout << "Example 8: Direct ArparaCamera." << std::endl;
    std::cout << "Example 9: Direct ArparaCamera without opencv enable" << std::endl;
    std::cout << "Example 10: Dual ArparaCamera." << std::endl;
    std::cout << "Enter the example number: ";

    int example_index;
    std::cin >> example_index;

    if (example_index == 1)
    {
        eg1_capture();
    }
    else if (example_index == 2)
    {
        eg2_properties();
    }
    else if (example_index == 3)
    {
        eg3_camera_looper();
    }
    else if (example_index == 4)
    {
        eg4_exposure_fusion();
    }
    else if (example_index == 5)
    {
        eg5_disconnect_process();
    }
    else if (example_index == 6)
    {
        eg6_stub();
    }
    else if (example_index == 7)
    {
        eg7_arpara_camera();
    }
    else if (example_index == 8)
    {
        eg8_arpara_camera();
    }
    else if ( example_index == 9)
    {
        eg9_arpara_camera();
    }else if (example_index == 10)
    {
        eg10_dual_camera();
    }
}