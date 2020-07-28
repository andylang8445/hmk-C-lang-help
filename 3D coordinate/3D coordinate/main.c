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
#define ERRORCODE -1

struct angleInBothDegreeAndRadians{
    double degree;
    double radian;
};

// 3D coordinates.
struct Coordinate3D {// 구조체 정의
    double x,y,z;
};


struct line3Dcoordinate {   // 구조체 정의
    struct Coordinate3D start;        // 시작점(S) 공간좌표, 벡터 OS
    struct Coordinate3D  end;         // 끝점(E) 공간좌표, 벡터 OE
    struct Coordinate3D vector;       // 벡터방정식       r-r0=tv의 꼴에서 tv 부분
    double vectorSize;
};

struct allInOneStructure {
    struct line3Dcoordinate v1,v2;
    struct angleInBothDegreeAndRadians angles;
    int Parallel_Equal_CODE;
};

double convertRadtoDegree(double rad){
    double degree;
    degree=rad*180/PI;
    return degree;
}

double dotProduct(struct line3Dcoordinate* v1, struct line3Dcoordinate* v2){
    struct Coordinate3D vector1, vector2;
    double result;
    
    vector1 = v1->vector;
    vector2 = v2->vector;
    
    result=((vector1.x)*(vector2.x))+((vector1.y)*(vector2.y))+((vector1.z)*(vector2.z));
    
    return result;
}

double sizeOfVector(struct line3Dcoordinate* v){
    double size;
    size=sqrt(((v->vector.x)*(v->vector.x))+((v->vector.y)*(v->vector.y))+((v->vector.z)*(v->vector.z)));
    return size;
}

// https://darkpgmr.tistory.com/121 Angle between two vectors
struct angleInBothDegreeAndRadians angleCalc(struct line3Dcoordinate* v1, struct line3Dcoordinate* v2){
    struct angleInBothDegreeAndRadians result;
    double numerator, denominator, calcresult;
    
    
    numerator=dotProduct(v1, v2);
    denominator=(sizeOfVector(v1)*sizeOfVector(v2));
    
    //printf("\n\tnumerator: %lg\n\tdenominator: %lg",numerator,denominator);
    
    calcresult=acos(numerator/denominator);
    if(isnan(calcresult) == 0){// not nan
        result.radian = calcresult;
        result.degree = convertRadtoDegree(calcresult);
    }
    else{
        result.radian = result.degree = 0.0;
    }
    return result;
}

void conversion3dcoordinateToVector(struct allInOneStructure* temp){
    /*printf("\n\tv1: (sx,sy,sz)=(%lg,%lg,%lg), (ex,ey,ez)=(%lg,%lg,%lg)",temp->v1.start.x,temp->v1.start.y,temp->v1.start.z,temp->v1.end.x,temp->v1.end.y,temp->v1.end.z);
    printf("\n\tv2: (sx,sy,sz)=(%lg,%lg,%lg), (ex,ey,ez)=(%lg,%lg,%lg)\n",temp->v2.start.x,temp->v2.start.y,temp->v2.start.z,temp->v2.end.x,temp->v2.end.y,temp->v1.end.z);*/
    
    temp->v1.vector.x=(temp->v1.end.x)-(temp->v1.start.x);
    temp->v1.vector.y=(temp->v1.end.y)-(temp->v1.start.y);
    temp->v1.vector.z=(temp->v1.end.z)-(temp->v1.start.z);
    
    temp->v2.vector.x=(temp->v2.end.x)-(temp->v2.start.x);
    temp->v2.vector.y=(temp->v2.end.y)-(temp->v2.start.y);
    temp->v2.vector.z=(temp->v2.end.z)-(temp->v2.start.z);
}

struct allInOneStructure checkParallelOrConcidental(struct allInOneStructure* input){
    struct allInOneStructure result;
    result.angles=(angleCalc(&input->v1, &input->v2));
    result.v1.vectorSize=sizeOfVector(&input->v1);
    result.v2.vectorSize=sizeOfVector(&input->v2);
    if(result.angles.degree==0){
        if(result.v1.vectorSize==result.v2.vectorSize){
            result.Parallel_Equal_CODE=COINCIDENTAL;
        }
        else{
            result.Parallel_Equal_CODE=PARALLEL;
        }
    }
    else{
        result.Parallel_Equal_CODE=ERRORCODE;
    }
    return result;
}

