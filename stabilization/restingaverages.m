X_average = mean(restingdata(:,2))
Y_average = mean(restingdata(:,3))
Z_average = mean(restingdata(:,4))
plot(restingdata(:,2));
hold on;
plot(restingdata(:,3));
plot(restingdata(:,4));
title("Accelerometer Data at Rest");
xlabel("sample");
hold off;
