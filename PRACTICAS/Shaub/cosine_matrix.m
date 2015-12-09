function [C]=cosine_matrix(angles,order)

C = eye(3);
for i = 1:3
    ord = order(i);
    ang = angles(i);
    M = rotate_matrix(ang,ord);
    C = M*C;
end


        