function [K_total]=JuZhenhebing(nodes_num,K1,contri_1,K2,contri_2,K3,contri_3,K4,contri_4,K5,contri_5)

%使用说明：本函数为刚度矩阵合并，输出值为合并后的总刚度矩阵
%nodes_num为系统中的节点数量，注意是节点数量而非维度，利用三根杆的例题就应该输入4
%K1~K5是五个已经求出来的刚度矩阵，一般而言考题不会出超过五个的单元划分，如果只有四个那么最后一个K输入0即可；
%contri_1~contri_5是贡献自由度，行向量或者列向量都无所谓，[1,2,5,6]这种

matrix_dimension=2*nodes_num;
K_total=zeros(matrix_dimension,matrix_dimension);
C1=length(K1);
C2=length(K2);
C3=length(K3);
C4=length(K4);
C5=length(K5);

if C1>1
 for i=1:C1
   for j=1:C1
     a=contri_1(i);
     b=contri_1(j);
     K_total(a,b)=K_total(a,b)+K1(i,j);
   end 
 end
end
 

if C2>1
 for i=1:C2
   for j=1:C2
     a=contri_2(i);
     b=contri_2(j);
     K_total(a,b)=K_total(a,b)+K2(i,j);
   end 
 end
end
 
if C3>1
 for i=1:C3
   for j=1:C3
     a=contri_3(i);
     b=contri_3(j);
     K_total(a,b)=K_total(a,b)+K3(i,j);
   end 
 end
end

if C4>1
 for i=1:C4
   for j=1:C4
     a=contri_4(i);
     b=contri_4(j);
     K_total(a,b)=K_total(a,b)+K4(i,j);
   end 
 end
end

if C5>1
 for i=1:C5
   for j=1:C5
     a=contri_5(i);
     b=contri_5(j);
     K_total(a,b)=K_total(a,b)+K5(i,j);
   end 
 end
end

end