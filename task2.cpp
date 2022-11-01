#include<iostream>
#include<thread>
#include<opencv2/opencv.hpp>
#include<time.h>

using namespace std;
using namespace cv;


class Camera_Lib {
public:
	Mat image;
	int c = 0;
	void init_camera() {
		VideoCapture cap(0);
		int frame_width = static_cast<int>(cap.get(3));
		int frame_height = static_cast<int>(cap.get(4));
		int format = cap.get(CAP_PROP_FORMAT);
		cout << format << endl;
		Size frame_size(frame_width, frame_height);
		int fps = 20;
		VideoWriter output("Resources/output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, frame_size);
		cout << "adsdasd";
		std::thread t1(&Camera_Lib::read_camera_input, this,cap,output);
		t1.join();
		cout << "t1 done";
	}


	void read_camera_input(VideoCapture cap, VideoWriter output) {
		cout << "in fnc";
		if (!cap.isOpened()) {
			cout << "Error opening the camera";
		}
		else {
			time_t start, end;
			time(&start);
			int frame_start = 0;
			while (true){
				cap >> image;
				waitKey(1);
				cout << "read cam";
				frame_start++;
				time(&end);
				display_video(image);
				waitKey(10);
				double sec = difftime(end, start);
				calc_disp_fps(frame_start, sec);
				bool issuccess = cap.read(image);
				if (issuccess == true) {
					output.write(image);
				}
				int key;
				key = waitKey(50);
				if (key == 'q' || key == 27) {
					break;
				}
			}
			//cap.release();
			//destroyAllWindows();
		}
	}



	void display_video(Mat image) {
		imshow("frame", image);

	}

	int calc_disp_fps(int a, double sec) {
		double fps = a / sec;
		if (fps < 1000)
			cout << fps << endl;
		return fps;
	}
};

int main() {
	Camera_Lib c;
	c.init_camera();
	return 0;
}

