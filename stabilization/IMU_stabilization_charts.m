figure(1)
subplot(1,2,1);
plot(IMUdatapoints(:,2),'.');
title("X-axis Variation");
xlabel('Iteraion');
ylabel('Accelerometer Reading');
subplot(1,2,2)
hist(IMUdatapoints(:,2));
title("X-axis Histogram");
xlabel('Accelerometer Reading');
ylabel('Frequency');


figure(2)
subplot(1,2,1);
plot(IMUdatapoints(:,3), '.');
title("Y-axis Variation");
xlabel('Iteraion');
ylabel('Accelerometer Reading');
subplot(1,2,2)
hist(IMUdatapoints(:,3));
title("Y-axis Histogram");
xlabel('Accelerometer Reading');
ylabel('Frequency');

figure(3)
title("Z-Axis");
subplot(1,2,1)
plot(IMUdatapoints(:,4), '.');
title("Z-axis Variation");
xlabel('Iteraion');
ylabel('Accelerometer Reading');
subplot(1,2,2)
hist(IMUdatapoints(:,4));
title("Z-axis Histogram");
xlabel('Accelerometer Reading');
ylabel('Frequency');