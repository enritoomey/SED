function [r_vec,v_vec]=Kep_2_Cart_input_deg(a,e,inc_deg,w_deg,f_deg,GG_deg,mu)
% [r_vec,v_vec]=Kep_2_Cart(a,e,inc_deg,w_deg,f_deg,OM_deg)

d2r=pi/180;

inc=inc_deg*d2r;
GG=GG_deg*d2r;
w=w_deg*d2r;
f=f_deg*d2r;
% 
% A = [cos(GG)*cos(w)-sin(GG)*sin(w)*cos(inc), -cos(GG)*sin(w)-sin(GG)*cos(w)*cos(inc), sin(GG)*sin(inc);
%     sin(GG)*cos(w)+cos(GG)*sin(w)*cos(inc), -sin(GG)*sin(w)+cos(GG)*cos(w)*cos(inc), -cos(GG)*sin(i);
%     sin(w)*sin(inc), cos(w)*sin(inc), cos(inc)];
% 
% r_vec_manu = a*(1-e^2)/(1+e*cos(f))* A*[cos(f);sin(f);0];
% 
% v_vec_manu = sqrt(mu/(a*(1-e^2)))* A*[-sin(f);e+cos(f);0];


r_vec=a*(1-e^2)/(1+e*cos(f))*[cos(f+w)*cos(GG)-cos(inc)*sin(f+w)*sin(GG);
                                                    cos(f+w)*sin(GG)+cos(inc)*sin(f+w)*cos(GG);
                                                    sin(inc)*sin(f+w)];
                                                                                               
v_vec=sqrt(mu/(a*(1-e^2)))*[-cos(GG)*sin(f+w)-sin(GG)*cos(inc)*cos(f+w)-e*(cos(GG)*sin(w)+sin(GG)*cos(w)*cos(inc));
                                               cos(GG)*cos(inc)*cos(f+w)-sin(GG)*sin(f+w)-e*(sin(GG)*sin(w)-cos(GG)*cos(w)*cos(inc));
                                               sin(inc)*(cos(f+w)+e*cos(w))]; 
                                                                                    
end
