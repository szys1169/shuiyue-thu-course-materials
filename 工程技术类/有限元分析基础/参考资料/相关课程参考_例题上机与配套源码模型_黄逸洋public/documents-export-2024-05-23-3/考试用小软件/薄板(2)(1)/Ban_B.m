function out = Ban_B(x,y,Pi,Pj,Pm,Pp)
%应变矩阵  x,y是点坐标，变量   Pi,Pj,Pm,Pp为节点坐标，1*2向量
%   此处显示详细说明
out = [xiaoB( x,y,Pi(1),Pi(2) ),xiaoB( x,y,Pj(1),Pj(2) ),xiaoB( x,y,Pm(1),Pm(2) ),xiaoB( x,y,Pp(1),Pp(2) )];
end

