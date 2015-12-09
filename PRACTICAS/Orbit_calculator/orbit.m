function f_dot = orbit(f,mu,p,e)
    f_dot = sqrt(mu/p^3)*(1+e*cos(f))^2;
end