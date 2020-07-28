//
//  main.c
//  3D coordinate
//
//  Created by Hongjun Yun on 2020-07-26.
//  Copyright © 2020 Hongjun Yun. All rights reserved.
//

#include <stdio.h>
#include <math.h>

#define COINCIDENTAL 1
#define PARALLEL 2
#define PI 3.14159265359

// 3D coordinates.
struct Coordinate3D {// 구조체 정의
    double x,y,z;
};

struct line3Dcoordinate {   // 구조체 정의
    struct Coordinate3D start;        // 시작점(S) 공간좌표, 벡터 OS
    struct Coordinate3D  end;         // 끝점(E) 공간좌표, 벡터 OE
    struct Coordinate3D vector;       // 벡터방정식       r-r0=tv의 꼴에서 tv 부분
};

double convertRadtoDegree(double rad){
    double degree;
    degree=rad*180/PI;
    return degree;
}

// https://darkpgmr.tistory.com/121 Angle between two vectors
double angleCalc(struct line3Dcoordinate* v1, struct line3Dcoordinate* v2){
    double numerator, denominator, result;
    
    
    numerator=(((v1->vector.x)*(v2->vector.x))+((v1->vector.y)*(v2->vector.y))+((v1->vector.z)*(v2->vector.z)));
    
    denominator=sqrt(((v1->vector.x)*(v1->vector.x))+((v1->vector.y)*(v1->vector.y))+((v1->vector.z)*(v1->vector.z)))*sqrt(((v2->vector.x)*(v2->vector.x))+((v2->vector.y)*(v2->vector.y))+((v2->vector.z)*(v2->vector.z)));
    
    //printf("\n\tnumerator: %lg\n\tdenominator: %lg",numerator,denominator);
    
    result=acos(numerator/denominator);
    if(isnan(result)!=0){
        return 0;
    }
    else{
        return convertRadtoDegree(result);
    }
}

void conversion3dcoordinateToVector(struct line3Dcoordinate* temp){
    temp->vector.x=(temp->end.x)-(temp->start.x);
    temp->vector.y=(temp->end.y)-(temp->start.y);
    temp->vector.z=(temp->end.z)-(temp->start.z);
}

int checkParallelOrConcidental(struct line3Dcoordinate* temp1,struct line3Dcoordinate* temp2){
    double tx,ty,tz;
    tx=((temp2->start.x-temp1->start.x)/temp1->vector.x);
    ty=((temp2->start.y-temp1->start.y)/temp1->vector.y);
    tz=((temp2->start.z-temp1->start.z)/temp1->vector.z);
    if((tx==ty)&&(ty==tz)){
        return COINCIDENTAL;//represents they are the same line(coincidental)
    }
    else{
        return PARALLEL;//represents they are parallel
    }
}

void compVxVyVz(struct line3Dcoordinate* temp1, struct line3Dcoordinate* temp2){
    if (temp1->vector.x * temp2->vector.y == temp1->vector.y * temp2->vector.x && temp1->vector.y * temp2->vector.z == temp1->vector.z * temp2->vector.y) {
        //완전히 동일 또는 배수 체크 통과
        //two vectors are either parallel or coincidental
        int result=checkParallelOrConcidental(temp1,temp2);
        switch (result) {
            case COINCIDENTAL:
                printf("Two vectors are coincidental(same vector).\nThey has infinite number of point of intersection.\n");
                return;
            case PARALLEL:
                printf("Two vectors are parallel.\nThey has no point of intersection.\n");
                return;
            default:
                printf("Error.\n");
                return;
        }
    }
    printf("Two vectors are neither parallel or coincidental.\nThey has POI(Point of Intersection)\n");
}

int main(int argc, const char * argv[]) {
    struct line3Dcoordinate l1, l2;
    double angleBetweenTwoVectors;
    printf("input the first coordinate in x,y,z form: ");
    scanf("%lf,%lf,%lf",&l1.start.x,&l1.start.y,&l1.start.z);
    printf("input the second coordinate in x,y,z form: ");
    scanf("%lf,%lf,%lf",&l1.end.x,&l1.end.y,&l1.end.z);
    printf("input the third coordinate in x,y,z form: ");
    scanf("%lf,%lf,%lf",&l2.start.x,&l2.start.y,&l2.start.z);
    printf("input the fourth coordinate in x,y,z form: ");
    scanf("%lf,%lf,%lf",&l2.end.x,&l2.end.y,&l2.end.z);
    
    conversion3dcoordinateToVector(&l1);
    conversion3dcoordinateToVector(&l2);
    
    printf("First Vector: %lg, %lg, %lg\n",l1.vector.x,l1.vector.y,l1.vector.z);
    printf("Second Vector: %lg, %lg, %lg\n",l2.vector.x,l2.vector.y,l2.vector.z);
    
    compVxVyVz(&l1, &l2);
    
    angleBetweenTwoVectors=angleCalc(&l1, &l2);
    printf("\nThe angle between two vectors is %lg degree(s)\n", angleCalc(&l1, &l2));
    
    return 0;
}
