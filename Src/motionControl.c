#include "motionControl.h"
#include "pca9685.h"

const uint8 stepNumber = 10;//�Źؽڹ켣ȡ����
const uint8 hipTheta = 50; //�Źؽ�ת���Ƕ�
uint8 hitStep = hipTheta/stepNumber; //�Źؽڵ��ת������
const uint8 kneeTheta = 30; //ϥ�ؽ�ת���Ƕ�
uint8 kneeStep = kneeTheta/stepNumber; //ϥ�ؽڵ��ת������

//
void motionInit(float fre) {
	PCA9685_Go();
	SetPWMFreq(fre);
}

//���ƶ��ת�ǣ�����ֵת��Ϊ�Ƕ�ֵ  
void setTheta(uint32_t number, uint32_t theta) {
	uint32_t count = 0;
	if (theta < 180) {
		count = 102 + theta*4096/90/20;
		SetPWM(number, 0, count);		
	}
}

//�Źؽ��˶�����
//void hipControl() {
//}

//ϥ�ؽ��˶�����
//void kneeControl() {
//}




//����վ��
void robotStand() {
	//��һ��: ��ǰ���Һ�
	setTheta(LeftFront_hip, 105);
	setTheta(LeftFront_knee, 120);
	setTheta(RightBack_hip, 115);
	setTheta(RightBack_knee, 120);
	HAL_Delay(5);
	
	//�ڶ��飺��ǰ�����
	setTheta(RightFront_hip, 90);
	setTheta(RightFront_knee, 70);
	setTheta(LeftBack_hip, 60);
	setTheta(LeftBack_knee, 60);
	HAL_Delay(5);
}

//ǰ��
void forward() {

	//ǰ������
	for (uint8 i = 0; i <= stepNumber; ++i) {
		//�Źؽ�
		setTheta(LeftFront_hip, 70 + hitStep*i);
		setTheta(RightBack_hip, 140 - hitStep*i);
		setTheta(RightFront_hip, 65 + hitStep*i);
		setTheta(LeftBack_hip, 95 - hitStep*i);
		//ϥ�ؽ�
		if (i <= stepNumber/2) {
			setTheta(LeftFront_knee, 120 + kneeStep*i*2);
			setTheta(RightBack_knee, 120 + kneeStep*i*2);
			setTheta(RightFront_knee, 60);
			setTheta(LeftBack_knee, 60);
		} else {
			setTheta(LeftFront_knee, 180 - 2*kneeStep*i);
			setTheta(RightBack_knee, 180 -  2*kneeStep*i);
			setTheta(RightFront_knee, 60);
			setTheta(LeftBack_knee, 60);
		}
		HAL_Delay(5);
	}
	
	//�������
	for (uint8 i = 0; i <= stepNumber; ++i) {
		//�Źؽ�
		setTheta(LeftFront_hip, 130 - hitStep*i);
		setTheta(RightBack_hip, 90 + hitStep*i);
		setTheta(RightFront_hip, 115 - hitStep*i);
		setTheta(LeftBack_hip, 45 + hitStep*i);
		//ϥ�ؽ�
		if (i <= stepNumber/2) {
			setTheta(LeftFront_knee, 120);
			setTheta(RightBack_knee, 120);
			setTheta(RightFront_knee, 60 - kneeStep*i*2);
			setTheta(LeftBack_knee, 60 - kneeStep*i*2);
		} else {
			setTheta(LeftFront_knee, 120);
			setTheta(RightBack_knee, 120);
			setTheta(RightFront_knee, 2*kneeStep*i);
			setTheta(LeftBack_knee, 2*kneeStep*i);
		}
		HAL_Delay(5);
	}
}

//��ת
//void rotate(void) {
//		
//	
//}

