//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
class Texture{
private:
    cv::Mat image_data;

public:
    Texture(const std::string& name)
    {
        image_data = cv::imread(name);
        // 3. 关键检查：如果图片为空，立即报错并停止，而不是继续运行
        if (image_data.empty())
        {
            std::cerr << "\n[ERROR] OpenCV 无法读取图片！" << std::endl;
            std::cerr << "请检查：1. 文件是否存在  2. 路径是否全英文  3. 路径斜杠是否正确" << std::endl;
            // 抛出异常防止程序死在 cv::cvtColor
            throw std::runtime_error("Texture file not found or empty: " + name);
        }
        cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
        
        width = image_data.cols;
        height = image_data.rows;
    }

    int width, height;

    Eigen::Vector3f getColor(float u, float v)
    {
        if (u < 0) u = 0;
        if (u > 1) u = 1;
        if (v < 0) v = 0;
        if (v > 1) v = 1;
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

};
#endif //RASTERIZER_TEXTURE_H