struct allInOneStructure compVxVyVz(struct allInOneStructure* input){
    struct allInOneStructure result;
    result=*input;
    if (input->v1.vector.x * input->v2.vector.y == input->v1.vector.y * input->v2.vector.x && input->v1.vector.y * input->v2.vector.z == input->v1.vector.z * input->v2.vector.y) {
        //완전히 동일 또는 배수 체크 통과
        //two vectors are either parallel or coincidental
        result=checkParallelOrConcidental(input);
        switch (result.Parallel_Equal_CODE) {
            case COINCIDENTAL:
                printf("Two vectors are coincidental(same vector).\nThey has infinite number of point of intersection.\n");
                return result;
            case PARALLEL:
                printf("Two vectors are parallel.\nThey has no point of intersection.\n");
                return result;
            default:
                printf("Error.\n");
                return result;
        }
    }
    printf("Two vectors are neither parallel or coincidental.\nThey has POI(Point of Intersection)\n");
    return result;
}

int inputformSelecter(){
    int selection;
    printf("Please input the form of vecter\n\t1. vecter a=(x,y,z) form\n\t2. two points that vector passes (coordinates for point m and n)\ninput: ");
    scanf("%d",&selection);
    return selection;
}

struct line3Dcoordinate vectorvectorForminput(int n){//vector a=(a,b,c) form
    struct line3Dcoordinate vector;
    
    vector.start.x=vector.start.y=vector.start.z=0;
    printf("Vector number %d:\n",n);
    printf("\tinput the vector in x,y,z form: ");
    scanf("%lf,%lf,%lf",&vector.end.x,&vector.end.y,&vector.end.z);
    
    return vector;
}

struct line3Dcoordinate vectorpointForminput(int n){//point m(x1,y1,z1),n(x2,y2,z2) form
    struct line3Dcoordinate vector;
    
    printf("Vector number %d:\n",n);
    printf("\tinput the first coordinate in x,y,z form: ");
    scanf("%lf,%lf,%lf",&vector.start.x,&vector.start.y,&vector.start.z);
    printf("\tinput the second coordinate in x,y,z form: ");
    scanf("%lf,%lf,%lf",&vector.end.x,&vector.end.y,&vector.end.z);
    
    return vector;
}

int main(int argc, const char * argv[]) {
    struct allInOneStructure totalStructure;
    switch(inputformSelecter()){
        case 1:
            totalStructure.v1=vectorvectorForminput(1);
            totalStructure.v2=vectorvectorForminput(2);
            break;
        case 2:
            totalStructure.v1=vectorpointForminput(1);
            totalStructure.v2=vectorpointForminput(2);
            break;
        default:
            printf("Wrong Input!\nPlease relaunch the program");
            return 0;
    }
    
    conversion3dcoordinateToVector(&totalStructure);
    totalStructure=compVxVyVz(&totalStructure);
    
    /*printf("\n\tv1: (sx,sy,sz)=(%lg,%lg,%lg), (ex,ey,ez)=(%lg,%lg,%lg)",totalStructure.v1.start.x,totalStructure.v1.start.y,totalStructure.v1.start.z,totalStructure.v1.end.x,totalStructure.v1.end.y,totalStructure.v1.end.z);
    printf("\n\tv2: (sx,sy,sz)=(%lg,%lg,%lg), (ex,ey,ez)=(%lg,%lg,%lg)\n",totalStructure.v2.start.x,totalStructure.v2.start.y,totalStructure.v2.start.z,totalStructure.v2.end.x,totalStructure.v2.end.y,totalStructure.v1.end.z);*/
    
    printf("\n\t First Vector: (%lg, %lg, %lg)\n",totalStructure.v1.vector.x,totalStructure.v1.vector.y,totalStructure.v1.vector.z);
    printf("\t Second Vector: (%lg, %lg, %lg)\n\n",totalStructure.v2.vector.x,totalStructure.v2.vector.y,totalStructure.v2.vector.z);
    printf("\nThe angle between two vectors is:\n\t %lg degree(s) or %lg radian(s)\n", totalStructure.angles.degree,totalStructure.angles.radian);
    
    return 0;
}
