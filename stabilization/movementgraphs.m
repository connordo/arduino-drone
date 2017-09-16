samples = movement(:,1);
accel_x = movement(:,2);
accel_y = movement(:,3);
accel_z = movement(:,4);
gyro_x = movement(:,5);
gyro_y = movement(:,6);
gyro_z = movement(:,7);

figure(1);
subplot(2,1,1);
plot(samples, gyro_x, '-');
hold on;
plot(samples, gyro_y, '-');
plot(samples, gyro_z, '-');
legend('X-axis','Y-axis','Z-axis');
title("Gyroscope");
xlabel("Sample");
hold off;

subplot(2,1,2);
plot(samples, accel_x, '-');
hold on;
plot(samples, accel_y, '-');
plot(samples, accel_z, '-');
legend('X-axis','Y-axis','Z-axis');
title("Accelerometer");
xlabel("Sample");
hold off;