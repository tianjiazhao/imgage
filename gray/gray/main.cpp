#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;
enum mode {
    cv_to_g = 0,
    cv_to_rate = 1,
    cv_to_average = 2
}c;
/**
 * @brief gray
 * @param img
 * @param flag : cv_to_g
 *               cv_to_rate    Gray(i,j)=0.299*R(i,j)+0.587*G(i,j)+0.114*B(i,j);
 *               cv_to_average Gray(i,j)=[R(i,j)+G(i,j)+B(i,j)]/3;
 * @return Mat
 */
Mat gray(Mat img,int flag = cv_to_g)
{
    Mat gray(img.rows,img.cols,CV_8UC1);
    if(flag == cv_to_g)
    {
        uchar *ptr = img.data;
        uchar *ptr_end = ptr + img.cols*img.rows*3;
        uchar *ptr_g = gray.data;
        for(;ptr != ptr_end;ptr++,ptr_g++)
        {
            *ptr_g = *(++ptr);
            (++ptr);
        }
        return gray;
    }else if (flag == cv_to_rate) {
        static const float coeffs0[] = { 0.299f, 0.587f, 0.114f };
        uchar *ptr = img.data;
        uchar *ptr_end = ptr + img.cols*img.rows*3;
        uchar *ptr_g = gray.data;
        for(;ptr != ptr_end;ptr++,ptr_g++)
        {
            *ptr_g = coeffs0[0]* (*ptr) + coeffs0[1]*(*(ptr+1))+coeffs0[2]*(*(ptr+2));
            ptr = ptr + 2;
        }
        return gray;
    }else if (flag == cv_to_average) {
        float rate = 1.0/3.0;
        uchar *ptr = img.data;
        uchar *ptr_end = ptr + img.cols*img.rows*3;
        uchar *ptr_g = gray.data;
        for(;ptr != ptr_end;ptr++,ptr_g++)
        {
            *ptr_g = rate* (*ptr) + rate*(*(ptr+1))+rate*(*(ptr+2));
            ptr = ptr + 2;
        }
        return gray;
    }
}

int main()
{
    Mat img = imread("1.jpg");
    img = gray(img,cv_to_g);
    imshow("img",img);
    waitKey(0);
}
