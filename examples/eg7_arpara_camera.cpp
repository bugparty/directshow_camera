#include "eg7_arpara_camera.h"

#include <arpara_camera.h>
#include <iostream>

using namespace DirectShowCamera;

void eg7_arpara_camera()
{
    // Get a empty camera
    ArparaCamera camera = ArparaCamera();

    // Get available camera list
    std::cout << "Start to list the available cameras..." << std::endl;
    std::vector<CameraDevice> cameraDeivceList = camera.getArparaCameras();
    for (int i = 0; i < cameraDeivceList.size(); i++) {
        std::cout << cameraDeivceList[i] << std::endl;
    }
    if (cameraDeivceList.size() == 0)
    {
        std::cout << "no arpara camera found, exiting" << std::endl;
    } else
    {
        // Get first support resolution in the first camera
        std::vector <std::pair<int, int>> resolutions = cameraDeivceList[0].getResolutions();
        std::cout << "Width: " + std::to_string(resolutions[0].first) + ", Height: " + std::to_string(resolutions[0].second)  << std::endl;



        // Open the first camera in the biggest resolution
        std::cout << "Open the first camera..." << std::endl;
        camera.open(cameraDeivceList[0],
            resolutions[resolutions.size() - 1].first,
            resolutions[resolutions.size() - 1].second
        );
        std::cout << "show DirectShow properties" << std::string(*camera.getDirectShowProperties()) << std::endl;
        // Get exposure in second
        double exposureTime = camera.getExposure();
        if (exposureTime > 0.0)
        {
            std::cout << "Exposure: " + std::to_string(exposureTime) + "s" << std::endl;
            // Set exposure as the largest value
            std::vector<double> exposures = camera.getPossibleExposureValues();
            camera.setExposure(exposures[exposures.size() - 1]);
            std::cout << "Set exposure to " + std::to_string(exposures[exposures.size() - 1]) + "s" << std::endl;

        }
        else
        {
            std::cout << "This device doesn't support exposure time" << std::endl;
        }


        // Reset all properties to default
        std::cout << "Reset properties to default..." << std::endl;
        //camera.resetProperties();
        {
            camera.startCapture();
            // Wait for 1 second
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            cv::Mat frame;
            while (true)
            {
                frame = camera.getMat();
                cv::imshow("frame", frame);
                if (cv::waitKey(1) == 'q')
                {
                    break;
                }
            }
        }
    }

    camera.stopCapture();
    // Close the camera.
    camera.close();
    
}