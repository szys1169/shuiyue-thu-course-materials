function out = D(E,v)
%E模量,v泊松比
%   此处显示详细说明
out=E/(1-v^2)*[ 1 v 0;
              v 1 0
              0 0 (1-v)/2;];
end

