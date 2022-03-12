#ifndef __FILTERS_H
#define __FILTERS_H

typedef float fp32;

typedef __packed struct
{
    fp32 input;        //��������
    fp32 out;          //�˲����������
    fp32 num;       //�˲�����
    fp32 frame_period; //�˲���ʱ���� ��λ s
}first_order_filter_type_t;

typedef struct {
    float X_last; //��һʱ�̵����Ž��  X(k-|k-1)
    float X_mid;  //��ǰʱ�̵�Ԥ����  X(k|k-1)
    float X_now;  //��ǰʱ�̵����Ž��  X(k|k)
    float P_mid;  //��ǰʱ��Ԥ������Э����  P(k|k-1)
    float P_now;  //��ǰʱ�����Ž����Э����  P(k|k)
    float P_last; //��һʱ�����Ž����Э����  P(k-1|k-1)
    float kg;     //kalman����
    float A;      //ϵͳ����
	float B;
    float Q;
    float R;
    float H;
}kalman_filter_type_t;

extern void first_order_filter_init(first_order_filter_type_t *first_order_filter_type, fp32 frame_period,fp32 num);
extern void first_order_filter_cali(first_order_filter_type_t *first_order_filter_type, fp32 input);

float kalman_filter( float ResrcData,float ProcessNiose_Q,float MeasureNoise_R);
void kalman_filter_create(kalman_filter_type_t *p,float T_Q,float T_R);
float kalman_filter_cali(kalman_filter_type_t* p,float dat);

#endif
