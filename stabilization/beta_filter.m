function [x_deriv] = beta_filter(x, beta)

x_deriv = zeros(1,length(x));

for i = 2:length(x);
    x_deriv(i) = (beta*x_deriv(i-1)) + ((1-beta)*(x(i)-x(i-1)));
end
