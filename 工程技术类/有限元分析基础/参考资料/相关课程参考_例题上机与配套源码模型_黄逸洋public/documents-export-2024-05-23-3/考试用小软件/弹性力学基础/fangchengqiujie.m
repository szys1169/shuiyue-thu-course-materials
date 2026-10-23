function [delta,F]=fangchengqiujie(K,delta_known,position_du,F_known,position_Fu)
  %使用说明：本函数为大刚度方程求解
  %K为总刚度矩阵，delta_known为已知的位移条件（为列向量），position_du为未知的位移在位移向量中的位置，为一个行向量；
  %F_known为一个列向量，表示已知的载荷条件，position_Fu为位置的载荷在力向量中所在的行数，为一个行向量

   C0=length(K);
   Cd=length(position_du);
   K_reduce=zeros(Cd,Cd);
 
   for i=1:Cd
     for j=1:Cd
       a=position_du(i);
       b=position_du(j);
       K_reduce(i,j)=K(a,b);
     end
   end
   
   delta_unknown=K_reduce\F_known;
   delta=zeros(C0,1);
   for i=1:Cd
       a=position_du(i);
       delta(a)=delta_unknown(i);
   end
   
   for i=1:(C0-Cd)
       a=position_Fu(i);
       delta(a)=delta_known(i);
   end

   F=K*delta;
   
end


