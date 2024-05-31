적용점 어떤픽셀에 적용할건지
/* 과제1번
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(){
	Mat element1 = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat element2 = getStructuringElement(MORPH_CROSS, Size(3, 3));
	Mat element3 = getStructuringElement(MORPH_ELLIPSE, Size(6, 3));
	cout << "MORPH_RECT" << endl;cout << element1 << endl;
	cout << "MORPH_CROSS" << endl; cout << element2 << endl;
	cout << "MORPH_ELLIPSE" << endl; cout << element3 << endl;
	return 0;
}

/* 과제2번
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(){
    Mat src = imread("letterj.png");// 원본 이미지 로드
    if (src.empty()){cerr << "이미지를 불러오는 데 실패하였습니다!" << endl;return -1;}
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY); // 컬러 이미지를 그레이스케일로 변환
    Mat bin;
    threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);// 이진화
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));// 모폴로지 연산을 이용하여 노이즈 제거
    Mat dst;
	morphologyEx(bin, dst, MORPH_OPEN, kernel);
    imshow("src", src);
    imshow("bin", bin);
    imshow("dst", dst);
    waitKey();
    destroyAllWindows();
    return 0;
}

/* 과제3번
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(void){
	Mat src = imread("letterj2.png", IMREAD_GRAYSCALE);// 원본 이미지 로드
	if (src.empty()) { cerr << "이미지를 불러오는 데 실패하였습니다!" << endl; return -1; }
	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);// 이진화
	Mat eroded;
	erode(bin, eroded, Mat()); // 침식 연산을 통한 에지 구하기 / 3x3 구조 요소 사용
	Mat dilated;
	dilate(bin, dilated, Mat()); // 팽창 연산을 통한 에지 구하기 / 3x3 구조 요소 사용
	Mat edges = dilated - eroded;// 에지 표시
	imshow("src", src);// 원본 결과 출력
	imshow("bin", bin);// 이진화 결과 출력
	imshow("eroded", eroded);// 침식 결과 출력
	imshow("dilated", dilated);// 팽창 결과 출력
	imshow("edges", edges);// 에지 결과 출력
	waitKey();
	destroyAllWindows();
	return 0;
}
/*과제4번
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main() {
	Mat src = imread("car.jpg");// 원본 이미지 로드
	if (src.empty()) { cerr << "이미지를 불러오는 데 실패하였습니다!" << endl; return -1; }
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);// 컬러 영상을 그레이스케일로 변환
	Mat blurred;
	blur(gray, blurred, Size(5, 5));// 블러링 적용 (5x5 마스크)
	Mat edges;
	Sobel(blurred, edges, CV_8U, 1, 0, 3);// (Sobel 필터)수직 방향 에지 검출
	Mat binary;
	threshold(edges, binary, 150, 255, THRESH_BINARY);// 이진화 (임계값 조정)
	Mat kernel = getStructuringElement(MORPH_RECT, Size(50, 10)); // 마스크
	Mat closed;
	morphologyEx(binary, closed, MORPH_CLOSE, kernel);// 닫기 연산 수행
	imshow("원본", src);
	imshow("블러링 적용", blurred);
	imshow("에지 검출", edges);
	imshow("이진화", binary);
	imshow("닫기 연산", closed);
	waitKey();
	return 0;
}
*/
![1-1](https://github.com/hyeonsukk2/openCV_chap11-2/assets/169273583/8c69a2b9-7610-4fdc-ad12-737ec66ec04a)

과제1번
구조요소행렬의 3 가지 종류를 getStructuringElement 함수를
이용하여 구하고 다음과 같이 출력해보시오 행렬의 크기는 입력

1) 사각형 모양의 구조

2) 십자가 모양의 구조

![1-2](https://github.com/hyeonsukk2/openCV_chap11-2/assets/169273583/88a34f4f-af4b-4336-9e35-8eb05eaf3f87)

과제2번
원본영상 (letterj png) 을 이진화 시킨 후 모폴로지연산을 이용하여
아래 결과처럼 글자 안과 밖의 모든 노이즈를 제거해보라
원본영상은 컬러 영상이므로 반드시 이진 영상으로 변환 후 처리할 것
* 원본영상 노이즈 제거 과정

1)컬러 이미지를 그레이스케일로 변환

2)이진화(threshold)

3)모폴로지 연산을 이용하여 노이즈 제거(getStructuringElement)

4)열기연산 수행(morphologyEx)

평균값필터나 가우시안 필터를 적용한 것과 차이점은 무엇인가
평균값 필터: 이미지에서 픽셀의 값을 평균화하여 노이즈를 감소시킵니다. 이 필터는 커널(마스크)의 크기 내 모든 픽셀의 값의 평균을 계산하여 중심 픽셀의 값을 대체합니다.
가우시안 필터: 픽셀의 주변 가중치에 따라 가중 평균을 계산하여 픽셀의 값을 완화합니다. 이 필터는 픽셀의 가중치를 가우시안 분포에 따라 설정하여 중심 픽셀 주변의 픽셀이 더 큰 영향을 미치도록 합니다.


![1-3](https://github.com/hyeonsukk2/openCV_chap11-2/assets/169273583/dd5ff3da-f053-4555-8278-211e00b7c5ae)

과제3번
원본영상 (letterj 2 png) 을 이진화 시킨 후 아래 결과처럼 침식 또는
팽창연산을 이용하여 에지를 구하라 캐니연산 사용하지 말것
원본영상은 컬러 영상이므로 반드시 이진 영상으로 변환 후 처리할 것


1) 이진화(threshold)

2)침식 연산을 통한 에지 구하기 / 3x3 구조 요소 사용(erode)

3)팽창 연산을 통한 에지 구하기 / 3x3 구조 요소 사용(dilate)

4)에지 표시

![1-4](https://github.com/hyeonsukk2/openCV_chap11-2/assets/169273583/7514ffde-e035-49b9-ba6d-f44f5ae03945)

과제4번
원본영상 (car jpg) 에서 번호판 영역을 4 번째 영상처럼 하나의 흰색
블록으로 표시하고자 한다 먼저 컬러영상을 그레이로 변환하고 그레이
영상에서 노이즈 제거를 위해 블러링 5 x 5 마스크 적용하고 sobel 함수를
이용하여 수직방향의 에지 (x 축 방향 미분 만 검출한다 2 번째 영상
수직에지 영상을 이진화하고 3 번째 영상 마지막으로 닫기연산을
수행한다 4 번째 영상 닫기연산시 구조요소행렬의 사이즈는 5 행 32 열로
가로방향으로 긴 사각형 형태의 마스크를 이용하여 숫자들을 하나의
객체로 합쳐준다
이진화시는 오츠방법은 사용하지 말고 임계값을 직접 조정해보세요
4 번째 영상에서 숫자영역의 면적이 가장 커야 합니다

1)컬러 영상을 그레이스케일로 변환(cvtColor)

2)블러링 적용 (5x5 마스크)(blur)

3)(Sobel 필터)수직 방향 에지 검출(Sobel)

4)이진화 (임계값 조정)(threshold)

5)마스크(getStructuringElement)

6)닫기 연산 수행(morphologyEx)