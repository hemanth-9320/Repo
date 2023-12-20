#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " </home/the/Desktop/mpmc>" << std::endl;
        return -1;
    }

    cv::Mat image1 = cv::imread(argv[1]);
    cv::Mat image2 = cv::imread(argv[2]);

    if (image1.empty() || image2.empty()) {
        std::cerr << "Error: Could not open one or both of the images." << std::endl;
        return -1;
    }

    if (image1.size() != image2.size()) {
        std::cerr << "Error: Images have different dimensions." << std::endl;
        return -1;
    }

    cv::Mat diff;
    cv::absdiff(image1, image2, diff);

    cv::Mat squared_diff;
    cv::multiply(diff, diff, squared_diff);

    cv::Scalar mse = cv::mean(squared_diff);
    double mse_value = mse[0] + mse[1] + mse[2];

    std::cout << "Mean Squared Error (MSE): " << mse_value << std::endl;

    if (mse_value == 0) {
        std::cout << "Authentication is successful" << std::endl;
    } else {
        int trials = 0;
        while (trials < 3) {
            std::cout << "Please try again" << trials + 1 << ": ";
            std::string image_path;
            std::cin >> image_path;
            cv::Mat image_trial = cv::imread(image_path);

            if (image_trial.empty()) {
                std::cerr << "Error: Could not open the provided image." << std::endl;
            } else if (image1.size() != image_trial.size()) {
                std::cerr << "Error: Image dimensions do not match." << std::endl;
            } else {
                cv::absdiff(image1, image_trial, diff);
                cv::multiply(diff, diff, squared_diff);
                mse = cv::mean(squared_diff);  // Corrected this line
                mse_value = mse[0] + mse[1] + mse[2];  // Corrected this line

                if (mse_value == 0) {
                    std::cout << "Authentication is successful" << std::endl;
                    break;
                } else {
                    std::cout << "Trial " << trials + 1 << " failed." << std::endl;
                }
            }
            trials++;
        }

        if (trials >= 3) {
            std::cout << "Authentication failed" << std::endl;
        }
    }

    return 0;
}

