function r = GanXi_DengXiaoZaiHe(q,l)
%平面刚架，等效节点载荷，局部坐标      q均布力 l单元长度
r = [0 -q*l/2 -q*l^2/12 0 -q*l/2 q*l^2/12;]';
end

