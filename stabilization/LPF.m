function [x_filtered] = LPF(x, alpha)

x_filtered = x;
for i = 2:length(x)
    x_filtered(i) = (alpha*x_filtered(i-1)) + ((1-alpha)*x(i));
end

end