function [a,exc,inc_deg,w_deg,f_deg,GG_deg] = Cart_2_Kep_input_km(r_ini,v_ini,mu)
r2d = 180/pi;

h = cross(r_ini,v_ini); %[m²/s]
h_norm = norm(h);
c = cross(v_ini,h) - mu*r_ini/norm(r_ini);
exc = norm(c)/mu;
p = norm(h)^2/mu;
a = p/(1-exc^2);
f_deg = cos((p/norm(r_ini)-1)/exc)*r2d;
C = [r_ini/norm(r_ini);cross(h,r_ini)/norm(cross(h,r_ini));h/h_norm];
inc_deg = acos(h(3)/h_norm)*r2d;
if C(2,3) == 0;
    w_deg = 0*r2d;
else 
    w_deg = atan(C(1,3)/C(2,3))*r2d-f_deg;
end
if C(3,2) == 0;
    GG_deg = 0*r2d;
else
    GG_deg = atan(-C(1,3)/C(2,3))*r2d;
end