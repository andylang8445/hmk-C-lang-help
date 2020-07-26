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
    double vx,vy,vz;        // 벡터방정식
};

void conversion3dcoordinateToVector(struct line3Dcoordinate* temp){
    temp->vx=(temp->ex)-(temp->sx);
    temp->vy=(temp->ey)-(temp->sy);
    temp->vz=(temp->ez)-(temp->sz);
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
    return 0;
}
