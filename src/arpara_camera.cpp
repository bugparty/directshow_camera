#include "arpara_camera.h"
namespace DirectShowCamera
{

    std::vector<CameraDevice> ArparaCamera::getArparaCameras() {
        auto cameras = getCameras();
        std::vector<CameraDevice> arparaCameras;
        for (auto& camera : cameras)
        {
            if (camera.getFriendlyName().find("OV580") != std::string::npos)
            {
                arparaCameras.emplace_back(camera);
            }
        }
        return arparaCameras;
    }
    void yuy2toGrey(unsigned char* in, unsigned char* pOut, int height, int width)
    {
        if (pOut == nullptr) return;
        for (size_t i = 0; i < height * width; ++i)
        {
            pOut[i] = in[i * 2];
        }
    }
    /**
* @brief Get a new frame from the camera. the frame format is GRAY8.
* @param onlyGetNewMat (Option) Set it as true if you only want to get the new Frame. Default as false
* @return Return the frame buffer is success, or return nullptr if failed.
*/
    unsigned char* ArparaCamera::getCameraGrayImage(bool onlyGetNewFrame)
    {
        allocateImageBuffer();
        bool result = getFrame(mYuyBuffer, NULL, onlyGetNewFrame);
        if (!result) return nullptr;
        yuy2toGrey(mYuyBuffer, mGrayBuffer, getHeight(), getWidth());
        return mGrayBuffer;
    }
    /**
 * @brief Allocate yuy2 and gray image buffer
 * @return Return true if success
*/
    bool ArparaCamera::allocateImageBuffer()
    {
        if (mGreyBufferSize != getHeight() * getWidth())
        {
            mGreyBufferSize = getHeight() * getWidth();
            if (mYuyBuffer != nullptr)
            {
                delete[] mYuyBuffer;
            }
            if (mGrayBuffer != nullptr)
            {
                delete[] mGrayBuffer;
            }
            mGrayBuffer = new unsigned char[mGreyBufferSize];
            mYuyBuffer = new unsigned char[mGreyBufferSize * 2];
        }
        return mGrayBuffer && mYuyBuffer;
    }

#ifdef HAS_OPENCV
    /**
 * @brief Get cv::Mat of the current frame
 *
 * @param[in] onlyGetNewMat (Option) Set it as true if you only want to get the new Mat. Default as false
 * @return Return cv::Mat
*/
    cv::Mat ArparaCamera::getMat(bool onlyGetNewMat)
    {
        
        // Reallocate frame buffer size if changed
        if (m_matBufferSize != m_directShowCamera->getFrameTotalSize())
        {
            allocateMatBuffer();
        }

        // Get frame
        bool success = getFrame(m_matBuffer, NULL, onlyGetNewMat);

        if (success)
        {
            //strip y channel out to grey
            yuy2toGrey(m_matBuffer, mMatDstBuffer, getHeight(), getWidth());
            cv::Mat out2(getHeight(), getWidth(), CV_8UC1, mMatDstBuffer);
            return out2;
        }
        else
        {
            cv::Mat result;
            return result;
        }
    }
    /**
 * @brief Get the available DirectShowCameraDevice list. It is a advance option. Suggest to use getCameras().
 * @return Return the available DirectShowCameraDevice list
*/
    std::vector<DirectShowCameraDevice> ArparaCamera::getDirectShowArparaCameras()
    {
        std::vector<DirectShowCameraDevice> result = getDirectShowCameras();
        std::vector<DirectShowCameraDevice> arparaCameras;
        for (auto& camera : result)
        {
            if (camera.getFriendlyName().find("OV580") != std::string::npos)
            {
                arparaCameras.push_back(camera);
            }
        }
        return arparaCameras;
        
    }


    bool ArparaCamera::allocateMatBuffer()
    {
        bool result = UVCCamera::allocateMatBuffer();
        if (!result) return result;
        if (mMatDstBufferSize != getHeight() * getWidth())
        {
            mMatDstBufferSize = getHeight() * getWidth();
            if (mMatDstBuffer != nullptr)
            {
                delete[] mMatDstBuffer;
            }
            mMatDstBuffer = new unsigned char[mMatDstBufferSize];
        }
    }
#endif
}

