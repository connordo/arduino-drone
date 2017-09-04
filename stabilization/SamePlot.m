figure(1);
subplot(2,1,1);
plot(IMUGyropoints(:,4), '-');
hold on;
plot(IMUGyropoints(:,5), '-');
plot(IMUGyropoints(:,6), '-');
legend('X-axis','Y-axis','Z-axis');
title("Gyroscope");
hold off;

subplot(2,1,2);
plot(IMUGyropoints(:,1), '-');
hold on;
plot(IMUGyropoints(:,2), '-');
plot(IMUGyropoints(:,3), '-');
legend('X-axis','Y-axis','Z-axis');
title("Accelerometer");
hold off;