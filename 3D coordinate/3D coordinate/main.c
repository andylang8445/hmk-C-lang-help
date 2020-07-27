//
//  main.c
//  3D coordinate
//
//  Created by Hongjun Yun on 2020-07-26.
//  Copyright © 2020 Hongjun Yun. All rights reserved.
//

#include <stdio.h>

struct line3Dcoordinate {   // 구조체 정의
    double sx,sy,sz;        // 시작점(S) 공간좌표, 벡터 OS
    double ex,ey,ez;        // 끝점(E) 공간좌표, 벡터 OE
    double vx,vy,vz;        // 벡터방정식       r-r0=tv의 꼴에서 tv 부분
};

void conversion3dcoordinateToVector(struct line3Dcoordinate* temp){
    temp->vx=(temp->ex)-(temp->sx);
    temp->vy=(temp->ey)-(temp->sy);
    temp->vz=(temp->ez)-(temp->sz);
}

int checkParallelOrConcidental(struct line3Dcoordinate* temp1,struct line3Dcoordinate* temp2){
    double tx,ty,tz;
    tx=((temp2->sx-temp1->sx)/temp1->vx);
    ty=((temp2->sy-temp1->sy)/temp1->vy);
    tz=((temp2->sz-temp1->sz)/temp1->vz);
    if((tx==ty)&&(ty==tz)){
        return 1;//represents they are the same line(coincidental)
    }
    else{
        return 2;//represents they are parallel
    }
}

void compVxVyVz(struct line3Dcoordinate* temp1,struct line3Dcoordinate* temp2){
    if((temp1->vx==temp2->vx)&&(temp1->vy==temp2->vy)&&(temp1->vz==temp2->vz)){
        //완전히 동일
        //two vectors are either parallel or coincidental
        int result=checkParallelOrConcidental(temp1,temp2);
        if(result==1){
            printf("Two vectors are coincidental(same vector).\nThey has infinite number of point of intersection.\n");
        }
        else if(result==2){
            printf("Two vectors are parallel.\nThey has no point of intersection.\n");
        }
    }
    else if((((temp1->vx)*(temp2->vy))==((temp2->vx)*(temp1->vy)))&&(((temp1->vx)*(temp2->vz))==((temp2->vx)*(temp1->vz)))){
        if((((temp1->vy)*(temp2->vx))==((temp2->vy)*(temp1->vx)))&&(((temp1->vy)*(temp2->vz))==((temp2->vy)*(temp1->vz)))){
            if((((temp1->vz)*(temp2->vx))==((temp2->vz)*(temp1->vx)))&&(((temp1->vz)*(temp2->vy))==((temp2->vz)*(temp1->vy)))){
                // 배수 체크
                //two vectors are either parallel or coincidental
                int result=checkParallelOrConcidental(temp1,temp2);
                if(result==1){
                    printf("Two vectors are coincidental(same vector).\nThey has infinite number of point of intersection.\n");
                }
                else if(result==2){
                    printf("Two vectors are parallel.\nThey has no point of intersection.\n");
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    struct line3Dcoordinate l1,l2;
    printf("input the first coordinate in x,y,z form: ");
    scanf("%lf,%lf,%lf",&l1.sx,&l1.sy,&l1.sz);
    printf("input the second coordinate in x,y,z form: ");
    scanf("%lf,%lf,%lf",&l1.ex,&l1.ey,&l1.ez);
    printf("input the third coordinate in x,y,z form: ");
    scanf("%lf,%lf,%lf",&l2.sx,&l2.sy,&l2.sz);
    printf("input the fourth coordinate in x,y,z form: ");
    scanf("%lf,%lf,%lf",&l2.ex,&l2.ey,&l2.ez);
    
    conversion3dcoordinateToVector(&l1);
    conversion3dcoordinateToVector(&l2);
    
    printf("First Vector: %lf,%lf,%lf\n",l1.vx,l1.vy,l1.vz);
    printf("Second Vector: %lf,%lf,%lf\n",l2.vx,l2.vy,l2.vz);
    
    compVxVyVz(&l1,&l2);
    
    return 0;
}
