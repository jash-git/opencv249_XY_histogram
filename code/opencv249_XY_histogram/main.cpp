#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include <iostream>
#include <cstdio>

#include <sys/timeb.h>
#if defined(WIN32)
    #define  TIMEB    _timeb
    #define  ftime    _ftime
    typedef __int64 TIME_T;
#else
    #define TIMEB timeb
    typedef long long TIME_T;
#endif

using namespace cv;
using namespace std;

void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int main()
{
    //原图
    Mat srcImage=imread("Lena_original.jpg");
    if(srcImage.data)
    {
        imshow("Lena_original",srcImage);
        //灰度化
        cvtColor(srcImage,srcImage,CV_RGB2GRAY);
        //otsu阈值分割
        threshold(srcImage,srcImage,0,255,CV_THRESH_OTSU+CV_THRESH_BINARY);
        imshow("BINARY",srcImage);

        //计算垂直投影
        int *colheight =new int[srcImage.cols];
         //数组必须赋初值为零，否则出错。无法遍历数组。
        memset(colheight,0,srcImage.cols*4);
        int value;
        for(int i=0;i<srcImage.rows;i++)
        {
            for(int j=0;j<srcImage.cols;j++)
            {
                value=srcImage.at<uchar>(i,j);
                if(value==255)
                {
                    colheight[j]++;
                }

            }
        }

        //繪出垂直投影
        Mat histogramImage(srcImage.rows,srcImage.cols,CV_8UC1);
        for(int i=0;i<srcImage.rows;i++)
        {
            for(int j=0;j<srcImage.cols;j++)
            {
                value=0;  //设置为黑色。
                histogramImage.at<uchar>(i,j)=value;
            }
        }
        for(int i=0;i<srcImage.cols;i++)
        {
            for(int j=0;j<colheight[i];j++)
            {
                value=255;  //设置为白色
                histogramImage.at<uchar>(j,i)=value;
            }
        }
        imshow("X-histogram",histogramImage);


        //计算水平投影
        int *colheighttwo =new int[srcImage.rows];
        //数组必须赋初值为零，否则出错。无法遍历数组。
        memset(colheighttwo,0,srcImage.rows*4);
        int valuetwo;
        for(int i=0;i<srcImage.rows;i++)
        {
            for(int j=0;j<srcImage.cols;j++)
            {
                valuetwo=srcImage.at<uchar>(i,j);
                if(valuetwo==255)
                {
                    colheighttwo[i]++;
                }
            }
        }

        Mat plantImage(srcImage.rows,srcImage.cols,CV_8UC1);  //创建一个新的mat型
        //把这个图全部画成黑色
        for(int i=0;i<srcImage.rows;i++)
        {
            for(int j=0;j<srcImage.cols;j++)
            {
                valuetwo=0;  //设置为黑色。
                plantImage.at<uchar>(i,j)=valuetwo;
            }
        }


        for(int i=0;i<srcImage.rows;i++)
        {
            for(int j=0;j<colheighttwo[i];j++)
            {
                valuetwo=255;  //设置为白色
                plantImage.at<uchar>(i,j)=valuetwo;
            }
        }

        imshow("Y-histogram",plantImage);
    }
    waitKey(0);
    Pause();
    return 0;
}
