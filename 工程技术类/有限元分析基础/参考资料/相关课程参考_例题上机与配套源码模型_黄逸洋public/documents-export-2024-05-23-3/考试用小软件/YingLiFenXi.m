fx = -100; fy = 30; fz = 10; %σx σy σz
txy = 10; tyz = 50; tzx = -50; %τ
n = [0.15199 -0.721676 -0.675339]';  %主矢量


S = [ fx txy tzx;
      txy fy tyz;
      tzx tyz fz;]
disp('应力矢量tn')
tn = S*n

disp('正应力σn')
sigma_n = tn'*n

disp('剪应力τn')
taon = sqrt( tn'*tn - sigma_n^2 )

[Fangxiang,Yingli]=eig(S)
disp('记得自己排个序，方向是列向量');

disp('Von Mises应力')
sigma_e =1/sqrt(2)* sqrt( ( Yingli(1,1) - Yingli(2,2) )^2 + ( Yingli(2,2) - Yingli(3,3) )^2 + ( Yingli(3,3) - Yingli(1,1) )^2 )