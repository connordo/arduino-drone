sampledata250deps2g = csvread('250dps2g.csv');
samples = sampledata250deps2g(:,1);
accel_x = sampledata250deps2g(:,2);
accel_y = sampledata250deps2g(:,3);
accel_z = sampledata250deps2g(:,4);

figure(1)
subplot(4,1,1);
plot(samples, accel_x, '-',samples, accel_y, '-', samples, accel_z, '-');
axis tight;
title("2 g");

sampledata500dps4g = csvread('500dps4g.csv');
samples = sampledata500dps4g(:,1);
accel_x = sampledata500dps4g(:,2);
accel_y = sampledata500dps4g(:,3);
accel_z = sampledata500dps4g(:,4);

subplot(4,1,2);
plot(samples, accel_x, '-',samples, accel_y, '-', samples, accel_z, '-');
axis tight;
title("4 g");

sampledata1000dps8g = csvread('1000dps8g.csv');
samples = sampledata1000dps8g(:,1);
accel_x = sampledata1000dps8g(:,2);
accel_y = sampledata1000dps8g(:,3);
accel_z = sampledata1000dps8g(:,4);

subplot(4,1,3);
plot(samples, accel_x, '-',samples, accel_y, '-', samples, accel_z, '-');
axis tight;
title("8 g");

sampledata2000dps16g = csvread('2000dps16g.csv');
samples = sampledata2000dps16g(:,1);
accel_x = sampledata2000dps16g(:,2);
accel_y = sampledata2000dps16g(:,3);
accel_z = sampledata2000dps16g(:,4);

subplot(4,1,4);
plot(samples, accel_x, '-',samples, accel_y, '-', samples, accel_z, '-');
axis tight;
title("16 g");

%% Bias testing
figure(2)
accel_x = accel_x - mean(accel_x(1:100));
accel_y = accel_y - mean(accel_y(1:100));
accel_z = accel_z - mean(accel_z(330:460));

accel_x = accel_x * 16 * 9.8 * .000029; %I think I just found my scaling factor
accel_y = accel_y * 16 * 9.8 * .000029;
accel_z = accel_z * 16 * 9.8 * .000029;

plot(samples, accel_x, '-', samples, accel_y, '-', samples, accel_z, '-');
axis tight;
