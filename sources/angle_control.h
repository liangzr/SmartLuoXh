extern float gravity;//�������ٶȻ���õ��ĽǶ�
extern float gyro;//�����ǲɵĵĽ��ٶ�
extern float angle;//����ó��ĽǶ�
void Kalman_Filter(void);
void Complementary_filter();
void get_gravity_zero();
void get_gyro_zero();
void get_gravity(void);
void get_gyro(void);
float angle_out();