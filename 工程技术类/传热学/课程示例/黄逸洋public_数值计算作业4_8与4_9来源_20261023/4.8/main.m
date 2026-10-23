h=40;
tf=25;
la=45;%lambda
dx=0.08;
qw=1500;
p1=qw*dx/la;
p2=h*dx/la;
e_tresh=0.1;%绝对误差阈值
e_max=0;%两个矩阵最大绝对误差
timeMax=1000;%最大迭代次数，超过则认为不收敛
T=zeros(6,4);%当前温度分布
NT=zeros(6,4);%新的的温度分布
for i=1:1:6
    NT(i,4)=200;
end
for time=1:1:timeMax   %循环迭代
    T=NT;%更新温度分布
    for i=2:1:5 
        for j=2:1:3
            NT(i,j)=0.25*(T(i+1,j)+T(i-1,j)+T(i,j-1)+T(i,j+1));%中间节点
        end
        NT(i,1)=0.25*(2*T(i,2)+T(i-1,1)+T(i+1,1))+0.5*p1;%下部边界
    end
    for j=2:1:3
        NT(1,j)=0.25*(T(1,j+1)+T(1,j-1)+2*T(2,j));%左侧边界
        NT(6,j)=(2*T(5,j)+T(6,j+1)+T(6,j-1)+2*p2*tf)/(4+2*p2);%右侧边界
    end
    NT(1,1)=0.5*(T(2,1)+T(1,2)+p1);%左下角点
    NT(6,1)=(T(5,1)+T(6,2)+p1+tf*p2)/(2+p2);%右下角点
    e_max=max(max(abs(NT-T)));%计算前后温度矩阵差值的绝对值最大值
    if e_max<e_tresh   %收敛
        disp(NT);
        %contourf(NT);%colormap
        disp(time);
        disp(e_max);
        return;
    end
end
disp('not convergent');%超出最大迭代次数认为不收敛

    

