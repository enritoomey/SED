function [M] = rotate_matrix(ang,ord)

switch ord
    case 1
        M = [1 0 0;
            0 cos(ang) sin(ang);
            0 -sin(ang) cos(ang)];
    case 2
        M = [cos(ang) 0 -sin(ang);
              0   1   0;
              sin(ang) 0 cos(ang)];
    case 3
        M = [cos(ang) sin(ang) 0;
            -sin(ang) cos(ang) 0;
            0 0 1];
end