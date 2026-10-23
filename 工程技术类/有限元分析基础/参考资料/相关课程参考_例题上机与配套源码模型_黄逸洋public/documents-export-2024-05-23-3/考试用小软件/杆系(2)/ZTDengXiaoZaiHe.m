function r = ZTDengXiaoZaiHe(q,l,a)
%平面刚架，等效节点载荷，整体坐标     q均布力 l单元长度  a单元方向°
r = GanXi_DAT(a) * GanXi_DengXiaoZaiHe(q,l);
end

