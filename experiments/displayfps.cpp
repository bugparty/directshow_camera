

#include <arpara_camera.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include "arpara_quad_camera.h"

using namespace DirectShowCamera;

void getFpsOfCamera()
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
        std::cout << "no  camera found, exiting" << std::endl;
    }
    else
    {
        // Get first support resolution in the first camera
        std::vector <std::pair<int, int>> resolutions = cameraDeivceList[0].getResolutions();
        std::cout << "Width: " + std::to_string(resolutions[0].first) + ", Height: " + std::to_string(resolutions[0].second) << std::endl;



        // Open the first camera in the biggest resolution
        std::cout << "Open the first camera..." << std::endl;
        camera.open(cameraDeivceList[0],
            resolutions[resolutions.size() - 1].first,
            resolutions[resolutions.size() - 1].second
        );
        std::cout << "show DirectShow properties" << std::string(*camera.getDirectShowProperties()) << std::endl;
        {
            camera.startCapture();
            // Wait for 1 second
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            cv::Mat frame;
            bool quit = false;
            std::thread t([&camera, &quit]
                {
					while(!quit)
					{
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        std::cout << "fps" << camera.getFPS() << std::endl;
					}

                });
            
            while (true)
            {
                frame = camera.getMat();
                cv::imshow("frame", frame);
                if (cv::waitKey(1) == 'q')
                {
                    quit = true;
                    break;
                    
                }
            }
            t.join();
        }
    }

    camera.stopCapture();
    // Close the camera.
    camera.close();


}

int main(int argc, char**argv)
{
    getFpsOfCamera();
	return 0;
}
