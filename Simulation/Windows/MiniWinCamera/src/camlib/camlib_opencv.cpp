#include <stdio.h>
#include "opencv2/opencv.hpp"

class CamlibOpenCV
{
public:
    CamlibOpenCV(void);
    ~CamlibOpenCV(void);
    void CaptureImage(void);
    uint16_t* GetFrame(void);

private:
    cv::VideoCapture camera;
    cv::Mat mat;
    uint16_t frame[160 * 120];
    bool captured;
};

static CamlibOpenCV* camlibOpenCV;

static int handleError(int status, const char* func, const char* msg, const char* file, int line, void* data)
{
    return 0;
}

CamlibOpenCV::CamlibOpenCV(void) : camera(0), captured(false)
{
    cv::redirectError(handleError);
}

CamlibOpenCV::~CamlibOpenCV(void)
{
    camera.release();
}

void CamlibOpenCV::CaptureImage(void)
{
    if (camera.isOpened())
    {
        cv::Size newSize(160, 120);
        cv::Mat mat2;
        if (camera.read(mat2))
        {
            resize(mat2, mat, newSize, 0, 0);
            captured = true;
        }
        else
        {
            captured = false;
        }
    }
    else
    {
        captured = false;
    }
}

uint16_t* CamlibOpenCV::GetFrame(void)
{
	uint16_t x;
	uint16_t y;
	uint32_t i = 0U;
	uint32_t j = 0U;

	if (!captured)
	{
		return frame;
	}

	for (y = 0U; y < 120U; y++)
	{
		uint8_t* data = mat.ptr<uint8_t>(y);
		for (x = 0U; x < 160U; x++)
		{
			uint16_t B = (uint16_t)(*data);
			data++;
			uint16_t G = (uint16_t)(*data);
			data++;
			uint16_t R = (uint16_t)(*data);
			data++;

			frame[i] = (B >> 3) | ((G >> 2) << 5) | (R >> 3) << 11;
			i++;
		}
	}

	return frame;
}

extern "C" void camlib_init(void)
{
    if (camlibOpenCV == nullptr)
    {
        camlibOpenCV = new CamlibOpenCV();
    }
}

extern "C" void camlib_capture(void)
{
    if (camlibOpenCV != nullptr)
    {
        static_cast<CamlibOpenCV*>(camlibOpenCV)->CaptureImage();
    }
}

extern "C" uint16_t *camlib_get_frame(void)
{
    if (camlibOpenCV != nullptr)
    {
    	return static_cast<CamlibOpenCV*>(camlibOpenCV)->GetFrame();
    }

	return NULL;
}
